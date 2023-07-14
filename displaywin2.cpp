#include "pch.h"
#include "displaywin2.h"

IMPLEMENT_DYNAMIC(displaywin2,CWnd)
displaywin2::displaywin2(){
	
	m_grid_move_count = 0;
	
	SubGrid_Count_per_MainGrid = 5;
	MainGrid_Count = 5;
	
	m_data_index = -1;
	m_data_count = 300;
	
	m_scroll_index = 0;
	m_max = 100;
	m_min = -100;

	m_current_degree = 0;
}
displaywin2::~displaywin2(){}
BEGIN_MESSAGE_MAP(displaywin2,CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


void displaywin2::OnPaint()
{
	OnDrawImage();
}

int displaywin2::OnCreate(LPCREATESTRUCT lpCreateStruct) // 이곳은 데이터 초기화선언 및 랜덤씨앗설정 및 타이머설정임
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)return -1;

	mp_data = new double[m_data_count];
	
	for (int i = 0; i < m_data_count; i++)
	{
		mp_data[i] = double(0);
	}

	srand((unsigned)time(NULL));
	SetTimer(1, 1, NULL);

	return 0;
}

double displaywin2::GetCurrentData()
{
	if (m_data_index < 0)return double(0);
	return mp_data[m_data_index];
}

void displaywin2::setScaleRange(int paramMax, int paraMin)
{	
}


void displaywin2::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==1)
	{
		m_current_degree = (m_current_degree + 20) % 360;
		if (m_data_index < m_data_count - 1)
		{
			m_data_index++;
			if (m_data_index >= SubGrid_Count_per_MainGrid * MainGrid_Count + 2)
			{
				m_scroll_index++;
			}
		}
		else {
			memcpy(mp_data, mp_data + 1,sizeof(double )*(m_data_count-1));
		}
		mp_data[m_data_index] = int(tan(m_current_degree * 3.141592 / 180) * ((rand() % 20) + 10)) % 50;
		if (SubGrid_Count_per_MainGrid > 0)
			m_grid_move_count = (m_grid_move_count + 1) % SubGrid_Count_per_MainGrid;
		Invalidate(FALSE);
		//GetParent()->Invalidate(FALSE);
	}
	else CWnd::OnTimer(nIDEvent);
}


void displaywin2::OnDestroy()
{
	KillTimer(1);
	delete[] mp_data;

	CWnd::OnDestroy();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void displaywin2::OnDrawImage()
{
	// Picture Control DC를 생성.
	// IDC_PC_IMAGE는 Picture Control의 Resource ID.
	CPaintDC dc(this);

	// Picture Control 크기를 얻는다.
	CRect r;
	GetClientRect(&r);

	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// Picture Control DC에 호환되는 새로운 CDC를 생성. (임시 버퍼)
	memDC.CreateCompatibleDC(&dc);

	//// Picture Control의 크기와 동일한 비트맵을 생성.
	bitmap.CreateCompatibleBitmap(&dc, r.Width(), r.Height());

	//// 임시 버퍼에서 방금 생성한 비트맵을 선택하면서, 이전 비트맵을 보존.
	pOldBitmap = memDC.SelectObject(&bitmap);

	//// 임시 버퍼에 검은색으로 채움.
	memDC.PatBlt(0, 0, r.Width(), r.Height(), BLACKNESS);

	// 임시 버퍼(memDC)에 그리는 동작을 수행.
	////////////////////////////////////////////////////////////////////////////////////

	GetClientRect(r);
	memDC.FillSolidRect(r, RGB(255, 255, 255));
	int i = 0;
	//CPen  설정 
	CPen mainGridPen(PS_DOT, 1, RGB(0, 0, 0)),
		 subGridPen(PS_DOT, 1, (100, 100, 100)),
		 dataLinePen(PS_SOLID, 1, RGB(255, 0, 0));

	//화면 값에 대해 스텝을 나눈다.
	double step = r.Width() / MainGrid_Count,
		   dataStep = step / SubGrid_Count_per_MainGrid;

	//	Subgrid작업 -> mainGrid작업 -> 값 작업
	CPen* pOldPen = memDC.SelectObject(&subGridPen); //pOldPen 에 기존 값을 입력시킴과 동시에 subgridpen입력, 
	//selectObject 는 신기하게 새로운게 들어오면 기존에 있던 값을 내뱉는다.
	for (i = 0; i * dataStep < r.Width(); i++)
	{
		memDC.MoveTo(int(i * dataStep), 0);
		//if((int(i*dataStep)%(int)step)==0)
		memDC.LineTo(int(i * dataStep), r.bottom);
	}

	memDC.SelectObject(&mainGridPen);

	for (i = 0; i * step < r.Width(); i++)
	{
		memDC.MoveTo(int(i * step), 0);
		memDC.LineTo(int(i * step), r.bottom);
	}

	for (i = 0; i * int((r.Height() * 20 / (m_max - m_min))) < r.Height(); i++)
	{
		memDC.MoveTo(r.left, i * int((r.Height() * 20 / (m_max - m_min))));
		memDC.LineTo(r.right, i * int((r.Height() * 20 / (m_max - m_min))));
	}

	if (m_data_index >= 0)
	{
		memDC.SelectObject(&dataLinePen);

		memDC.MoveTo(r.right, r.Height() - int(r.Height() * (mp_data[m_data_index] - m_min)) / (m_max - m_min));
		for (i = 0; i < m_data_index - m_scroll_index + 1; i++) //m_data_index 도 올라가고, m_scroll_index 도 올라가서 결국은 일정한 거리를 유지
		{
			memDC.LineTo(r.right - int(i * dataStep), r.Height() - int(r.Height() * (mp_data[m_data_index - i] - m_min)) / (m_max - m_min)); //뒤로 밀린구간까지 그려줘야 한다. x는 쉽고, y는 전에 높이를 기억해서 목적지를 설정.. 
		}
	}
	memDC.SelectObject(pOldPen);
	//dataLinePen.DeleteObject();
	//mainGridPen.DeleteObject();
	//subGridPen.DeleteObject();
	////////////////////////////////////////////////////////////////////////////////////

	//// 임시 버퍼를 Picture Control에 그린다.
	dc.BitBlt(0, 0, r.Width(), r.Height(), &memDC, 0, 0, SRCCOPY);

	//// 이전 비트맵으로 재설정.
	memDC.SelectObject(pOldBitmap);

	//// 생성한 리소스 해제.
	memDC.DeleteDC();
	bitmap.DeleteObject();
}

BOOL displaywin2::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return FALSE;//CWnd::OnEraseBkgnd(pDC);
}
