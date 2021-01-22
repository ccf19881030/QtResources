// realtimetrack.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "realtimetrack.h"
#include "realtimetrackDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRealtimetrackApp

BEGIN_MESSAGE_MAP(CRealtimetrackApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRealtimetrackApp construction

CRealtimetrackApp::CRealtimetrackApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CRealtimetrackApp object

CRealtimetrackApp theApp;


// CRealtimetrackApp initialization

BOOL CRealtimetrackApp::InitInstance()
{
	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need

	CRealtimetrackDlg dlg;
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
