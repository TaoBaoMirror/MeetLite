
// MeetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Meet.h"
#include "MeetDlg.h"
#include "afxdialogex.h"
#include "ShortMassage.h"
#include"commondef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMeetDlg 对话框

#define ON_PHONE_NUMBER_GET_SUCCESS 0xE8000001



CMeetDlg::CMeetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMeetDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMeetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMeetDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CMeetDlg::OnBnClickedButtonStart)
	ON_MESSAGE(MY_NOTIFICATION,OnNotification)
END_MESSAGE_MAP()


// CMeetDlg 消息处理程序

BOOL CMeetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMeetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMeetDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMeetDlg::GetPhoneNumberThread(void* params)
{
	ThreadPram *pThreadPrams=(ThreadPram*)params;
	ShortMassage vManager;
	if(vManager.Login())
	{
		//while(true)
		{
			std::string phone=vManager.GetAPhoneNumber();
			::SendMessage(pThreadPrams->mWND,MY_NOTIFICATION,(WPARAM)ON_PHONE_NUMBER_GET_SUCCESS,(LPARAM)phone.c_str());
		}
	}
	GlobalFree(params);
}
void CMeetDlg::GetVirifyCodeThread(void* params)
{
	int cnt=0;
	ShortMassage vManager;
	while(cnt<5)
	{
		Sleep(10000);
		vManager.GetVeryfyNumberForPhone((char*)params);
	}
}

void CMeetDlg::OnBnClickedButtonStart()
{
	ThreadPram *pThreadPrams=(ThreadPram*)GlobalAlloc(0,sizeof(ThreadPram));
	pThreadPrams->mWND=GetSafeHwnd();
	CreateThread(0,0,(LPTHREAD_START_ROUTINE)GetPhoneNumberThread,(LPVOID)pThreadPrams,0,0);
}
LRESULT CMeetDlg::OnNotification(WPARAM wParam, LPARAM lParam)
{
	int vResult=true;
	int vMSGTYPE=wParam;
	if(vMSGTYPE==ON_PHONE_NUMBER_GET_SUCCESS)
	{
		char* phone=(char*)lParam;
		CreateThread(0,0,(LPTHREAD_START_ROUTINE)GetVirifyCodeThread,phone,0,0);
		vResult=FALSE;
	}
	return vResult;
}