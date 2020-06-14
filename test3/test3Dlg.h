﻿
// test3Dlg.h: 头文件
//

#pragma once


// Ctest3Dlg 对话框类
class Ctest3Dlg : public CDialogEx
{
// 构造
public:
	Ctest3Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CDC m_dcMem;//一个与视频dc兼容的主位图内存dc

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void InitBackground();//对话框初始化背景
public:
//	afx_msg void OnBnClickedButton2();
//	afx_msg void OnClickedButtonBase1();
	afx_msg void OnClickedButtonBase1();
	afx_msg void OnBnClickedButtonBase2();
};
