//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���ChildView.cpp	��CChildView��ִ���ļ�

	��Ȩ��Firebird Software Workroom ����

	��������Դ����İ�Ȩ�ܡ��л����񹲺͹�����Ȩ�����Լ���
		  ����ط��ɺ���Լ�ı������κ��л���õ���Դ�����
		  ���˺ͻ�����δ��������ȷ��Ȩ�����ý���Դ��������
		  �κ���ҵĿ��(ֱ�ӵĻ��ӵ�)�����ڷ���ҵĿ�ĵ�ʹ
		  �� (�������ơ�������������޸�)�� ԭ����û���ر�
		  �������������������ĵ���˵������Դ��������ԭ
		  ���ߵ�����Ȩ��

	��д���ش���(chings)	2000.5

	���磺Tel��(0792)6323086	E_mail��chings@163.net
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
//���ڹ���
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
