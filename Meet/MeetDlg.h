
// MeetDlg.h : ͷ�ļ�
//

#pragma once

#define  MY_NOTIFICATION WM_USER+132
// CMeetDlg �Ի���
class CMeetDlg : public CDialogEx
{
// ����
public:
	CMeetDlg(CWnd* pParent = NULL);	// ��׼���캯��
	static void ThreadGetPhone(void* params);
	static void ThreadSendCheckCodeRequest(void* params);
	static void ThreadGetVirifyNumber(void* params);
	static void ThreadCheckVerifyNumber(void* params);
// �Ի�������
	enum { IDD = IDD_MEET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	afx_msg LRESULT OnNotification(WPARAM wParam, LPARAM lParam);
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
};
