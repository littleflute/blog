//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：fbextapi.cpp

	版权：Firebird Software Workroom 保留

	声明：本源程序的版权受《中华人民共和国著作权法》以及其
		  它相关法律和条约的保护。任何有机会得到本源程序的
		  个人和机构，未经作者明确授权，不得将本源程序用于
		  任何商业目的(直接的或间接的)。对于非商业目的的使
		  用 (包括复制、传播、编译和修改)， 原则上没有特别
		  的限制条款，但请在相关文档中说明其来源，并尊重原
		  作者的署名权。

	编写：秦传安(chings)	1999.12 - 2000.5

	联络：Tel：(0792)6323086	E_mail：chings@163.net
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#include "fbextapi.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
void WINAPI Draw3DRect(HDC hDC,LPRECT pRect,COLORREF clrTopLeft, COLORREF clrBottomRight,int nWidth)
{
	int x,y,cx,cy;
	x = pRect->left;
	y = pRect->top;
	cx = pRect->right - pRect->left ;
	cy = pRect->bottom - pRect->top;
	int i = 0;
	for(i=0;i<nWidth;i++)
	{
		FillSolidRect(hDC,x, y, cx - 1, 1, clrTopLeft);
		FillSolidRect(hDC,x, y, 1, cy - 1, clrTopLeft);
		FillSolidRect(hDC,x + cx, y, -(i+1), cy, clrBottomRight);
		FillSolidRect(hDC,x, y + cy, cx, -(i+1), clrBottomRight);
		x++;
		y++;
		cx--;
		cy--;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void WINAPI FillSolidRect(HDC hDC,int x,int y,int cx,int cy,COLORREF clr)
{
	RECT rc;
	rc.left = x;
	rc.top = y;
	rc.right = x+cx;
	rc.bottom = y+cy;
	SetBkColor(hDC, clr);
	ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
}
void WINAPI FillSolidRect(HDC hDC,LPRECT prc,COLORREF clr)
{
	SetBkColor(hDC, clr);
	ExtTextOut(hDC, 0, 0, ETO_OPAQUE, prc, NULL, 0, NULL);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL WINAPI MoveWindow(HWND hWnd,LPRECT pRect,BOOL bRepaint)
{
	return ::MoveWindow(hWnd,pRect->left,pRect->top,pRect->right - pRect->left,
						pRect->bottom - pRect->top,bRepaint);
}
//////////////////////////////////////////////////////////////////////////////
//
HBITMAP WINAPI CreateGradientBMP(HDC hDC,COLORREF cl1,COLORREF cl2,int nWidth,int nHeight,int nDir,int nNumColors)
{
	if(nNumColors > 256)
		nNumColors = 256;

	COLORREF		PalVal[256];

	int nIndex;
	BYTE peRed,peGreen,peBlue;

	int r1=GetRValue(cl1);
	int r2=GetRValue(cl2);
	int g1=GetGValue(cl1);
	int g2=GetGValue(cl2);
	int b1=GetBValue(cl1);
	int b2=GetBValue(cl2);

    for (nIndex = 0; nIndex < nNumColors; nIndex++)
    {
        peRed = (BYTE) r1 + MulDiv((r2-r1),nIndex,nNumColors-1);
        peGreen = (BYTE) g1 + MulDiv((g2-g1),nIndex,nNumColors-1);
        peBlue = (BYTE) b1 + MulDiv((b2-b1),nIndex,nNumColors-1);

		PalVal[nIndex]=(peRed << 16) | (peGreen << 8) | (peBlue);
	}

	int x,y,w,h;
	w=nWidth;
	h=nHeight;
	
	LPDWORD			pGradBits;
	BITMAPINFO		GradBitInfo;

	pGradBits=(DWORD*) malloc(w*h*sizeof(DWORD));
	memset(&GradBitInfo,0,sizeof(BITMAPINFO));

	GradBitInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
	GradBitInfo.bmiHeader.biWidth=w;
	GradBitInfo.bmiHeader.biHeight=h;
	GradBitInfo.bmiHeader.biPlanes=1;
	GradBitInfo.bmiHeader.biBitCount=32;
	GradBitInfo.bmiHeader.biCompression=BI_RGB;
	
	if(nDir==0) 
	{
		for(y=0;y<h;y++) 
		{
			for(x=0;x<w;x++) 
			{
				*(pGradBits+(y*w)+x)=PalVal[MulDiv(nNumColors,y,h)];
			}
		}
	}
	else if(nDir==1) 
	{
		for(y=0;y<h;y++)
		{
			int l,r;
			l=MulDiv((nNumColors/2),y,h);
			r=l+(nNumColors/2)-1;
			for(x=0;x<w;x++)
			{
				*(pGradBits+(y*w)+x)=PalVal[l+MulDiv((r-l),x,w)];
			}
		}
	}
	else if(nDir==2)
	{
		for(x=0;x<w;x++)
		{
			for(y=0;y<h;y++)
			{
				*(pGradBits+(y*w)+x)=PalVal[MulDiv(nNumColors,x,w)];
			}
		}
	}
	else if(nDir==3)
	{
		for(y=0;y<h;y++)
		{
			int l,r;
			r=MulDiv((nNumColors/2),y,h);
			l=r+(nNumColors/2)-1;
			for(x=0;x<w;x++)
			{
				*(pGradBits+(y*w)+x)=PalVal[l+MulDiv((r-l),x,w)];
			}
		}
	}

	HBITMAP hBmp = CreateDIBitmap(hDC,&GradBitInfo.bmiHeader,CBM_INIT,
						pGradBits,&GradBitInfo,DIB_RGB_COLORS);

	free(pGradBits);

	return hBmp;
}

//////////////////////////////////////////////////////////////////////////////////
void WINAPI ClientToScreen(HWND hWnd,LPRECT pRect)
{
	POINT p1,p2;
	p1.x = pRect->left;
	p1.y = pRect->top;
	p2.x = pRect->right;
	p2.y = pRect->bottom;

	ClientToScreen(hWnd,&p1);
	ClientToScreen(hWnd,&p2);

	pRect->left = p1.x;
	pRect->top = p1.y;
	pRect->right = p2.x;
	pRect->bottom = p2.y;
}
/////////////////////////////////////////////////////////////////////////////////////
void WINAPI TileBitmap(HDC hDC,LPRECT pRc,HDC bmpDC,int bmpWidth,int bmpHeight)
{
	int x,y;
	for(y=0;y<(pRc->bottom-pRc->top);y+=bmpHeight)
	{
		for(x=0;x<(pRc->right-pRc->left);x+=bmpWidth)
		{
			BitBlt(hDC,x,y,bmpWidth,bmpHeight,bmpDC,0,0,SRCCOPY);
		}
	}
}
////////////////////////////////////////////////////////////////////////
void WINAPI CenterWindow(HWND hWnd)
{
	RECT rcParent,rcChild;
	HWND hParent = GetParent(hWnd);
	
	if(!hParent)
		hParent = GetDesktopWindow();

	GetWindowRect(hParent,&rcParent);
	
	GetWindowRect(hWnd,&rcChild);

	LONG x,y;

	x = (LONG)((rcParent.right - rcParent.left) - (rcChild.right - rcChild.left)) / 2 + rcParent.left;
	y = (LONG)((rcParent.bottom - rcParent.top) - (rcChild.bottom - rcChild.top)) / 2 + rcParent.top;

    SetWindowPos(hWnd,0,x,y,0,0,SWP_NOSIZE); 
}
////////////////////////////////////////////////////////////////////////
void WINAPI LineRect(HDC hDC,LPRECT pRc)
{
	SetROP2(hDC,R2_NOT);
	MoveToEx(hDC,pRc->left,pRc->top,NULL);
	LineTo(hDC,pRc->right,pRc->top);
	LineTo(hDC,pRc->right,pRc->bottom);
	LineTo(hDC,pRc->left,pRc->bottom);
	LineTo(hDC,pRc->left,pRc->top);
}
////////////////////////////////////////////////////////////////////////
void WINAPI DrawDragRect(HDC hDC,LPRECT pRect,int nWidth)
{
	RECT rc;
	CopyRect(&rc,pRect);
	for(int i=0;i<nWidth;i++)
	{
		DrawFocusRect(hDC,&rc);
		InflateRect(&rc,-1,-1);
	}
}
////////////////////////////////////////////////////////////////////////
void WINAPI NormalizeRect(LPRECT prc)
{
	if((prc == NULL) || IsRectEmpty(prc))return;

	RECT rc;
	CopyRect(&rc,prc);

	prc->left = min(rc.left,rc.right);
	prc->top = min(rc.top,rc.bottom);
	prc->right = max(rc.left,rc.right);
	prc->bottom = max(rc.top,rc.bottom);
}