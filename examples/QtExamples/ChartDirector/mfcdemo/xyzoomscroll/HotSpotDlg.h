// HotSpotDlg.h : header file
//

#pragma once

// Forward declarations
class ImageMapHandler;


// CHotSpotDlg dialog
class CHotSpotDlg : public CDialog
{
public:
// Construction
	CHotSpotDlg(CWnd* pParent = NULL);   // standard constructor

// Public interface
	virtual void SetData(ImageMapHandler *data);

// Dialog Data
	enum { IDD = IDD_HOTSPOTPARAM };
	CListCtrl	m_ParamList;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();


// Implementation
protected:
	// Generated message map functions
	DECLARE_MESSAGE_MAP()


private:
	ImageMapHandler *hotSpotData;
};
