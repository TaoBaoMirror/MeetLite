
// MeetDlg.cpp : ʵ���ļ�
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


// CMeetDlg �Ի���

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


// CMeetDlg ��Ϣ�������

BOOL CMeetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMeetDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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