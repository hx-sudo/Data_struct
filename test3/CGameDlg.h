#pragma once
#include "global.h"
#include "CGameControl.h"
#include"CHelpDialog.h"


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
	CDC m_dcCache;//缓存的内存dc
	CDC m_dcPause;//暂停图片的内存dc
	CDC m_dcMem;//主内存dc(背景使用，水果图使用)，传到视频内存，输出
	CDC m_dcBG;//保存背景图dc
	CDC m_dcElement;//保存水果图dc
	CDC m_dcMask;//水果图掩码（黑0底白1图）
	CPoint m_ptGameTop;//游戏区域起点坐标
	CSize m_sizeElement;//单个水果图片大小
	bool m_bFirstPoint;//标志，图片是否为第一次选中
	Vertex m_ptSelFirst;//两次选中图片的坐标
	Vertex m_ptSelSec;
	CRect m_rtGameRect;//游戏区域
	CGameControl m_gControl;//游戏控制类对象
	bool m_bPlaying;//游戏正在进行标志
	bool m_bPause;//游戏暂停与否

	void InitBackground();//初始化背景
	virtual BOOL OnInitDialog();//初始化对话框
	void InitElement();//初始化水果图到内存dc
	void DrawTipFrame(int nRpw, int nCol);//根据选择的图片绘制其周围矩形提示框
	void DrawTipLine(Vertex avPath[PICNUM], int nVexnum);//绘制选择的相同的两个点之间的连线（中心绘制）
	void UpdateMap();//更新游戏地图
	void UpdateWindos();//调整窗口大小，更新游戏界面，从生成的游戏地图图结构中取出顶点，同时取出相应元素，显示在游戏地图
	void JudgeWin();//判断胜负，时间和空
	void DrawGameTime();//绘制游戏时间

public:

	afx_msg void OnPaint();//绘制客户区
//	afx_msg void OnBnClickedButton1();
//	afx_msg void OnDropdownButton1(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnClickedButton1();//开始按钮，绘制水果地图,开始游戏设置游戏标志，禁用开始按钮
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);//左键点击游戏图
	

	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	// //进度条控件的映射变量
	CProgressCtrl m_GameProgress;
	afx_msg void OnNMCustomdrawGameTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};

