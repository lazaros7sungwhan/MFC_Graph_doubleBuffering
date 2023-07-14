#pragma once
#include <afxwin.h>
class displaywin2 : public CWnd
{
    DECLARE_DYNAMIC(displaywin2)
    public:
		int m_grid_move_count,
			SubGrid_Count_per_MainGrid,
			MainGrid_Count,
			m_data_index,
			m_data_count,
			m_scroll_index,
			m_max,m_min, m_current_degree;
		double* mp_data;

		double GetCurrentData();

		void setScaleRange(int paramMax, int paraMin);
		void OnDrawImage();


    displaywin2();
    virtual ~displaywin2();
    DECLARE_MESSAGE_MAP()
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

