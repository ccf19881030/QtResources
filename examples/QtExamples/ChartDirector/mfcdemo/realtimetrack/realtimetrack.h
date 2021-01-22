// realtimetrack.h : main header file for the REALTIMETRACK application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRealtimetrackApp:
// See realtimetrack.cpp for the implementation of this class
//

class CRealtimetrackApp : public CWinApp
{
public:
	CRealtimetrackApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRealtimetrackApp theApp;
