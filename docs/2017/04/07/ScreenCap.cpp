//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：ScreenCap.cpp

	版权：Firebird Software Workroom 保留

	声明：本源程序的版权受《中华人民共和国著作权法》以及其
		  它相关法律和条约的保护。任何有机会得到本源程序的
		  个人和机构，未经作者明确授权，不得将本源程序用于
		  任何商业目的(直接的或间接的)。对于非商业目的的使
		  用 (包括复制、传播、编译和修改)， 原则上没有特别
		  的限制条款，但请在相关文档中说明其来源，并尊重原
		  作者的署名权。

	编写：秦传安(chings)	2000.5

	联络：Tel：(0792)6323086	E_mail：chings@163.net
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#include "fclstd.h"
#include "resource.h"
#include "MainWnd.h"
#include "ScreenCap.h"

//######################################################################
HBITMAP (__stdcall *LoadFromFile)(LPCTSTR);
BOOL (__stdcall *SaveToFile)(HBITMAP,LPCTSTR);
//#######################################################################
CScreenCap::CScreenCap()
{
	m_hInstImage = NULL;
}

CScreenCap::~CScreenCap()
{
}
//#######################################################################
BOOL CScreenCap::InitInstance()
{
	SetRegistryKey("Firebird");//设置注册表主键

	char caption[16];
	lstrcpy(caption,"屏幕捕快");

	m_hInstImage = LoadLibrary("FBImage.dll");
	if(m_hInstImage)
	{
		(FARPROC&)LoadFromFile = GetProcAddress(m_hInstImage,"LoadFromFile");
		(FARPROC&)SaveToFile = GetProcAddress(m_hInstImage,"SaveToFile");
		if(!LoadFromFile || !SaveToFile)
		{
			FreeLibrary(m_hInstImage);
			m_hInstImage = NULL;
		}
	}

	if(m_hInstImage)
	{
		m_dwVersion = 0x00010008;
		lstrcat(caption,"1.8版");
	}
	else
	{
		m_dwVersion = 0;//演示版
		lstrcat(caption,"演示版");
	}

	CMainWnd* pFrame = new CMainWnd();

	//创建主窗口
	if(pFrame->Create(m_hInstance,caption,NULL,NULL) == FALSE)
		return FALSE;

	//设置图标
	HICON hIcon = LoadIcon(m_hInstance,MAKEINTRESOURCE(IDI_MAINICON));
	SendMessage(pFrame->m_hWnd,WM_SETICON,(WPARAM)ICON_SMALL,(LPARAM)hIcon);

	LPAPP_SETINGS pas = pFrame->GetSetings();

	//从注册表中得到窗口初始位置和尺寸的数据
	if(RegGetBinary("Config","WindowPlacement",(LPBYTE)&pFrame->m_WndPlm,sizeof(WINDOWPLACEMENT)))
	{
		if(pas->nStartMode != 0)
			pFrame->m_WndPlm.showCmd = SW_HIDE;
		SetWindowPlacement(pFrame->m_hWnd,&pFrame->m_WndPlm);
	}

	m_pMainWnd = pFrame;

	m_hAccel = LoadAccelerators(m_hInstance,MAKEINTRESOURCE(IDR_MAINFRAME));

	if(pas->nStartMode == 0)
	{
		//显示主窗口
		ShowWindow(pFrame->m_hWnd,SW_SHOW);
		UpdateWindow(pFrame->m_hWnd);
	}
	else
		SendMessage(pFrame->m_hWnd,WM_COMMAND,MAKEWPARAM(ID_ICONMODE,0),0);

	return TRUE;//程序初始化成功
}
//#######################################################################
int CScreenCap::ExitInstance()
{
	CMainWnd* pFrame = (CMainWnd*)m_pMainWnd;
	RegSetBinary("Config","WindowPlacement",(LPBYTE)&pFrame->m_WndPlm,sizeof(WINDOWPLACEMENT));

	if(m_hInstImage)
		FreeLibrary(m_hInstImage);
	
	return CFBApp::ExitInstance();
}
//#######################################################################
/////////////////////////////////////////////////////////////////////////////////
//

CScreenCap theApp;
////////////////////////////////////////////////////////////////////////////
CScreenCap* WINAPI GetApp()
{
	return &theApp;
}
////////////////////////////////////////////////////////////////////////////////////
//
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	theApp.m_hInstance = hInstance;
	theApp.m_pszAppName = "屏幕捕快";
	theApp.m_strCmdLine = lpCmdLine;
	if(theApp.InitInstance() == TRUE)
		return theApp.Run();
	else
		return theApp.ExitInstance();
}
