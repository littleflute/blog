// B1Mng.h : main header file for the B1MNG DLL
//

#if !defined(AFX_B1MNG_H__85330EF8_3B2E_4F71_B790_449A7598FAFC__INCLUDED_)
#define AFX_B1MNG_H__85330EF8_3B2E_4F71_B790_449A7598FAFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CB1MngApp
// See B1Mng.cpp for the implementation of this class
//

class CB1MngApp : public CWinApp
{
public:
	CB1MngApp();
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CB1MngApp)
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(CB1MngApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#include <math.h>

#define IDM_ALIGN_LEFT                  40003
#define IDM_ALIGN_RIGHT                 40004
#define IDM_ALIGN_CENTER                40005
#define IDM_ALIGN_JUSTIFIED             40006
#define EZ_ATTR_BOLD          1
#define EZ_ATTR_ITALIC        2
#define EZ_ATTR_UNDERLINE     4
#define EZ_ATTR_STRIKEOUT     8
#define MY_VERSION		"V:0346"
#define MY_TEXT			"MY_TEXT"
#define DEVICE_LIST     "从指定目录下枚举出[B1插件]结果列表：\n"

//#include <vector> 
//using namespace std;

class CLfDC 
{
	class CXdGDI
	{
	private:
		HFONT xdCreateFont (HDC hdc, TCHAR * szFaceName, int iDeciPtHeight,
			int iDeciPtWidth, int iAttributes, BOOL fLogRes){
			FLOAT      cxDpi, cyDpi ;
			HFONT      hFont ;
			LOGFONT    lf ;
			POINT      pt ;
			TEXTMETRIC tm ;
			
			SaveDC (hdc) ;
			
			SetGraphicsMode (hdc, GM_ADVANCED) ;
			ModifyWorldTransform (hdc, NULL, MWT_IDENTITY) ;
			SetViewportOrgEx (hdc, 0, 0, NULL) ;
			SetWindowOrgEx   (hdc, 0, 0, NULL) ;
			
			if (fLogRes)
			{
				cxDpi = (FLOAT) GetDeviceCaps (hdc, LOGPIXELSX) ;
				cyDpi = (FLOAT) GetDeviceCaps (hdc, LOGPIXELSY) ;
			}
			else
			{
				cxDpi = (FLOAT) (25.4 * GetDeviceCaps (hdc, HORZRES) /
					GetDeviceCaps (hdc, HORZSIZE)) ;
				
				cyDpi = (FLOAT) (25.4 * GetDeviceCaps (hdc, VERTRES) /
					GetDeviceCaps (hdc, VERTSIZE)) ;
			}
			
			pt.x = (int) (iDeciPtWidth  * cxDpi / 72) ;
			pt.y = (int) (iDeciPtHeight * cyDpi / 72) ;
			
			DPtoLP (hdc, &pt, 1) ;
			
			lf.lfHeight         = - (int) (fabs (pt.y) / 10.0 + 0.5) ;
			lf.lfWidth          = 0 ;
			lf.lfEscapement     = 0 ;
			lf.lfOrientation    = 0 ;
			lf.lfWeight         = iAttributes & EZ_ATTR_BOLD      ? 700 : 0 ;
			lf.lfItalic         = iAttributes & EZ_ATTR_ITALIC    ?   1 : 0 ;
			lf.lfUnderline      = iAttributes & EZ_ATTR_UNDERLINE ?   1 : 0 ;
			lf.lfStrikeOut      = iAttributes & EZ_ATTR_STRIKEOUT ?   1 : 0 ;
			lf.lfCharSet        = DEFAULT_CHARSET ;
			lf.lfOutPrecision   = 0 ;
			lf.lfClipPrecision  = 0 ;
			lf.lfQuality        = 0 ;
			lf.lfPitchAndFamily = 0 ;
			
			lstrcpy (lf.lfFaceName, szFaceName) ;
			
			hFont = CreateFontIndirect (&lf) ;
			
			if (iDeciPtWidth != 0)
			{
				hFont = (HFONT) SelectObject (hdc, hFont) ;
				
				GetTextMetrics (hdc, &tm) ;
				
				DeleteObject (SelectObject (hdc, hFont)) ;
				
				lf.lfWidth = (int) (tm.tmAveCharWidth *
					fabs (pt.x) / fabs (pt.y) + 0.5) ;
				
				hFont = CreateFontIndirect (&lf) ;
			}
			
			RestoreDC (hdc, -1) ;
			return hFont ;
		}
		
	public:
		void OnXdCreate2DData(IN int x, IN int y,IN int w, IN int h,
			OUT BYTE *pData,bool bClr)
		{ 
			OnDrawRect(x,y,w,h,RGB(0,0,255));
		}
		
		void OnDrawFillFontText(char *szString,int cxArea, int cyArea){
			HDC &hdc = m_hDC; 
			HFONT        hFont ;
			SIZE         size ;
			
			hFont = xdCreateFont (hdc, TEXT ("Times New Roman"), 1440, 0, 0, TRUE) ;
			
			SelectObject (hdc, hFont) ;
			SetBkMode (hdc, TRANSPARENT) ;
			
			GetTextExtentPoint32 (hdc, szString, lstrlen (szString), &size) ;
			
			BeginPath (hdc) ;
			TextOut (hdc, (cxArea - size.cx) / 2, (cyArea - size.cy) / 2,
				szString, lstrlen (szString)) ;
			EndPath (hdc) ;
			
			SelectObject (hdc, CreateHatchBrush (HS_DIAGCROSS, RGB (255, 0, 0))) ;
			SetBkColor (hdc, RGB (0, 0, 255)) ;
			SetBkMode (hdc, OPAQUE) ;
			
			StrokeAndFillPath (hdc) ;
			
			DeleteObject (SelectObject (hdc, GetStockObject (WHITE_BRUSH))) ;
			SelectObject (hdc, GetStockObject (SYSTEM_FONT)) ;
			DeleteObject (hFont) ;
			
		}
		void OnJustify (PTSTR pText, RECT * prc, int iAlign)
		{
			HDC &hdc = m_hDC;
			
			int   xStart, yStart, cSpaceChars ;
			PTSTR pBegin, pEnd ;
			SIZE  size ;
			
			yStart = prc->top ;
			do                            // for each text line
			{
				cSpaceChars = 0 ;        // initialize number of spaces in line
				
				while (*pText == ' ')    // skip over leading spaces
					pText++ ;
				
				pBegin = pText ;         // set pointer to char at beginning of line
				
				do                       // until the line is known
				{
					pEnd = pText ;      // set pointer to char at end of line
					
					// skip to next space 
					
					while (*pText != '\0' && *pText++ != ' ') ;
					
					if (*pText == '\0')
						break ;
					
					// after each space encountered, calculate extents
					
					cSpaceChars++ ;
					GetTextExtentPoint32(hdc, pBegin, pText - pBegin - 1, &size) ;
				}
				while (size.cx < (prc->right - prc->left)) ;
				
				cSpaceChars-- ;               // discount last space at end of line
				
				while (*(pEnd - 1) == ' ')    // eliminate trailing spaces
				{
					pEnd-- ;
					cSpaceChars-- ;
				}
				
				// if end of text and no space characters, set pEnd to end
				
				if (*pText == '\0' || cSpaceChars <= 0)
					pEnd = pText ;
				
				GetTextExtentPoint32 (hdc, pBegin, pEnd - pBegin, &size) ;
				
				switch (iAlign)               // use alignment for xStart
				{
				case IDM_ALIGN_LEFT:
					xStart = prc->left ;
					break ;
					
				case IDM_ALIGN_RIGHT:
					xStart = prc->right - size.cx ;
					break ;
					
				case IDM_ALIGN_CENTER:
					xStart = (prc->right + prc->left - size.cx) / 2 ;
					break ;
					
				case IDM_ALIGN_JUSTIFIED:
					if (*pText != '\0' && cSpaceChars > 0)
						SetTextJustification (hdc,
						prc->right - prc->left - size.cx,
						cSpaceChars) ;
					xStart = prc->left ;
					break ;
				}
				// display the text
				
				TextOut (hdc, xStart, yStart, pBegin, pEnd - pBegin) ;
				
				// prepare for next line
				
				SetTextJustification (hdc, 0, 0) ;
				yStart += size.cy ;
				pText = pEnd ;
			}
			while (*pText && yStart < prc->bottom - size.cy) ;
		}
		void OnDrawRuler(RECT * prc){
			static int iRuleSize [16] = { 360, 72, 144, 72, 216, 72, 144, 72,
				288, 72, 144, 72, 216, 72, 144, 72 } ;
			HDC &hdc = m_hDC;
			
			int        i, j ;
			POINT      ptClient ;
			
			SaveDC (hdc) ;
			
			// Set Logical Twips mapping mode
			
			SetMapMode (hdc, MM_ANISOTROPIC) ;
			SetWindowExtEx (hdc, 1440, 1440, NULL) ;
			SetViewportExtEx (hdc, GetDeviceCaps (hdc, LOGPIXELSX),
				GetDeviceCaps (hdc, LOGPIXELSY), NULL) ;
			
			// Move the origin to a half inch from upper left
			
			SetWindowOrgEx (hdc, -720, -720, NULL) ;
			
			// Find the right margin (quarter inch from right)
			
			ptClient.x = prc->right ;
			ptClient.y = prc->bottom ;
			DPtoLP (hdc, &ptClient, 1) ;
			ptClient.x -= 360 ;
			
			// Draw the rulers
			
			MoveToEx (hdc, 0,          -360, NULL) ;
			LineTo   (hdc, ptClient.x, -360) ;
			MoveToEx (hdc, -360,          0, NULL) ;
			LineTo   (hdc, -360, ptClient.y) ;
			
			for (i = 0, j = 0 ; i <= ptClient.x ; i += 1440 / 16, j++)
			{
				MoveToEx (hdc, i, -360, NULL) ;
				LineTo   (hdc, i, -360 - iRuleSize [j % 16]) ;
			}
			
			for (i = 0, j = 0 ; i <= ptClient.y ; i += 1440 / 16, j++)
			{
				MoveToEx (hdc, -360, i, NULL) ;
				LineTo   (hdc, -360 - iRuleSize [j % 16], i) ;
			}
			
			RestoreDC (hdc, -1) ;
			
		}
		void OnDrawText(int x,int y,char *sz,COLORREF rgb)
		{
			if(NULL==m_hDC) return;
			HBRUSH  hBrush  = (HBRUSH)CreateSolidBrush(rgb);
			HBRUSH  hOldBrush = (HBRUSH)SelectObject(m_hDC,hBrush); 
			
			TextOut (m_hDC, x, y, sz,25) ;
			
			SelectObject(m_hDC,hOldBrush);
			DeleteObject(hBrush);
			
			
		}
		void OnDrawRect(int x,int y,int w,int h,COLORREF rgb)
		{
			if(NULL==m_hDC) return;
			HBRUSH  hBrush  = (HBRUSH)CreateSolidBrush(rgb);
			HBRUSH  hOldBrush = (HBRUSH)SelectObject(m_hDC,hBrush);
			
			::Rectangle(m_hDC,x,y,w,h);
			
			SelectObject(m_hDC,hOldBrush);
			DeleteObject(hBrush);
			
		}
		void SetRECT(RECT &r,int x,int y,int w,int h){
			r.left		= x;
			r.top		= y;
			r.right		= w;
			r.bottom	= h;
		}
		
		
		
		CXdGDI(HDC &hDC)
		{
			m_hDC = hDC;
		} 
		
		CXdGDI()
		{
			m_hDC = NULL;
		}
		virtual ~CXdGDI()
		{
		}
		
private:
	HDC		m_hDC;
};
public: 
	
	void plUpsidedown24Rgb(BYTE *p,int w,int h){
		BYTE *pNew = new BYTE[w*h*3];
		memset(pNew,255,w*h*3);
		//*
		BYTE *pI = p;
		BYTE *pN = pNew + w * 3* (h-1);
		for(int i = 0; i < h; i++)
		{
			memcpy(pN,pI,w*3);
			pI += w*3;
			pN -= w*3;
		}
		//*/
		memcpy(p,pNew,w*h*3); 
		delete []pNew;
	}
	void OnXd_DrawG1()
	{
		HDC		&hDC = m_hMemDC;  
		xdPaintRoutine (hDC, 300,300);
	}
	void OnXd_DrawG()
	{
		
		HDC		&hDC = m_hMemDC;  
		
		CXdGDI d(hDC);
		RECT	rc;
		rc.left		= 0;
		rc.top		= 0;
		rc.right	= 300;
		rc.bottom	= 300;
		d.OnDrawRuler(&rc);
		
		static BYTE		bitsHello1 []   = { 0x51, 0x77, 0x10, 0x00,
			0x57, 0x77, 0x50, 0x00, 
			0x13, 0x77, 0x50, 0x00,
			0x57, 0x77, 0x50, 0x00,
			0x51, 0x11, 0x10, 0x00 
		} ;
		static BITMAP	bitmapHello1     = { 0, 20, 5, 4, 1, 1 } ;
		
		static BYTE		bitsG []		= { 0xff, 0x1f, //1 0x1f, 0x00,
			0xff, 0x1f, //2 0x50, 0x00, 
			0xfe, 0x4f, //3 0x50, 0x00,
			0xfe, 0x1f, //4 0x50, 0x00,
			0xfe, 0x1f, //5 0x10, 0x00 
			
		} ;
		static BITMAP	bmpG     = { 0, 16, 40, 2, 1, 1 } ;
		
		
		
		static HBITMAP	hBitmap ;
		static int		cxClient, cyClient, cxSource, cySource ;
		bmpG.bmBits				= bitsG ; 
		hBitmap							= CreateBitmapIndirect (&bmpG) ;  
		cxSource						= bmpG.bmWidth ;
		cySource						= bmpG.bmHeight ;
		HDC hdcMem						= CreateCompatibleDC (hDC) ;
		cxClient						= cxSource;//800;
		cyClient						= cxSource;//600;
		
		
		SelectObject (hdcMem, hBitmap) ; 
		
		for (int y = 0 ; y < cyClient ; y += cySource)
			for (int x = 0 ; x < cxClient ; x += cxSource)
			{
				BitBlt (hDC, 300, 300, cxSource, cySource, hdcMem, 0, 0, SRCCOPY) ;
			}
			
			DeleteDC (hdcMem) ; 
	}
	void OnXddrawMusicStr(int x,int y,char *sz,int nBkMode)
	{
		HDC		&hDC = m_hMemDC;
		xdMusicstring(hDC,x,y,sz,nBkMode);
	}
	void OnXdDrawStr(int x,int y,char* sz)
	{
		HDC		&hDC = m_hMemDC;
		if(NULL==hDC) return;
		
		HBRUSH  hBrush  = (HBRUSH)CreateSolidBrush(RGB(255,0,0));
		HBRUSH  hOldBrush = (HBRUSH)SelectObject(hDC,hBrush); 
		
		TextOut (hDC, x, y, sz,strlen(sz)) ;
		
		SelectObject(hDC,hOldBrush);
		DeleteObject(hBrush);
	}
	
	void OnXdGetData(int w, int h, BYTE *pData)
	{
		BYTE *p = pData;
		BITMAP csBitmap;
		HBITMAP		&hB = m_hBmp;
		
		int nRetValue = GetObject(hB, sizeof(csBitmap), &csBitmap);
		unsigned long nBpp, nWBmp, nHBmp;
		
		if (nRetValue) {
			nWBmp   = (long)csBitmap.bmWidth;
			nHBmp	= (long)csBitmap.bmHeight;
			nBpp    = (long)csBitmap.bmBitsPixel;
			long sz = csBitmap.bmWidth*csBitmap.bmHeight*(csBitmap.bmBitsPixel>>3);
			csBitmap.bmBits = (void *) new BYTE[ sz ];
			GetBitmapBits((HBITMAP)hB, sz, csBitmap.bmBits ); 
		} 
		else 
		{ 
			return ;
		}
		
		if ( nBpp == 32 )
		{
			for ( unsigned long y = 0; y < nHBmp; y ++ )
			{
				for ( unsigned long x = 0; x < nWBmp; x ++ ) 
				{
					RGBQUAD * rgb = ((RGBQUAD *) ((char*)(csBitmap.bmBits) 
						+ csBitmap.bmWidthBytes*y + x*sizeof(DWORD)) ); 
					p[ 0 ]	= rgb->rgbBlue;
					p[ 1 ]	= rgb->rgbGreen;
					p[ 2 ]	= rgb->rgbRed;
					p+=3;
				}
				p+=(w-nWBmp)*3;
			}
		} 
		else if ( nBpp == 24 )
		{
			for ( unsigned long y = 0; y < nHBmp; y ++ ) 
			{
				for ( unsigned long x = 0; x < nWBmp; x ++ )
				{ 
					RGBTRIPLE rgbi = *((RGBTRIPLE *) ((char*)(csBitmap.bmBits)
						+ csBitmap.bmWidthBytes*y + x*3) );
					
					RGBQUAD rgbq;
					rgbq.rgbRed = rgbi.rgbtRed;
					rgbq.rgbGreen = rgbi.rgbtGreen;
					rgbq.rgbBlue = rgbi.rgbtBlue;
					
					p[ (nHBmp - 1 - y)*nWBmp + x ]		= rgbq.rgbBlue;
					p[ (nHBmp - 1 - y)*nWBmp + x + 1 ]	= rgbq.rgbGreen;
					p[ (nHBmp - 1 - y)*nWBmp + x + 2 ]	= rgbq.rgbRed;
				}
			}
		}  
		if(csBitmap.bmBits) delete []csBitmap.bmBits;
	}
	
	void OnXdDrawRect(int x, int y, int w, int h, COLORREF rgb) 
	{
		HDC		&hDC = m_hMemDC;
		if(NULL==hDC) return;
		HBRUSH  hBrush  = (HBRUSH)CreateSolidBrush(rgb);
		HBRUSH  hOldBrush = (HBRUSH)SelectObject(hDC,hBrush);
		
		::Rectangle(hDC,x,y,x+w,y+h);
		
		SelectObject(hDC,hOldBrush);
		DeleteObject(hBrush); 
	}
	CLfDC()
	{
		m_nWMax			= 300;
		m_nHMax			= 300;
		m_hScreenDC		= ::GetDC(NULL);//CreateDC("DISPLAY", NULL, NULL, NULL);
		m_hMemDC 		= CreateCompatibleDC(m_hScreenDC);
		m_hBmp			= CreateCompatibleBitmap(m_hScreenDC, m_nWMax, m_nHMax);
		m_hOldBmp		= (HBITMAP) SelectObject(m_hMemDC, m_hBmp);
		
		
		//	OnXddrawMusicStr(0,0,"abc=)';",0);
		m_pBits			= new BYTE[m_nWMax*m_nHMax*3];
	}
	virtual ~CLfDC()
	{
		SelectObject(m_hMemDC, m_hOldBmp); 
		DeleteObject(m_hBmp);
		DeleteDC(m_hMemDC);  
		::ReleaseDC(NULL, m_hScreenDC);
		delete []m_pBits;
	}
private:  
	HDC					m_hScreenDC;
	HDC					m_hMemDC;
	HBITMAP				m_hBmp; 
	HBITMAP				m_hOldBmp;
	BYTE				*m_pBits;
	int				m_nWMax;
	int				m_nHMax; 
	void xdMusicstring(HDC hdc,int x,int y,char *sz,int nBkMode)
	{
		HFONT        hFont ;
		SIZE         size ;
		
		hFont = xdEzCreateFont (hdc, TEXT ("akvo"), 400, 0, 0, TRUE) ;
		
		SelectObject (hdc, hFont) ;
		
		GetTextExtentPoint32 (hdc, sz, lstrlen (sz), &size) ;
		
		int nMode = SetBkMode (hdc, nBkMode) ; 
		TextOut (hdc, x, y,	sz, lstrlen (sz)) ; 
		SetBkMode (hdc, nMode) ;
		
		SelectObject (hdc, GetStockObject (SYSTEM_FONT)) ;
		DeleteObject (hFont) ;
	}
	
	void xdPaintRoutine (HDC hdc, int cxArea, int cyArea)
	{
		static TCHAR szString [] = TEXT ("abc:()") ;
		HFONT        hFont ;
		SIZE         size ;
		
		hFont = xdEzCreateFont (hdc, TEXT ("akvo"), 800, 0, 0, TRUE) ;
		
		SelectObject (hdc, hFont) ;
		
		GetTextExtentPoint32 (hdc, szString, lstrlen (szString), &size) ;
		
		BeginPath (hdc) ;
		TextOut (hdc, (cxArea - size.cx) / 2, (cyArea - size.cy) / 2,
			szString, lstrlen (szString)) ;
		EndPath (hdc) ;
		
		StrokePath (hdc) ;
		
		SelectObject (hdc, GetStockObject (SYSTEM_FONT)) ;
		DeleteObject (hFont) ;
	}
	void ref1()
	{
		HDC hdc=::GetDC(NULL);
		HDC memdc=CreateCompatibleDC(hdc);
		RECT rc;
		BITMAP bmp;
		HBITMAP holdbmp,hbmp=NULL;
		//	LoadBitmap(hInstDVBRes,MAKEINTRESOURCE(IDB_CLOCK));//从资源加载位图
		holdbmp=(HBITMAP)SelectObject(memdc,hbmp);//这里把hbmp的位图选择到兼容DC memdc,之后这个兼容DC就拥有和
		//hbmp同样大小的绘图区域,注意超出位图返回的GDI输出都是无效的.
		GetObject(hbmp,sizeof(BITMAP),&bmp);//这里获取位图的大小信息,事实上也是兼容DC绘图输出的范围
		SetRect(&rc,0,0,bmp.bmWidth,bmp.bmHeight);
		DrawText(memdc,"Center Line Text", -1,&rc,DT_VCENTER|DT_SINGLELINE|DT_CENTER);//在兼容DC中间位置输出字符串
		//这样以来我们就相当于把hbmp这个位图加上了文字标注,我们可以把这个增加了文字标注的位图保存起来.一个简单的图像处理基本就OK了.
		SelectObject(memdc,holdbmp);//复原兼容DC数据.
		DeleteDC(memdc);
		::ReleaseDC(NULL, hdc);
		
	}
	
	HFONT xdEzCreateFont (HDC hdc, TCHAR * szFaceName, int iDeciPtHeight,
		int iDeciPtWidth, int iAttributes, BOOL fLogRes)
	{
		FLOAT      cxDpi, cyDpi ;
		HFONT      hFont ;
		LOGFONT    lf ;
		POINT      pt ;
		TEXTMETRIC tm ;
		
		SaveDC (hdc) ;
		
		SetGraphicsMode (hdc, GM_ADVANCED) ;
		ModifyWorldTransform (hdc, NULL, MWT_IDENTITY) ;
		SetViewportOrgEx (hdc, 0, 0, NULL) ;
		SetWindowOrgEx   (hdc, 0, 0, NULL) ;
		
		if (fLogRes)
		{
			cxDpi = (FLOAT) GetDeviceCaps (hdc, LOGPIXELSX) ;
			cyDpi = (FLOAT) GetDeviceCaps (hdc, LOGPIXELSY) ;
		}
		else
		{
			cxDpi = (FLOAT) (25.4 * GetDeviceCaps (hdc, HORZRES) /
				GetDeviceCaps (hdc, HORZSIZE)) ;
			
			cyDpi = (FLOAT) (25.4 * GetDeviceCaps (hdc, VERTRES) /
				GetDeviceCaps (hdc, VERTSIZE)) ;
		}
		
		pt.x = (int) (iDeciPtWidth  * cxDpi / 72) ;
		pt.y = (int) (iDeciPtHeight * cyDpi / 72) ;
		
		DPtoLP (hdc, &pt, 1) ;
		
		lf.lfHeight         = - (int) (fabs (pt.y) / 10.0 + 0.5) ;
		lf.lfWidth          = 0 ;
		lf.lfEscapement     = 0 ;
		lf.lfOrientation    = 0 ;
		lf.lfWeight         = iAttributes & EZ_ATTR_BOLD      ? 700 : 0 ;
		lf.lfItalic         = iAttributes & EZ_ATTR_ITALIC    ?   1 : 0 ;
		lf.lfUnderline      = iAttributes & EZ_ATTR_UNDERLINE ?   1 : 0 ;
		lf.lfStrikeOut      = iAttributes & EZ_ATTR_STRIKEOUT ?   1 : 0 ;
		lf.lfCharSet        = DEFAULT_CHARSET ;
		lf.lfOutPrecision   = 0 ;
		lf.lfClipPrecision  = 0 ;
		lf.lfQuality        = 0 ;
		lf.lfPitchAndFamily = 0 ;
		
		lstrcpy (lf.lfFaceName, szFaceName) ;
		
		hFont = CreateFontIndirect (&lf) ;
		
		if (iDeciPtWidth != 0)
		{
			hFont = (HFONT) SelectObject (hdc, hFont) ;
			
			GetTextMetrics (hdc, &tm) ;
			
			DeleteObject (SelectObject (hdc, hFont)) ;
			
			lf.lfWidth = (int) (tm.tmAveCharWidth *
				fabs (pt.x) / fabs (pt.y) + 0.5) ;
			
			hFont = CreateFontIndirect (&lf) ;
		}
		
		RestoreDC (hdc, -1) ;
		return hFont;
	}
};

class CMyLib 
{ 
	class CB1Dll
	{
	public:
		CB1Dll(HWND hWnd,int idx,char *sz):
		  m_nIdx(idx),m_bSelect(false),m_hWnd(hWnd)
		{ 
			x = 10;
			y = 33 + idx * 50;
			w = 266;
			h = 33;
			sprintf(m_szFileName,"%s",sz);
			pvLoad(); 
		}
		CB1Dll():m_bSelect(false),m_hWnd(NULL){
			sprintf(m_szFileName,"B1/BlMusic.dll");
			pvLoad();
		}
		~CB1Dll(){
			pvUnLoad();
		} 
		BLSTATUS CB1Dll::pl2Init(HWND h)
		{
			BLSTATUS r					= BL_STATUS_NOT_SUPPORT_INTERFACE;
			BL_LPARAM_CONTEXT	c		= {0};
			c.m							= BL_WM_INIT;
			c.idFrom					= BL_ID_B1_MNG;
			c.idTo						= BL_ID_B1_ALL;
			c.LPARAM.CallBack.pFun		= pvCallbackFunc;
			c.LPARAM.CallBack.pParam	= this;
			sprintf(c.szVerify,"BEAUTIFULLOVER"); 

			r = prCallLibFun(h,c.m,0,(LPARAM)&c);
			
			if(BL_STATUS_OK != r)// && BL_ID_B1_ALL == c.idTo)
			{ 
			}
			return r;
		}
		BLSTATUS OnBlCallLibFun(HWND h,UINT m,WPARAM w,LPARAM l)
		{
			BLSTATUS r = BL_STATUS_NOT_SUPPORT_INTERFACE;
			if(NULL==this)
			{
				r = BL_STATUS_PARAMETER_INVALID;
			}
			else
			{
				r= prCallLibFun(h,m,w,l);
			}
			return r;
		}
		void plLBtnDow(LPARAM l)
		{
			int i = (int)(short)LOWORD(l);
			int j = (int)(short)HIWORD(l);
			CPoint p(i,j);
			CRect r(x,y,x+w,y+h); 
			if (r.PtInRect(p))
			{		 
				m_bSelect = true; 
			}
			else
			{
				m_bSelect = false;
			}
		}
		void plShowMe(CLfDC &l)
		{ 
			l.OnXdDrawRect(x,y,w,h,RGB(255,255,0));
			l.OnXdDrawStr(x+5,y+5,m_szFileName);
			if(m_bSelect)
			{
				l.OnXdDrawRect(x-3,y-3,10,10,RGB(255,0,0));
				l.OnXdDrawRect(x+w-3,y-3,10,10,RGB(255,0,0));
				l.OnXdDrawRect(x-3,y+h-3,10,10,RGB(255,0,0));
				l.OnXdDrawRect(x+w-3,y+h-3,10,10,RGB(255,0,0));
				char sz[15];
				sprintf(sz,"index = %d",m_nIdx);
				l.OnXdDrawStr(x+5,y+25,sz); 
			}
		}
	private: 
		HMODULE		m_hModule;
		HWND		m_hWnd;
		char		m_szFileName[256];
		int			m_nIdx;
		int			x,y,w,h;
		bool		m_bSelect; 
		
		BLSTATUS pvCallLibFun(HWND h,char *szFun,UINT m,WPARAM w,LPARAM l)
		{
			BLSTATUS r = BL_STATUS_NOT_SUPPORT_INTERFACE; 
			
			if(NULL != m_hModule)
			{
				FARPROC pFunc = GetProcAddress(m_hModule, szFun);
				if (pFunc ) {
					r = (* (OnBLAPI *)pFunc)(h,m,w,l);   
				}
			}
			else
			{
				r = BL_STATUS_NOT_FOUND_LIBARY;
			}
			return r;
		}
		BLSTATUS prCallLibFun(HWND h,UINT m,WPARAM w,LPARAM l)
		{
			BLSTATUS r = BL_STATUS_NOT_SUPPORT_INTERFACE; 
			r = pvCallLibFun(h,"OnBlApi",m,w,l);
			return r;
		} 
		void pvLoad()
		{
			m_hModule = LoadLibrary(m_szFileName);
		}
		void pvUnLoad()
		{
			if(m_hModule)
			{
				FreeLibrary (m_hModule);
				m_hModule = NULL;
			}
		}
		void CB1Dll::pv2DoInCB(BYTE *p)  
		{
			static int i = 0; 
			if(m_bSelect)
			{
				::SendMessage(m_hWnd,BL_WM_B1_0XB101,(WPARAM)p,300);
			}
		}
		static int CALLBACK pvCallbackFunc(BL_CB_INF *pInfo)
		{
			int r = 0;
			CB1Dll *pThis = (CB1Dll*)pInfo->pCaller;
			BYTE *p = (BYTE*)pInfo->pParam;
			pThis->pv2DoInCB(p);
			
			return r;
		}
	};
	
	class CB1DllMng
	{
	public:
		CB1DllMng():m_nDlls(0){}
		~CB1DllMng()
		{ 
		}
		CB1Dll* pl2SelectDll(int idx)
		{
			CB1Dll* p = NULL;
			p = m_pDlls[idx];
			return p;
		}
		void plInitAll(HWND h)
		{

			for ( int i=0; i <0; ++ i)
			{ 
				if ( 0)
				{ 
					CB1Dll *p = NULL;
					BLSTATUS r = p->pl2Init(h);
				}
			}
		}
		void plLBtndow(LPARAM l)
		{
			for (int i=0;i<m_nDlls;i++)//vi = v.begin(); vi < v.end(); ++ vi)
			{ 
				if (m_pDlls[i])
				{ 
					CB1Dll *p = m_pDlls[i];
					p->plLBtnDow(l);
				}
			}
		}
		void plShowAll(CLfDC &l)
		{ 
			for(int i=0;i<m_nDlls;i++)// ( vi = v.begin(); vi != v.end(); ++ vi)
			{ 
				if ( m_pDlls[i])
				{ 
					CB1Dll *p = m_pDlls[i];//NULL;//(*vi);
					p->plShowMe(l);
				}
			}
		}
		void OnUnloadDlls()
		{   
			for (int i=0;i<m_nDlls;i++)// vi = v.begin(); vi != v.end(); ++ vi)
			{
				if (m_pDlls[i]){ 
					delete m_pDlls[i];//(*vi);
				}
			}
			
//			v.clear();
		}
		
		void plLoadDlls(HWND hWnd)
		{
			char szSearchPath[MAX_PATH], szDllPath[MAX_PATH],szBaseDir[MAX_PATH];
			char szBuffer[MAX_PATH];
			::GetModuleFileName(NULL, szBuffer, MAX_PATH - 1);
			
			xdGetBaseDir(szBuffer,szBaseDir); 
			
			wsprintf(szDllPath,"%s\\%s", szBaseDir, "B1");  
			
			wsprintf(szSearchPath,"%s\\%s", szDllPath, "*.dll");   
			
			WIN32_FIND_DATA wfd = {0};
			HANDLE handle = FindFirstFile(szSearchPath, &wfd);
			
			if (INVALID_HANDLE_VALUE == handle)
				return;
			
			int n = 0;
			do { 
				n++;
				char szDllFullName[MAX_PATH];
				wsprintf(szDllFullName,"%s\\%s", szDllPath,wfd.cFileName);  
				
				CB1Dll *p = new CB1Dll(hWnd,n,szDllFullName);	
				if (p != NULL) {
//					v.push_back(p);
					m_pDlls[m_nDlls] = p;
					m_nDlls++;
				}
				
			} while(FindNextFile(handle, &wfd));
			//	d.plMsgBox(n);
			FindClose(handle); 
		}
		
	private:
	private:
		void xdGetBaseDir(IN char* lpFileName,OUT char* lpDir)
		{
			char *p = lpFileName;
			char *pOut = lpDir;
			for(int i=0;'.'!=p[i];i++)
			{
				pOut[i] = p[i];
			}
			pOut[i] = NULL;
			for(int j=i;'\\'!=pOut[j];j--)//Search '\\'
			{
			}
			pOut[j] = NULL;
			
		}
		
//		std::vector<CB1Dll *>				m_VectorSet,&xdv;
//		std::vector<CB1Dll *>::iterator		vi;
		CB1Dll	*							m_pDlls[100];
		int									m_nDlls;
		CBlDebug							d;
		void x_Bottom_____(){}
	};
	class CMyMsg
	{
	public:
		CMyMsg(CMyLib *p):m_pLib(p){ 
			m_x		= 0;
			m_y		= 0;
			m_nDx	= 0;
			m_nDy	= 0;
			m_nMx	= 0;
			m_nMy	= 0;
		}
		~CMyMsg(){}
		void plDoMsg(HWND h,UINT m, WPARAM w, LPARAM l)
		{
			BLSTATUS r = pvDoMsg(h,m,w,l); 
		}
		void OnXdLBtnDown(int x,int y)
		{
			m_nDx = x;
			m_nDy = y;
		}
		void OnXdMouseMove(int x,int y)
		{  
		}
		
		void OnXdLBtnUp(int x,int y)
		{ 
		}
		
	private: 
		int		m_x;
		int		m_y;
		int		m_nDx,m_nDy;
		int		m_nMx,m_nMy; 
		CMyLib	*m_pLib;
		
		BLSTATUS pvDoMsg(HWND h,UINT m, WPARAM w, LPARAM l)
		{
			BLSTATUS r = BL_STATUS_NOT_SUPPORT_INTERFACE;
			switch(m)
			{   
			case BL_WM_B1_PRP_1:
				r = m_pLib->GetDll()->OnBlCallLibFun(h,m,w,l); 
				break;
			case BL_WM_CMD_B0_2_B1_01: 
				r = m_pLib->GetDll()->OnBlCallLibFun(h,m,w,l); 				
				break;
				
			case WM_KEYUP: 
			case WM_KEYDOWN:
			case WM_DEADCHAR:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			case WM_SYSCHAR:
			case WM_SYSDEADCHAR: 
			case WM_CHAR:
				{    
					m_pLib->GetDll()->OnBlCallLibFun(h,m,w,l);
					r = BL_STATUS_OK;
				}
				break;
			case WM_LBUTTONDOWN:
				{ 
					if(BL_ID_B1_MNG==w)
					{
						m_pLib->GetMng()->plLBtndow(l);
					}
					else
					{
						m_pLib->GetDll()->OnBlCallLibFun(h,m,w,l); 
					}

					r = BL_STATUS_OK;	

				}
				break;
			case WM_LBUTTONUP: 
				break;
			case WM_MOUSEMOVE: 
				break;
			case WM_SIZING:
				{
				}
				break;
			case  WM_PAINT:
				{ 
				}break;
			case WM_SIZE:
				{ 
					
				}
				break;
			default:
				r = BL_STATUS_OK;
				break;
			}
			return r;
		}
	};
	
	class CThread
	{
	public:
		
		//! Default constructor 
		CThread()
		{
			m_hThread = NULL;
			m_dwID = 0;
			m_bSuspended = false;
		}
		
		//! destructor
		virtual ~CThread() 
		{ 
			Release(1000); 
		}
		//! Get the thread's ID
		operator DWORD()
		{
			return m_dwID;
		}
	protected:
		//! Creates a thread
		BOOL pvCreate(
			LPTHREAD_START_ROUTINE pProcess,        //!< Thread function
			LPVOID pParam=NULL,                     //!< Parameter handed over to the thread function
			int Priority=THREAD_PRIORITY_NORMAL,    //!< The thread's priority
			DWORD CreationFlags = 0                 //!< Flags controlling the thread's creation
			)
		{
			ASSERT(pProcess);
			m_hThread = ::CreateThread(NULL, 0, pProcess, pParam, CreationFlags, &m_dwID);
			TRACE("CThread.Create(). Handle = %x, ID = %x\n", m_hThread, m_dwID);
			m_bSuspended = CreationFlags && CREATE_SUSPENDED;
			if( m_hThread==NULL ) 
				return FALSE;
			if( !::SetThreadPriority(m_hThread, Priority) ) {
				::CloseHandle(m_hThread);
				return FALSE;
			}
			return TRUE;
		}
		
		//! Close the thread handle and wait for the thread to die
		BOOL Release(DWORD timeout = INFINITE)
		{
			if( m_hThread==NULL ) 
				return TRUE;
			if ( WaitForSingleObject(m_hThread, timeout) != WAIT_OBJECT_0 )
			{
				// The thread didn't die. Terminate it
				TRACE("Must terminate thread. Handle = %x\n", m_hThread);
				Terminate(0);
				WaitForSingleObject(m_hThread, 10000);
			}
			
			return Detach();
		}
		
		//! Close the thread handle, but don't wait for the thread to die
		BOOL Detach()
		{
			if ( m_hThread == NULL )
				return TRUE;
			if( ::CloseHandle(m_hThread)==FALSE ) 
				return FALSE;
			m_hThread = NULL;
			m_dwID = 0;
			return TRUE;
		}
		
		//! Set the thread's priority
		BOOL SetPriority(int Priority)
		{
			ASSERT(m_hThread);
			return ::SetThreadPriority(m_hThread, Priority);
		}
		
		//! Suspend the thread
		BOOL Suspend()
		{
			ASSERT(m_hThread);
			if( m_bSuspended ) 
				return TRUE;
			if( ::SuspendThread(m_hThread)==-1 ) 
				return FALSE;
			m_bSuspended = true;
			return TRUE;
		}
		
		//! Resume the thread
		BOOL Resume()
		{
			ASSERT(m_hThread);
			if( !m_bSuspended ) return TRUE;
			if( ::ResumeThread(m_hThread)==-1 ) return FALSE;
			m_bSuspended = false;
			return TRUE;
		}
		
		//! Terminate the thread (don't...)
		BOOL Terminate(DWORD dwExitCode)
		{
			ASSERT(m_hThread);
			return ::TerminateThread(m_hThread, dwExitCode);
		}
		
		//! Get the thread's exit code
		BOOL GetExitCode(DWORD *pExitCode)
		{
			ASSERT(m_hThread);
			ASSERT(pExitCode);
			return ::GetExitCodeThread(m_hThread, pExitCode);
		}
		
		//! Get the thread's handle
		operator HANDLE() 
		{ 
			return m_hThread; 
		}
		
		
		//! Check if the thread is currently suspended
		bool IsSuspended() 
		{ 
			return m_bSuspended; 
		}
		
	private:
		//! The thread's handle
		HANDLE			m_hThread;
		
		//! The thread's ID
		DWORD			m_dwID;
		
		//! Indicates if the thread is currently suspended
		bool m_bSuspended;
		
	};   ///CThread
	class CMyThread: public CThread
	{
		#define NEARLYINFINITE       6000
	public:
		CMyThread():m_bRunning(true){
			m_hDisplayOver = CreateEvent(NULL, FALSE , FALSE, NULL);
		}
		~CMyThread(){
			CloseHandle(m_hDisplayOver);
		}
		void plRun(void *p)
		{
			m_bRunning = true;
			pvCreate(pvMyFun,p);
		}
		void pl2Stop()
		{
			m_bRunning = false;
			WaitForSingleObject(m_hDisplayOver, NEARLYINFINITE);
		}

		bool plIsRunning()
		{
			return m_bRunning;
		}
	private:
		static DWORD WINAPI			pvMyFun(void *p1)
		{
			DWORD dwR = 0;
			CMyLib*  pL = (CMyLib*) p1;
			HWND h = pL->GetHWnd();
			static n=300;
			static BYTE bt[300*300*3];
			int i=0;
			while(pL->GetMyThread()->plIsRunning())
			{ 
				i++;
				Sleep(10); 
				static CLfDC l;
				l.OnXdDrawRect(0,0,300,300,RGB(123,185,5));
				l.OnXd_DrawG();
				char s[115]; 
				sprintf(s,"BlMng.dll(%s): i=%03d [Sleep(10)]",MY_VERSION,i); 
				l.OnXdDrawStr(11,220,s);  
				l.OnXdDrawRect(200,50,30,30,RGB(255,0,0));
				pL->plShowDlls(l);
				l.OnXdGetData(300,300,bt);				
				l.plUpsidedown24Rgb(bt,300,300);   
			 
				PostMessage(h,BL_WM_B0_0XB001,(WPARAM)bt,n);
			} 
			SetEvent(pL->GetMyThread()->m_hDisplayOver);
			return dwR;
		}
	private:
		bool			m_bRunning;
		HANDLE			m_hDisplayOver; 
		
	};
	public:
		CMyLib(HWND h):m_hWnd(h),m_pSelectDll(NULL)
		{
			m_B1DllMng.plLoadDlls(h);
			plSelectDll(1);
			m_myThread.plRun(this);
		}
		~CMyLib(){}
		void plShowDlls(CLfDC &l)
		{  
			m_B1DllMng.plShowAll(l);
		} 
		void plSelectDll(int idx)
		{
			m_pSelectDll = m_B1DllMng.pl2SelectDll(idx);
		}
		CB1Dll* GetDll()
		{
			return m_pSelectDll;
		}
		CB1DllMng* GetMng()
		{
			return &m_B1DllMng;
		}
		CMyThread* GetMyThread()
		{
			return &m_myThread;
		}
		HWND GetHWnd()
		{
			return m_hWnd;
		}
		BLSTATUS plBlApi(HWND h,UINT m, WPARAM w, LPARAM l)
		{
			BLSTATUS			r		= BL_STATUS_NOT_SUPPORT_INTERFACE;
			BL_LPARAM_CONTEXT	*pBLC	= (BL_LPARAM_CONTEXT*)l;
			pv2Do(h,m,w,l);
			switch(m)
			{
			case WM_CLOSE:
				GetMyThread()->pl2Stop();
				break;
			case BL_WM_INIT:
				{
					char szW[1000];
					char szL[296]; 
					if(m_pSelectDll)
						m_pSelectDll->OnBlCallLibFun(m_hWnd,BL_WM_B0_0XB100,(WPARAM)szW,(LPARAM)szL);
					
					char szV[15];
					sprintf(szV,MY_VERSION); 
					char * szDev = (char*)w;
					if(szDev)
					{
						sprintf(szDev,"[B1Mng.dll %s]\n %s \n ",szV,DEVICE_LIST);
					}
					m_B1DllMng.plInitAll(h);
				}
				break;
			default:
				break;
			} 
			return r;
		}
	private:
		HWND						m_hWnd;
		CMyThread					m_myThread;  
		CB1Dll						*m_pSelectDll;
		CB1DllMng					m_B1DllMng;
		CBlDebug					d;  
		
		void pv2Do(HWND h,UINT m, WPARAM w, LPARAM l)
		{
			if(NULL==m_hWnd)
			{
				m_hWnd = h;
			} 
			if(h)
			{
				CMyMsg msg(this);	
				msg.plDoMsg(h,m,w,l);
			} 
			
		}
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_B1MNG_H__85330EF8_3B2E_4F71_B790_449A7598FAFC__INCLUDED_)
