
// MedicalImageStoreDlg.cpp : ʵ���ļ�
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


// CMedicalImageStoreDlg �Ի���



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


// CMedicalImageStoreDlg ��Ϣ�������

BOOL CMedicalImageStoreDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMedicalImageStoreDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		MessageBox(L"�˺Ż��������");
	}
}


void CMedicalImageStoreDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
