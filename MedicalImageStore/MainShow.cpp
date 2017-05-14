// MainShow.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicalImageStore.h"
#include "MainShow.h"
#include "SwiftTools.h"
#include "afxdialogex.h"
#include "LoginJudge.h"
#include "User.h"


// CMainShow 对话框

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
	HICON hIcon[3];      // 图标句柄数组   
	HTREEITEM hRoot;     // 树的根节点的句柄   
	HTREEITEM hCataItem; // 可表示任一分类节点的句柄   
	HTREEITEM hArtItem;  // 可表示任一文章节点的句柄   

						 // 加载三个图标，并将它们的句柄保存到数组   
	//hIcon[0] = theApp.LoadIcon(IDI_WEB_ICON);
	//hIcon[1] = theApp.LoadIcon(IDI_CATALOG_ICON);
	//hIcon[2] = theApp.LoadIcon(IDI_ARTICLE_ICON);

	// 创建图像序列CImageList对象   
	//m_imageList.Create(32, 32, ILC_COLOR32, 3, 3);
	// 将三个图标添加到图像序列   
	/*for (int i = 0; i<3; i++)
	{
		m_imageList.Add(hIcon[i]);
	}*/

	// 为树形控件设置图像序列   
	//m_webTree.SetImageList(&m_imageList, TVSIL_NORMAL);

	// 插入根节点   
	hRoot = m_webTree.InsertItem(_T("account"), 0, 0);
	// 在根节点下插入子节点   
	hCataItem = m_webTree.InsertItem(_T("container1"), 1, 1, hRoot, TVI_LAST);
	// 为“IT互联网”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_webTree.SetItemData(hCataItem, 1);
	// 在“IT互联网”节点下插入子节点   
	hArtItem = m_webTree.InsertItem(_T("container2"), 2, 2, hCataItem, TVI_LAST);
	// 为“百度文章1”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_webTree.SetItemData(hArtItem, 2);
	// 在“IT互联网”节点下插入另一子节点   
	hArtItem = m_webTree.InsertItem(_T("container3"), 2, 2, hCataItem, TVI_LAST);
	// 为“谷歌文章2”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_webTree.SetItemData(hArtItem, 3);
	// 在根节点下插入第二个子节点   
	hCataItem = m_webTree.InsertItem(_T("container2"), 1, 1, hRoot, TVI_LAST);
	// 为“数码生活”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_webTree.SetItemData(hCataItem, 4);
	// 在“数码生活”节点下插入子节点   
	hArtItem = m_webTree.InsertItem(_T("智能手机文章1"), 2, 2, hCataItem, TVI_LAST);
	// 为“智能手机文章1”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_webTree.SetItemData(hArtItem, 5);
	// 在“数码生活”节点下插入另一子节点   
	hArtItem = m_webTree.InsertItem(_T("平板电脑文章2"), 2, 2, hCataItem, TVI_LAST);
	// 为“平板电脑文章2”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_webTree.SetItemData(hArtItem, 6);
	// 在根节点下插入第三个子节点   
	hCataItem = m_webTree.InsertItem(_T("container3"), 1, 1, hRoot, TVI_LAST);
	// 为“软件开发”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_webTree.SetItemData(hCataItem, 7);
	// 在“软件开发”节点下插入子节点   
	hArtItem = m_webTree.InsertItem(_T("C++编程入门系列1"), 2, 2, hCataItem, TVI_LAST);
	// 为“C++编程入门系列1”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_webTree.SetItemData(hArtItem, 8);
	// 在“软件开发”节点下插入另一子节点   
	hArtItem = m_webTree.InsertItem(_T("VS2010/MFC编程入门2"), 2, 2, hCataItem, TVI_LAST);
	// 为“VS2010/MFC编程入门2”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_webTree.SetItemData(hArtItem, 9);
	// 在根节点下插入第四个子节点   
	hCataItem = m_webTree.InsertItem(_T("container4"), 1, 1, hRoot, TVI_LAST);
	// 为“娱乐休闲”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_webTree.SetItemData(hCataItem, 10);
	// 在“娱乐休闲”节点下插入子节点   
	hArtItem = m_webTree.InsertItem(_T("玛雅文明文章1"), 2, 2, hCataItem, TVI_LAST);
	// 为“玛雅文明文章1”节点添加附加的编号数据，在鼠标划过该节点时显示   
	m_webTree.SetItemData(hArtItem, 11);
	// 在“娱乐休闲”节点下插入另一子节点   
	hArtItem = m_webTree.InsertItem(_T("IT笑话2"), 2, 2, hCataItem, TVI_LAST);
	// 为“IT笑话2”节点添加附加的编号数据，在鼠标划过该节点时显示   
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


// CMainShow 消息处理程序


void CMainShow::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


//void CMainShow::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}


void CMainShow::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMainShow::OnBnClickedButtonOpenFile()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器   
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_FILE_ADDRESS, strFilePath);
	}
}

void CMainShow::OnTvnSelchangedTreeUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
