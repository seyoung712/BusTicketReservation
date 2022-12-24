
// BusTicket3Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "BusTicket3.h"
#include "BusTicket3Dlg.h"
#include "afxdialogex.h"
#include <windows.h> //sleep*

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
public:
	afx_msg void OnBnClickedButton1();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CBusTicket3Dlg 대화 상자



CBusTicket3Dlg::CBusTicket3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BUSTICKET3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	val = 50; //멤버변수 초기화*
}

//변수추가**
void CBusTicket3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, btime); //시간대 ComboBox
	DDX_Text(pDX, IDC_EDIT2, result); //요금 EditControl
	DDX_Control(pDX, IDC_RADIO1, b_des); //목적지 RadioButton
	DDX_Text(pDX, IDC_EDIT3, b_call); //연락처 EditControl
}

BEGIN_MESSAGE_MAP(CBusTicket3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CBusTicket3Dlg::OnEnChangeEdit1)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CBusTicket3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBusTicket3Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CBusTicket3Dlg::OnBnClickedButton3)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CBusTicket3Dlg 메시지 처리기

BOOL CBusTicket3Dlg::OnInitDialog()
{
	//*
	static CFont VDCFont;

	VDCFont.CreateFont(40, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, 0, 0, 0, 0, 0, 0, _T(""));

	CDialogEx::OnInitDialog();

	//*
	CRect rect;
	screen.top = 0;
	screen.left = 0;
	screen.bottom = ::GetSystemMetrics(SM_CYSCREEN);
	screen.right = ::GetSystemMetrics(SM_CXSCREEN);

	htimer = SetTimer(1, 1000, NULL);

	GetWindowRect(rect);
	vsize = rect.Width();
	hsize = rect.Height();

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

	// TODO: 여기에 추가 초기화 작업을 추가합니다.**

	btime.ResetContent();
	btime.AddString(_T("4시00분"));
	btime.AddString(_T("4시30분"));
	btime.AddString(_T("5시00분"));
	btime.AddString(_T("5시30분"));
	btime.AddString(_T("6시00분"));
	btime.AddString(_T("6시30분"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CBusTicket3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBusTicket3Dlg::OnPaint()
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
		/*int rnd;
		srand(time(NULL)); //rand 함수*/
		CClientDC dc(this); //화면에 dc정보 얻어오기(객체생성)*

		//타이머 설정
		CString str;
			//str2;
		str.Format(_T("%d"), val); //자료형 반환
		dc.TextOutW(520, 5, str);
		
		/*
		str2 = (LPSTR)buf; //파일입출력 자료
		dc.TextOutW(300, 50, str2);
		*/



		/*
		int i = 1, count = 0;
		
		image1.Load(_T("./res/back1.jpg"));
		image2.Load(_T("./res/back2.jpg"));
		image3.Load(_T("./res/back3.jpg"));
		//image1.BitBlt(dc.m_hDC, 0, 0);
		
		
		while (count <= 30){
			//rnd = (rand() % 3) + 1; //1~3사이의 난수 생성
			
			switch (i) {
			case 1:
				//
				//image1.Load(_T("./res/back1.jpg"));
				image1.BitBlt(dc.m_hDC, 0, 0);
				Sleep(1000);
				break;
			case 2:
				//Invalidate();
				//image2.Load(_T("./res/back2.jpg"));
				image2.BitBlt(dc.m_hDC, 0, 0);
				Sleep(1000);
				break;
			case 3:
				//Invalidate();
				//image3.Load(_T("./res/back3.jpg"));
				image3.BitBlt(dc.m_hDC, 0, 0);
				Sleep(1000);
				i = 1;
				break;
			}
			i++; count++;
		}
		*/

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CBusTicket3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBusTicket3Dlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CBusTicket3Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	SetTimer(1, 1000, NULL); //1초 간격의 타이머 생성*

	CDialogEx::OnLButtonDown(nFlags, point);
}

//타이머**
void CBusTicket3Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Invalidate();
	val--;

	if (val == 10) {
		MessageBox(_T("10초 남았습니다."));
		return;
	}
	if (val == 0) {
		KillTimer(1); //타이머 종료
		MessageBox(_T("시간이 종료되었습니다. \n종료 후 다시 입력해주세요."));
		return;
	}
	CTime gct = CTime::GetCurrentTime();
	CString strDATE;
	CString strTIME;

	strDATE.Format(_T("%d - %d - %d"), gct.GetYear(), gct.GetMonth(), gct.GetDay());
	GetDlgItem(IDC_STATIC_DATE)->SetWindowText((LPCTSTR)strDATE);

	strTIME.Format(_T("%d : %d : %d"), gct.GetHour(), gct.GetMinute(), gct.GetSecond());
	GetDlgItem(IDC_STATIC_TIME)->SetWindowText((LPCTSTR)strTIME);

	Invalidate();

	CDialogEx::OnTimer(nIDEvent);
}


void CAboutDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}

//금액확인*
void CBusTicket3Dlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	UpdateData(true);

	int price = 0; //요금 초기화

	CButton* r1 = (CButton*)GetDlgItem(IDC_RADIO1);
	CButton* r2 = (CButton*)GetDlgItem(IDC_RADIO2);
	CButton* r3 = (CButton*)GetDlgItem(IDC_RADIO3);
	CButton* r4 = (CButton*)GetDlgItem(IDC_RADIO4);
	CButton* r5 = (CButton*)GetDlgItem(IDC_RADIO5);
	CButton* r6 = (CButton*)GetDlgItem(IDC_RADIO6);

	//라디오버튼 -> elseif
	if (r1->GetCheck()) {
		price = price + 6000;
	}
	else if (r2->GetCheck()) {
		price = price + 5800;
	}
	else if (r3->GetCheck()) {
		price = price + 6300;
	}
	else if (r4->GetCheck()) {
		price = price + 5300;
	}
	else if (r5->GetCheck()) {
		price = price + 5500;
	}
	else {
		price = price + 5500;
	}
		
	CString str;
	str.Format(_T("%d원"), price);
	result.Empty();
	result.Append(str);
	UpdateData(false);
	
}

//예약하기
void CBusTicket3Dlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	b_call.IsEmpty();

	CString str;
	str.Append(b_call);
	str.Append(_T(" 로 알림드립니다."));
	MessageBox(str);
	UpdateData(false);

	
	CFile file;
	file.Open(_T("test.txt"), CFile::modeCreate | CFile::modeReadWrite); //(파일명, 생성과 읽기쓰기)
	/*
	int str2;
	str2.Format(_T("%d"), b_call);
	char* userCall = str2;

	file.Write(buf, sizeof(buf));
	file.Read(buf, sizeof(buf));

	Invalidate();
	file.Close();
	*/
	
}


void CBusTicket3Dlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

//색상 변경**
HBRUSH CBusTicket3Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_1) {
		pDC->SetTextColor(RGB(255, 0, 0));
	} 

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
