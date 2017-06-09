// MainShow.cpp : ʵ���ļ�
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
	//DDX_Control(pDX, IDC_EDIT1, show_info);
	DDX_Control(pDX, IDC_PICTURE, DCM_show);
}

BOOL CMainShow::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HICON hIcon[3];      // ͼ��������   
	HTREEITEM hRoot;     // ���ĸ��ڵ�ľ��   
	HTREEITEM hCataItem; // �ɱ�ʾ��һ����ڵ�ľ��   
	HTREEITEM hArtItem;  // �ɱ�ʾ��һ���½ڵ�ľ��   
	CRect rc;
	CWnd *pWnd = GetDlgItem(IDC_PICTURE);//IDC_PIC_2DΪ�ؼ�ID
	pWnd->GetClientRect(&rc);//rcΪ�ؼ��Ĵ�С��
	picture_x = rc.Height();
	picture_y = rc.Width();
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

	for (int i = 0; i < User::containerLength; i++)
	{
		SwiftObject::getAllObject(User::containers[i].name, i);
	}

	// ������ڵ�   
	hRoot = m_webTree.InsertItem(User::user_name, 0, 0);
	// �ڸ��ڵ��²����ӽڵ�   
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


// CMainShow ��Ϣ�������


void CMainShow::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


BOOL CMainShow::UploadFile(LPCTSTR strURL, //��������ϴ�������ҳ���URL
	LPCTSTR strLocalFileName)  //���ϴ��ı����ļ�·��
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
		cis.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //���ӳ�ʱ����
		cis.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);  //����1��
		pHC = cis.GetHttpConnection(strServer, wPort);  //ȡ��һ��Http����
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

BOOL CMainShow::Download(const CString& strFileURLInServer, //�������ļ���URL
	const CString & strFileLocalFullPath)//��ŵ����ص�·��
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
	session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //����֮��ĵȴ���ʱ
	session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);   //���Դ���
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
				NULL);  //���������ļ�
			if (hFile == INVALID_HANDLE_VALUE)
			{
				pHttpFile->Close();
				pHttpConnection->Close();
				session.Close();
				return false;
			}

			char szInfoBuffer[1000];  //������Ϣ
			DWORD dwFileSize = 0;   //�ļ�����
			DWORD dwInfoBufferSize = sizeof(szInfoBuffer);
			BOOL bResult = FALSE;
			bResult = pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,
				(void*)szInfoBuffer, &dwInfoBufferSize, NULL);
			dwFileSize = atoi(szInfoBuffer);
			const int BUFFER_LENGTH = 1024 * 10;
			pszBuffer = new char[BUFFER_LENGTH];  //��ȡ�ļ��Ļ���
			DWORD dwWrite, dwTotalWrite;
			dwWrite = dwTotalWrite = 0;
			UINT nRead = pHttpFile->Read(pszBuffer, BUFFER_LENGTH); //��ȡ������������
			while (nRead > 0)
			{
				WriteFile(hFile, pszBuffer, nRead, &dwWrite, NULL);  //д�������ļ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	sInfo.lpszTitle = _T("��ѡ��һ���ļ��У�");
	sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
	sInfo.lpfn = NULL;

	// ��ʾ�ļ���ѡ��Ի���  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// ȡ���ļ�����  
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
