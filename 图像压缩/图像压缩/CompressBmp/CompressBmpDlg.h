// CompressBmpDlg.h : header file
//

#pragma once
#include "operate.h"
#include "afxcmn.h"

// CCompressBmpDlg dialog
class CCompressBmpDlg : public CDialog
{
// Construction
public:
	CCompressBmpDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_COMPRESSBMP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
public:
	compress m_com;

// Implementation
protected:
	HICON m_hIcon;


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
public:
	CString m_beginefile;
public:
	afx_msg void OnBnClickedButton2();
public:
	CString m_bfile;
	CString m_efile;
public:
	afx_msg void OnBnClickedButton3();
public:
	afx_msg void OnBnClickedButton4();
public:
	CProgressCtrl m_pro;
};
