// CHelpDialog.cpp: 实现文件
//

#include "pch.h"
#include "test3.h"
#include "CHelpDialog.h"
#include "afxdialogex.h"


// CHelpDialog 对话框

IMPLEMENT_DYNAMIC(CHelpDialog, CDialogEx)

CHelpDialog::CHelpDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDC_DIALOG_HELP, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//星星图标

}

CHelpDialog::~CHelpDialog()
{
}

void CHelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CHelpDialog 消息处理程序


BOOL CHelpDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	
	SetIcon(m_hIcon, TRUE);  //图标
	SetIcon(m_hIcon, FALSE);  

	CClientDC dc(this);
	HANDLE hBmpHelp = ::LoadImage(NULL, _T("thame\\picture\\basic_help.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	m_dcHelp.CreateCompatibleDC(&dc);//创建与视频内容兼容的内存DC
	m_dcHelp.SelectObject(hBmpHelp);//将位图资源选入DC


	//帮助图片显示区域
	CRect dlgRect;
	GetWindowRect(dlgRect);
	m_rtHelp.left = 0;
	m_rtHelp.top = 0;
	m_rtHelp.bottom = dlgRect.Height()-100 ;
	m_rtHelp.right = dlgRect.Width();
	

	//创建内存DC大小
	CRect rtClient;
	this->GetWindowRect(&rtClient);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, rtClient.Width(), rtClient.Height());
	m_dcMem.SelectObject(&bmpMem);


	
	
	m_dcMem.BitBlt(0, 0, rtClient.Width(), rtClient.Height(), NULL, 0, 0, WHITENESS);//绘制白色背景
	m_dcMem.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, 0, SRCCOPY);//帮助图片

	//绘制帮助信
	UpdateHelp(0);

	//设置滚动条范围
	CBitmap bmpHelp;
	bmpHelp.Attach(hBmpHelp);
	BITMAP bmpInfo;
	bmpHelp.GetBitmap(&bmpInfo);

	//设置滚动条的范围
	((CScrollBar*)this->GetDlgItem(IDC_SCROLLBAR1))->SetScrollRange(0, bmpInfo.bmHeight);
	


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CHelpDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()


	//绘制背景图片
	dc.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcMem, 0, 0, SRCCOPY);

}


void CHelpDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int pos = pScrollBar->GetScrollPos();
	int nMinPos;
	int nMaxPos;
	pScrollBar->GetScrollRange(&nMinPos, &nMaxPos);    //得到滚动条的范围

	switch (nSBCode)
	{
	case SB_LINEUP: //点击向上按钮
		pos -= 1;
		break;
	case SB_LINEDOWN: //点击向下按钮
		pos += 1;
		break;
	case SB_PAGEUP: //向上翻页
		pos -= 10;
		break;
	case SB_PAGEDOWN: //向下翻页
		pos += 10;
		break;
	case SB_TOP: //顶部
		pos = nMinPos;
		break;
	case SB_BOTTOM: //底部
		pos = nMaxPos;
		break;
	case SB_THUMBPOSITION: //点击在滑块上
		pos = nPos;
		break;
	default:
		break;
	}

	//设置滚动条当前点的值
	pScrollBar->SetScrollPos(pos, TRUE);
	//更新帮助信息
	UpdateHelp(pos);

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CHelpDialog::UpdateHelp(int nPos)
{
	//将重绘区，绘制成白色
	m_dcMem.BitBlt(0,0, m_rtHelp.Width(),m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	//绘制当前点的帮助信息
	m_dcMem.BitBlt(0,0, m_rtHelp.Width(),m_rtHelp.Height(), &m_dcHelp, 0, nPos, SRCCOPY);
	InvalidateRect(m_rtHelp,FALSE);
}
