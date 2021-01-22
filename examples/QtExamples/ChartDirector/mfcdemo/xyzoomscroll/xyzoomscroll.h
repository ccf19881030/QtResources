// xyzoomscroll.h : main header file for the XYZOOMSCROLL application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CXyzoomscrollApp:
// See xyzoomscroll.cpp for the implementation of this class
//

class CXyzoomscrollApp : public CWinApp
{
public:
	CXyzoomscrollApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CXyzoomscrollApp theApp;
