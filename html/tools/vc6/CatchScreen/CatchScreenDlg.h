//Download by http://www.NewXing.com
// CatchScreenDlg.h : header file
//

#if !defined(AFX_CATCHSCREENDLG_H__536FDBC8_7DB2_4BEF_8943_70DBE8AD845F__INCLUDED_)
#define AFX_CATCHSCREENDLG_H__536FDBC8_7DB2_4BEF_8943_70DBE8AD845F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Resource.h"
#include "MyEdit.h"

#ifndef MYTRACKER_
#include "MyTracker.h"
#endif
/////////////////////////////////////////////////////////////////////////////
// CCatchScreenDlg dialog

class CCatchScreenDlg : public CDialog
{
private:
#pragma warning (disable : 4183)
	CCatchScreenDlg::xdSave2File(HDC hDC,HBITMAP hBmp,char *filePath)
	{
		HBITMAP				hBitmap = hBmp;

		int					iXdBits;
		WORD				wXdBitCount;
		DWORD				dwPaletteSize=0, dwBmBitsSize=0, dwDIBSize=0, dwWritten=0;
		BITMAP				Bitmap; 
		BITMAPFILEHEADER	bmfHdr; 
		BITMAPINFOHEADER	bi; 
		LPBITMAPINFOHEADER	lpbi; 
		HANDLE				fh, hDib, hPal,hOldPal=NULL;
		
		iXdBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);

		if (iXdBits <= 1)  wXdBitCount = 1;
		else if (iXdBits <= 4)  wXdBitCount = 4;
		else if (iXdBits <= 8)  wXdBitCount = 8;
		else      wXdBitCount = 24;
		
		GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
		bi.biSize   = sizeof(BITMAPINFOHEADER);
		bi.biWidth   = Bitmap.bmWidth;
		bi.biHeight   = Bitmap.bmHeight;
		bi.biPlanes   = 1;
		bi.biBitCount  = wXdBitCount;
		bi.biCompression = BI_RGB;
		bi.biSizeImage  = 0;
		bi.biXPelsPerMeter = 0;
		bi.biYPelsPerMeter = 0;
		bi.biClrImportant = 0;
		bi.biClrUsed  = 0;
		
		dwBmBitsSize = ((Bitmap.bmWidth * wXdBitCount + 31) / 32) * 4 * Bitmap.bmHeight;
		
		hDib = GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
		lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
		*lpbi = bi;
		
		hPal = GetStockObject(DEFAULT_PALETTE);
		if (hPal)
		{
			hDC = ::GetDC(NULL);
			hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);
			RealizePalette(hDC);
		}
		
		GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight,
			(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize, 
			(BITMAPINFO *)lpbi, DIB_RGB_COLORS);
		
		if (hOldPal)
		{
			::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
			RealizePalette(hDC);
			::ReleaseDC(NULL, hDC);
		}
		
		fh = CreateFile(filePath, GENERIC_WRITE,0, NULL, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		
		if (fh == INVALID_HANDLE_VALUE)  
			return 	0;
		
		bmfHdr.bfType = 0x4D42; // "BM"
		dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize; 
		bmfHdr.bfSize = dwDIBSize;
		bmfHdr.bfReserved1 = 0;
		bmfHdr.bfReserved2 = 0;
		bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
		
		WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
		WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
		
		GlobalUnlock(hDib);
		GlobalFree(hDib);
		CloseHandle(fh); 
	}

//**********************************************************************
public:

	int m_xScreen;
	int m_yScreen;

	BOOL m_bShowMsg;                //��ʾ��ȡ���δ�С��Ϣ
	BOOL m_bDraw;                   //�Ƿ�Ϊ��ȡ״̬
	BOOL m_bFirstDraw;              //�Ƿ�Ϊ�״ν�ȡ
	BOOL m_bQuit;                   //�Ƿ�Ϊ�˳�
	CPoint m_startPt;				//��ȡ�������Ͻ�
	CMyTracker m_rectTracker;     //��Ƥ����
	CBrush m_brush;					//
    HCURSOR m_hCursor;              //���
	CBitmap * m_pBitmap;            //����λͼ

	CRgn m_rgn;						//������������
public:
	HBITMAP CopyScreenToBitmap(LPRECT lpRect,BOOL bSave=FALSE);   //�������浽λͼ
	void DrawTip();                            //��ʾ������ʾ��Ϣ
	void DrawMessage(CRect &inRect,CDC * pDC);       //��ʾ��ȡ������Ϣ
	void PaintWindow();               //�ػ�����
//**********************************************************************
// Construction
public:
	void ChangeRGB();
	
	
	CCatchScreenDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCatchScreenDlg)
	enum { IDD = IDD_CATCHSCREEN_DIALOG };
	CMyEdit	m_tipEdit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCatchScreenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCatchScreenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CATCHSCREENDLG_H__536FDBC8_7DB2_4BEF_8943_70DBE8AD845F__INCLUDED_)
