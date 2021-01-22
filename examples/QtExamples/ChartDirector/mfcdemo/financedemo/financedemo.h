// financedemo.h : main header file for the FINANCEDEMO application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFinancedemoApp:
// See financedemo.cpp for the implementation of this class
//

class CFinancedemoApp : public CWinApp
{
public:
	CFinancedemoApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFinancedemoApp theApp;
