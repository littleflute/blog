//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：FBCoolBar.cpp  类CFBCoolBar的执行文件

	版权：Firebird Software Workroom

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
#include "fclstd.h"
#include "FBCtrlBar.h"

//#######################################################################
//
//			class CFBCoolBar
//
//#########################################################################

//////////////////////////////////////////////////////////////////////
CFBCoolBar::CFBCoolBar()
{
	m_nBandCount	= 0;
	m_nLineCount	= 0;
	m_nBkFlag		= 0;
	m_hBkBmpDC		= NULL;
}

CFBCoolBar::~CFBCoolBar()
{
	if(m_hBkBmpDC)
		DeleteDC(m_hBkBmpDC);

	if(m_nBandCount)
	{
		for(int i=0;i<m_nBandCount;i++)
		{
			delete m_pBandInfo[i];
		}
	}

	if(m_nLineCount)
	{
		for(int i=0;i<m_nLineCount;i++)
		{
			delete m_pLineInfo[i];
		}
	}
}
//////////////////////////////////////////////////////////////////////
void CFBCoolBar::GetChildWndRect(LPRECT pRect)
{
	if(m_nBandCount == 0)return;

	int i,j,k,n;
	k = 0;
	for(j=0;j<m_nLineCount;j++)
	{
		n = m_pLineInfo[j]->nBandCount;
		for(i=0;i<n;i++)
		{
			m_pBandInfo[k+i]->rcBand.top = pRect->top;
			m_pBandInfo[k+i]->rcBand.bottom = pRect->top + m_pLineInfo[j]->nHeight;
			if(i==0)
				m_pBandInfo[k+i]->rcBand.left = pRect->left;
			else
				m_pBandInfo[k+i]->rcBand.left = m_pBandInfo[k+i-1]->rcBand.right;
			m_pBandInfo[k+i]->rcBand.right = m_pBandInfo[k+i]->rcBand.left + m_pBandInfo[i]->cxMinSize;
			if(j)
			{
				m_pBandInfo[k+i]->rcBand.top -= 1;
				m_pBandInfo[k+i]->rcBand.bottom -= 1;
			}
		}
		int space = pRect->right - m_pBandInfo[k+i-1]->rcBand.right;
		if(space>0)
		{
			for(i=0;i<n;i++)
			{
				m_pBandInfo[k+i]->rcBand.right += space;
				if(m_pBandInfo[k+i]->nIndex)
					m_pBandInfo[k+i]->rcBand.left += space;
			}
		}
		m_pBandInfo[k+i-1]->rcBand.right -= 3;
		pRect->top += m_pLineInfo[j]->nHeight;
		k += n;
	}
}
//////////////////////////////////////////////////////////////////////////
void CFBCoolBar::SetBkBitmap(HBITMAP hBmp,int type)
{
	if(!hBmp)return;

	BITMAP bmp;
	GetObject(hBmp, sizeof(bmp), &bmp);
	m_nBkBmpWidth = bmp.bmWidth;
	m_nBkBmpHeight = bmp.bmHeight;

	if(m_hBkBmpDC)
	{
		HBITMAP hb = (HBITMAP)GetCurrentObject(m_hBkBmpDC,OBJ_BITMAP);
		if(hb)
			DeleteObject(hb);
		DeleteDC(m_hBkBmpDC);
	}

	m_hBkBmpDC = CreateCompatibleDC(GetDC(m_hWnd));
	SelectObject(m_hBkBmpDC,hBmp);
	DeleteObject(hBmp);

	m_nBkFlag = type;

	Invalidate();
}
//////////////////////////////////////////////////////////////////////////
void CFBCoolBar::UseGradientBk(COLORREF clr1,COLORREF clr2,int style)
{
	int cx = GetSystemMetrics(SM_CXSCREEN);

	HBITMAP hBmp = CreateGradientBMP(GetDC(m_hWnd),clr1,
							clr2,cx,m_nHeight,style);
	SetBkBitmap(hBmp);
}
///////////////////////////////////////////////////////////////////////////
LRESULT CFBCoolBar::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lResult = 0;
	switch(msg)
	{
	case WM_ERASEBKGND:
		OnEraseBkgnd((HDC)wParam,lResult);
		break;
	default:
		lResult = CFBCtrlBar::WindowProc(msg,wParam,lParam);
		break;
	}
	return lResult;
}
//////////////////////////////////////////////////////////////////////////
void CFBCoolBar::AddBand(LPCB_BANDINFO pbi)
{
	if(m_nBandCount>=_BAND_MAXNUM)return;

	LPCB_BANDINFO pcbif = new CB_BANDINFO;

	pcbif->bShow = pbi->bShow;
	pcbif->cxMinSize = pbi->cxMinSize;
	pcbif->cyMinSize = pbi->cyMinSize;
	pcbif->hWnd = pbi->hWnd;
	pcbif->cchText = pbi->cchText;
	pcbif->pText = pbi->pText;
	pcbif->uID = pbi->uID;
	pcbif->nLines = pbi->nLines;
	if(pcbif->nLines>_LINE_MAXNUM -1)//不能超过最大行数
		pcbif->nLines = _LINE_MAXNUM -1;
	if(pcbif->nLines > m_nLineCount)//不能跳行
		pcbif->nLines = m_nLineCount;

	//如果Band有文本标题, 计算当前设备场境下文本字符串的逻辑尺寸, 以便挪出位置.
	if(pbi->cchText)
	{
		SIZE sz;
		HDC hDC = GetDC(m_hWnd);
		HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		SelectObject(hDC,hFont);
		GetTextExtentPoint(hDC,pbi->pText,pbi->cchText,&sz);
		pcbif->cxText = sz.cx;
		pcbif->cyText = sz.cy;
	}

	LPCB_LINEINFO pcli;

	if(m_nBandCount == 0 || pcbif->nLines > m_nLineCount-1)
	{
		pcli = new CB_LINEINFO;//新起一行
		pcli->nBandCount = 0;
		pcli->nHeight = 0;
		pcli->nVisibleCount = 0;
		m_pLineInfo[m_nLineCount] = pcli;

		m_nLineCount++;
		pcbif->nIndex = 0;

		if(m_nBandCount == 0)//第一个加上去的Band必须在第0行
			pcbif->nLines = 0;
	}
	else//不是新行
		pcbif->nIndex = m_pLineInfo[pcbif->nLines]->nBandCount;

	//在同一行中, 以最高的Band为基准
	//将行高加4是为了留出边框
	if(pcbif->cyMinSize+4 > m_pLineInfo[pcbif->nLines]->nHeight)
		m_pLineInfo[pcbif->nLines]->nHeight = pcbif->cyMinSize+4;

	int i;

	SetParent(pbi->hWnd,m_hWnd);//重置Band的父窗口
	m_pBandInfo[m_nBandCount] = pcbif;

	m_nBandCount++;
	m_pLineInfo[pcbif->nLines]->nBandCount++;
	if(pcbif->bShow)
		m_pLineInfo[pcbif->nLines]->nVisibleCount++;

	//CoolBar的高度等于各行高度相加
	m_nHeight = 0;
	for(i=0;i<m_nLineCount;i++)
	{
		if(m_pLineInfo[i]->nVisibleCount)
			m_nHeight += m_pLineInfo[i]->nHeight;
	}

	for(i=m_nBandCount-1;i>0;i--)
	{
		if(m_pBandInfo[i]->nLines < m_pBandInfo[i-1]->nLines)
		{
			pcbif = m_pBandInfo[i-1];
			m_pBandInfo[i-1] = m_pBandInfo[i];
			m_pBandInfo[i] = pcbif;
		}
		else
			break;
	}
}
//////////////////////////////////////////////////////////////////////////
void CFBCoolBar::OnSize()
{
	if(!m_nBandCount)return;

	RECT rc;
	GetClientRect(m_hWnd,&rc);
	GetChildWndRect(&rc);

	for(int i = m_nBandCount; i>0 ;i--)
		MoveChildWnd(i-1,TRUE);
}
//////////////////////////////////////////////////////////////////////////
void CFBCoolBar::MoveChildWnd(int nIndex,BOOL bRedraw)
{
	RECT rc;

	rc.left = m_pBandInfo[nIndex]->rcBand.left + 2;
	rc.top = m_pBandInfo[nIndex]->rcBand.top + 2;
	rc.right = m_pBandInfo[nIndex]->rcBand.right - 2;
	rc.bottom = m_pBandInfo[nIndex]->rcBand.bottom - 2;
	if(m_nStyle&CBS_GRIPPER)
		rc.left += 12;
	if(m_pBandInfo[nIndex]->bShow)
	{
		if(m_pBandInfo[nIndex]->cyMinSize < (rc.bottom - rc.top))
			rc.top += ((rc.bottom - rc.top) - m_pBandInfo[nIndex]->cyMinSize)/2;
		if(m_pBandInfo[nIndex]->cchText)
			rc.left += m_pBandInfo[nIndex]->cxText + 2;
		SetWindowPos(m_pBandInfo[nIndex]->hWnd,NULL,rc.left,rc.top,
						rc.right-rc.left,rc.bottom-rc.top,SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOCOPYBITS);//SWP_SHOWWINDOW);
	}
}
/////////////////////////////////////////////////////////////////////////
void CFBCoolBar::OnPaint(HDC hDC,LPRECT prcPaint)
{
	if(!IsShow())return;

	UINT style = m_nStyle;
	m_nStyle &= ~CBS_GRIPPER;
	CFBCtrlBar::OnPaint(hDC,prcPaint);
	m_nStyle = style;

	RECT rc;
	GetClientRect(m_hWnd,&rc);
	int rt = rc.right;

	for(int i=0;i<m_nBandCount;i++)
	{
		if(m_pBandInfo[i]->bShow)
		{
			rc.top = m_pBandInfo[i]->rcBand.top;
			rc.bottom = m_pBandInfo[i]->rcBand.bottom;
			rc.left = m_pBandInfo[i]->rcBand.left;
			rc.right = m_pBandInfo[i]->rcBand.right;
			if(m_pBandInfo[i]->nIndex == 0 && m_nLineCount>1 && m_pBandInfo[i]->nLines!=m_nLineCount-1)
			{
				rc.left += 1;
				rc.right = rt - 1;
				DrawEdge(hDC,&rc,EDGE_ETCHED,BF_BOTTOM);
				rc.left -= 1;
				rc.right = m_pBandInfo[i]->rcBand.right;
			}
			if(m_pBandInfo[i]->nIndex)
			{
				rc.top += 1;
				rc.bottom -= 1;
				DrawEdge(hDC,&rc,EDGE_ETCHED,BF_LEFT);
				rc.top -= 1;
				rc.bottom += 1;
			}
			if(m_nStyle&CBS_GRIPPER)
				DrawGripper(hDC,&rc);
			if(m_pBandInfo[i]->cchText)
			{
				::SetBkMode(hDC, TRANSPARENT);
				HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
				SelectObject(hDC,hFont);
				int x = m_pBandInfo[i]->rcBand.left + 14;
				int y =m_pBandInfo[i]->rcBand.top + (m_pBandInfo[i]->rcBand.bottom - m_pBandInfo[i]->rcBand.top - m_pBandInfo[i]->cyText)/2;
				TextOut(hDC,x,y,m_pBandInfo[i]->pText,m_pBandInfo[i]->cchText);
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////
int	CFBCoolBar::IdToIndex(UINT uID)
{
	if(m_nBandCount == 0)return -1;

	BOOL flag = FALSE;

	int i;
	for(i=0;i<m_nBandCount;i++)
	{
		if(m_pBandInfo[i]->uID == uID)
		{
			flag = TRUE;
			break;
		}
	}

	if(flag)
		return i;
	else
		return -1;
}
//////////////////////////////////////////////////////////////////////////
void CFBCoolBar::ShowBand(UINT uID,BOOL bShow)
{
	int nIndex = IdToIndex(uID);
	if(nIndex == -1)return;

	if(m_pBandInfo[nIndex]->bShow == bShow)
		return;

	m_pBandInfo[nIndex]->bShow = bShow;

	if(bShow)
	{
		ShowWindow(m_pBandInfo[nIndex]->hWnd,SW_SHOW);
		if(m_pLineInfo[m_pBandInfo[nIndex]->nLines]->nVisibleCount == 0)
		{
			m_nHeight += m_pLineInfo[m_pBandInfo[nIndex]->nLines]->nHeight;
			bShow = TRUE;
		}
		else
			bShow = FALSE;
		m_pLineInfo[m_pBandInfo[nIndex]->nLines]->nVisibleCount++;
		if(bShow)
			SendMessage(GetParent(m_hWnd),WM_SIZE,0,0);
		else
			MoveChildWnd(nIndex,TRUE);
	}
	else
	{
		ShowWindow(m_pBandInfo[nIndex]->hWnd,SW_HIDE);
		m_pLineInfo[m_pBandInfo[nIndex]->nLines]->nVisibleCount--;
		if(m_pLineInfo[m_pBandInfo[nIndex]->nLines]->nVisibleCount == 0)
		{
			m_nHeight -= m_pLineInfo[m_pBandInfo[nIndex]->nLines]->nHeight;
			bShow = TRUE;
			SendMessage(GetParent(m_hWnd),WM_SIZE,-1,-1);
		}
		else
			bShow = FALSE;
	}

	if(!bShow)
		RedrawWindow(m_hWnd,&m_pBandInfo[nIndex]->rcBand,NULL,RDW_ERASE|RDW_INVALIDATE|RDW_ERASENOW|RDW_ALLCHILDREN);
}
//////////////////////////////////////////////////////////////////////////
void CFBCoolBar::OnEraseBkgnd(HDC hDC,LRESULT& lResult)
{
	lResult = 1;

	switch(m_nBkFlag)
	{
	case 0:
		lResult = CFBCtrlBar::WindowProc(WM_ERASEBKGND,(WPARAM)hDC,0);
		break;
	case 1:
	case 2:
		{
			RECT rc;
			GetClientRect(m_hWnd,&rc);

			if(m_nBkFlag == 1)
				TileBitmap(hDC,&rc,m_hBkBmpDC,m_nBkBmpWidth,m_nBkBmpHeight);
			else if(m_nBkFlag == 2)
				StretchBlt(hDC,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top,
							m_hBkBmpDC,0,0,m_nBkBmpWidth,m_nBkBmpHeight,SRCCOPY);
			else
				lResult = CFBCtrlBar::WindowProc(WM_ERASEBKGND,(WPARAM)hDC,0);
		}
		break;
	default:
		lResult = CFBCtrlBar::WindowProc(WM_ERASEBKGND,(WPARAM)hDC,0);
		break;
	}
}
