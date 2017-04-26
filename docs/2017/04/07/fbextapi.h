//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：fbextapi.h

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
#ifndef _FBEXTAPI_H__
#define _FBEXTAPI_H__
//////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
/////////////////////////////////////////////////////////////////////////////////
void WINAPI Draw3DRect(HDC hDC,LPRECT pRect,COLORREF clrTopLeft, COLORREF clrBottomRight,int nWidth);
void WINAPI FillSolidRect(HDC hDC,int x,int y,int cx,int cy,COLORREF clr);
void WINAPI FillSolidRect(HDC hDC,LPRECT prc,COLORREF clr);
BOOL WINAPI MoveWindow(HWND hWnd,LPRECT pRect,BOOL bRepaint);
void WINAPI ClientToScreen(HWND hWnd,LPRECT pRect);
HBITMAP WINAPI CreateGradientBMP(HDC hDC,COLORREF cl1,COLORREF cl2,int nWidth,int nHeight,int nDir,int nNumColors = 256);
void WINAPI TileBitmap(HDC hDC,LPRECT pRc,HDC bmpDC,int bmpWidth,int bmpHeight);
void WINAPI CenterWindow(HWND hWnd);
void WINAPI LineRect(HDC hDC,LPRECT pRc);
void WINAPI DrawDragRect(HDC hDC,LPRECT pRect,int nWinth = 3);
void WINAPI NormalizeRect(LPRECT prc);
////////////////////////////////////////////////////////////////////////////////////////
#endif//_FBEXTAPI_H__