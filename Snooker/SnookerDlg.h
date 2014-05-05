
// SnookerDlg.h : ͷ�ļ�
//

#pragma once
#include "snookergame.h"
#include "afxwin.h"
#include "SnookerSurface.h"


// CSnookerDlg �Ի���
class CSnookerDlg : public CDialogEx, public SnookerSurface
{
// ����
public:
	CSnookerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SNOOKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual void onBallsStop();
	virtual void setTimer(int ms);
	virtual void killTimer();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	void SetDrawTimer(void);
	void KillDrawTimer(void);
	int m_nDrawIntervalTime;
	void StretchToCanvas(void);
	afx_msg void OnBnClickedWiznext();
	afx_msg void OnBnClickedButtonTestStop();
	afx_msg void OnBnClickedButtonTest1step();
	afx_msg void OnBnClickedButtonTestInit();
//	unsigned int m_uTestNSteps;
	afx_msg void OnBnClickedButtonTestNSteps();
	UINT m_uRunNSteps;
	afx_msg void OnBnClickedButtonTestHit();
	double m_dTestSpeedX;
	double m_dTestSpeedY;
};
