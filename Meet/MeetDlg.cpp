
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
#define ON_PHONENUMBER_GET_SUCCESS 0xE8000001
#define ON_CHECKCODE_SEND_SUCCESS 0xE8000002
#define ON_VIRYFICODE_GET_SUCCESS 0xE8000003



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


void CMeetDlg::OnBnClickedButtonStart()
{
	CreateThread(0,0,(LPTHREAD_START_ROUTINE)ThreadGetPhone,(LPVOID)CWnd::m_hWnd,0,0);
}
void CMeetDlg::ThreadGetPhone(void* params)
{
	ShortMassage vManager;
	if(vManager.Login())
	{
		std::string phone=vManager.GetAPhoneNumber();
		if(phone!="")
		::SendMessage((HWND)params,MY_NOTIFICATION,(WPARAM)ON_PHONENUMBER_GET_SUCCESS,(LPARAM)phone.c_str());
	}
}
void CMeetDlg::ThreadSendCheckCodeRequest(void* params)
{

}
void CMeetDlg::ThreadGetVirifyNumber(void* params)
{

}
void CMeetDlg::ThreadCheckVerifyNumber(void* params)
{

}
LRESULT CMeetDlg::OnNotification(WPARAM wParam, LPARAM lParam)
{
	int vResult=true;
	int vMSGTYPE=wParam;
	if(vMSGTYPE==ON_PHONENUMBER_GET_SUCCESS)
	{
		CreateThread(0,0,(LPTHREAD_START_ROUTINE)ThreadSendCheckCodeRequest,(LPVOID)CWnd::m_hWnd,0,0);//���������ʺ���Ϣ
		vResult=FALSE;
	}
	else if(vMSGTYPE==ON_VIRYFICODE_GET_SUCCESS)
	{
		char* phone=(char*)lParam;
		CreateThread(0,0,(LPTHREAD_START_ROUTINE)GetVirifyCodeThread,phone,0,0);
		vResult=FALSE;
	}
	else if(vMSGTYPE==ON_CHECKCODE_SEND_SUCCESS)
	{
		vResult=FALSE;
	}
	return vResult;
}