// CGameDlg.cpp: 实现文件
//

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
	m_anMap[4][4] = { 0 };
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
END_MESSAGE_MAP()


// CGameDlg 消息处理程序

/*
基本模式游戏背景
*/
void CGameDlg::InitBackground()
{
	//::调用api,加载图片
	HANDLE bmp = ::LoadImage(NULL,TEXT("thame\\picture\\fruit_bg.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	
	//将位图加载到dc
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	m_dcMem.SelectObject(bmp);//将对象放入位图dc

}

/*虚函数，对话框初始化
*/
BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 设置此对话框的图标。 
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	InitBackground();//初始化背景，将图片加载到内存dc中
	InitElement();//初始化水果图片，将图片加载到内存dc中

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

		/*
		调整窗口大小
		*/
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


	//将位图内存拷贝到视频dc中，显示背景
	dc.BitBlt(0,0,1200,800,&m_dcMem,0,0,SRCCOPY);

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




/*基本模式-开始按钮
*/
void CGameDlg::OnClickedButton1()
{
	/*水果图地图初始化
	*/
	//初始化地图数组
	int anMap[4][4] = {
		2,0,1,3,
		2,2,1,3,
		2,1,0,0,
		1,3,0,3,
	};
	for (int i = 0; i < 4; i++)
	{
		for (int  j = 0; j < 4; j++)
		{
			m_anMap[i][j] = anMap[i][j];
		}
	}

	//像素
	int nLeft = 100;
	int nTop = 100;//原点到游戏区域起始距离
	int nElemW = 40;
	int nElemH = 40;//每个图的长宽

	for (int i = 0; i < 4; i++)//i,y
	{
		for (int j = 0; j < 4; j++)//j,x
		{
			//通过初始化加载的水果图dc
			//逐行逐列从数组，将相应行列编号的图片数据中放到dc中
			//m_dcMem.BitBlt(nLeft+j*nElemW,nTop+i*nElemH,nElemW,nElemH,&m_dcElement,0,m_anMap[i][j]*nElemH,SRCCOPY);
				
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcMask, 0, m_anMap[i][j] * nElemH, SRCPAINT);//与掩码图相或
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH,
				&m_dcElement, 0, m_anMap[i][j] * nElemH, SRCAND);//与原图相或
			/*
			掩码图黑底0白图1与与背景图xx相或-》彩底x白图1
			彩底x白图1与原图白底1彩图x相与-》彩底x彩图x
			*/
		}
	}
	Invalidate(FALSE);			//未能成功显示，客户区无效，invalidate绘制更新部分，进行覆盖

}
