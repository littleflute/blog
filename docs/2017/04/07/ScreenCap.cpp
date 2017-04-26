//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���ScreenCap.cpp

	��Ȩ��Firebird Software Workroom ����

	��������Դ����İ�Ȩ�ܡ��л����񹲺͹�����Ȩ�����Լ���
		  ����ط��ɺ���Լ�ı������κ��л���õ���Դ�����
		  ���˺ͻ�����δ��������ȷ��Ȩ�����ý���Դ��������
		  �κ���ҵĿ��(ֱ�ӵĻ��ӵ�)�����ڷ���ҵĿ�ĵ�ʹ
		  �� (�������ơ�������������޸�)�� ԭ����û���ر�
		  �������������������ĵ���˵������Դ��������ԭ
		  ���ߵ�����Ȩ��

	��д���ش���(chings)	2000.5

	���磺Tel��(0792)6323086	E_mail��chings@163.net
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
	SetRegistryKey("Firebird");//����ע�������

	char caption[16];
	lstrcpy(caption,"��Ļ����");

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
		lstrcat(caption,"1.8��");
	}
	else
	{
		m_dwVersion = 0;//��ʾ��
		lstrcat(caption,"��ʾ��");
	}

	CMainWnd* pFrame = new CMainWnd();

	//����������
	if(pFrame->Create(m_hInstance,caption,NULL,NULL) == FALSE)
		return FALSE;

	//����ͼ��
	HICON hIcon = LoadIcon(m_hInstance,MAKEINTRESOURCE(IDI_MAINICON));
	SendMessage(pFrame->m_hWnd,WM_SETICON,(WPARAM)ICON_SMALL,(LPARAM)hIcon);

	LPAPP_SETINGS pas = pFrame->GetSetings();

	//��ע����еõ����ڳ�ʼλ�úͳߴ������
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
		//��ʾ������
		ShowWindow(pFrame->m_hWnd,SW_SHOW);
		UpdateWindow(pFrame->m_hWnd);
	}
	else
		SendMessage(pFrame->m_hWnd,WM_COMMAND,MAKEWPARAM(ID_ICONMODE,0),0);

	return TRUE;//�����ʼ���ɹ�
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
	theApp.m_pszAppName = "��Ļ����";
	theApp.m_strCmdLine = lpCmdLine;
	if(theApp.InitInstance() == TRUE)
		return theApp.Run();
	else
		return theApp.ExitInstance();
}
