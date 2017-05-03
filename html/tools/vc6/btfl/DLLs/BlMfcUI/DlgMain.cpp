// DlgMain.cpp : implementation file
//

#include "stdafx.h"
#include "blmfcui.h"
#include "DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMain dialog


CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMain::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMain)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMain)
	DDX_Control(pDX, IDC_STATIC_MSG, m_StaticDevice);
	DDX_Control(pDX, IDC_STATIC_CLIENT, m_StaticClient);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMain, CDialog)
	//{{AFX_MSG_MAP(CDlgMain)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMain message handlers

LRESULT CDlgMain::WindowProc(UINT m, WPARAM w, LPARAM l) 
{
	static CMyMsg msg(this);
	msg.pl2Do(m,w,l); 
	return CDialog::WindowProc(m, w, l);
}

BOOL CDlgMain::PreTranslateMessage(MSG* pMsg) 
{ 
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
	case WM_KEYUP: 
	case WM_DEADCHAR:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_SYSCHAR:
	case WM_SYSDEADCHAR:
	case WM_CHAR:
		pMsg->hwnd = m_hWnd;
		return FALSE;
	} 
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgMain::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CRect rt; 
	GetClientRect(&rt);
	m_StaticClient.MoveWindow(POS,TOP,rt.Width()/2,rt.Height()-25-TOP);
	m_StaticDevice.MoveWindow(rt.Width()/2+POS,TOP,rt.Width()/2-POS*2,rt.Height()-25-TOP);

	char szText[1000];
	char szDev[296];  
	  
	m_MyDll.OnBlCallLibFun(m_hWnd,BL_WM_INIT,(WPARAM)szDev,(LPARAM)szText);

//	m_StaticClient.SetWindowText(szText);
  	m_StaticDevice.SetWindowText(szDev);
	
	SetTimer(1, 1000, NULL);

	SetWindowText(m_strTitle); 
	
	m_MyStatusBar.OnXdInit(this);
	m_MyToolBar.plInit(this,IDR_TOOLBAR_MAIN);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMain::OnTimer(UINT nIDEvent) 
{ 
	// TODO: Add your message handler code here and/or call default
	m_MyStatusBar.ShowCurrentTime();
//	m_StaticClient.plDraw(); 

	CDialog::OnTimer(nIDEvent);
}
