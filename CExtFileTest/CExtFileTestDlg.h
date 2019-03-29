// CExtFileTestDlg.h : header file
//

#if !defined(AFX_CEXTFILETESTDLG_H__09F5B36B_FDD0_4C4E_9F82_0E515AE43501__INCLUDED_)
#define AFX_CEXTFILETESTDLG_H__09F5B36B_FDD0_4C4E_9F82_0E515AE43501__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCExtFileTestDlg dialog

class CCExtFileTestDlg : public CDialog
{
// Construction
public:
	CCExtFileTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCExtFileTestDlg)
	enum { IDD = IDD_CEXTFILETEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCExtFileTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCExtFileTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CEXTFILETESTDLG_H__09F5B36B_FDD0_4C4E_9F82_0E515AE43501__INCLUDED_)
