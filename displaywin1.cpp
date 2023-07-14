#include "pch.h"
#include "displaywin1.h"
#include "MFC_graph_Test_1Dlg.h"

double i = 0;
CString str;
IMPLEMENT_DYNAMIC(displaywin1, CWnd)
displaywin1::displaywin1() { m_margin_grid_color = RGB(0,255,0); }
displaywin1::~displaywin1(){}

BEGIN_MESSAGE_MAP(displaywin1, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_MESSAGE(KSW_CUSTOM1, &displaywin1::OnKswCustom1)
END_MESSAGE_MAP()

int displaywin1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)return -1;
	CRect r;
	GetClientRect(r);
	m_displaywin2.CreateEx(WS_EX_CLIENTEDGE, NULL, NULL, WS_VISIBLE | WS_CHILD, CRect(70,r.top+20,r.right-20,r.bottom-50), this, 2020);
	return 0;
}

void displaywin1::OnPaint()
{
	CPaintDC dc(this); 
	CRect r,graphrect;
	GetClientRect(r);
	dc.FillSolidRect(r, RGB(100, 100, 100));

	// 마진 그리드 그리기
	CPen main_grid_pen(PS_SOLID, 5,m_margin_grid_color);
	CPen* p_old_pen = dc.SelectObject(&main_grid_pen);
	
	dc.MoveTo(r.right - 20, r.top + 20);
	dc.LineTo(r.right - 20, r.bottom - 50);

	dc.MoveTo(r.left + 75, r.bottom - 50);
	dc.LineTo(r.right - 20, r.bottom - 50);

	// 현재 값 나오게 하기 
	CFont* p_Old_Font = dc.SelectObject(&g_default_font);
	int old_mode = dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	CString str;
	str.Format(_T("CurrentData: %.2f"), 12.34);
	dc.TextOutW(10, r.bottom - 30, str);

	m_displaywin2.GetClientRect(graphrect);
	//ScreenToClient(graphrect);
	double step = graphrect.Height() / 10.0;
	double value_step = (max_data_indisp1 - min_data_indisp1) / 10.0;

	int font_height = dc.GetTextExtent(_T("A")).cy;

	for (int i=0; i < 11; i++)
	{
		str.Format(_T("%6.2f"), max_data_indisp1 - value_step * i);
		dc.TextOutW(graphrect.left+10, int((graphrect.top+20) + i * step) - font_height / 2, str); // 옆 가이드 라인의 위치 선정
	}
	dc.SetBkMode(old_mode);
	dc.SelectObject(p_Old_Font);
	dc.SelectObject(p_old_pen);
	main_grid_pen.DeleteObject();
}

afx_msg LRESULT displaywin1::OnKswCustom1(WPARAM wParam, LPARAM lParam)
{
	CMFCgraphTest1Dlg* pDlg = (CMFCgraphTest1Dlg*)AfxGetMainWnd();
	min_data_indisp1 = pDlg->min_data;
	max_data_indisp1 = pDlg->max_data;
	Invalidate(false);
	setscalrange(pDlg->max_data, pDlg->min_data);
	return 0;
}

void displaywin1::setscalrange(int paramMax, int paramMin) {
	max_data_indisp1 = paramMax;
	min_data_indisp1 = paramMin;
	MessageBox(_T("setting"));
}