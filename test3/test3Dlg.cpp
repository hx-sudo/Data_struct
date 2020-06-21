
// test3Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "test3.h"
#include "test3Dlg.h"
#include "afxdialogex.h"
#include "CGameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
*/


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

/*
// Ctest3Dlg 对话框的函数编写
*/
Ctest3Dlg::Ctest3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//星星图标
}//构造函数

void Ctest3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Ctest3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON_BASE2, &Ctest3Dlg::OnBnClickedButton2)
//	ON_BN_CLICKED(IDC_BUTTON_BASE1, &Ctest3Dlg::OnClickedButtonBase1)
ON_BN_CLICKED(IDC_BUTTON_BASE1, &Ctest3Dlg::OnClickedButtonBase1)
ON_BN_CLICKED(IDC_BUTTON_BASE2, &Ctest3Dlg::OnBnClickedButtonBase2)
END_MESSAGE_MAP()


// Ctest3Dlg 消息处理程序，对话框初始化
BOOL Ctest3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitBackground();//初始化背景



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Ctest3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

/*
操作系统显示对话框窗口发送wm-paint消息
-》到应用程序-》对话框消息队列-》onpaint在视频内存中绘制窗口界面
*/
//收到wmpaint消息，绘制对话框
void Ctest3Dlg::OnPaint()
{
	if (IsIconic())
	{

		//cdc设备环境对象类，类似画布
		CPaintDC dc(this); //cpaintdc是cdc子类，响应wmpaint消息的dc， 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
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
		MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
		CenterWindow();//剧中显示



		//创建cpaintdc对象,cdc画布子类
		CPaintDC dc(this);

		/*
		gdi（图形设备界面，管理win程序所有图形输出）绘制欢迎字
		通过cpaintdc获取视频内存dc（DC设备环境描述表，应用程序与输出设备之间的桥梁），
		字体选入dc中，通过dc.textout绘制显示出文字
		
		*/
		//创建字体
		CFont font;
		font.CreatePointFont(200,_T("Courier New"));
		CFont* oldFont;
		oldFont = dc.SelectObject(&font);//将字体选入dc中
		//绘制欢迎语
		CString strText = _T("Welcome");
		//获取区大小
		CRect rect;
		GetClientRect(&rect);
		//获取字符串宽高，居中显示
		CSize size;
		size = dc.GetTextExtent(strText, strText.GetLength());
		int x = (rect.Width() - size.cx) / 2;
		int y = (rect.Height() - size.cy) / 2;
		

		/*
		绘制背景图片
		从位图内存中拷贝到视频内存，进行显示
		背景图片和对话框大小对应的800x600像素
		*/
		dc.BitBlt(0, 0, 800 , 600 , &m_dcMem, 0, 0, SRCCOPY);//从位图内存拷贝到视频内存，显进行显示
		dc.TextOut(x, y, strText);//显示welcome内容，在背景图的上面


		CDialogEx::OnPaint();
	}
}

/*主界面//初始化背景
位图加载静态背景不可边loadbitmap，动态背景可变loadimagew
*/
void Ctest3Dlg::InitBackground()
{
	/*
	gdi绘图
	创建位图cbitmap，将位图加载如内存dc中
	位图文件-》位图对象->位图内存dc（释放位图对象，调用onpaint时直接从内存dc中调用数据，位图只用读取一次，提高运行效率）
	（-》视图dc-》显示器）
	*/
	//加载位图
	CBitmap bmpMain;
	bmpMain.LoadBitmap(IDB_NAME_BG);//背景图片
	//创建兼容dc
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	//将为图选进dc中
	m_dcMem.SelectObject(&bmpMain);

}



//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Ctest3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void Ctest3Dlg::OnBnClickedButton2()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


//void Ctest3Dlg::OnClickedButtonBase1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}

/*
基本模式，调用domodel函数创建显示基本游戏对话框（模态：只有当前界面可点击和非模态）
*/
void Ctest3Dlg::OnClickedButtonBase1()
{
	this->ShowWindow(SW_HIDE);//隐藏主界面
	CGameDlg dlg;
	dlg.DoModal();//跳转到基本模式，模式创建并显示基本模式模态对话框
	this->ShowWindow(SW_SHOW);
}


void Ctest3Dlg::OnBnClickedButtonBase2()
{
	// TODO: 在此添加控件通知处理程序代码
}

/*
WM_LBUTTONUP左键释放消息响应函数
*/
void CAboutDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonUp(nFlags, point);
}
