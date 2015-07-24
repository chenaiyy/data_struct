// PhoneBookDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PhoneBook.h"
#include "PhoneBookDlg.h"
#include "avltree.h"
#include "phonecard.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
AvlTree CardTree;
Phone Card;
vector<Phone> vec;
int m_count=0;
bool AlterOrNot=FALSE;
bool Grey=FALSE;


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhoneBookDlg dialog

CPhoneBookDlg::CPhoneBookDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPhoneBookDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPhoneBookDlg)
	m_email = _T("");
	m_group = _T("");
	m_hphone = _T("");
	m_name = _T("");
	m_ophone = _T("");
	m_recoard = _T("");
	m_telephone = _T("");
	m_cbExamble = _T("");
	m_search = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhoneBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPhoneBookDlg)
	DDX_Control(pDX, IDGROUP, m_cbBox);
	DDX_Control(pDX, IDC_LIST2, m_grouplist);
	DDX_Control(pDX, IDC_LIST1, m_namelist);
	DDX_Text(pDX, ID_EMAIL, m_email);
	DDV_MaxChars(pDX, m_email, 25);
	DDX_Text(pDX, ID_GROUP, m_group);
	DDV_MaxChars(pDX, m_group, 10);
	DDX_Text(pDX, ID_HPHONE, m_hphone);
	DDV_MaxChars(pDX, m_hphone, 12);
	DDX_Text(pDX, ID_NAME, m_name);
	DDV_MaxChars(pDX, m_name, 10);
	DDX_Text(pDX, ID_OPHONE, m_ophone);
	DDV_MaxChars(pDX, m_ophone, 12);
	DDX_Text(pDX, ID_RECOARD, m_recoard);
	DDV_MaxChars(pDX, m_recoard, 100);
	DDX_Text(pDX, ID_TELEPHONE, m_telephone);
	DDV_MaxChars(pDX, m_telephone, 11);
	DDX_CBString(pDX, IDGROUP, m_cbExamble);
	DDV_MaxChars(pDX, m_cbExamble, 10);
	DDX_Text(pDX, IDC_SEARCH1, m_search);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPhoneBookDlg, CDialog)
	//{{AFX_MSG_MAP(CPhoneBookDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_BN_CLICKED(IDC_ALTER, OnAlter)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_OUTPUT, OnOutput)
	ON_BN_CLICKED(IDC_INPUT, OnInput)
	ON_BN_CLICKED(IDC_NAMESEARCH, OnNamesearch)
	ON_BN_CLICKED(IDC_TELEPHONESEARCH, OnTelephonesearch)
	ON_BN_CLICKED(IDC_HPHONESEARCH, OnHphonesearch)
	ON_BN_CLICKED(IDC_OPHONESEARCH, OnOphonesearch)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhoneBookDlg message handlers

BOOL CPhoneBookDlg::OnInitDialog()
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
	GetDlgItem(ID_NAME)->EnableWindow(FALSE);
	GetDlgItem(ID_HPHONE)->EnableWindow(FALSE);
	GetDlgItem(ID_TELEPHONE)->EnableWindow(FALSE);
	GetDlgItem(ID_OPHONE)->EnableWindow(FALSE);
	GetDlgItem(ID_EMAIL)->EnableWindow(FALSE);
	GetDlgItem(ID_GROUP)->EnableWindow(FALSE);
	GetDlgItem(ID_RECOARD)->EnableWindow(FALSE);
	GetDlgItem(IDC_UPDATE)->EnableWindow(FALSE);  //初始时令文本框内的数据不能修改

	int temp=0;
	int i;
	Phone cur;
	vector<Phone> vec1;
	
	ifstream infile("data.txt",ios::binary);
	infile.read((char*)&temp,sizeof(int));
	m_count=temp;
	if(temp)
	{
		for(i=0;i<temp;i++)
		{
			infile.read((char*)&cur,sizeof(cur));
			vec1.push_back(cur);
			m_namelist.AddString(cur.name);

			if(m_cbBox.FindStringExact( 0, cur.group)==CB_ERR)
				m_cbBox.AddString(cur.group);
		}
		infile.close();
		for(i=0;i<vec1.size();i++)
			CardTree.Insert(vec1[i]);
		LoadInfo(cur);
	}
	else
	{
		MessageBox("没有记录可调!","提示",MB_ICONERROR);
		return -1;
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPhoneBookDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPhoneBookDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPhoneBookDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPhoneBookDlg::LoadInfo(Phone cur)
{
	m_name=cur.name;
	m_group=cur.group;
	m_email=cur.email;
	m_ophone=cur.off_phone;
	m_telephone=cur.tel_phone;
	m_hphone=cur.home_phone;
	m_recoard=cur.speech;
	UpdateData(false);
}


void CPhoneBookDlg::OnAdd()		//添加操作
{
	// TODO: Add your control notification handler code here
	GetDlgItem(ID_NAME)->EnableWindow(TRUE);
	GetDlgItem(ID_HPHONE)->EnableWindow(TRUE);
	GetDlgItem(ID_TELEPHONE)->EnableWindow(TRUE);
	GetDlgItem(ID_OPHONE)->EnableWindow(TRUE);
	GetDlgItem(ID_EMAIL)->EnableWindow(TRUE);
	GetDlgItem(ID_GROUP)->EnableWindow(TRUE);
	GetDlgItem(ID_RECOARD)->EnableWindow(TRUE);
	GetDlgItem(IDC_UPDATE)->EnableWindow(TRUE);  //按键及文本框能够修改
	GetDlgItem(IDC_UP)->EnableWindow(FALSE);
	GetDlgItem(IDC_DOWN)->EnableWindow(FALSE);
	GetDlgItem(IDC_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_ALTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_DELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_NAMESEARCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_TELEPHONESEARCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_OPHONESEARCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_HPHONESEARCH)->EnableWindow(FALSE);
//	GetDlgItem(IDC_GROUPSEARCH)->EnableWindow(FALSE);//查询等按钮禁用
	AlterOrNot=TRUE;

	m_name="未命名";
	m_email="";
	m_group="其它";
	m_hphone="";
	m_ophone="";
	m_recoard="";
	m_telephone="";			//文本框里初始化
    UpdateData(0);
	m_count++;				//总结点数加1
}

void CPhoneBookDlg::OnUpdate()		//更新操作
{
	UpdateData();
	if(m_name=="")				//如果姓名输入框为空则发生错误
	{
		MessageBox("名字选项为空值!","worning",MB_ICONERROR);
		m_count--;
		return;
	}
	strcpy(Card.name,m_name);
	strcpy(Card.email,m_email);
	strcpy(Card.group,m_group);
	strcpy(Card.home_phone,m_hphone);
	strcpy(Card.off_phone,m_ophone);
	strcpy(Card.speech,m_recoard);
	strcpy(Card.tel_phone,m_telephone);

	if(m_cbBox.FindStringExact( 0, m_group)==CB_ERR)
		m_cbBox.AddString(m_group);

	CardTree.Insert(Card);			//将名片添加到树中
	m_namelist.ResetContent();		//清空列表中的所有项	
	if(!vec.empty())				//如果存储容器不为空，则清空容器
		vec.clear();
	CardTree.Inorder(Store);		//将更新后的电话簿存到容器里面去
	for(int i=0;i<vec.size();i++)
		m_namelist.InsertString(i,vec[i].name);

	GetDlgItem(ID_NAME)->EnableWindow(FALSE);
	GetDlgItem(ID_HPHONE)->EnableWindow(FALSE);
	GetDlgItem(ID_TELEPHONE)->EnableWindow(FALSE);
	GetDlgItem(ID_OPHONE)->EnableWindow(FALSE);
	GetDlgItem(ID_EMAIL)->EnableWindow(FALSE);
	GetDlgItem(ID_GROUP)->EnableWindow(FALSE);
	GetDlgItem(ID_RECOARD)->EnableWindow(FALSE);
	GetDlgItem(IDC_UPDATE)->EnableWindow(FALSE);//文本框里信息禁止更改

	GetDlgItem(IDC_UP)->EnableWindow(TRUE);
	GetDlgItem(IDC_DOWN)->EnableWindow(TRUE);
	GetDlgItem(IDC_ADD)->EnableWindow(TRUE);
	GetDlgItem(IDC_ALTER)->EnableWindow(TRUE);
	GetDlgItem(IDC_DELETE)->EnableWindow(TRUE);
	GetDlgItem(IDC_NAMESEARCH)->EnableWindow(TRUE);
	GetDlgItem(IDC_TELEPHONESEARCH)->EnableWindow(TRUE);
	GetDlgItem(IDC_OPHONESEARCH)->EnableWindow(TRUE);
	GetDlgItem(IDC_HPHONESEARCH)->EnableWindow(TRUE);
//	GetDlgItem(IDC_GROUPSEARCH)->EnableWindow(TRUE);//查询等按钮重启
}

void CPhoneBookDlg::OnDelete()		//删除操作
{
	// TODO: Add your control notification handler code here
	if (MessageBox("是否真的删除？","敬告",MB_ICONQUESTION|MB_OKCANCEL) == IDCANCEL)
		return;	//弹出确认对话框
	AlterOrNot=TRUE;
	AvlNode* p=new AvlNode;
	char ch[20];
	strcpy(ch,m_name);
	CardTree.Search(p,ch);
	

	CardTree.Delete(p);
	m_count--;

	int i;
	if(!vec.empty())				//如果存储容器不为空，则清空容器
		vec.clear();
	CardTree.Inorder(Store);		//将更新后的电话簿存到容器里面去
	
	Phone cur;
	for( i=0;i<vec.size()&&vec[i].name!=ch;i++);
	if(i=vec.size()-1)
		cur=vec[0];
	else
		cur=vec[++i];
	m_namelist.ResetContent();		//清空列表中的所有项
	if(m_count)
	{
		LoadInfo(cur);
		if(!vec.empty())				//如果存储容器不为空，则清空容器
			vec.clear();
		CardTree.Inorder(Store);		//将更新后的电话簿存到容器里面去
		for( i=0;i<vec.size();i++)
 		m_namelist.InsertString(i,vec[i].name);
	}
	else
	{
		m_name="";
		m_hphone="";
		m_ophone="";
		m_recoard="";
		m_telephone="";
		m_email="";
		m_group="";

		GetDlgItem(IDC_UP)->EnableWindow(FALSE);
		GetDlgItem(IDC_DOWN)->EnableWindow(FALSE);
		GetDlgItem(IDC_ALTER)->EnableWindow(FALSE);
		GetDlgItem(IDC_DELETE)->EnableWindow(FALSE);
		GetDlgItem(IDC_NAMESEARCH)->EnableWindow(FALSE);
		GetDlgItem(IDC_TELEPHONESEARCH)->EnableWindow(FALSE);
		GetDlgItem(IDC_OPHONESEARCH)->EnableWindow(FALSE);
		GetDlgItem(IDC_HPHONESEARCH)->EnableWindow(FALSE);
//		GetDlgItem(IDC_GROUPSEARCH)->EnableWindow(FALSE);//查询等按钮禁用

	}
	UpdateData(false);
}

void Store(AvlNode *u)
{
	if(u)
		vec.push_back(u->data);
}

void CPhoneBookDlg::OnUp()		//下一条操作
{
	// TODO: Add your control notification handler code here
	Phone cur;
	if(m_count==1)
	{
		MessageBox("没有上一条","提示");
		return;
	}
	vec.clear();
	CardTree.Inorder(Store);
	for(int i=0;i<vec.size()&&vec[i].name!=m_name;i++);
	if(i==0)
		cur=vec[vec.size()-1];
	else
		cur=vec[--i];

	LoadInfo(cur);

	UpdateData(false);
}

void CPhoneBookDlg::OnDown()		//下一条操作
{
	// TODO: Add your control notification handler code here
	Phone cur;
	if(m_count==1)
	{
		MessageBox("没有下一条","提示");
		return;
	}
	vec.clear();
	CardTree.Inorder(Store);
	for(int i=0;i<vec.size()&&vec[i].name!=m_name;i++);
	if(i==vec.size()-1)
		cur=vec[0];
	else
		cur=vec[++i];
	
	LoadInfo(cur);
	
	UpdateData(false);
}



void CPhoneBookDlg::OnAlter()		//修改操作
{
	// TODO: Add your control notification handler code here
	if (MessageBox("是否真的修改？","敬告",MB_ICONQUESTION|MB_OKCANCEL) == IDCANCEL)
		return;											//弹出确认对话框
	AlterOrNot=TRUE;
	AvlNode* p=new AvlNode;
	char ch[20];
	strcpy(ch,m_name);
	CardTree.Search(p,ch);
	CardTree.Delete(p);

	GetDlgItem(ID_NAME)->EnableWindow(TRUE);
	GetDlgItem(ID_HPHONE)->EnableWindow(TRUE);
	GetDlgItem(ID_TELEPHONE)->EnableWindow(TRUE);
	GetDlgItem(ID_OPHONE)->EnableWindow(TRUE);
	GetDlgItem(ID_EMAIL)->EnableWindow(TRUE);
	GetDlgItem(ID_GROUP)->EnableWindow(TRUE);
	GetDlgItem(ID_RECOARD)->EnableWindow(TRUE);
	GetDlgItem(IDC_UPDATE)->EnableWindow(TRUE);		//按键及文本框能够修改

	GetDlgItem(IDC_UP)->EnableWindow(FALSE);
	GetDlgItem(IDC_DOWN)->EnableWindow(FALSE);
	GetDlgItem(IDC_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_ALTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_DELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_NAMESEARCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_TELEPHONESEARCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_OPHONESEARCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_HPHONESEARCH)->EnableWindow(FALSE);
//	GetDlgItem(IDC_GROUPSEARCH)->EnableWindow(FALSE);//查询等按钮禁用
}


void CPhoneBookDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CWnd* pWnd=GetDlgItem(IDC_UPDATE);
	if(pWnd->IsWindowEnabled())
	{
		MessageBox("错误操作!","错误",MB_ICONERROR);
		return;
	}
	if(AlterOrNot)
	{	
		vec.clear();
		CardTree.Inorder(Store);
		ofstream outfile("data.txt",ios::binary);
		outfile.write((char*)&m_count,sizeof(int));
		for(int i=0;i<m_count;i++)
			outfile.write((char*)&vec[i],sizeof(vec[i]));
		outfile.close();
	}
	CDialog::OnClose();	
}

void CPhoneBookDlg::OnOutput() 
{
	// TODO: Add your control notification handler code here
	CWnd* pWnd=GetDlgItem(IDC_UPDATE);
	if(pWnd->IsWindowEnabled())
	{
		MessageBox("错误操作!","错误",MB_ICONERROR);
		return;
	}
	if(AlterOrNot)
	{
		ofstream outfile("OutPut.txt");
		outfile<<"名片总人数："<<m_count<<'\n';
		vec.clear();
		CardTree.Inorder(Store);
		for(int i=0;i<m_count;i++)
			outfile<<"姓名："<<vec[i].name<<'\0'<<"手机号码："<<vec[i].tel_phone
			<<'\0'<<"办公号码："<<vec[i].off_phone<<'\0'<<"住宅号码："<<vec[i].home_phone<<'\0'
			<<"邮箱地址："<<vec[i].email<<'\0'<<"所属群组："<<vec[i].group<<'\0'<<"备忘："<<
			vec[i].speech<<'\n';
		outfile.close();
	}
}

void CPhoneBookDlg::OnInput() 
{
	// TODO: Add your control notification handler code here
	
}

void CPhoneBookDlg::OnNamesearch() 
{
	// TODO: Add your control notification handler code here
	Phone cur;
	char ch[10];
	UpdateData();
	strcpy(ch,m_search);
	if(m_search=="")
	{
		MessageBox("请输入要查询的姓名!","提示",MB_ICONERROR);
		return;
	}
	if(CardTree.Search4(cur,ch))
		LoadInfo(cur);
	else
		MessageBox("没有记录!");
}

void CPhoneBookDlg::OnTelephonesearch() 
{
	// TODO: Add your control notification handler code here
	Phone cur;
	AvlTree tree;
	char ch[11];

	vec.clear();
	CardTree.Inorder(Store);

	for(int i=0;i<vec.size();i++)
 		 if(vec[i].tel_phone)
			 tree.Insert1(vec[i]);

	UpdateData();
	strcpy(ch,m_search);
	if(m_search=="")
	{
		MessageBox("请输入要查询的手机号!","提示",MB_ICONERROR);
		return;
	}
	if(tree.Search1(cur,ch))
		LoadInfo(cur);
	else
		MessageBox("没有记录!");

}

void CPhoneBookDlg::OnHphonesearch() 
{
	// TODO: Add your control notification handler code here
	Phone cur;
	AvlTree tree;
	char ch[12];
	
	vec.clear();
	CardTree.Inorder(Store);
	
	for(int i=0;i<vec.size();i++)
// 		while(vec[i].home_phone)
			tree.Insert3(vec[i]);
	
	UpdateData();
	strcpy(ch,m_search);
	if(m_search=="")
	{
		MessageBox("请输入要查询的住宅号!","提示",MB_ICONERROR);
		return;
	}
	if(tree.Search2(cur,ch))
		LoadInfo(cur);
	else
		MessageBox("没有记录!");
	
}

void CPhoneBookDlg::OnOphonesearch() 
{
	// TODO: Add your control notification handler code here
	Phone cur;
	AvlTree tree;
	char ch[12];
	
	vec.clear();
	CardTree.Inorder(Store);
	
	for(int i=0;i<vec.size();i++)
// 		while(vec[i].off_phone)
			tree.Insert2(vec[i]);
	
	UpdateData();
	strcpy(ch,m_search);
	if(m_search=="")
	{
		MessageBox("请输入要查询的办公号!","提示",MB_ICONERROR);
		return;
	}
	if(tree.Search3(cur,ch))
		LoadInfo(cur);
	else
		MessageBox("没有记录!");
	
}


void CPhoneBookDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here

	vec.clear();
	CardTree.Inorder(Store);
	m_grouplist.ResetContent();
	
	int nIndex = m_cbBox.GetCurSel();
	CString strCBText;
	char ch[10];
	
	m_cbBox.GetLBText(nIndex, strCBText);
	strcpy(ch,strCBText);
	
	for (int i=0;i<vec.size();i++)
		if(!strcmp(ch,vec[i].group))
			m_grouplist.AddString(vec[i].name);	
	
}
