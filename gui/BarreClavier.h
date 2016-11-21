/* 
 * File:   BarreClavier.h
 * Author: mathias
 *
 * Created on 15 mai 2010, 13:24
 */

#ifndef _BARRECLAVIER_H
#define	_BARRECLAVIER_H

#include "../EnClav.h"
#include "../clavier/Clavier.h"

#include <string>
#include <iostream>

#include <wx/toolbar.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/choice.h>
#include <wx/spinctrl.h>
#include <wx/wxchar.h>

class BarreClavier : public wxToolBar {
public:
	BarreClavier(
		wxWindow *parent,
		std::string clavTitle,
		std::string devName,
		EnClav *app);
	virtual ~BarreClavier();

	void SetMapList(vector<string> *maps);

protected:
	std::string clavTitle;
	std::string devName;
	std::string outPort;
	std::string carte;
	int bank;
	int prog;
	int velocity;
	bool capturing;
	Clavier *c;
	EnClav *app;

	wxButton *start_button;
	wxStaticText *label_clav;
	wxSlider *slider_velo;
	wxChoice *select_carte;
	wxStaticText *label_pg;
	wxSpinCtrl *spin_pg;
	wxStaticText *label_bk;
	wxSpinCtrl *spin_bk;
	wxChoice *select_port;

	// Event handlers
	virtual void OnButtonStartCaptureClick( wxCommandEvent& event );
	virtual void OnChoiceCarteSelected( wxCommandEvent& event );
	virtual void OnChoicePortSelected( wxCommandEvent& event );
	virtual void OnSpinPgUpdated( wxCommandEvent& event );
	virtual void OnSpinBkUpdated( wxCommandEvent& event );

	void GriserWidgets();
	void DegriserWidgets();
	void UpdatePgBk();
};

#endif	/* _BARRECLAVIER_H */

