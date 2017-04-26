//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���fbextapi.h

	��Ȩ��Firebird Software Workroom ����

	��������Դ����İ�Ȩ�ܡ��л����񹲺͹�����Ȩ�����Լ���
		  ����ط��ɺ���Լ�ı������κ��л���õ���Դ�����
		  ���˺ͻ�����δ��������ȷ��Ȩ�����ý���Դ��������
		  �κ���ҵĿ��(ֱ�ӵĻ��ӵ�)�����ڷ���ҵĿ�ĵ�ʹ
		  �� (�������ơ�������������޸�)�� ԭ����û���ر�
		  �������������������ĵ���˵������Դ��������ԭ
		  ���ߵ�����Ȩ��

	��д���ش���(chings)	1999.12 - 2000.5

	���磺Tel��(0792)6323086	E_mail��chings@163.net
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