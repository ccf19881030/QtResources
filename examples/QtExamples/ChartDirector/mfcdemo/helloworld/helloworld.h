// helloworld.h : main header file for the HELLOWORLD application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CHelloworldApp:
// See helloworld.cpp for the implementation of this class
//

class CHelloworldApp : public CWinApp
{
public:
	CHelloworldApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CHelloworldApp theApp;
