// CompressBmpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CompressBmp.h"
#include "CompressBmpDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCompressBmpDlg dialog




CCompressBmpDlg::CCompressBmpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompressBmpDlg::IDD, pParent)
	, m_beginefile(_T(""))
	, m_bfile(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCompressBmpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_beginefile);
	DDX_Text(pDX, IDC_EDIT2, m_bfile);
	DDX_Control(pDX, IDC_PROGRESS1, m_pro);
}

BEGIN_MESSAGE_MAP(CCompressBmpDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CCompressBmpDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCompressBmpDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCompressBmpDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCompressBmpDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CCompressBmpDlg message handlers

BOOL CCompressBmpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCompressBmpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCompressBmpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCompressBmpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCompressBmpDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(true);
	dlg.DoModal();
    m_beginefile=dlg.GetPathName();
	UpdateData(false);
}

void CCompressBmpDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	if(m_com.comp(m_beginefile,&m_pro))
		MessageBox(_T("—πÀı≥…π¶!"));
	else
		MessageBox(_T("—πÀı ß∞‹!"));
}


void CCompressBmpDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CString s;
	CFileDialog dlg(true);
	dlg.DoModal();
    m_bfile=dlg.GetPathName();
	UpdateData(false);
	s=m_bfile.Right(7);
	s=s.Left(s.GetLength()-3);
	m_efile=m_bfile;
	m_efile=m_efile.Left(m_bfile.GetLength()-7);
	m_efile+="(∏Ωº˛)";
	m_efile+=s;

}

void CCompressBmpDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	if(m_com.uncomp(m_bfile,m_efile,&m_pro))
		MessageBox(_T("Ω‚—π≥…π¶!"));
	else
		MessageBox(_T("Ω‚—π ß∞‹!"));
}
