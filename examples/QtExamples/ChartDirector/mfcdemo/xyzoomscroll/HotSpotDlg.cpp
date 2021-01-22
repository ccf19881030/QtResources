///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2012 Advanced Software Engineering Limited
//
// You may use and modify the code in this file in your application, provided the code and
// its modifications are used only in conjunction with ChartDirector. Usage of this software
// is subjected to the terms and condition of the ChartDirector license.
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
// CHotSpotDlg Implementation
//
// The purpose of the hot spot dialog is to list out hot spot parameters. It is a simple
// dialog with just a list control and an OK button.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chartdir.h"
#include "xyzoomscroll.h"
#include "ChartViewer.h"
#include "HotSpotDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CHotSpotDlg dialog


CHotSpotDlg::CHotSpotDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHotSpotDlg::IDD, pParent)
{
	hotSpotData = 0;
}

void CHotSpotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHotSpotDlg)
	DDX_Control(pDX, IDC_PARAMLIST, m_ParamList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHotSpotDlg, CDialog)
	//{{AFX_MSG_MAP(CHotSpotDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotSpotDlg message handlers

/////////////////////////////////////////////////////////////////////////////
// CHotSpotDlg implementation

void CHotSpotDlg::SetData(ImageMapHandler *data)
{
	// set the data for the dialog
	hotSpotData = data;
}

BOOL CHotSpotDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//
	// fill the list control with data from the hot spot
	//

	m_ParamList.InsertColumn(0, _T("Param"), LVCFMT_LEFT, 75);
	m_ParamList.InsertColumn(1, _T("Value"), LVCFMT_LEFT, 240);

	if (0!= hotSpotData)
	{
		int i = 0;
		const char *key;
		while (0 != (key = hotSpotData->getKey(i)))
		{
			//remember to use UTF8toTCHAR for possible conversion, as ChartDirector
			//uses UTF8, while MFC uses TCHAR
			m_ParamList.InsertItem(i, UTF8toTCHAR(key));
			m_ParamList.SetItemText(i, 1, UTF8toTCHAR(hotSpotData->getValue(i)));
			++i;
		}
	}

	return TRUE;
}
