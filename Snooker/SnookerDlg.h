
// SnookerDlg.h : 头文件
//

#pragma once
#include "snookergame.h"
#include "afxwin.h"


// CSnookerDlg 对话框
class CSnookerDlg : public CDialogEx
{
// 构造
public:
	CSnookerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SNOOKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void DrawFrame(void);
	int m_nDrawWidth;
	int m_nDrawHeight;
	int m_nDisplayWidth;
	int m_nDisplayHeight;
	double m_dPixelPerM;
	SnookerGame m_Game;
	int m_nX;
	int m_nY;
	CDC m_dcMem;
	int m_nDrawTimesOfDisplay;
};
