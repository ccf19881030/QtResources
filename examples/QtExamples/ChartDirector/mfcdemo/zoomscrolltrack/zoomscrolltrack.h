// zoomscrolltrack.h : main header file for the ZOOMSCROLLTRACK application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CZoomscrolltrackApp:
// See zoomscrolltrack.cpp for the implementation of this class
//

class CZoomscrolltrackApp : public CWinApp
{
public:
	CZoomscrolltrackApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CZoomscrolltrackApp theApp;
