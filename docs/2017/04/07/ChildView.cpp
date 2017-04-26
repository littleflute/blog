//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：ChildView.cpp	类CChildView的执行文件

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
#include "ImageView.h"
#include "ChildView.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChildView::CChildView()
{
}

CChildView::~CChildView()
{

}
//////////////////////////////////////////////////////////////////////
//窗口过程
LRESULT CChildView::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == FBWM_SETSIZE)
	{
		LPRECT prc = (LPRECT)lParam;

		SetWindowPos(m_hWnd,NULL,prc->left,prc->top,
				prc->right - prc->left,prc->bottom - prc->top,
				SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOCOPYBITS);
		return 0;
	}
	
	return CFBTabCtrl::WindowProc(msg,wParam,lParam);
}
//////////////////////////////////////////////////////////////////////
int CChildView::AddImage(HBITMAP hBmp,LPTSTR pszCaption)
{
	if(hBmp == NULL)return -1;

	CImageView* pImg = new CImageView();

	if(!pImg->Create(this,(UINT)GetItemCount()+0xC800))
	{
		delete pImg;
		return -1;
	}

	pImg->SetBkColor(m_clrBack);

	if(pImg->LoadFromHandle(hBmp) == FALSE)
	{
		delete pImg;
		return -1;
	}

	int n = AddView(pImg,pszCaption);
	
	if(n == -1)
	{
		DeleteObject(hBmp);
		delete pImg;
		return -1;
	}

	pImg->SetOwner(m_pOwner);

	SetActiveView(n);
	Invalidate(TRUE);
	return n;
}
//////////////////////////////////////////////////////////////////////
int CChildView::AddImage(LPTSTR szFileName)
{
	HBITMAP hBmp = (HBITMAP)LoadImage(NULL,szFileName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	int i = lstrlen(szFileName) -1;
	for(;i>0;i--)
	{
		if(szFileName[i] == '\\')
			break;
	}

	return AddImage(hBmp,szFileName+(i+1));
}
//////////////////////////////////////////////////////////////////////
BOOL CChildView::SaveCurrentImage(LPTSTR szFile)
{
	CImageView* pView = (CImageView*)m_pActiveView;
	if(!pView)return FALSE;

	return pView->SaveToBMPFile(szFile);
}
//////////////////////////////////////////////////////////////////////
void  CChildView::EnableSelect(BOOL bEnable)
{
	if(!m_pActiveView)
		return;

	CImageView* pImg = (CImageView*)m_pActiveView;

	if(pImg->IsEmpty())
		return;

	pImg->m_bCanSel = bEnable;
}
//////////////////////////////////////////////////////////////////////
void  CChildView::ChangeBkColor(COLORREF clr)
{
	if(m_clrBack == clr)
		return;

	m_clrBack = clr;

	int n = GetItemCount();
	if(n == 0)return;

	CImageView* pImg;

	for(int i = 0; i<n; i++)
	{
		pImg = (CImageView*)GetAt(i);
		if(pImg)
			pImg->SetBkColor(clr);
	}

	if(m_pActiveView)
		m_pActiveView->Invalidate();
}
