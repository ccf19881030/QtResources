// simplezoomscroll.h : main header file for the SIMPLEZOOMSCROLL application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSimplezoomscrollApp:
// See simplezoomscroll.cpp for the implementation of this class
//

class CSimplezoomscrollApp : public CWinApp
{
public:
	CSimplezoomscrollApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSimplezoomscrollApp theApp;
