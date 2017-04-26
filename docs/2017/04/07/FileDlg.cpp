//Download by http://www.NewXing.com
// FileDlg.cpp: implementation of the CFileDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdfbx.h"
#include "FileDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

char CFileDlg::name[64];
HDC CFileDlg::hBmpDC = NULL;
LONG CFileDlg::picHeight = 0;
LONG CFileDlg::picWidth = 0;
HWND CFileDlg::hMainWnd = NULL;
RECT CFileDlg::rcPic;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileDlg::CFileDlg()
{
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hInstance = NULL;
	ofn.hwndOwner = NULL;
	ofn.Flags = OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY;
	ofn.lCustData = NULL;
	ofn.lpfnHook = NULL;
	ofn.lpstrCustomFilter = NULL;
	ofn.lpstrDefExt = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrFilter = "所有文件\0*.*\0";
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = NULL;
	ofn.lpTemplateName = NULL;
	ofn.nFileExtension = NULL;
	ofn.nFileOffset = 0;
	ofn.nFilterIndex = 1;
	ofn.nMaxCustFilter = 0;
	ofn.nMaxFile = 256;
	ofn.nMaxFileTitle = 0;

	ZeroMemory(name,64);
	ZeroMemory(szFile,256);
}
///////////////////////////////////////////////////////////////////////////////////
CFileDlg::~CFileDlg()
{
}
/////////////////////////////////////////////////////////////////////////////////
void CFileDlg::SetTemplate(HINSTANCE hInst,HWND hOwner,UINT nTemplateID,BOOL bHook)
{
	ofn.hInstance = hInst;
	hMainWnd = hOwner;
	ofn.Flags |= OFN_ENABLETEMPLATE;
	ofn.lpTemplateName = MAKEINTRESOURCE(nTemplateID);
	if(bHook)
	{
		ofn.Flags |= OFN_ENABLEHOOK;
		ofn.lpfnHook = OFNHookProc;
	}
}
///////////////////////////////////////////////////////////////////
BOOL CFileDlg::DoModal(BOOL flag)
{
	if(flag == TRUE)
		return GetOpenFileName(&ofn);
	else
		return GetSaveFileName(&ofn);
}
///////////////////////////////////////////////////////////////////////////////
LPSTR CFileDlg::GetFilePath()
{
	return szFile;
}
/////////////////////////////////////////////////////////////////////////
//打开文件对话框的钩子函数
UINT CFileDlg::OFNHookProc(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
	UINT uResult = 0;
	switch(msg)
	{
    case WM_INITDIALOG:
		CenterWindow(GetParent(hdlg));
		uResult = 1;
        break;
	case WM_NOTIFY:
		{
			LPOFNOTIFY pNotify = (LPOFNOTIFY)lParam;
			LPTSTR filename = pNotify->lpOFN->lpstrFile;
			if(pNotify->hdr.code == CDN_SELCHANGE)
			{
				ZeroMemory(filename,255);				
				int size = SendMessage(GetParent(hdlg),CDM_GETFILEPATH ,255,(LPARAM)filename);
				if(size)
				{
					char theName[64];
					CommDlg_OpenSave_GetSpec(GetParent(hdlg),theName,64);
					int cmp = strcmp(name,theName);
					if(cmp != 0)
					{
						strcpy(name,theName);
						HBITMAP hBmp = NULL;
						hBmp = (HBITMAP)SendMessage(hMainWnd,OFM_GETBITMAP,0,(LPARAM)filename);
						if(hBmp)
						{
							if(hBmpDC)
							{
								DeleteDC(hBmpDC);
								hBmpDC = NULL;
								FillSolidRect(GetDC(hdlg),rcPic.left,rcPic.top,rcPic.right - rcPic.left,
												rcPic.bottom - rcPic.top,GetSysColor(COLOR_3DFACE));
							}
							BITMAP bmp;
							hBmpDC = CreateCompatibleDC(GetDC(hdlg));
							GetObject(hBmp,sizeof(bmp),&bmp);
							picWidth = bmp.bmWidth;
							picHeight = bmp.bmHeight;
							SelectObject(hBmpDC,hBmp);
							DeleteObject(hBmp);
							//SendMessage(hdlg,WM_ERASEBKGND,(WPARAM)GetDC(hdlg),0);

							OFNHookProc(hdlg,WM_PAINT,0,0);
						}
					}
				}
			}
		}
		break;
	case WM_PAINT:
		{
			//RECT rcPic;
			GetClientRect(hdlg,&rcPic);
			HDC hDC = GetDC(hdlg);
			rcPic.top += 200;
			int right = rcPic.right;
			DrawEdge(hDC,&rcPic,EDGE_ETCHED,BF_RECT);
			rcPic.left += 39;
			rcPic.right = right;
			rcPic.top += 1;
			rcPic.bottom -= 1;
			DrawEdge(hDC,&rcPic,EDGE_ETCHED,BF_LEFT);
			//COLORREF clr1 = GetSysColor(COLOR_3DHILIGHT);
			//COLORREF clr2 = GetSysColor(COLOR_3DSHADOW);
			//Draw3DRect(hDC,&rcPic,clr2,clr1,2);
			//rcPic.bottom = bottom;
			//Draw3DRect(hDC,&rcPic,clr1,clr2,2);
			if(hBmpDC)
			{
				LONG x,y,w,h;
				rcPic.top += 4;
				rcPic.bottom -= 4;
				rcPic.left += 4;
				rcPic.right -= 4;
				LONG cx = rcPic.right - rcPic.left;
				LONG cy = rcPic.bottom - rcPic.top;
				if((picWidth/picHeight) > (cx/cy))
				{
					if(picWidth>cx)
					{
						w = cx;
						h = (LONG)picHeight*cx/picWidth;
						x = rcPic.left;
					}
					else
					{
						w = picWidth;
						h = picHeight;
						x = rcPic.left+(LONG)(cx-w)/2;
					}
					y = rcPic.top + (LONG)(cy-h)/2;
				}
				else
				{
					if(picHeight>cy)
					{
						h = cy;
						w = (LONG)picWidth*cy/picHeight;
						y = rcPic.top;
					}
					else
					{
						h = picHeight;
						w = picWidth;
						y = rcPic.top + (LONG)(cy-h)/2;
					}
					x = rcPic.left + (LONG)(cx-w)/2;
				}

				rcPic.left = x-2;
				rcPic.top = y-2;
				rcPic.right = x+w+2;
				rcPic.bottom = y+h+2;
				StretchBlt(hDC,x,y,w,h,
				        hBmpDC,0,0,picWidth,picHeight,SRCCOPY);

				COLORREF clr1 = GetSysColor(COLOR_3DHILIGHT);
				COLORREF clr2 = GetSysColor(COLOR_3DSHADOW);
				Draw3DRect(hDC,&rcPic,clr1,clr2,2);
			}
		}
		break;
	case WM_ERASEBKGND:
		{
			RECT rc;
			GetClientRect(hdlg,&rc);
			rc.top += 200;
/*			rc.left += 42;
			rc.right -= 2;
			rc.bottom -= 2;
			FillSolidRect((HDC)wParam,rc.left,rc.top,rc.right - rc.left,rc.bottom - rc.top,RGB(0,128,64));
			rc.left -= 2;
			rc.top -= 2;
			rc.right += 2;
			rc.bottom += 2;*/
			FillSolidRect((HDC)wParam,rc.left,rc.top,rc.right - rc.left,rc.bottom - rc.top,GetSysColor(COLOR_3DFACE));
			ExcludeClipRect((HDC)wParam,rc.left,rc.top,rc.right,rc.bottom);
			OFNHookProc(hdlg,WM_PAINT,wParam,0);
		}
		break;
	case WM_DESTROY:
		if(hBmpDC)
			DeleteDC(hBmpDC);
		hBmpDC = NULL;
		break;
	default:
		break;
	}
	return uResult;
}
