[V0.0.3](https://github.com/littleflute/blog/edit/master/docs/2017/04/29/index.md)

[show me](https://littleflute.github.io/blog/docs/2017/04/29/)

<script src="../../../xd.js"></script>


~~~C++
// File: XdW32.cpp 
// Littleflute's Windows32 App

#include "windows.h"
 
class CXdApp
{
#pragma warning( disable : 4183 )
public:
	CXdApp::CXdApp(){
		strcpy(m_szTitle,getV());
		strcpy(m_szWindowClass,"XdW32"); 
	};
	CXdApp::~CXdApp(){};
	char* CXdApp::getV(){ return "CXdApp: V0.0.1";};
	int	CXdApp::go(HINSTANCE hInstance,
                     int       nCmdShow)
	{
		if (!InitInstance (hInstance, nCmdShow)) 
		{ 
			return FALSE; 
		}

		MSG msg;
		HACCEL hAccelTable = NULL;   
		
		while (GetMessage(&msg, NULL, 0, 0)) 
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		
		return msg.wParam;
		
	}
private:
	HINSTANCE	m_hInst; 
	TCHAR		m_szTitle[256]; 
	TCHAR		m_szWindowClass[256];
	ATOM CXdApp::MyRegisterClass(HINSTANCE hInstance)
	{
		WNDCLASSEX wcex;
		
		wcex.cbSize = sizeof(WNDCLASSEX); 
		
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= (WNDPROC)WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance; 
		wcex.hIcon			= LoadIcon(NULL,IDI_WINLOGO); 
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL; 
		wcex.lpszClassName	= m_szWindowClass; 
		wcex.hIconSm		= LoadIcon(NULL,IDI_WINLOGO);
		
		return RegisterClassEx(&wcex);
	}
	BOOL CXdApp::InitInstance(HINSTANCE hInstance, int nCmdShow)
	{
		HWND hWnd;
		
		m_hInst = hInstance;  
		MyRegisterClass(m_hInst);
		hWnd = CreateWindow(m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
		
		if (!hWnd)
		{
			return FALSE;
		}
		
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
		
		return TRUE;
	}
	

	static	LRESULT CALLBACK	CXdApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		int			wmId, wmEvent;
		PAINTSTRUCT ps;
		HDC			hdc;
		TCHAR		szHello[256]; 
		strcpy(szHello,"Hello world!");
		
		switch (message) 
		{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case 1:
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
			
			case WM_LBUTTONDOWN:
				::MessageBox(NULL,"My Msg","My Title",MB_ICONINFORMATION|MB_YESNO);
				break;
			case WM_PAINT:
				hdc = BeginPaint(hWnd, &ps);
				// TODO: Add any drawing code here...
				RECT rt;
				GetClientRect(hWnd, &rt);
				DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
				EndPaint(hWnd, &ps);
				break;
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}
};
CXdApp g_myApp;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{ 
	return	g_myApp.go(hInstance,nCmdShow);
}
~~~
