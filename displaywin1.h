#pragma once
#include <afxwin.h>
#include "displaywin2.h"
#define KSW_CUSTOM1 (WM_USER+1)

class displaywin1 : public CWnd
{
    DECLARE_DYNAMIC(displaywin1)

public:
    displaywin1();
    COLORREF m_margin_grid_color; // À±°û ±×¸®µå Ä®¶ó ¼³Á¤
    displaywin2 m_displaywin2;
    int min_data_indisp1=-100, max_data_indisp1=100;
    CFont g_default_font;

    virtual ~displaywin1();
    void setscalrange(int paramMax, int paramMin);

    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnPaint();
protected:
    afx_msg LRESULT OnKswCustom1(WPARAM wParam, LPARAM lParam);
};

