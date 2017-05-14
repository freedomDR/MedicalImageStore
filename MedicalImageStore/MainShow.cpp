// MainShow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MedicalImageStore.h"
#include "MainShow.h"
#include "SwiftTools.h"
#include "afxdialogex.h"
#include "LoginJudge.h"
#include "User.h"


// CMainShow �Ի���

IMPLEMENT_DYNAMIC(CMainShow, CDialogEx)

CMainShow::CMainShow(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
{

}

CMainShow::~CMainShow()
{
}

void CMainShow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATI_USER_NAME, user_name);
	DDX_Control(pDX, IDC_EDIT_FILE_ADDRESS, file_address);
	DDX_Control(pDX, IDC_TREE_USER, m_webTree);
}

BOOL CMainShow::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HICON hIcon[3];      // ͼ��������   
	HTREEITEM hRoot;     // ���ĸ��ڵ�ľ��   
	HTREEITEM hCataItem; // �ɱ�ʾ��һ����ڵ�ľ��   
	HTREEITEM hArtItem;  // �ɱ�ʾ��һ���½ڵ�ľ��   

						 // ��������ͼ�꣬�������ǵľ�����浽����   
	//hIcon[0] = theApp.LoadIcon(IDI_WEB_ICON);
	//hIcon[1] = theApp.LoadIcon(IDI_CATALOG_ICON);
	//hIcon[2] = theApp.LoadIcon(IDI_ARTICLE_ICON);

	// ����ͼ������CImageList����   
	//m_imageList.Create(32, 32, ILC_COLOR32, 3, 3);
	// ������ͼ����ӵ�ͼ������   
	/*for (int i = 0; i<3; i++)
	{
		m_imageList.Add(hIcon[i]);
	}*/

	// Ϊ���οؼ�����ͼ������   
	//m_webTree.SetImageList(&m_imageList, TVSIL_NORMAL);

	// ������ڵ�   
	hRoot = m_webTree.InsertItem(_T("account"), 0, 0);
	// �ڸ��ڵ��²����ӽڵ�   
	hCataItem = m_webTree.InsertItem(_T("container1"), 1, 1, hRoot, TVI_LAST);
	// Ϊ��IT���������ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_webTree.SetItemData(hCataItem, 1);
	// �ڡ�IT���������ڵ��²����ӽڵ�   
	hArtItem = m_webTree.InsertItem(_T("container2"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ���ٶ�����1���ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_webTree.SetItemData(hArtItem, 2);
	// �ڡ�IT���������ڵ��²�����һ�ӽڵ�   
	hArtItem = m_webTree.InsertItem(_T("container3"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ���ȸ�����2���ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_webTree.SetItemData(hArtItem, 3);
	// �ڸ��ڵ��²���ڶ����ӽڵ�   
	hCataItem = m_webTree.InsertItem(_T("container2"), 1, 1, hRoot, TVI_LAST);
	// Ϊ����������ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_webTree.SetItemData(hCataItem, 4);
	// �ڡ���������ڵ��²����ӽڵ�   
	hArtItem = m_webTree.InsertItem(_T("�����ֻ�����1"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ�������ֻ�����1���ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_webTree.SetItemData(hArtItem, 5);
	// �ڡ���������ڵ��²�����һ�ӽڵ�   
	hArtItem = m_webTree.InsertItem(_T("ƽ���������2"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ��ƽ���������2���ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_webTree.SetItemData(hArtItem, 6);
	// �ڸ��ڵ��²���������ӽڵ�   
	hCataItem = m_webTree.InsertItem(_T("container3"), 1, 1, hRoot, TVI_LAST);
	// Ϊ������������ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_webTree.SetItemData(hCataItem, 7);
	// �ڡ�����������ڵ��²����ӽڵ�   
	hArtItem = m_webTree.InsertItem(_T("C++�������ϵ��1"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ��C++�������ϵ��1���ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_webTree.SetItemData(hArtItem, 8);
	// �ڡ�����������ڵ��²�����һ�ӽڵ�   
	hArtItem = m_webTree.InsertItem(_T("VS2010/MFC�������2"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ��VS2010/MFC�������2���ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_webTree.SetItemData(hArtItem, 9);
	// �ڸ��ڵ��²�����ĸ��ӽڵ�   
	hCataItem = m_webTree.InsertItem(_T("container4"), 1, 1, hRoot, TVI_LAST);
	// Ϊ���������С��ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_webTree.SetItemData(hCataItem, 10);
	// �ڡ��������С��ڵ��²����ӽڵ�   
	hArtItem = m_webTree.InsertItem(_T("������������1"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ��������������1���ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_webTree.SetItemData(hArtItem, 11);
	// �ڡ��������С��ڵ��²�����һ�ӽڵ�   
	hArtItem = m_webTree.InsertItem(_T("ITЦ��2"), 2, 2, hCataItem, TVI_LAST);
	// Ϊ��ITЦ��2���ڵ���Ӹ��ӵı�����ݣ�����껮���ýڵ�ʱ��ʾ   
	m_webTree.SetItemData(hArtItem, 12);

	user_name.SetWindowTextW(User::user_name);

	SwiftTools::Test();
	return 0;
}


BEGIN_MESSAGE_MAP(CMainShow, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CMainShow::OnBnClickedCancel)
//	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMainShow::OnTvnSelchangedTree1)
ON_EN_CHANGE(IDC_EDIT_FILE_ADDRESS, &CMainShow::OnEnChangeEdit1)
ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CMainShow::OnBnClickedButtonOpenFile)
ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_USER, &CMainShow::OnTvnSelchangedTreeUser)
END_MESSAGE_MAP()


// CMainShow ��Ϣ�������


void CMainShow::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


//void CMainShow::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//}


void CMainShow::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMainShow::OnBnClickedButtonOpenFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ù�����   
	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
	// ������ļ��Ի���   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_FILE_ADDRESS, strFilePath);
	}
}

void CMainShow::OnTvnSelchangedTreeUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
