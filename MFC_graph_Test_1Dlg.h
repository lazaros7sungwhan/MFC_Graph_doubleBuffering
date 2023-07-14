
// MFC_graph_Test_1Dlg.h: 헤더 파일
//
#include "displaywin1.h"
#include "displaywin2.h"
#pragma once
//#define KSW_CUSTOM1 (WM_USER+1)

// CMFCgraphTest1Dlg 대화 상자
class CMFCgraphTest1Dlg : public CDialogEx
{
public:
	CMFCgraphTest1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	displaywin1 m_displaywin1;
	double min_data=2, max_data;
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_GRAPH_TEST_1_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton button1;
protected:
public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	CEdit edit3;
};
