
// MedicalImageStoreDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicalImageStore.h"
#include "MedicalImageStoreDlg.h"
#include "MainShow.h"
#include "afxdialogex.h"
#include "LoginJudge.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMedicalImageStoreDlg 对话框



CMedicalImageStoreDlg::CMedicalImageStoreDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MEDICALIMAGESTORE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMedicalImageStoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_USER, user_name);
	DDX_Control(pDX, IDC_EDIT_PASS, pass_word);
	DDX_Control(pDX, IDC_EDIT1, user_group);
}

BEGIN_MESSAGE_MAP(CMedicalImageStoreDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMedicalImageStoreDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMedicalImageStoreDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMedicalImageStoreDlg 消息处理程序

BOOL CMedicalImageStoreDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMedicalImageStoreDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMedicalImageStoreDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMedicalImageStoreDlg::OnBnClickedOk()
{
	CString userName;
	user_name.GetWindowTextW(userName);
	CString passWord;
	pass_word.GetWindowTextW(passWord);
	CString userGroup;
	user_group.GetWindowTextW(userGroup);

	DWORD status = LoginJudge::judge(userGroup,userName, passWord);

	if (status == HTTP_STATUS_OK)
	{
		this->ShowWindow(SW_HIDE);
		CMainShow mainShow;
		mainShow.DoModal();
		this->ShowWindow(SW_SHOW);
		//::SendMessage(this->GetSafeHwnd(), WM_CLOSE, NULL, NULL);
	}
	else
	{
		MessageBox(L"账号或密码错误");
	}
}


void CMedicalImageStoreDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
