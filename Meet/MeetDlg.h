
// MeetDlg.h : 头文件
//

#pragma once

#define  MY_NOTIFICATION WM_USER+132
// CMeetDlg 对话框
class CMeetDlg : public CDialogEx
{
// 构造
public:
	CMeetDlg(CWnd* pParent = NULL);	// 标准构造函数
	static void GetPhoneNumberThread(void* params);
	static void GetVirifyCodeThread(void* params);
// 对话框数据
	enum { IDD = IDD_MEET_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	afx_msg LRESULT OnNotification(WPARAM wParam, LPARAM lParam);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
};
