#pragma once


// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };//通过id关联对话框
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;//对话框图标
	CDC m_dcMem;//内存dc(背景使用，水果图使用)
	CDC m_dcElement;//保存水果图dc
	CDC m_dcMask;//水果图掩码（黑0底白1图）
	int m_anMap[4][4];//以坐标表示二维数组，对应图片，-1则无图

	void InitBackground();
	virtual BOOL OnInitDialog();
	void InitElement();

public:

	afx_msg void OnPaint();
//	afx_msg void OnBnClickedButton1();
//	afx_msg void OnDropdownButton1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButton1();
};
