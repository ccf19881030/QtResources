// trackaxis.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "trackaxis.h"
#include "trackaxisDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtrackaxisApp

BEGIN_MESSAGE_MAP(CtrackaxisApp, CWinApp)
END_MESSAGE_MAP()


// CtrackaxisApp construction

CtrackaxisApp::CtrackaxisApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CtrackaxisApp object

CtrackaxisApp theApp;


// CtrackaxisApp initialization

BOOL CtrackaxisApp::InitInstance()
{
	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need

	CtrackaxisDlg dlg;
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
