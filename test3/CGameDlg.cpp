// CGameDlg.cpp: 实现文件
//表示层，游戏窗口类，绘制游戏界面与用户交互，将操作转化为数据，传入逻辑层，在返回数据显示
//通过vertex在逻辑层间传递信息


#include "pch.h"
#include <iostream>
#include "test3.h"
#include "CGameDlg.h"
#include "afxdialogex.h"
#include "resource.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//星星图标

	m_ptGameTop.x= GAMETOP;//游戏区域起点坐标,单位像素
	m_ptGameTop.y = GAMETOP;
	m_sizeElement.cx= SIZEELEMENT;//单个水果图片大小
	m_sizeElement.cy = SIZEELEMENT;

	//初始化游戏更新区域，消除时使用
	m_rtGameRect.top = m_ptGameTop.y;//游戏区域左上角坐标
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElement.cx * NUMELEMENT;//游戏区域右下角坐标
	m_rtGameRect.bottom= m_rtGameRect.top + m_sizeElement.cy * NUMELEMENT;

	//初始点的标识
	m_bFirstPoint = true;//图片为第一次选中
	m_bPlaying = false;//游戏标志


}//构造函数

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_GAME_TIMER, m_GameProgress);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
//	ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnBnClickedButton1)
//	ON_NOTIFY(BCN_DROPDOWN, IDC_BUTTON1, &CGameDlg::OnDropdownButton1)
ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnClickedButton1)
ON_WM_LBUTTONUP()
ON_BN_CLICKED(IDC_BUTTON3, &CGameDlg::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON4, &CGameDlg::OnBnClickedButton4)
ON_BN_CLICKED(IDC_BUTTON2, &CGameDlg::OnBnClickedButton2)
//ON_NOTIFY(NM_CUSTOMDRAW,IDC_GAME_TIMER, &CGameDlg::OnNMCustomdrawGameTime)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTTON5, &CGameDlg::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON6, &CGameDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序

/*
基本模式游戏背景
*/
void CGameDlg::InitBackground()
{
	CClientDC dc(this);
	//::调用api,加载图片
	HANDLE bmp = ::LoadImage(NULL,TEXT("thame\\picture\\fruit_bg.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	//创建与视频内存兼的内存dc
	m_dcBG.CreateCompatibleDC(&dc);
	m_dcBG.SelectObject(bmp);//将资源放到内存dc

	//将位图加载到dc，目的显示背景
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc,1200,800);
	m_dcMem.SelectObject(bmpMem);//将对象放入位图dc
	m_dcMem.BitBlt(0, 0, 1200, 800, &m_dcBG, 0, 0, SRCCOPY);//制作背景到内存dc
	
	

	

}

/*虚函数，对话框初始化
*/
BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//窗口标题this->SetWindowTextW(_T(""));
	// 设置此对话框的图标。 
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	
	InitBackground();//初始化背景，将图片加载到内存dc中
	InitElement();//初始化水果图片，将图片加载到内存dc中
	UpdateWindos();//窗口大小
	//游戏未开始进度条隐藏和剩余时间控件
	this->GetDlgItem(IDC_GAME_TIMER)->ShowWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

/*
操作系统显示对话框窗口发送wm-paint消息
-》到应用程序-》对话框消息队列-》onpaint在视频内存中绘制窗口界面
*/
void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	dc.BitBlt(0, 0, 1200, 800, &m_dcMem, 0, 0, SRCCOPY);

}

/*
		调整窗口大小
		*/
void CGameDlg::UpdateWindos()
{
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);//获取窗口大小
	this->GetClientRect(rtClient);//获取客户区大小
	//标题栏和外边框大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	//设置窗口大小
	MoveWindow(0, 0, 1200 + nSpanWidth, 800 + nSpanHeight);
	CenterWindow();//剧中显示
}



/*游戏水果图，掩码图初始化保存到dc中，按列从上到下0—n
加载掩盖游戏地图的图片
*/
void CGameDlg:: InitElement()
{
	//::调用api,加载图片
	HANDLE bmp = ::LoadImage(NULL, TEXT("thame\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HANDLE bmp2 = ::LoadImage(NULL, TEXT("thame\\picture\\fruit_pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//将位图加载到dc
	CClientDC dc(this);
	m_dcElement.CreateCompatibleDC(&dc);//创建与视频内容兼容的内存dc
	m_dcElement.SelectObject(bmp);//将对象放入位图dc

	m_dcPause.CreateCompatibleDC(&dc);
	m_dcPause.SelectObject(bmp2);
	//CBitmap bitmap;
	m_bPause = false;

	//掩码图1像素RGB3字节，黑0白1
	HANDLE hMask = ::LoadImage(NULL, TEXT("thame\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMask);//将对象放入位图dc


}




/*基本模式-开始按钮，绘制水果地图
开始游戏设置游戏标志，禁用开始按钮
*/
void CGameDlg::OnClickedButton1()
{
	if (m_bPause==true)
	{
		return;
	}
	m_gControl.StartGame();//初始化数组
	m_bPlaying = true;//游戏已开始
	this->GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);//开始按钮不可用
	
	m_GameProgress.SetRange(0,60*1);//进度条范围300
	m_GameProgress.SetStep(-1);//变化步数值
	m_GameProgress.SetPos(60 * 1);//设置初始值
	//启动定时器
	this->SetTimer(PLAY_TIMER_ID,1000,NULL);//间隔1000毫秒
	DrawGameTime();//绘制当前秒数

	this->GetDlgItem(IDC_GAME_TIMER)->ShowWindow(TRUE);//开始游戏进度条可见
	//更新游戏界面
	UpdateMap();
	Invalidate(FALSE);//未能成功显示，客户区无效，invalidate绘制更新部分界面，进行覆盖

}


//-暂停按钮
void CGameDlg::OnBnClickedButton2()
{
	if (m_bPlaying == false)
		return;
	if (m_bPause==false)//游戏正在进行
	{
		m_dcMem.BitBlt(10, 10, 1000, 600, &m_dcPause, 0, 0, SRCCOPY);

		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
		this->GetDlgItem(IDC_BUTTON2)->SetWindowTextW(_T("继续"));
	}
	else//游戏已暂停
	{
		UpdateMap();

		InvalidateRect(m_rtGameRect, FALSE);    //局部矩形更新
		this->GetDlgItem(IDC_BUTTON2)->SetWindowTextW(_T("暂停"));
	}
	m_bPause = !m_bPause;
}

//-提示按钮，调用控制层help
void CGameDlg::OnBnClickedButton3()
{
	if (m_bPlaying == false)
		return;//游戏未开始
	Vertex avPath[PICNUM];//连接路径的顶点
	int nVexnum = 0;//连接顶点的个数
	if (m_gControl.Help(avPath, nVexnum) == false)
		return;
	else
	{
		DrawTipFrame(avPath[0].row,avPath[0].col);//画第一个提示框
		DrawTipFrame(avPath[nVexnum-1].row, avPath[nVexnum-1].col);//画第二个提示框
		DrawTipLine(avPath,nVexnum);//画连线
		Sleep(500);//延迟更新
		UpdateMap();
		InvalidateRect(m_rtGameRect, FALSE);
	}
}

//-重排按钮
void CGameDlg::OnBnClickedButton4()
{
	if (m_bPlaying == false)
		return;//游戏未开始
	m_gControl.ResetGraph(); 
	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE);
}


//-设置
void CGameDlg::OnBnClickedButton5()
{
}

//-帮助
void CGameDlg::OnBnClickedButton6()
{
	CHelpDialog hlg;//帮助对话框类
	hlg.DoModal();//显示
}





/*
跟新绘制游戏地图，仅仅游戏部分
*/
void CGameDlg::UpdateMap()
{
	//单位像素
	int nLeft = m_ptGameTop.x;//游戏区域起点位置
	int nTop = m_ptGameTop.y;
	int nElemW = SIZEELEMENT;//每个图的长宽
	int nElemH = SIZEELEMENT;
	//先绘制游戏部分背景图片
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(),
		&m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i < NUMELEMENT; i++)//
	{
		for (int j = 0; j < NUMELEMENT; j++)//
		{
			int nInfo = m_gControl.GetElement(i,j);//返回图片编号，在控制类中判断连接消子返回，消子在逻辑类中具体实现
			//通过初始化加载的水果图dc
			//逐行逐列从数组，将相应行列编号的图片数据中放到dc中
			
				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
					&m_dcMask, 0, nInfo * nElemH, SRCPAINT);//与掩码图相或

				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
					&m_dcElement, 0, nInfo * nElemH, SRCAND);//与原图相与
			
			/*
			掩码图黑底0白图1与与背景图xx相或-》彩底x白图1
			彩底x白图1与原图白底1彩图x相与-》彩底x彩图x
			*/
		}
	}
}

/*
WM_LBUTTONUP左键释放消息响应函数,参数点击区域，坐标c
获取点击的游戏图行号，绘制提示框，判断两次选择是否同,消除
连通判断后判断胜负，胜将游戏标志置位未开始，开始游戏按钮可用
*/
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	if (m_bPlaying==false)
	{
		return;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
	if (point.x<m_ptGameTop.x|| point.y < m_ptGameTop.y)
	{
		//点击不在游戏区域
		return 	CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElement.cy;//点击的水果图行号（现-起）/单位
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElement.cx;//点击的水果图列号
	if (nRow> NUMELEMENT -1||nCol> NUMELEMENT-1)
	{
		//点击不在游戏区域
		return 	CDialogEx::OnLButtonUp(nFlags, point);
	}

	if (m_bFirstPoint)
	{//第一次选中图片，保存坐标
		DrawTipFrame(nRow, nCol);//通过点击获取的行号绘制选中图标的提示框
		m_gControl.SetFirstPoint(nRow, nCol);//设置第一个顶点
	}
	else
	{//第二次选中，同时判断两次选中的是否为同一种图片
		DrawTipFrame(nRow, nCol);//通过点击获取的行号绘制选中图标的提示框
		m_gControl.SetSecPoint(nRow, nCol);//设置第一个顶点
		Vertex avPath[PICNUM];//连接路径的顶点
		int nVexnum = 0;//连接顶点的个数
		if (m_gControl.Link(avPath, nVexnum))//在函数中直接判断连接，消子标记
		{
			DrawTipLine(avPath, nVexnum);//两图连接起来
			UpdateMap();//更新水果图游戏地图

		}
		Sleep(200);//ms绘制连线后，延迟，在重绘游戏地图
		InvalidateRect(m_rtGameRect,FALSE);//重绘游戏区域，是否擦除背景，引起屏幕闪烁更新
		
		JudgeWin();//判断胜负
	
	}
	m_bFirstPoint = !m_bFirstPoint;//标志取反，循环使用

}


/*根据选择的图片绘制其周围矩形提示框
*/
void CGameDlg::DrawTipFrame(int nRow,int nCol)
{
	CClientDC dc(this);//获取当前dc
	CBrush brush(RGB(233, 43, 43));//构造颜色画刷1像素1RGB
	CRect rtTipFrame;//提示框
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElement.cx;//选中单个水果图标左上角坐标
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElement.cy;//选中单个水果图标左上角坐标
	rtTipFrame.right = rtTipFrame.left + m_sizeElement.cx;//选中单个图标的宽
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElement.cy;//选中单个图标的高
	dc.FrameRect(rtTipFrame, &brush);//将提示框加到dc中
}


/*
*///绘制选择的相同的两个点之间的连线（中心绘制）
void  CGameDlg::DrawTipLine(Vertex avPath[PICNUM],int nVexnum)
{
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));//设置画笔
	CPen* poldPen = dc.SelectObject(&penLine);//将画笔选入dc
	//绘制连接直线线起点和终点
	dc.MoveTo(m_ptGameTop.x + avPath[0].col * m_sizeElement.cx + m_sizeElement.cx / 2,
			m_ptGameTop.y + avPath[0].row * m_sizeElement.cy + m_sizeElement.cy / 2);

	for (int i = 0; i < nVexnum-1; i++)
	{
		
		dc.LineTo(m_ptGameTop.x + avPath[i+1].col * m_sizeElement.cx + m_sizeElement.cx / 2,
			m_ptGameTop.y + avPath[i+1].row * m_sizeElement.cy + m_sizeElement.cy / 2);
	}

	dc.SelectObject(poldPen);
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying && m_bPause == false)
	{
		m_GameProgress.StepIt();//设置进度条位置
		DrawGameTime();
		JudgeWin();//超时判断胜负


	}

	CDialogEx::OnTimer(nIDEvent);
}


//判断胜负，时间和空
void  CGameDlg::JudgeWin()
{
	BOOL gameState = m_gControl.IsWin(m_GameProgress.GetPos());
	if (gameState==2)//继续游戏
	{
		return;
	}
	else
	{
		m_bPlaying = false;//游戏停止
		KillTimer(PLAY_TIMER_ID);//关闭定时器
		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (gameState==1)
		{
			MessageBox(_T("获胜"), strTitle);
		}
		else
		{
			if (gameState == 0)
			{
				MessageBox(_T("失败"), strTitle);
			}
		}
		this->GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);//开始按钮还原
	}
}

//绘制游戏时间//绘制当前秒数
void  CGameDlg::DrawGameTime()
{

	//创建字体
	CFont font;
	font.CreatePointFont(150, _T("Courier New"));
	CFont* oldFont;
	CDC *dc=this->GetDC();
	oldFont = dc->SelectObject(&font);//将字体选入dc中
	dc->SetTextColor(RGB(255, 0, 0));

	CString str;
	str.Format(_T("%d"), m_GameProgress.GetPos());
	CSize size=dc->GetTextExtent(str, str.GetLength());
	dc->TextOut(888, 678, str);//显示内容，在背景图的上面

	//UpdateMap();
	//InvalidateRect(m_rtGameRect, FALSE);

}


void CGameDlg::OnNMCustomdrawGameTime(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


