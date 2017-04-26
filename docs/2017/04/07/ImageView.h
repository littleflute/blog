//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：ImageView.h	类CImageView的头文件

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
#ifndef _IMAGEVIEW_H__
#define _IMAGEVIEW_H__

#include "FBView.h"

#define FB_IVN_SELECTED		0xB301
//#####################################################################
typedef struct tagIMAGE_INFO{
	HBITMAP		hBmp;
	int			cx,cy;
	int			nPixelFmt;
}IMAGE_INFO,*LPIMAGE_INFO;
//#####################################################################
class CImageView : public CFBView
{
public:
	CImageView();
	~CImageView();

	BOOL LoadFormBMPFile(LPTSTR szFileName);
	BOOL LoadFromHandle(HBITMAP hBmp);
	BOOL SaveToBMPFile(LPTSTR szFileName);
	void SetEmpty();
	void CalcSize();
	BOOL Draw();
	BOOL Crop();

	BOOL IsEmpty(){
		return (m_ImgInfo.hBmp == NULL);}

	LPBITMAPINFO GetBitmapInfo(HBITMAP hBmp);

	LPIMAGE_INFO GetImageInfo(){
		return &m_ImgInfo;}

	void ResetPos(){
		m_xSrc = m_ySrc = 0;}

	static HBITMAP CopyBitmap(HDC hDC,HBITMAP hBmp);

	BOOL			m_bCanSel;
	RECT			m_rcSel;
protected:

	IMAGE_INFO		m_ImgInfo;
	RECT			m_rcDest;
	int				m_xSrc,m_ySrc;
	BOOL			m_xFlag,m_yFlag;
	POINT			m_ptBegin;
	BOOL			m_bMouseDown,m_bCanMove;

	static HCURSOR	m_hDownCur,m_hUpCur,m_hSelCur;

	void			OnLButtonDown(POINT& pt,UINT key);
	void			OnMouseMove(POINT& pt,UINT key);
	void			OnLButtonUp();
	BOOL			OnSetCursor();
	virtual void	OnDraw(HDC hDC);
	virtual BOOL	DrawBackground(HDC hDC);
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};
//#####################################################################
#endif//_IMAGEVIEW_H__