// mfcdemo.h : main header file for the MFCDEMO application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CmfcdemoApp:
// See mfcdemo.cpp for the implementation of this class
//

class CmfcdemoApp : public CWinApp
{
public:
	CmfcdemoApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation
	DECLARE_MESSAGE_MAP()
};

extern CmfcdemoApp theApp;
