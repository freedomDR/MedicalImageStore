
// MedicalImageStoreDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CMedicalImageStoreDlg �Ի���
class CMedicalImageStoreDlg : public CDialogEx
{
// ����
public:
	CMedicalImageStoreDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEDICALIMAGESTORE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit user_name;
	CEdit pass_word;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit user_group;
};
