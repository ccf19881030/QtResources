// zoomscrolltrack2.h : main header file for the ZOOMSCROLLTRACK2 application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CZoomscrolltrack2App:
// See zoomscrolltrack2.cpp for the implementation of this class
//

class CZoomscrolltrack2App : public CWinApp
{
public:
	CZoomscrolltrack2App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CZoomscrolltrack2App theApp;
