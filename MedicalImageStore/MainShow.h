#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CMainShow 对话框

class CMainShow : public CDialogEx
{
	DECLARE_DYNAMIC(CMainShow)

public:
	CMainShow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainShow();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	CStatic user_name;
//	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButtonOpenFile();
	CEdit file_address;
	afx_msg void OnTvnSelchangedTreeUser(NMHDR *pNMHDR, LRESULT *pResult);
	CTreeCtrl m_webTree;
	afx_msg void OnBnClickedButtonUpload();
	BOOL UploadFile(LPCTSTR strURL, LPCTSTR strLocalFileName);
	BOOL Download(const CString& strFileURLInServer, const CString & strFileLocalFullPath);
	CEdit show_info;
};
