/* 
 * File:   Gui.h
 * Author: mathias
 *
 * Created on 14 mai 2010, 12:49
 */

#ifndef _GUI_H
#define	_GUI_H

#include <map>
#include <string>

#include "../EnClav.h"
#include "EnClavAbout.h"
#include "EnClavGui.h"
#include "BarreClavier.h"

using namespace std;

class Gui : public EnClavGui {

public:
	Gui(EnClav *app);
	virtual ~Gui();

protected:
	// Handlers for EnClavGuiBase events.
	void OnButtonRefreshJackClick( wxCommandEvent& event );
	void OnCbIncludePS2Check( wxCommandEvent& event );
	void OnButtonDetectClClick( wxCommandEvent& event );
	void OnMenuQuitter( wxCommandEvent& event );
	void OnMenuPreferences( wxCommandEvent& event );
	void OnMenuApropos( wxCommandEvent& event );

private:
	EnClav *app;
	map<string,BarreClavier*> *mapBarClav;
	BarreClavier *CreerBarreClavier();
	bool incPS2;
	int globalVelocity;
	vector<string> *avMaps;
};

#endif	/* _GUI_H */