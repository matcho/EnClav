#ifndef __EnClavAbout__
#define __EnClavAbout__

/**
@file
Subclass of EnClavAboutBase, which is generated by wxFormBuilder.
*/

#include "EnClavGuiBase.h"

/** Implementing EnClavAboutBase */
class EnClavAbout : public EnClavAboutBase
{
protected:
	// Handlers for EnClavAboutBase events.
	void OnClose( wxCloseEvent& event );
	void OnButtonFermerClick( wxCommandEvent& event );
	
public:
	static const char *EMPLACEMENT_ABOUT_HTML;
	/** Constructor */
	EnClavAbout( wxWindow* parent );
};

#endif // __EnClavAbout__
