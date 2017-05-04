
~~~C++
//BlWHelp.h
/*
2017.05.05 2:39AM bjt
littleflute
*/

class CBlWHelp
{
#pragma warning (disable : 4183)
public:
	CBlWHelp::CBlWHelp(){
		strcpy(m_szV,"V0.0.1");
	}
	CBlWHelp::~CBlWHelp(){}

    LRESULT	CBlWHelp::onMSG(HWND h,UINT m,WPARAM w,WPARAM l)
	{ 
		switch (m) 
		{
		case WM_LBUTTONDOWN:
			pvLbtDown(h,w,l);
			break;
		case WM_HOTKEY:
			m_blHk.onKey(h,w);
			break;
		case WM_CREATE:
			pvCreate(h,w,l);
			break;
		case WM_COMMAND:
			{
				WORD wmId    = LOWORD(w); 
				WORD wmEvent = HIWORD(w); 
				// Parse the menu selections:
				switch (wmId)
				{ 
				case IDM_EXIT: 
					pvAppExit();
					break; 
				}
			}
			break; 
		default:
				{
				}
			break;
		} 
		return 0;
	}

private:
	char		m_szV[16];
	
	#include "BlWHotKey.h"
	CBlWHotKey	m_blHk;
private:
	void pvCreate(HWND h,WPARAM w,LPARAM l)
	{
		m_blHk.onRegKey(h,444,MOD_CONTROL,39); 
	}
	void pvLbtDown(HWND h,WPARAM w,LPARAM l)
	{
		WORD x = LOWORD (l) ;
		WORD y = HIWORD (l) ;
		HDC hDC = ::GetDC(h);
		::Ellipse(hDC,x-50,y-50,x+50,y+50);
		::ReleaseDC(h,hDC);
	}
	void pvAppExit()
	{
	}
	
};
~~~
