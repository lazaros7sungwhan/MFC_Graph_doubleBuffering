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

int displaywin2::OnCreate(LPCREATESTRUCT lpCreateStruct) // �̰��� ������ �ʱ�ȭ���� �� �������Ѽ��� �� Ÿ�̸Ӽ�����
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

void displaywin2::OnDrawImage()
{
	// Picture Control DC�� ����.
	// IDC_PC_IMAGE�� Picture Control�� Resource ID.
	CPaintDC dc(this);

	// Picture Control ũ�⸦ ��´�.
	CRect r;
	GetClientRect(&r);

	CDC memDC;
	CBitmap* pOldBitmap, bitmap;

	// Picture Control DC�� ȣȯ�Ǵ� ���ο� CDC�� ����. (�ӽ� ����)
	memDC.CreateCompatibleDC(&dc);

	//// Picture Control�� ũ��� ������ ��Ʈ���� ����.
	bitmap.CreateCompatibleBitmap(&dc, r.Width(), r.Height());

	//// �ӽ� ���ۿ��� ��� ������ ��Ʈ���� �����ϸ鼭, ���� ��Ʈ���� ����.
	pOldBitmap = memDC.SelectObject(&bitmap);

	//// �ӽ� ���ۿ� ���������� ä��.
	memDC.PatBlt(0, 0, r.Width(), r.Height(), BLACKNESS);

	// �ӽ� ����(memDC)�� �׸��� ������ ����.
	////////////////////////////////////////////////////////////////////////////////////

	GetClientRect(r);
	memDC.FillSolidRect(r, RGB(255, 255, 255));
	int i = 0;
	//CPen  ���� 
	CPen mainGridPen(PS_DOT, 1, RGB(0, 0, 0)),
		 subGridPen(PS_DOT, 1, (100, 100, 100)),
		 dataLinePen(PS_SOLID, 1, RGB(255, 0, 0));

	//ȭ�� ���� ���� ������ ������.
	double step = r.Width() / MainGrid_Count,
		   dataStep = step / SubGrid_Count_per_MainGrid;

	//	Subgrid�۾� -> mainGrid�۾� -> �� �۾�
	CPen* pOldPen = memDC.SelectObject(&subGridPen); //pOldPen �� ���� ���� �Է½�Ŵ�� ���ÿ� subgridpen�Է�, 
	//selectObject �� �ű��ϰ� ���ο�� ������ ������ �ִ� ���� ����´�.
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
		for (i = 0; i < m_data_index - m_scroll_index + 1; i++) //m_data_index �� �ö󰡰�, m_scroll_index �� �ö󰡼� �ᱹ�� ������ �Ÿ��� ����
		{
			memDC.LineTo(r.right - int(i * dataStep), r.Height() - int(r.Height() * (mp_data[m_data_index - i] - m_min)) / (m_max - m_min)); //�ڷ� �и��������� �׷���� �Ѵ�. x�� ����, y�� ���� ���̸� ����ؼ� �������� ����.. 
		}
	}
	memDC.SelectObject(pOldPen);
	//dataLinePen.DeleteObject();
	//mainGridPen.DeleteObject();
	//subGridPen.DeleteObject();
	////////////////////////////////////////////////////////////////////////////////////

	//// �ӽ� ���۸� Picture Control�� �׸���.
	dc.BitBlt(0, 0, r.Width(), r.Height(), &memDC, 0, 0, SRCCOPY);

	//// ���� ��Ʈ������ �缳��.
	memDC.SelectObject(pOldBitmap);

	//// ������ ���ҽ� ����.
	memDC.DeleteDC();
	bitmap.DeleteObject();
}

BOOL displaywin2::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return FALSE;//CWnd::OnEraseBkgnd(pDC);
}
