// CGameDlg.cpp: 实现文件
//表示层，游戏窗口类，绘制游戏界面与用户交互，将操作转化为数据，传入逻辑层，在返回数据显示
//通过vertex在逻辑层间传递信息


#include "pch.h"
#include <iostream>
#include "test3.h"
#include "CGameDlg.h"
#include "afxdialogex.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//星星图标

	m_ptGameTop.x=100;//游戏区域起点坐标,单位像素
	m_ptGameTop.y = 100;
	m_sizeElement.cx=40;//单个水果图片大小
	m_sizeElement.cy = 40;
	
	//初始化游戏更新区域，消除时使用
	m_rtGameRect.top = m_ptGameTop.y;//游戏区域左上角坐标
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElement.cx * 10;//游戏区域右下角坐标
	m_rtGameRect.bottom= m_rtGameRect.top + m_sizeElement.cy * 10;

	//初始点的标识
	m_bFirstPoint = true;//图片为第一次选中

}//构造函数

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
//	ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnBnClickedButton1)
//	ON_NOTIFY(BCN_DROPDOWN, IDC_BUTTON1, &CGameDlg::OnDropdownButton1)
ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnClickedButton1)
ON_WM_LBUTTONUP()
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


//void CGameDlg::OnBnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


/*游戏水果图，掩码图初始化保存到dc中，按列从上到下0—n
*/
void CGameDlg:: InitElement()
{
	//::调用api,加载图片
	HANDLE bmp = ::LoadImage(NULL, TEXT("thame\\picture\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//将位图加载到dc
	CClientDC dc(this);
	m_dcElement.CreateCompatibleDC(&dc);//创建与视频内容兼容的内存dc
	m_dcElement.SelectObject(bmp);//将对象放入位图dc

	//掩码图1像素RGB3字节，黑0白1
	HANDLE hMask = ::LoadImage(NULL, TEXT("thame\\picture\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMask);//将对象放入位图dc
}




/*基本模式-开始按钮，绘制水果地图
*/
void CGameDlg::OnClickedButton1()
{
	/*水果图地图初始化
	//初始化地图数组
	int anMap[8][8] = {
		1,3,5,3,5,3,6,0,
		2,4,6,3,2,2,0,5,
		2,4,5,1,5,2,4,1,
		3,3,4,5,3,3,5,3,
		6,5,6,6,4,2,5,1,
		5,6,3,4,5,6,0,0,
		2,1,1,5,6,4,4,3,
		0,0,6,3,4,4,6,2,
	};
	for (int i = 0; i < 8; i++)
	{
		for (int  j = 0; j < 8; j++)
		{
			m_anMap[i][j] = anMap[i][j];
		}
	}*/
	m_gControl.StartGame();//初始化数组

	//更新游戏界面
	UpdateMap();
	Invalidate(FALSE);//未能成功显示，客户区无效，invalidate绘制更新部分界面，进行覆盖

}

/*
跟新绘制游戏地图，仅仅游戏部分
*/
void CGameDlg::UpdateMap()
{
	//单位像素
	int nLeft = m_ptGameTop.x;//游戏区域起点位置
	int nTop = m_ptGameTop.y;
	int nElemW = 40;//每个图的长宽
	int nElemH = 40;
	//先绘制游戏部分背景图片
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), m_rtGameRect.Height(),
		&m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i < 10; i++)//
	{
		for (int j = 0; j < 10; j++)//
		{
			int nInfo = m_gControl.GetElement(i,j);//返回图片编号
			//通过初始化加载的水果图dc
			//逐行逐列从数组，将相应行列编号的图片数据中放到dc中
			//m_dcMem.BitBlt(nLeft+j*nElemW,nTop+i*nElemH,nElemW,nElemH,&m_dcElement,0,m_anMap[i][j]*nElemH,SRCCOPY);//复制
			
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
*/
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnLButtonUp(nFlags, point);
	if (point.x<m_ptGameTop.x|| point.y < m_ptGameTop.y)
	{
		//点击不在游戏区域
		return 	CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElement.cy;//点击的水果图行号（现-起）/单位
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElement.cx;//点击的水果图列号
	if (nRow>9||nCol>9)
	{
		//点击不在游戏区域
		return 	CDialogEx::OnLButtonUp(nFlags, point);
	}

	if (m_bFirstPoint)
	{//第一次选中图片，保存坐标
		DrawTipFrame(nRow, nCol);//通过点击获取的行号绘制选中图标的提示框
		//m_ptSelFirst.x = nCol;//列
		//m_ptSelFirst.y = nRow;
		m_gControl.SetFirstPoint(nRow, nCol);//设置第一个顶点
	}
	else
	{//第二次选中，同时判断两次选中的是否为同一种图片
		DrawTipFrame(nRow, nCol);//通过点击获取的行号绘制选中图标的提示框
			//m_ptSelSec.x = nCol;//行
			//m_ptSelSec.y = nRow;
		m_gControl.SetSecPoint(nRow, nCol);//设置第一个顶点
		Vertex avPath[8];//连接路径的顶点
		int nVexnum = 0;//连接顶点的个数
		if (m_gControl.Link(avPath, nVexnum))//在函数中直接判断连接，消子标记
		{
			DrawTipLine(avPath, nVexnum);//两图连接起来
			//m_anMap[m_ptSelFirst.y][m_ptSelFirst.x] = -1;//-1表示两个点消除
			//m_anMap[m_ptSelSec.y][m_ptSelSec.x] = -1;
			UpdateMap();//更新水果图游戏地图
		}
		Sleep(200);//ms绘制连线后，延迟，在重绘游戏地图
		InvalidateRect(m_rtGameRect,FALSE);//重绘游戏区域，是否擦除背景，引起屏幕闪烁更新
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

/*判断选择的一对图片是否为同种图片
bool CGameDlg::IsLink()
{
	if (m_anMap[m_ptSelFirst.y][m_ptSelFirst.x]== m_anMap[m_ptSelSec.y][m_ptSelSec.x])
	{
		//两次选中的为同一种
		return true;
	}
	return false;
}*/

/*
*///绘制选择的相同的两个点之间的连线（中心绘制）
void  CGameDlg::DrawTipLine(Vertex avPath[8],int nVexnum)
{
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));//设置画笔
	CPen* poldPen = dc.SelectObject(&penLine);//将画笔选入dc
	//绘制连接直线线起点和终点

	for (int i = 0; i < nVexnum-1; i++)
	{
		dc.MoveTo(m_ptGameTop.x + avPath[i].col * m_sizeElement.cx + m_sizeElement.cx / 2,
			m_ptGameTop.y + avPath[i].row * m_sizeElement.cy + m_sizeElement.cy / 2);
		dc.LineTo(m_ptGameTop.x + avPath[i+1].col * m_sizeElement.cx + m_sizeElement.cx / 2,
			m_ptGameTop.y + avPath[i+1].row * m_sizeElement.cy + m_sizeElement.cy / 2);
	}

	dc.SelectObject(poldPen);
}