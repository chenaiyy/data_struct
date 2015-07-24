// PhoneBookDlg.h : header file
//

#if !defined(AFX_PHONEBOOKDLG_H__38E920F3_C897_4A44_BE22_D07C297A46AB__INCLUDED_)
#define AFX_PHONEBOOKDLG_H__38E920F3_C897_4A44_BE22_D07C297A46AB__INCLUDED_


#include "avlnode.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPhoneBookDlg dialog

class CPhoneBookDlg : public CDialog
{
// Construction
public:
	CPhoneBookDlg(CWnd* pParent = NULL);	// standard constructor
	void LoadInfo(Phone cur);
// 	void Next(Phone&);

//	void Store(AvlNode *u);
	

// Dialog Data
	//{{AFX_DATA(CPhoneBookDlg)
	enum { IDD = IDD_PHONEBOOK_DIALOG };
	CComboBox	m_cbBox;
	CListBox	m_grouplist;
	CListBox	m_namelist;
	CString	m_email;
	CString	m_group;
	CString	m_hphone;
	CString	m_name;
	CString	m_ophone;
	CString	m_recoard;
	CString	m_telephone;
	CString	m_cbExamble;
	CString	m_search;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhoneBookDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPhoneBookDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAdd();
	afx_msg void OnUpdate();
	afx_msg void OnDelete();
	afx_msg void OnUp();
	afx_msg void OnDown();
	afx_msg void OnAlter();
	afx_msg void OnClose();
	afx_msg void OnOutput();
	afx_msg void OnInput();
	afx_msg void OnNamesearch();
	afx_msg void OnTelephonesearch();
	afx_msg void OnHphonesearch();
	afx_msg void OnOphonesearch();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHONEBOOKDLG_H__38E920F3_C897_4A44_BE22_D07C297A46AB__INCLUDED_)
