
// myapp_1Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// Cmyapp_1Dlg 对话框
class Cmyapp_1Dlg : public CDialogEx
{
// 构造
public:
	Cmyapp_1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYAPP_1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CButton btn_begin_test;
	afx_msg void OnBnClickedBeginText();
//	afx_msg void OnTCard(UINT /*idAction*/, DWORD /*dwActionData*/);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int time_sum;
	CString getFormatTime(int time_left);
	CString tv_time_left;
	CString et_zkz;
	CString et_sfz;

	int check_zkz(CString zkz);
	int check_sfz(CString sfz);
};
