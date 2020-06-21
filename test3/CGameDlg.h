#pragma once
#include "global.h"
#include "CGameControl.h"


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
	CDC m_dcMem;//主内存dc(背景使用，水果图使用)，传到视频内存，输出
	CDC m_dcBG;//保存背景图dc
	CDC m_dcElement;//保存水果图dc
	CDC m_dcMask;//水果图掩码（黑0底白1图）
	//int m_anMap[8][8];//以坐标表示二维数组，对应图片，-1则无图
	CPoint m_ptGameTop;//游戏区域起点坐标
	CSize m_sizeElement;//单个水果图片大小
	bool m_bFirstPoint;//标志，图片是否为第一次选中
	Vertex m_ptSelFirst;//两次选中图片的坐标
	Vertex m_ptSelSec;
	CRect m_rtGameRect;//游戏区域
	CGameControl m_gControl;//游戏控制类

	void InitBackground();//初始化背景
	virtual BOOL OnInitDialog();//初始化对话框
	void InitElement();//初始化水果图到内存dc
	void DrawTipFrame(int nRpw, int nCol);//根据选择的图片绘制其周围矩形提示框
	//bool IsLink();//判断选择的一堆图片是否为同种图片
	void DrawTipLine(Vertex avPath[8], int nVexnum);//绘制选择的相同的两个点之间的连线（中心绘制）
	void UpdateMap();//更新游戏地图
	void UpdateWindos();//调整窗口大小，更新游戏界面

public:

	afx_msg void OnPaint();//绘制客户区
//	afx_msg void OnBnClickedButton1();
//	afx_msg void OnDropdownButton1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickedButton1();//开始按钮，绘制水果地图
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);//左键点击游戏图
};

