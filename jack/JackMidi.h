/* 
 * File:   JackMidi.h
 * Author: mathias
 *
 * Created on 8 mai 2010, 23:03
 */

#ifndef _JACKMIDI_H
#define	_JACKMIDI_H

//#include <sys/types.h>
//#include <sys/time.h>
//#include <unistd.h>
#include <cassert>
#include <cstring>
//#include <sysexits.h>
#include <jack/jack.h>
#include <jack/midiport.h>
#include <jack/ringbuffer.h>

#define NNOTES 127

#define RINGBUFFER_SIZE		1024*sizeof(struct MidiMessage)

#define MIDI_PROGRAM_CHANGE	0xC0
#define MIDI_CONTROLLER		0xB0
#define MIDI_RESET		0xFF
#define MIDI_HOLD_PEDAL		64
#define MIDI_ALL_SOUND_OFF	120
#define MIDI_ALL_MIDI_CONTROLLERS_OFF	121
#define MIDI_ALL_NOTES_OFF	123
#define MIDI_BANK_SELECT_MSB	0
#define MIDI_BANK_SELECT_LSB	32

#define MIDI_NOTE_ON		0x90
#define MIDI_NOTE_OFF		0x80

struct MidiMessage {
	jack_nframes_t	time;
	int		len;	/* Length of MIDI message, in bytes. */
	unsigned char	data[3];
};

class JackMidi {
public:
	static const char *OUTPUT_PORT_NAME;
	static const char *INPUT_PORT_NAME;

	JackMidi(const char *name);
	JackMidi(const JackMidi& orig);

	struct MidiMessage *midi_message_from_midi_event(jack_midi_event_t event);
	void process_midi_input(jack_nframes_t nframes);
	double nframes_to_ms(jack_nframes_t nframes);
	void process_midi_output(jack_nframes_t nframes);
	//int process_callback(jack_nframes_t nframes, void *notused);
	int queue_message(struct MidiMessage *ev);
	void queue_new_message(int b0, int b1, int b2);
	void send_program_change(int bank, int program);
	int createRingbuffer(void);
	int registerOutputPort(const char *name);
	int registerInputPort(const char *name);
	int initJack (const char * package_name);
	void panic(void);
	void closeJack();

	static int p_callback(jack_nframes_t nframes, void *inst);

	virtual ~JackMidi();
private:
	jack_port_t *output_port;
	jack_port_t *input_port;
	jack_client_t *jack_client;
	jack_ringbuffer_t *ringbuffer;

	int program;
	int bank;
	int channel;
	int rate_limit;
	int time_offsets_are_zero;
};

#endif	/* _JACKMIDI_H */