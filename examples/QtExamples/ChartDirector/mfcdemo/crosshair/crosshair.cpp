// crosshair.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "crosshair.h"
#include "crosshairDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcrosshairApp

BEGIN_MESSAGE_MAP(CcrosshairApp, CWinApp)
END_MESSAGE_MAP()


// CcrosshairApp construction

CcrosshairApp::CcrosshairApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CcrosshairApp object

CcrosshairApp theApp;


// CcrosshairApp initialization

BOOL CcrosshairApp::InitInstance()
{
	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need

	CcrosshairDlg dlg;
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
