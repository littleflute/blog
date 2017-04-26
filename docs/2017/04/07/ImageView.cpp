//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：ImageView.cpp	类CImageView的执行文件

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
#include "ScreenCap.h"
#include "stdio.h"
#include "ImageView.h"
//#####################################################################
#define DIBSCANLINE_WIDTHBYTES(bits)    (((bits)+31)/32*4)
//#####################################################################
HCURSOR CImageView::m_hDownCur = NULL;
HCURSOR CImageView::m_hUpCur = NULL;
HCURSOR CImageView::m_hSelCur = LoadCursor(NULL,IDC_CROSS);
//#####################################################################
CImageView::CImageView()
{
	m_bMouseDown	= FALSE;
	m_bCanMove		= FALSE;
	m_bCanSel		= FALSE;

	SetRectEmpty(&m_rcSel);

	if(!m_hDownCur)
		m_hDownCur = LoadCursor(GetApp()->m_hInstance,MAKEINTRESOURCE(IDC_MOVE_DOWN));
	if(!m_hUpCur)
		m_hUpCur = LoadCursor(GetApp()->m_hInstance,MAKEINTRESOURCE(IDC_MOVE_UP));

	memset(&m_ImgInfo,0,sizeof(IMAGE_INFO));
}

CImageView::~CImageView()
{
	if(m_ImgInfo.hBmp)
		DeleteObject(m_ImgInfo.hBmp);
}
//####################################################################
LRESULT CImageView::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lResult = 0;

	switch(msg)
	{
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			OnLButtonDown(pt,(UINT)wParam);
		}
		break;
	case WM_LBUTTONUP:
		if(m_bCanSel)
		{
			ReleaseCapture();
			if(!IsRectEmpty(&m_rcSel))
				SendMessage(m_pOwner->m_hWnd,FBWM_NOTIFY,MAKEWPARAM(GetWndID(),FB_IVN_SELECTED),0);
		}
		if(m_bCanMove)
		{
			m_bMouseDown = FALSE;
			OnSetCursor();
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			OnMouseMove(pt,(UINT)wParam);
		}
		break;
	case WM_SIZE:
		CalcSize();
		Invalidate(TRUE);
		break;
	case WM_SETCURSOR:
		if(!OnSetCursor())
			lResult = DefWindowProc(m_hWnd,msg,wParam,lParam);
		break;
	case WM_RBUTTONUP:
		{
			HMENU hMenu = LoadMenu(GetInstance(),MAKEINTRESOURCE(IDR_CONTEXT));
			HMENU hSub = GetSubMenu(hMenu,0);
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			ClientToScreen(m_hWnd,&pt);
			TrackPopupMenu(hSub,TPM_LEFTALIGN|TPM_LEFTBUTTON
						   |TPM_RIGHTBUTTON,pt.x,pt.y,
						   0,m_pOwner->m_hWnd,NULL);
		}
		break;
    default:
		lResult = CFBView::WindowProc(msg,wParam,lParam);
		break;
	}

	return lResult;
}
//#####################################################################
BOOL CImageView::LoadFromHandle(HBITMAP hBmp)
{
	if(!hBmp)return FALSE;

	if(m_ImgInfo.hBmp)
	{
		DeleteObject(m_ImgInfo.hBmp);
		m_ImgInfo.hBmp = NULL;
	}

	m_ImgInfo.hBmp = hBmp;

	BITMAP bmp;
	GetObject(m_ImgInfo.hBmp,sizeof(BITMAP),&bmp);
	m_ImgInfo.cx = bmp.bmWidth;
	m_ImgInfo.cy = bmp.bmHeight;
	m_ImgInfo.nPixelFmt = bmp.bmBitsPixel;

	m_xSrc = m_ySrc = 0;
	CalcSize();

	return TRUE;
}
//#####################################################################
BOOL CImageView::LoadFormBMPFile(LPTSTR szFileName)
{
	HBITMAP hBmp = (HBITMAP)LoadImage(NULL,szFileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	return LoadFromHandle(hBmp);
}
//#####################################################################
void CImageView::SetEmpty()
{
	if(m_ImgInfo.hBmp)
		DeleteObject(m_ImgInfo.hBmp);

	memset(&m_ImgInfo,0,sizeof(IMAGE_INFO));
	SetRectEmpty(&m_rcDest);
	Invalidate();
}
//#####################################################################
BOOL CImageView::Draw()
{
	if(m_ImgInfo.hBmp == NULL)
		return FALSE;

	HDC hdc = GetDC(m_hWnd);
	HDC hBmpDC = CreateCompatibleDC(hdc);
	SelectObject(hBmpDC,m_ImgInfo.hBmp);

	BitBlt(hdc,m_rcDest.left,m_rcDest.top,m_rcDest.right - m_rcDest.left,
		   m_rcDest.bottom - m_rcDest.top,hBmpDC,m_xSrc,m_ySrc,SRCCOPY);

	if(m_bCanSel && !IsRectEmpty(&m_rcSel))
		DrawFocusRect(hdc,&m_rcSel);

	DeleteDC(hBmpDC);
	ReleaseDC(m_hWnd,hdc);

	return TRUE;
}
//#####################################################################
BOOL CImageView::Crop()
{
	if(!m_ImgInfo.hBmp || IsRectEmpty(&m_rcSel))
		return FALSE;

	HDC hDC = GetDC(m_hWnd);
	HDC hBmpDC = CreateCompatibleDC(hDC);
	HDC hImgDC = CreateCompatibleDC(hDC);
	if(!hBmpDC || !hImgDC)
		return FALSE;

	HBITMAP hBmp = CreateCompatibleBitmap(hDC,m_rcSel.right - m_rcSel.left,
										  m_rcSel.bottom - m_rcSel.top);
	if(!hBmp)
	{
		DeleteDC(hBmpDC);
		DeleteDC(hImgDC);
		return FALSE;
	}

	SelectObject(hBmpDC,hBmp);
	SelectObject(hImgDC,m_ImgInfo.hBmp);

	int x = m_rcSel.left + m_xSrc - m_rcDest.left;
	int y = m_rcSel.top + m_ySrc - m_rcDest.top;
	BitBlt(hBmpDC,0,0,m_rcSel.right - m_rcSel.left,
		   m_rcSel.bottom - m_rcSel.top,hImgDC,x,
		   y,SRCCOPY);

	LoadFromHandle(hBmp);
	DeleteDC(hBmpDC);
	DeleteDC(hImgDC);
	ReleaseDC(m_hWnd,hDC);

	SetRectEmpty(&m_rcSel);
	CalcSize();
	Invalidate();

	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////
void CImageView::CalcSize()
{
	if(m_ImgInfo.hBmp == NULL)return;

	RECT rc;
	GetClientRect(m_hWnd,&rc);
	int cx = rc.right - rc.left;
	int cy = rc.bottom - rc.top;

	if(cx == 0 || cy == 0)return;

	if(m_ImgInfo.cx < cx)
	{
		m_rcDest.left = (int)(cx - m_ImgInfo.cx)/2;
		m_rcDest.right = m_rcDest.left + m_ImgInfo.cx;
		m_xFlag = FALSE;
	}
	else
	{
		m_rcDest.left = rc.left;
		m_rcDest.right = rc.right;
		if(m_ImgInfo.cx == cx)
			m_xFlag = FALSE;
		else
			m_xFlag = TRUE;
	}

	if(m_ImgInfo.cy < cy)
	{
		m_rcDest.top = (int)(cy - m_ImgInfo.cy)/2;
		m_rcDest.bottom = m_rcDest.top + m_ImgInfo.cy;
		m_yFlag = FALSE;
	}
	else
	{
		m_rcDest.top = rc.top;
		m_rcDest.bottom = rc.bottom;
		if(m_ImgInfo.cy == cy)
			m_yFlag = FALSE;
		else
			m_yFlag = TRUE;
	}

	if(m_xFlag)
	{
		if(m_xSrc < 0)
			m_xSrc = 0;
		if(m_xSrc > (m_ImgInfo.cx - m_rcDest.right))
			m_xSrc = m_ImgInfo.cx - m_rcDest.right;
	}
	if(m_yFlag)
	{
		if(m_ySrc < 0)
			m_ySrc = 0;
		if(m_ySrc > (m_ImgInfo.cy - m_rcDest.bottom))
			m_ySrc = m_ImgInfo.cy - m_rcDest.bottom;
	}

	if(m_xFlag || m_yFlag)
		m_bCanMove = TRUE;
	else
		m_bCanMove = FALSE;
}
////////////////////////////////////////////////////////////////////////////////////
void CImageView::OnDraw(HDC hDC)
{
	CalcSize();
	Draw();
}
//####################################################################
BOOL CImageView::DrawBackground(HDC hDC)
{
	if(m_ImgInfo.hBmp)
		ExcludeClipRect(hDC,m_rcDest.left,m_rcDest.top,m_rcDest.right,m_rcDest.bottom);

	return CFBView::DrawBackground(hDC);
}
//####################################################################
BOOL CImageView::OnSetCursor()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(m_hWnd,&pt);

	if(!PtInRect(&m_rcDest,pt))
		return FALSE;

	if(m_bCanSel)
	{
		SetCursor(m_hSelCur);
		return TRUE;
	}

	if(m_bCanMove)
	{
		if(m_bMouseDown)
			SetCursor(m_hDownCur);
		else
			SetCursor(m_hUpCur);

		return TRUE;
	}

	return FALSE;
}
////////////////////////////////////////////////////////////////////////////////////
void CImageView::OnLButtonDown(POINT &pt,UINT key)
{
	if(m_bCanSel && !IsRectEmpty(&m_rcSel))
	{
		HDC hdc = GetDC(m_hWnd);
		DrawFocusRect(hdc,&m_rcSel);
		ReleaseDC(m_hWnd,hdc);
		SetRectEmpty(&m_rcSel);
	}

	if(PtInRect(&m_rcDest,pt))
	{
		m_bMouseDown = TRUE;
		m_ptBegin.x = pt.x;
		m_ptBegin.y = pt.y;

		if(m_bCanSel)
		{
			m_rcSel.left = m_rcSel.right = pt.x;
			m_rcSel.top = m_rcSel.bottom = pt.y;
			SetCapture(m_hWnd);
		}
		else
			OnSetCursor();
	}
}
////////////////////////////////////////////////////////////////////////////////////
void CImageView::OnMouseMove(POINT &pt,UINT key)
{
	BOOL bxMove,byMove;

	if(key == MK_LBUTTON && m_bCanSel)
	{
		HDC hdc = GetDC(m_hWnd);

		DrawFocusRect(hdc,&m_rcSel);

		m_rcSel.left = max(min(m_ptBegin.x,pt.x),m_rcDest.left);
		m_rcSel.top = max(min(m_ptBegin.y,pt.y),m_rcDest.top);
		m_rcSel.right = min(max(m_ptBegin.x,pt.x),m_rcDest.right);
		m_rcSel.bottom = min(max(m_ptBegin.y,pt.y),m_rcDest.bottom);

		DrawFocusRect(hdc,&m_rcSel);
		ReleaseDC(m_hWnd,hdc);
	}

	else if(key == MK_LBUTTON && m_bCanMove)
	{

		if(m_xFlag)
		{
			m_xSrc -= pt.x - m_ptBegin.x;
			m_ptBegin.x = pt.x;

			if(m_xSrc <0 )
			{
				m_xSrc = 0;
				bxMove = FALSE;
			}
			else if((m_xSrc + m_rcDest.right) > m_ImgInfo.cx)
			{
				m_xSrc =m_ImgInfo.cx - m_rcDest.right;
				bxMove = FALSE;
			}
			else
				bxMove = TRUE;
		}

		if(m_yFlag)
		{
			m_ySrc -= pt.y - m_ptBegin.y;
			m_ptBegin.y = pt.y;

			if(m_ySrc < 0)
			{
				m_ySrc = 0;
				byMove = FALSE;
			}
			else if((m_ySrc + m_rcDest.bottom) > m_ImgInfo.cy)
			{
				m_ySrc = m_ImgInfo.cy - m_rcDest.bottom;
				byMove = FALSE;
			}
			else
				byMove = FALSE;
		}

		if(bxMove || byMove)
			Draw();
	}
}
//####################################################################
BOOL CImageView::SaveToBMPFile(LPTSTR szFileName)
{
	if(!m_ImgInfo.hBmp || !szFileName)return FALSE;

    FILE*					pFile;	//文件指针
    BITMAPFILEHEADER		hdr;	//文件头
    LPBITMAPINFOHEADER		pbih;	//位图信息头
    LPBYTE					lpBits;	//内存指针 

	LPBITMAPINFO pbi = GetBitmapInfo(m_ImgInfo.hBmp);
	HDC hDC = GetDC(NULL);

    pbih = (LPBITMAPINFOHEADER) pbi;//从BITMAPINFO指针取得BITMAPINFOHEADER指针

	lpBits = new BYTE[pbih->biSizeImage];
    if (!lpBits)
		return FALSE;

    //得到DIB色彩表
    if (!GetDIBits(hDC, m_ImgInfo.hBmp, 0, (WORD) pbih->biHeight, 
                   lpBits, pbi, DIB_RGB_COLORS))
	{
		delete lpBits;
		delete pbih;
		return FALSE;
	}

	pFile = fopen(szFileName, "w+b");

	if(!pFile)
	{
		delete lpBits;
		delete pbih;
		return FALSE;
	}

    hdr.bfType = (WORD)('M'<<8)|'B';    //位图文件头位“BM”
	
	
	//计算整个文件的大小
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
                 pbih->biSize + pbih->biClrUsed 
                 * sizeof(RGBQUAD) + pbih->biSizeImage); 
 
    hdr.bfReserved1 = 0;
    hdr.bfReserved2 = 0; 
 
    //计算色彩数据阵列的位移
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
                    pbih->biSize + pbih->biClrUsed 
                    * sizeof (RGBQUAD); 
 

    //写入 BITMAPFILEHEADER (位图文件头)
	fseek(pFile,0,SEEK_SET);
	fwrite(&hdr,sizeof(BYTE),sizeof(BITMAPFILEHEADER),pFile);
	//位图信息头
	fwrite(pbih,sizeof(BYTE), sizeof(BITMAPINFOHEADER) 
                  + pbih->biClrUsed * sizeof (RGBQUAD),pFile);
 
    //写入色彩数据阵列
	fwrite(lpBits,sizeof(BYTE),pbih->biSizeImage,pFile);

	fclose(pFile);
	delete lpBits;
	delete pbih;

	return TRUE;
}
//####################################################################
LPBITMAPINFO CImageView::GetBitmapInfo(HBITMAP hBmp)
{
    BITMAP				bmp;//位图对象的BITMAP结构
    LPBITMAPINFO		pbmi;//位图信息结构指针 
	BITMAPINFOHEADER	bmih;//位图信息头结构
	WORD				size;
 
    //得到位图的BITMAP结构
    if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)) 
        return NULL;
 
	memset(&bmih,0,sizeof(BITMAPINFOHEADER));
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = bmp.bmWidth;
	bmih.biHeight = bmp.bmHeight;
	bmih.biPlanes = bmp.bmPlanes;
	bmih.biBitCount = bmp.bmBitsPixel;
	if ((bmih.biBitCount==16)||(bmih.biBitCount==32))
		bmih.biCompression = BI_BITFIELDS;
	else
		bmih.biCompression = BI_RGB;
	bmih.biSizeImage = bmp.bmHeight*DIBSCANLINE_WIDTHBYTES(bmp.bmWidth*bmp.bmBitsPixel);

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	bmih.biXPelsPerMeter = (cx*1000)/cx;
	bmih.biYPelsPerMeter = (cy*1000)/cy;

	if(bmih.biBitCount == 16 || bmih.biBitCount == 32)
		size = sizeof(DWORD)*3;
	else
		size = sizeof(RGBQUAD)*2^bmih.biBitCount;
	bmih.biClrUsed = 2^bmih.biBitCount;

	pbmi = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER) + size];
	if(!pbmi)
		return NULL;

	memcpy(pbmi,&bmih,sizeof(BITMAPINFOHEADER));

    return pbmi;
}
//###################################################################
HBITMAP CImageView::CopyBitmap(HDC hDC,HBITMAP hBmp)
{
	if(!hBmp || !hDC)
		return NULL;

	BITMAP bmp;
	HBITMAP hBmpDest = NULL;
	HDC hdcDest = NULL,hdcSrc = NULL;

	if(GetObject(hBmp,sizeof(BITMAP),&bmp) == 0)
		return NULL;

	hdcDest = CreateCompatibleDC(hDC);
	hdcSrc = CreateCompatibleDC(hDC);
	hBmpDest = CreateCompatibleBitmap(hDC,bmp.bmWidth,bmp.bmHeight);

	if(!hdcDest || !hdcSrc || !hBmpDest)
		goto Done;

	SelectObject(hdcDest,hBmpDest);
	SelectObject(hdcSrc,hBmp);

	BitBlt(hdcDest,0,0,bmp.bmWidth,bmp.bmHeight,hdcSrc,0,0,SRCCOPY);

Done:
	if(hdcDest)
		DeleteDC(hdcDest);
	if(hdcSrc)
		DeleteDC(hdcSrc);

	return hBmpDest;
}