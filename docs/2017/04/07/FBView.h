//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：FBView.h	类CFBView的头文件

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
#ifndef _FBVIEW_H__
#define _FBVIEW_H__
//####################################################################
#include "FBWnd.h"
//####################################################################
class CFBView : public CFBWnd
{
public:
	CFBView();
	~CFBView();

	BOOL Create(CFBWnd* pParent,UINT uID,UINT style = 0);

	void SetBkColor(COLORREF clr);
	void SetBkImage(HBITMAP hBmp);
	void SetBkImage(LPTSTR pszFilename);

protected:

	int			m_nBkMode;//背景模式,0:默认;1:单色;2:位图
	int			m_cxBkBmp,m_cyBkBmp;
	HDC			m_hBkBmpDC;
	HBRUSH		m_hBkBrush;

	virtual BOOL DrawBackground(HDC hDC);
	virtual void OnDraw(HDC hDC);
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};
//####################################################################
#endif//_FBVIEW_H__