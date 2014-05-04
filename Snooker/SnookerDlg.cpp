
// SnookerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Snooker.h"
#include "SnookerDlg.h"
#include "afxdialogex.h"
#include "Table.h"
#include <time.h>
#include "mmsystem.h"  //����ͷ�ļ�
#pragma comment(lib, "winmm.lib")  //����lib

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static void PASCAL TimeEventProc(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2);
static UINT calcTimerId;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSnookerDlg �Ի���



CSnookerDlg::CSnookerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSnookerDlg::IDD, pParent)
	, m_nDrawWidth(0)
	, m_nDrawHeight(0)
	, m_nDisplayWidth(0)
	, m_nDisplayHeight(0)
	, m_dPixelPerM(0)
	, m_nX(0)
	, m_nY(0)
	, m_nDrawTimesOfDisplay(0)
	, m_Game(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSnookerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSnookerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CSnookerDlg ��Ϣ�������

BOOL CSnookerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	float scale;
	scale = Table::STD_HEIGHT / Table::STD_WIDTH;
	CRect rcCanvasClient;
	GetDlgItem(IDC_CANVAS)->GetClientRect(rcCanvasClient);
    m_nDisplayWidth = rcCanvasClient.Width();
    m_nDisplayHeight = m_nDisplayWidth * scale;
    m_nX = 0;
    m_nY = (rcCanvasClient.Height() - m_nDisplayHeight) / 2;
    if (m_nDisplayHeight > rcCanvasClient.Height())
	{
		m_nDisplayHeight = rcCanvasClient.Height();
		m_nDisplayWidth = m_nDisplayHeight / scale;
		m_nX = (rcCanvasClient.Width() - m_nDisplayWidth) / 2;
		m_nY = 0;
    }
	m_nDrawTimesOfDisplay = 4;
	m_nDrawHeight = m_nDisplayHeight * m_nDrawTimesOfDisplay;
	m_nDrawWidth = m_nDisplayWidth * m_nDrawTimesOfDisplay;
	m_dPixelPerM = m_nDrawWidth / Table::STD_WIDTH;

	m_dcMem.CreateCompatibleDC(NULL);
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(
		GetDlgItem(IDC_CANVAS)->GetDC(), m_nDrawWidth, m_nDrawHeight);
	m_dcMem.SelectObject(memBitmap);

	m_Game.InitBalls();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSnookerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSnookerDlg::OnPaint()
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
		DrawFrame();
		CDC* pDc = GetDlgItem(IDC_CANVAS)->GetDC();
		pDc->SetStretchBltMode(HALFTONE);
	//	SetBrushOrgEx(*pDc, 0, 0, NULL);
		pDc->StretchBlt(m_nX, m_nY, m_nDisplayWidth, m_nDisplayHeight,
			&m_dcMem, 0, 0, m_nDrawWidth, m_nDrawHeight, SRCCOPY);
	//	pDc->BitBlt(m_nX, m_nY, m_nDisplayWidth, m_nDisplayHeight,
	//		&m_dcMem, 0, 0, SRCCOPY);
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSnookerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSnookerDlg::DrawFrame(void)
{
	static const COLORREF ballColor[SnookerGame::BALL_COUNT] = {
		RGB(255, 255, 255), RGB(255, 255, 0), RGB(0, 255, 0),
		RGB(165, 42, 42), RGB(0, 0, 255), RGB(255, 192, 203),
		RGB(0, 0, 0),
		RGB(255, 0, 0), RGB(255, 0, 0), RGB(255, 0, 0),
		RGB(255, 0, 0), RGB(255, 0, 0), RGB(255, 0, 0),
		RGB(255, 0, 0), RGB(255, 0, 0), RGB(255, 0, 0),
		RGB(255, 0, 0), RGB(255, 0, 0), RGB(255, 0, 0),
		RGB(255, 0, 0), RGB(255, 0, 0), RGB(255, 0, 0)};
	static const CBrush whiteBrush = CBrush(RGB(255, 255, 255));
	static const CBrush brushs[8] = {
		CBrush(ballColor[0]), CBrush(ballColor[1]),
		CBrush(ballColor[2]), CBrush(ballColor[3]),
		CBrush(ballColor[4]), CBrush(ballColor[5]),
		CBrush(ballColor[6]), CBrush(ballColor[7])};
	const double pixelInRadius = Ball::STD_RADIUS * m_dPixelPerM;
	
//	clock_t start_time=clock();

	m_dcMem.SelectObject(whiteBrush);
	m_dcMem.Rectangle(0, 0, m_nDrawWidth, m_nDrawHeight);

	for (int i = 0; i < 8; i++)
	{
		m_dcMem.SelectObject(brushs[i]);
		m_dcMem.Ellipse(m_Game.balls[i]->x * m_dPixelPerM - pixelInRadius,
						m_Game.balls[i]->y * m_dPixelPerM - pixelInRadius,
						m_Game.balls[i]->x * m_dPixelPerM + pixelInRadius,
						m_Game.balls[i]->y * m_dPixelPerM + pixelInRadius);
	}
	for (int i = 8; i < SnookerGame::BALL_COUNT; i++)
	{
		m_dcMem.Ellipse(m_Game.balls[i]->x * m_dPixelPerM - pixelInRadius,
						m_Game.balls[i]->y * m_dPixelPerM - pixelInRadius,
						m_Game.balls[i]->x * m_dPixelPerM + pixelInRadius,
						m_Game.balls[i]->y * m_dPixelPerM + pixelInRadius);
	}

/*	clock_t end_time=clock();
	CString str;
	str.Format(_T("Running time is: %dms"), (end_time-start_time)/CLOCKS_PER_SEC*1000);
	MessageBox(str);*/
}

void CSnookerDlg::onBallsStop()
{
}

void CSnookerDlg::setTimer(int ms)
{
	calcTimerId = timeSetEvent(ms, ms, TimeEventProc, (DWORD)this, TIME_PERIODIC);
}

void CSnookerDlg::killTimer()
{
	timeKillEvent(calcTimerId);
}

static void PASCAL TimeEventProc(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dwl, DWORD dw2)
{
	if (wTimerID == calcTimerId)
	{
		((CSnookerDlg*)dwUser)->m_Game.onTimer();
	}
}