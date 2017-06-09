// MainShow.cpp : 实现文件
//

#include "stdafx.h"
#include "MedicalImageStore.h"
#include "MedicalImageStoreDlg.h"
#include "MainShow.h"
#include "SwiftTools.h"
#include "afxdialogex.h"
#include "LoginJudge.h"
#include "User.h"
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkAutoInit.h>



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
	//DDX_Control(pDX, IDC_EDIT1, show_info);
	DDX_Control(pDX, IDC_PICTURE, DCM_show);
}

BOOL CMainShow::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HICON hIcon[3];      // 图标句柄数组   
	HTREEITEM hRoot;     // 树的根节点的句柄   
	HTREEITEM hCataItem; // 可表示任一分类节点的句柄   
	HTREEITEM hArtItem;  // 可表示任一文章节点的句柄   
	CRect rc;
	CWnd *pWnd = GetDlgItem(IDC_PICTURE);//IDC_PIC_2D为控件ID
	pWnd->GetClientRect(&rc);//rc为控件的大小。
	picture_x = rc.Height();
	picture_y = rc.Width();
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

	for (int i = 0; i < User::containerLength; i++)
	{
		SwiftObject::getAllObject(User::containers[i].name, i);
	}

	// 插入根节点   
	hRoot = m_webTree.InsertItem(User::user_name, 0, 0);
	// 在根节点下插入子节点   
	for (int i = 0; i < User::containerLength; i++)
	{
		hCataItem = m_webTree.InsertItem(User::containers[i].name, 1, 1, hRoot, TVI_LAST);
		m_webTree.SetItemData(hCataItem, i);
		for (int j = 0; j < User::containers[i].length; j++)
		{
			if (User::containers[i].swiftObject[j]->name != L"")
			{
				hArtItem = m_webTree.InsertItem(User::containers[i].swiftObject[j]->name, 2, 2, hCataItem, TVI_LAST);
				m_webTree.SetItemData(hArtItem, j);
			}
		}
	}
	   
	user_name.SetWindowTextW(User::user_name);
	//show_info.SetWindowTextW(User::headInfo);
	//SwiftTools::Test();
	reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
	renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	return 0;
}


BEGIN_MESSAGE_MAP(CMainShow, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CMainShow::OnBnClickedCancel)
//	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CMainShow::OnTvnSelchangedTree1)
ON_EN_CHANGE(IDC_EDIT_FILE_ADDRESS, &CMainShow::OnEnChangeEdit1)
ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CMainShow::OnBnClickedButtonOpenFile)
ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_USER, &CMainShow::OnTvnSelchangedTreeUser)
ON_BN_CLICKED(IDC_BUTTON_UPLOAD, &CMainShow::OnBnClickedButtonUpload)
ON_BN_CLICKED(IDC_Download, &CMainShow::OnBnClickedDownload)
END_MESSAGE_MAP()


// CMainShow 消息处理程序


void CMainShow::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	this->ShowWindow(SW_HIDE);
	CMedicalImageStoreDlg dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
	::SendMessage(this->GetSafeHwnd(), WM_CLOSE, NULL, NULL);
	*/
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
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	CString value;
	value = m_webTree.GetItemText(hItem);
	User::selectContainerName = value;
	int pos = m_webTree.GetItemData(hItem);
	if (User::user_name == value)
	{
		//show_info.SetWindowTextW(User::headInfo);
	}
	else if (User::containers[pos].name == value) 
	{
		//show_info.SetWindowTextW(User::containers[pos].headInfo);
		User::selectContainerId = pos;
	}
	else if (User::containers[User::selectContainerId].swiftObject[pos]->name == value)
	{
		//show_info.SetWindowTextW(User::containers[User::selectContainerId].swiftObject[pos]->headInfo);
		downloadFileName = User::containers[User::selectContainerId].swiftObject[pos]->name;
		downloadFileContainerName = User::containers[User::selectContainerId].name;
		Download(User::storage_url + L"\\" + downloadFileContainerName + "\\" + downloadFileName, L"./" + downloadFileName);
		CString mid = L"C:\\Users\\orange\\Desktop\\dongruotest\\3b_mpr_pr_hf_vfh.3.dcm";
		ShowDcm(L"./" + downloadFileName);
	}
	*pResult = 0;
}


void CMainShow::OnBnClickedButtonUpload()
{
	CString filename;
	file_address.GetWindowTextW(filename);
	int start = 0;
	CString result,file_name;
	result = filename.Tokenize(L"\\", start);
	while (result != L"")
	{
		file_name = result;
		result = filename.Tokenize(L"\\", start);
	}
	BOOL uti_result = UploadFile(User::storage_url+L"/"+User::selectContainerName+"/"+file_name, filename);
	if (uti_result == true)
	{
		MessageBox(L"success");
		HTREEITEM mid = m_webTree.GetSelectedItem();
		m_webTree.InsertItem(file_name, 2, 2, mid, TVI_LAST);
	}
	else
	{
		MessageBox(L"faile");
	}
}


BOOL CMainShow::UploadFile(LPCTSTR strURL, //负责接收上传操作的页面的URL
	LPCTSTR strLocalFileName)  //待上传的本地文件路径
{
	ASSERT(strURL != NULL && strLocalFileName != NULL);
	BOOL bResult = FALSE;
	DWORD dwType = 0;
	CString strServer;
	CString strObject;
	INTERNET_PORT wPort = 0;
	DWORD dwFileLength = 0;
	char * pFileBuff = NULL;
	CHttpConnection * pHC = NULL;
	CHttpFile * pHF = NULL;
	CInternetSession cis;
	bResult = AfxParseURL(strURL, dwType, strServer, strObject, wPort);
	if (!bResult)
		return FALSE;
	CFile file;
	try
	{
		if (!file.Open(strLocalFileName, CFile::shareDenyNone | CFile::modeRead))
			return FALSE;
		dwFileLength = file.GetLength();
		if (dwFileLength <= 0)
			return FALSE;
		pFileBuff = new char[dwFileLength];
		memset(pFileBuff, 0, sizeof(char) * dwFileLength);
		file.Read(pFileBuff, dwFileLength);
		const int nTimeOut = 5000;
		cis.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //联接超时设置
		cis.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);  //重试1次
		pHC = cis.GetHttpConnection(strServer, wPort);  //取得一个Http联接
		pHF = pHC->OpenRequest(CHttpConnection::HTTP_VERB_PUT, strObject, NULL, 1, NULL, NULL, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE);
		pHF->AddRequestHeaders(L"X-Auth-Token: " + User::auth_token);
		if (!pHF->SendRequest(NULL, 0, pFileBuff, dwFileLength))
		{
			delete[]pFileBuff;
			pFileBuff = NULL;
			pHF->Close();
			pHC->Close();
			cis.Close();
			return FALSE;
		}
		DWORD dwStateCode = 0;
		pHF->QueryInfoStatusCode(dwStateCode);
		if (dwStateCode == HTTP_STATUS_OK)
			bResult = TRUE;
	}
	catch (CInternetException * pEx)
	{
		LPTSTR sz = L"";
		pEx->GetErrorMessage(sz, 25);
		CString str;
		str.Format(L"InternetException occur!\r\n%s", sz);
		AfxMessageBox(str);
	}
	catch (CFileException& fe)
	{
		CString str;
		str.Format(L"FileException occur!\r\n%d", fe.m_lOsError);
		AfxMessageBox(str);
	}
	catch (...)
	{
		DWORD dwError = GetLastError();
		CString str;
		str.Format(L"Unknow Exception occur!\r\n%d", dwError);
		AfxMessageBox(str);
	}
	delete[]pFileBuff;
	pFileBuff = NULL;
	file.Close();
	pHF->Close();
	pHC->Close();
	cis.Close();
	return bResult;
}

BOOL CMainShow::Download(const CString& strFileURLInServer, //待下载文件的URL
	const CString & strFileLocalFullPath)//存放到本地的路径
{
	ASSERT(strFileURLInServer != "");
	ASSERT(strFileLocalFullPath != "");
	CInternetSession session;
	CHttpConnection* pHttpConnection = NULL;
	CHttpFile* pHttpFile = NULL;
	CString strServer, strObject;
	INTERNET_PORT wPort;
	DWORD dwType;
	const int nTimeOut = 2000;
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //重试之间的等待延时
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);   //重试次数
	char* pszBuffer = NULL;
	try
	{
		AfxParseURL(strFileURLInServer, dwType, strServer, strObject, wPort);
		pHttpConnection = session.GetHttpConnection(strServer, wPort);
		pHttpFile = pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, strObject, NULL, 1, NULL, NULL, INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE);
		pHttpFile->AddRequestHeaders(L"X-Auth-Token: " + User::auth_token);
		if (pHttpFile->SendRequest() == FALSE)
			return false;
		DWORD dwStateCode;
		pHttpFile->QueryInfoStatusCode(dwStateCode);
		if (dwStateCode == HTTP_STATUS_OK)
		{
			HANDLE hFile = CreateFile(strFileLocalFullPath, GENERIC_WRITE,
				FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
				NULL);  //创建本地文件
			if (hFile == INVALID_HANDLE_VALUE)
			{
				pHttpFile->Close();
				pHttpConnection->Close();
				session.Close();
				return false;
			}

			char szInfoBuffer[1000];  //返回消息
			DWORD dwFileSize = 0;   //文件长度
			DWORD dwInfoBufferSize = sizeof(szInfoBuffer);
			BOOL bResult = FALSE;
			bResult = pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,
				(void*)szInfoBuffer, &dwInfoBufferSize, NULL);
			dwFileSize = atoi(szInfoBuffer);
			const int BUFFER_LENGTH = 1024 * 10;
			pszBuffer = new char[BUFFER_LENGTH];  //读取文件的缓冲
			DWORD dwWrite, dwTotalWrite;
			dwWrite = dwTotalWrite = 0;
			UINT nRead = pHttpFile->Read(pszBuffer, BUFFER_LENGTH); //读取服务器上数据
			while (nRead > 0)
			{
				WriteFile(hFile, pszBuffer, nRead, &dwWrite, NULL);  //写到本地文件
				dwTotalWrite += dwWrite;
				nRead = pHttpFile->Read(pszBuffer, BUFFER_LENGTH);
			}
			delete[]pszBuffer;
			pszBuffer = NULL;
			CloseHandle(hFile);
		}
		else
		{
			delete[]pszBuffer;
			pszBuffer = NULL;
			if (pHttpFile != NULL)
			{
				pHttpFile->Close();
				delete pHttpFile;
				pHttpFile = NULL;
			}
			if (pHttpConnection != NULL)
			{
				pHttpConnection->Close();
				delete pHttpConnection;
				pHttpConnection = NULL;
			}
			session.Close();
			return false;
		}
	}
	catch (...)
	{
		delete[]pszBuffer;
		pszBuffer = NULL;
		if (pHttpFile != NULL)
		{
			pHttpFile->Close();
			delete pHttpFile;
			pHttpFile = NULL;
		}
		if (pHttpConnection != NULL)
		{
			pHttpConnection->Close();
			delete pHttpConnection;
			pHttpConnection = NULL;
		}
		session.Close();
		return false;
	}
	if (pHttpFile != NULL)
		pHttpFile->Close();
	if (pHttpConnection != NULL)
		pHttpConnection->Close();
	session.Close();
	return true;
}

void CMainShow::OnBnClickedDownload()
{
	// TODO: 在此添加控件通知处理程序代码
	CString download_path = selectFileFolder();
	BOOL utl_result = Download(User::storage_url + L"\\" + downloadFileContainerName + L"\\" + downloadFileName, download_path+"/"+ downloadFileName);
	if (utl_result == true)
	{
		MessageBox(L"success");
	}
	else
	{
		MessageBox(L"faile");
	}
}

CString CMainShow::selectFileFolder()
{
	TCHAR           szFolderPath[MAX_PATH] = { 0 };
	CString         strFolderPath = TEXT("");

	BROWSEINFO      sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = _T("请选择一个文件夹：");
	sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
	sInfo.lpfn = NULL;

	// 显示文件夹选择对话框  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// 取得文件夹名  
		if (::SHGetPathFromIDList(lpidlBrowse, szFolderPath))
		{
			strFolderPath = szFolderPath;
		}
	}
	if (lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}

	return strFolderPath;
}

void CMainShow::ShowDcm(CString & filename)
{
	USES_CONVERSION;
	char *nstringa = W2A(filename);
	
	reader->SetFileName(nstringa);
	reader->Update();

	
	imageViewer->SetParentId(DCM_show.GetSafeHwnd());
	
	imageViewer->SetSize(picture_x, picture_y);
	imageViewer->SetInputConnection(reader->GetOutputPort());
	

	imageViewer->SetupInteractor(renderWindowInteractor);
	imageViewer->Render();
	imageViewer->GetRenderer()->ResetCamera();
	imageViewer->Render();

	renderWindowInteractor->Start();
}
