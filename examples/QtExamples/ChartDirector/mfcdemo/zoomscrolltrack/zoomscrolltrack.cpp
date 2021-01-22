// zoomscrolltrack.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "zoomscrolltrack.h"
#include "zoomscrolltrackDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CZoomscrolltrackApp

BEGIN_MESSAGE_MAP(CZoomscrolltrackApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CZoomscrolltrackApp construction

CZoomscrolltrackApp::CZoomscrolltrackApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CZoomscrolltrackApp object

CZoomscrolltrackApp theApp;


// CZoomscrolltrackApp initialization

BOOL CZoomscrolltrackApp::InitInstance()
{
	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need

	CZoomscrolltrackDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
