/* 
 * File:   JackMidi.cpp
 * Author: mathias
 * 
 * Created on 8 mai 2010, 23:03
 */

#include "JackMidi.h"

#include <iostream>
#include <stdio.h>
#include <unistd.h>

/*#define VELOCITY_MAX		127
#define VELOCITY_HIGH		100
#define VELOCITY_NORMAL		64
#define VELOCITY_LOW		32
#define VELOCITY_MIN		1*/

using namespace std;

const char *JackMidi::OUTPUT_PORT_NAME = "midi_out";
const char *JackMidi::INPUT_PORT_NAME = "midi_in";

JackMidi::JackMidi(const char *name) {

	this->bank = 0;
	this->channel = 0;
	this->program = 0;

	this->initJack(name);
	
	if (registerOutputPort(OUTPUT_PORT_NAME) != 0) {
		cerr <<"Could not register JACK output port" << endl;
	}

	/*if (registerInputPort(INPUT_PORT_NAME) != 0) {
		cerr << "Could not register JACK input port" << endl;
	}*/

	int err = jack_activate(this->jack_client);
	if (err) {
		cerr << "Cannot activate JACK client" << endl;
	}

	//send_program_change(1,1);

	/*int note = 70;
	int current_velocity = 90;

	for (int j=0; j<10; j++) {
		queue_new_message(MIDI_NOTE_ON, note, current_velocity);
		sleep(1);
		cout << "off" << endl;
		queue_new_message(MIDI_NOTE_OFF, note, current_velocity);
		note++;
	}
	sleep(1);*/
}

JackMidi::JackMidi(const JackMidi& orig) {
}

struct MidiMessage *JackMidi::midi_message_from_midi_event(jack_midi_event_t event) {

	struct MidiMessage *ev = (struct MidiMessage*) malloc(sizeof(struct MidiMessage));
	//struct MidiMessage ev;

	if (&ev == 0) {
		perror("malloc");
		return 0;
	}

	assert(event.size >= 1 && event.size <= 3);

	ev->len = event.size;
	ev->time = event.time;

	memcpy(ev->data, event.buffer, ev->len);

	return ev;
}

void JackMidi::process_midi_input(jack_nframes_t nframes) {
	int		read, events, i;
	void           *port_buffer;
	jack_midi_event_t event;

	port_buffer = jack_port_get_buffer(this->input_port, nframes);
	if (port_buffer == 0) {
		cerr << "jack_port_get_buffer failed, cannot receive anything." << endl;
		return;
	}

	events = jack_midi_get_event_count(port_buffer);

	for (i = 0; i < events; i++) {
		struct MidiMessage *rev;

		read = jack_midi_event_get(&event, port_buffer, i);

		if (read) {
			/*(warn_from_jack_thread_context("jack_midi_event_get failed, RECEIVED NOTE LOST.");)*/
			continue;
		}

		if (event.size > 3) {
			/*(warn_from_jack_thread_context("Ignoring MIDI message longer than three bytes, probably a SysEx.");)*/
			continue;
		}

		rev = midi_message_from_midi_event(event);
		if (rev == NULL) {
			/*(warn_from_jack_thread_context("midi_message_from_midi_event failed, RECEIVED NOTE LOST.");)*/
			continue;
		}

		/*(g_idle_add(process_received_message_async, rev);)*/
	}
}

double JackMidi::nframes_to_ms(jack_nframes_t nframes) {

	jack_nframes_t sr;

	sr = jack_get_sample_rate(this->jack_client);
	assert(sr > 0);

	return (nframes * 1000.0) / (double)sr;
}

void JackMidi::process_midi_output(jack_nframes_t nframes) {

	int		read, t, bytes_remaining;
	unsigned char  *buffer;
	void           *port_buffer;
	jack_nframes_t	last_frame_time;
	struct MidiMessage ev;

	last_frame_time = jack_last_frame_time(this->jack_client);

	port_buffer = jack_port_get_buffer(this->output_port, nframes);
	if (port_buffer == NULL) {
		/*(warn_from_jack_thread_context("jack_port_get_buffer failed, cannot send anything.");)*/
		return;
	}

	jack_midi_clear_buffer(port_buffer);

	/* We may push at most one byte per 0.32ms to stay below 31.25 Kbaud limit. */
	bytes_remaining = nframes_to_ms(nframes) * rate_limit;

	while (jack_ringbuffer_read_space(this->ringbuffer)) {
		read = jack_ringbuffer_peek(this->ringbuffer, (char *)&ev, sizeof(ev));

		if (read != sizeof(ev)) {
			/*(warn_from_jack_thread_context("Short read from the ringbuffer, possible note loss.");)*/
			jack_ringbuffer_read_advance(this->ringbuffer, read);
			continue;
		}

		bytes_remaining -= ev.len;

		if (rate_limit > 0.0 && bytes_remaining <= 0) {
			/*(warn_from_jack_thread_context("Rate limiting in effect.");)*/
			break;
		}

		t = ev.time + nframes - last_frame_time;

		/* If computed time is too much into the future, we'll need
		   to send it later. */
		if (t >= (int)nframes)
			break;

		/* If computed time is < 0, we missed a cycle because of xrun. */
		if (t < 0)
			t = 0;

		if (this->time_offsets_are_zero)
			t = 0;

		jack_ringbuffer_read_advance(this->ringbuffer, sizeof(ev));

		buffer = jack_midi_event_reserve(port_buffer, t, ev.len);

		if (buffer == 0) {
			cerr << "jack_midi_event_reserve failed, NOTE LOST" << endl;
			break;
		}

		memcpy(buffer, ev.data, ev.len);
	}
}

/*int JackMidi::process_callback(jack_nframes_t nframes, void *notused) {

	// Check for impossible condition that actually happened to me, caused by some problem between jackd and OSS4.
	if (nframes <= 0) {
		cerr << "Process callback called with nframes = 0; bug in JACK?" << endl;
		return 0;
	}

	process_midi_input(nframes);
	process_midi_output(nframes);

	return 0;
}*/

/**
 * Wrapper statique pour le callback de libjack
 */
int JackMidi::p_callback(jack_nframes_t nframes, void *inst) {

	/* Check for impossible condition that actually happened to me, caused by some problem between jackd and OSS4. */
	if (nframes <= 0) {
		cerr << "Process callback called with nframes = 0; bug in JACK?" << endl;
		return 0;
	}

	JackMidi *jm = (JackMidi*) inst;

	//jm->process_midi_input(nframes);
	jm->process_midi_output(nframes);

	return 0;
}

int JackMidi::queue_message(struct MidiMessage *ev) {
	int		written;

	if (jack_ringbuffer_write_space(this->ringbuffer) < sizeof(*ev)) {
		cerr << "Not enough space in the ringbuffer, NOTE LOST" << endl;
		return -1;
	}

	written = jack_ringbuffer_write(this->ringbuffer, (char *)ev, sizeof(*ev));

	if (written != sizeof(*ev))
		cerr << "jack_ringbuffer_write failed, NOTE LOST" << endl;

	return written;
}

void JackMidi::queue_new_message(int b0, int b1, int b2) {
	struct MidiMessage ev;

	/* For MIDI messages that specify a channel number, filter the original
	   channel number out and add our own. */
	if (b0 >= 0x80 && b0 <= 0xEF) {
		b0 &= 0xF0;
		b0 += channel;
	}

	if (b1 == -1) {
		ev.len = 1;
		ev.data[0] = b0;

	} else if (b2 == -1) {
		ev.len = 2;
		ev.data[0] = b0;
		ev.data[1] = b1;

	} else {
		ev.len = 3;
		ev.data[0] = b0;
		ev.data[1] = b1;
		ev.data[2] = b2;
	}

	ev.time = jack_frame_time(this->jack_client);

	queue_message(&ev);
}

void JackMidi::send_program_change(int bank, int program) {

	if (jack_port_connected(this->output_port) == 0)
		return;

	queue_new_message(MIDI_CONTROLLER, MIDI_BANK_SELECT_LSB, bank % 128);
	queue_new_message(MIDI_CONTROLLER, MIDI_BANK_SELECT_MSB, bank / 128);
	queue_new_message(MIDI_PROGRAM_CHANGE, program, -1);
}

int JackMidi::createRingbuffer(void) {

	this->ringbuffer = jack_ringbuffer_create(RINGBUFFER_SIZE);

	if (this->ringbuffer == 0) {
		cerr << "Cannot create JACK ringbuffer" << endl;
	}

	jack_ringbuffer_mlock(this->ringbuffer);

	return 0;
}

int JackMidi::registerOutputPort(const char *name) {

	this->output_port = jack_port_register(this->jack_client, name, JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);

	return 0;
}

int JackMidi::registerInputPort(const char *name) {

	this->input_port = jack_port_register(this->jack_client, name, JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);

	return 0;
}

int JackMidi::initJack(const char * package_name) {

	this->jack_client = jack_client_open(package_name, JackNullOption, NULL);

	if (this->jack_client == 0) {
		cerr << "Could not connect to the JACK server; run jackd first?" << endl;
	}

	this->createRingbuffer();

	int err = jack_set_process_callback(this->jack_client, p_callback, this);
	if (err) {
		cerr << "Could not register JACK process callback" << endl;
	}

	return 0;
}

void JackMidi::closeJack() {

	cout << "closing Jack client" << endl;
	jack_deactivate(this->jack_client);
	jack_port_unregister(this->jack_client, this->output_port);
	jack_client_close(this->jack_client);
}

void JackMidi::panic(void) {
	int		i;

	/*
	 * These two have to be sent first, in case we have no room in the
	 * ringbuffer for all these MIDI_NOTE_OFF messages sent five lines below.
	 */
	queue_new_message(MIDI_CONTROLLER, MIDI_ALL_NOTES_OFF, 0);
	queue_new_message(MIDI_CONTROLLER, MIDI_ALL_SOUND_OFF, 0);

	for (i = 0; i < NNOTES; i++) {
		queue_new_message(MIDI_NOTE_OFF, i, 0);
		/*(piano_keyboard_set_note_off(keyboard, i);)*/
		usleep(100);
	}

	queue_new_message(MIDI_CONTROLLER, MIDI_HOLD_PEDAL, 0);
	queue_new_message(MIDI_CONTROLLER, MIDI_ALL_MIDI_CONTROLLERS_OFF, 0);
	queue_new_message(MIDI_CONTROLLER, MIDI_ALL_NOTES_OFF, 0);
	queue_new_message(MIDI_CONTROLLER, MIDI_ALL_SOUND_OFF, 0);
	queue_new_message(MIDI_RESET, -1, -1);
}

JackMidi::~JackMidi() {

	cout << "destruction de JackMidi" << endl;
	this->closeJack();
}