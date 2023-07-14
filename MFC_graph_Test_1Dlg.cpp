
// MFC_graph_Test_1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_graph_Test_1.h"
#include "MFC_graph_Test_1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


CMFCgraphTest1Dlg::CMFCgraphTest1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_GRAPH_TEST_1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCgraphTest1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, button1);
	DDX_Control(pDX, IDC_EDIT3, edit3);
}

BEGIN_MESSAGE_MAP(CMFCgraphTest1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCgraphTest1Dlg::OnBnClickedButton1)
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CMFCgraphTest1Dlg 메시지 처리기

BOOL CMFCgraphTest1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	//TODO: 여기에 추가 초기화 작업을 추가합니다.
	CRect r;
	GetDlgItem(IDC_Graph1)->GetWindowRect(r);
	ScreenToClient(r);
	m_displaywin1.CreateEx(WS_EX_CLIENTEDGE, NULL,NULL, WS_VISIBLE| WS_CHILD, r, this,1010);

	GetDlgItem(IDC_EDIT1)->SetWindowTextW(_T("-100"));
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(_T("100"));

	/*CRect rect2;
	GetClientRect(&rect2);
	CString str;
	str.Format(_T("%d, %d, %d, %d"), rect2.left, rect2.right, rect2.top, rect2.bottom);
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(str);
	*/return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCgraphTest1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCgraphTest1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCgraphTest1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCgraphTest1Dlg::OnBnClickedButton1(){
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(str);
	min_data=atof((CStringA)str);
	GetDlgItem(IDC_EDIT2)->GetWindowTextW(str);
	max_data = atof((CStringA)str);
	::SendMessage(m_displaywin1, KSW_CUSTOM1, 0, 0);
}


void CMFCgraphTest1Dlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	lpMMI->ptMinTrackSize.x = 890;
	lpMMI->ptMinTrackSize.y = 589;
	lpMMI->ptMaxTrackSize.x = 890;
	lpMMI->ptMaxTrackSize.y = 589;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
