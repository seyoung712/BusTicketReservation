
// BusTicket3Dlg.h: 헤더 파일
//

#pragma once


// CBusTicket3Dlg 대화 상자
class CBusTicket3Dlg : public CDialogEx
{
// 생성입니다.
public:
	int val; //타이머 변수*
	CBusTicket3Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CRect screen;
	int vsize, hsize;
	UINT htimer;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BUSTICKET3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	CImage image1, image2, image3; //이미지 파일*

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CComboBox btime;
	CString result;
	afx_msg void OnBnClickedButton1();
	CButton b_des;
	CString b_call;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	char buf[100]; //파일 입출력 변수
};
