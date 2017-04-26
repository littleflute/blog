//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：FBCtrlBar.cpp  类CFBCtrlBar的执行文件

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
#include "resource.h"
#include "FBCtrlBar.h"

//#######################################################################
//
//			class CFBCtrlBar
//
//#########################################################################
#define MOUSEMOVE_HOR		0x00000001
#define MOUSEMOVE_VER		0x00000002
#define MOUSEMOVE_ALL		0x00000003
//////////////////////////////////////////////////////////////////////
// 构造函数和析构函数
//////////////////////////////////////////////////////////////////////
CFBCtrlBar::CFBCtrlBar()
{
	m_bDock			= FALSE;
	m_bDown			= FALSE;
	m_nSizeFlag		= SIZEFLAG_NON;

	SetRectEmpty(&m_rcOver);
}

CFBCtrlBar::~CFBCtrlBar()
{
}
///////////////////////////////////////////////////////////////////////
//窗口过程
LRESULT CFBCtrlBar::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lResult = 0;

	switch(msg)
	{
	case WM_PAINT:
		{
			if(!GetUpdateRect(m_hWnd,NULL,FALSE))
				return 0;

			PAINTSTRUCT ps;
			BeginPaint(m_hWnd,&ps);
			OnPaint(ps.hdc,&ps.rcPaint);
			EndPaint(m_hWnd,&ps);
		}
		break;
	case WM_SIZE:
		OnSize();
		break;
	case FBWM_SETSIZE:
		OnSetSize((LPRECT)lParam);
		break;
	case WM_CLOSE:
		ShowWindow(m_hWnd,SW_HIDE);
		if(m_pOwner)
			lResult = SendMessage(m_pOwner->m_hWnd,FBWM_NOTIFY,MAKEWPARAM(GetWndID(),FB_CBN_CLOSE),0);
		break;
	case WM_COMMAND:
		if(m_pOwner)
			lResult = SendMessage(m_pOwner->m_hWnd,msg,wParam,lParam);
		break;
	case WM_NCLBUTTONDBLCLK://在标题栏双击时恢复上一次的停靠状态
		if(wParam != HTCAPTION)
			return CFBWnd::WindowProc(msg,wParam,lParam);
		DockStateChange(m_nPreState);
		break;
	case WM_LBUTTONDBLCLK:
		if(m_nStyle & CBS_FLYBY)
		{
			POINT pos;
			pos.x = LOWORD(lParam);
			pos.y = HIWORD(lParam);
			if(HitTest(&pos) == HITTEST_GRIPPER)
				DockStateChange(m_nPreState);
		}
		break;
	case WM_NCLBUTTONDOWN:
		if(wParam != HTCAPTION)
			return CFBWnd::WindowProc(msg,wParam,lParam);
		else
		{
			POINT pos;
			pos.x = LOWORD(lParam);
			pos.y = HIWORD(lParam);
			ScreenToClient(m_hWnd,&pos);
			OnLButtonDown(&pos,wParam);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pos;
			pos.x = LOWORD(lParam);
			pos.y = HIWORD(lParam);
			OnLButtonDown(&pos,wParam);
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pos;
			pos.x = LOWORD(lParam);
			pos.y = HIWORD(lParam);
			OnLButtonUp(&pos,wParam);
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pos;
			pos.x = LOWORD(lParam);
			pos.y = HIWORD(lParam);
			OnMouseMove(&pos,wParam);
		}
		break;
	case WM_SETCURSOR:
		{
			POINT pos;
			GetCursorPos(&pos);
			ScreenToClient(m_hWnd,&pos);
			if((HitTest(&pos) == HITTEST_SIZER && m_nDockState) || 
				(m_nSizeFlag != SIZEFLAG_NON && m_bDown))
			{
				HCURSOR hcur;
				if(m_nDockState& (CB_DOCK_TOP|CB_DOCK_BOTTOM))
				{
					hcur = LoadCursor(GetInstance(),MAKEINTRESOURCE(IDC_SIZINGNS));
					m_nSizeFlag = SIZEFLAG_NS;
				}
				else
				{
					hcur = LoadCursor(GetInstance(),MAKEINTRESOURCE(IDC_SIZINGWE));
					m_nSizeFlag = SIZEFLAG_WE;
				}
				SetCursor(hcur);
			}
			else
			{
				lResult = CFBWnd::WindowProc(msg,wParam,lParam);
				m_nSizeFlag = SIZEFLAG_NON;
			}
		}
		break;
	case WM_NOTIFY:
		OnNotify((LPNMHDR)lParam,lResult);
		break;
	default:
		lResult = CFBWnd::WindowProc(msg,wParam,lParam);
		break;
	}

	return lResult;
}
/////////////////////////////////////////////////////////////////////////////
BOOL CFBCtrlBar::Create(LPSTR		lpszCaption,
						CFBWnd*		pParent,
						UINT		nStyle,
						int			width,
						int			height,
						UINT		uID)
{
	m_nWidth = width;
	m_nHeight = height;
	m_nStyle = nStyle;

	UINT style = WS_CHILD|WS_VISIBLE;//|WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CFBWnd::Create(CLS_FBSTDWNDCLASS,
						  lpszCaption,
						  pParent->GetInstance(),
						  pParent,
						  style,
						  WS_EX_TOOLWINDOW,
						  (HMENU)uID);
}
//////////////////////////////////////////////////////////////////////////
void CFBCtrlBar::OnSetSize(LPRECT pRect)
{
	if(!m_bDock || !IsShow())return;

	RECT rc;
	CopyRect(&rc,pRect);

	switch(m_nDockState)
	{
	case CB_DOCK_TOP:
		rc.bottom = rc.top + m_nHeight;
		pRect->top += m_nHeight;
		break;
	case CB_DOCK_BOTTOM:
		rc.top = rc.bottom - m_nHeight;
		pRect->bottom -= m_nHeight;
		break;
	case CB_DOCK_LEFT:
		rc.right = rc.left + m_nWidth;
		pRect->left += m_nWidth;
		break;
	case CB_DOCK_RIGHT:
		rc.left = rc.right - m_nWidth;
		pRect->right -= m_nWidth;
		break;
	default:
		break;
	}

	if(m_nDockState != CB_DOCK_NON)
		SetWindowPos(m_hWnd,NULL,rc.left,rc.top,
			rc.right-rc.left,rc.bottom-rc.top,
			SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOCOPYBITS);
}
//////////////////////////////////////////////////////////////////////////
void CFBCtrlBar::OnSize()
{
	if((m_nStyle&CBS_FLYBY) && (m_nDockState == CB_DOCK_NON))
	{
		RECT rc;
		GetWindowRect(m_hWnd,&rc);
		CopyRect(&m_rcOver,&rc);
	}
}
///////////////////////////////////////////////////////////////////////////
void CFBCtrlBar::OnPaint(HDC hDC,LPRECT prcPaint)
{
	if(!m_bDock)return;

	RECT rc;
	GetClientRect(m_hWnd,&rc);

	UINT style = m_nStyle & CBS_BORDER_RECT;

	if(style)//画边框
	{
		if(style == CBS_BORDER_RECT)
			DrawEdge(GetDC(m_hWnd),&rc,EDGE_ETCHED,BF_RECT);
		else
		{
			if(style & CBS_BORDER_TOP)
				DrawEdge(GetDC(m_hWnd),&rc,EDGE_ETCHED,BF_TOP);
			if(style & CBS_BORDER_BOTTOM)
				DrawEdge(GetDC(m_hWnd),&rc,EDGE_ETCHED,BF_BOTTOM);
			if(style & CBS_BORDER_LEFT)
				DrawEdge(GetDC(m_hWnd),&rc,EDGE_ETCHED,BF_LEFT);
			if(style & CBS_BORDER_RIGHT)
				DrawEdge(GetDC(m_hWnd),&rc,EDGE_ETCHED,BF_RIGHT);
		}
	}
	if(m_nStyle & CBS_GRIPPER)//画把手
		DrawGripper(hDC,&rc);
}
////////////////////////////////////////////////////////////////////////
void CFBCtrlBar::Docking(UINT nDockState)
{
	m_bDock = TRUE;
	m_nDockState = nDockState;
	m_nPreState = nDockState;
}
////////////////////////////////////////////////////////////////////////////
//画把手
void CFBCtrlBar::DrawGripper(HDC hDC,LPRECT pRc)
{
	switch(m_nDockState)
	{
	case CB_DOCK_TOP:
	case CB_DOCK_BOTTOM:
		m_rcGripper.top = pRc->top + 2;
		m_rcGripper.bottom = pRc->bottom - 2;
		m_rcGripper.left = pRc->left + 4;
		m_rcGripper.right = m_rcGripper.left +8;
		pRc->top += 2;
		pRc->bottom -= 2;
		pRc->left += 4;
		pRc->right = pRc->left + 3;
		DrawEdge(hDC,pRc,BDR_RAISEDINNER,BF_RECT);
		pRc->left += 4;
		pRc->right += 4;
		DrawEdge(hDC,pRc,BDR_RAISEDINNER,BF_RECT);
		break;
	case CB_DOCK_LEFT:
	case CB_DOCK_RIGHT:
		m_rcGripper.left = pRc->left + 2;
		m_rcGripper.right = pRc->right - 2;
		m_rcGripper.top = pRc->top + 4;
		m_rcGripper.bottom = m_rcGripper.top +8;
		pRc->left += 2;
		pRc->right -= 2;
		pRc->top += 5;
		pRc->bottom = pRc->top + 3;
		DrawEdge(hDC,pRc,BDR_RAISEDINNER,BF_RECT);
		pRc->top += 4;
		pRc->bottom += 4;
		DrawEdge(hDC,pRc,BDR_RAISEDINNER,BF_RECT);
		break;
	}
}
////////////////////////////////////////////////////////////////////////////
void CFBCtrlBar::OnNotify(LPNMHDR pNMHDR,LRESULT& lResult)
{
	if(pNMHDR->hwndFrom != m_hWnd)
		SendMessage(pNMHDR->hwndFrom,WM_NOTIFY,(WPARAM)pNMHDR->idFrom,(LPARAM)pNMHDR);
}
////////////////////////////////////////////////////////////////////////////
void CFBCtrlBar::OnLButtonDown(LPPOINT pPos,UINT key)
{
	m_bDown = TRUE;
	SetCapture(m_hWnd);

	m_BeginP.x = m_MoveP.x = pPos->x;
	m_BeginP.y = m_MoveP.y = pPos->y;

	if(m_nSizeFlag != SIZEFLAG_NON)
	{
		m_nSized = 0;
		DrawSizeFlag();
		return;
	}

	if(!(m_nStyle&CBS_FLYBY) || HitTest(pPos)!=HITTEST_GRIPPER)
	{
		m_bDown = FALSE;
		ReleaseCapture();
		return;
	}


	SetCapture(m_hWnd);
	m_nFlyState = m_nDockState;

	GetWindowRect(m_hWnd,&m_rcFlyby);

	if(m_nFlyState != CB_DOCK_NON)
		LineRect(GetDC(NULL),&m_rcFlyby);
	else
		DrawDragRect(GetDC(NULL),&m_rcFlyby);
}
////////////////////////////////////////////////////////////////////////////
void CFBCtrlBar::OnLButtonUp(LPPOINT pPos,UINT key)
{
	if(!m_bDown)return;

	m_bDown = FALSE;
	ReleaseCapture();

	if(m_nSizeFlag != SIZEFLAG_NON)
	{
		DrawSizeFlag();

		if(m_nSized != 0)
		{
			if(m_nSizeFlag == SIZEFLAG_WE)//东西向拖动大小
			{
				if(m_nDockState == CB_DOCK_LEFT)
					m_nWidth += m_nSized;
				else
					m_nWidth -= m_nSized;
			}
			else//南北向拖动大小
			{
				if(m_nDockState == CB_DOCK_TOP)
					m_nHeight += m_nSized;
				else
					m_nHeight -= m_nSized;
			}

			SendMessage(m_pOwner->m_hWnd,FBWM_SETSIZE,0,0);
		}

		m_nSizeFlag = SIZEFLAG_NON;

		return;
	}

	if(!(m_nStyle&CBS_FLYBY))return;

	if(m_nFlyState != CB_DOCK_NON)
		LineRect(GetDC(NULL),&m_rcFlyby);
	else
	{
		DrawDragRect(GetDC(NULL),&m_rcFlyby);
		CopyRect(&m_rcOver,&m_rcFlyby);
	}

	DockStateChange(m_nFlyState);
}
////////////////////////////////////////////////////////////////////////////
void CFBCtrlBar::OnMouseMove(LPPOINT pPos,UINT key)
{
	if(!m_bDown)return;

	if(m_nSizeFlag != SIZEFLAG_NON)
	{
		DrawSizeFlag();

		m_MoveP.x = pPos->x;
		m_MoveP.y = pPos->y;

		if(m_nSizeFlag == SIZEFLAG_WE)
			m_nSized = m_MoveP.x - m_BeginP.x;
		else
			m_nSized = m_MoveP.y - m_BeginP.y;

		DrawSizeFlag();
		return;
	}

	if(!(m_nStyle&CBS_FLYBY))return;

	if(m_nFlyState != CB_DOCK_NON)
		LineRect(GetDC(NULL),&m_rcFlyby);
	else
		DrawDragRect(GetDC(NULL),&m_rcFlyby);
	
	m_rcFlyby.left += pPos->x - m_MoveP.x;
	m_rcFlyby.top += pPos->y - m_MoveP.y;
	m_rcFlyby.right += pPos->x - m_MoveP.x;
	m_rcFlyby.bottom += pPos->y - m_MoveP.y;

	UINT flag = 0;
	if(pPos->x != m_BeginP.x)
		flag |= MOUSEMOVE_HOR;
	if(pPos->y != m_BeginP.y)
		flag |= MOUSEMOVE_VER;

	if(GetFlybySide(flag))
	{
		RECT rc;
		GetClientRect(m_pOwner->m_hWnd,&rc);
		switch(m_nFlyState)
		{
		case CB_DOCK_TOP:
		case CB_DOCK_BOTTOM:
			{
				m_rcFlyby.right = m_rcFlyby.left+rc.right-rc.left;
				m_rcFlyby.bottom = m_rcFlyby.top + m_nHeight;
			}
			break;
		case CB_DOCK_LEFT:
		case CB_DOCK_RIGHT:
			{
				m_rcFlyby.bottom = m_rcFlyby.top + rc.bottom - rc.top;
				m_rcFlyby.right = m_rcFlyby.left + m_nWidth;
			}
			break;
		default:
			{
				if(IsRectEmpty(&m_rcOver))
				{
					m_rcFlyby.right = m_rcFlyby.left + 300;
					m_rcFlyby.bottom = m_rcFlyby.top + 240;
				}
				else
				{
					m_rcFlyby.right = m_rcFlyby.left + m_rcOver.right - m_rcOver.left;
					m_rcFlyby.bottom = m_rcFlyby.top + m_rcOver.bottom - m_rcOver.top;
				}
			}
			break;
		}
	}

	if(m_nFlyState != CB_DOCK_NON)
		LineRect(GetDC(NULL),&m_rcFlyby);
	else
		DrawDragRect(GetDC(NULL),&m_rcFlyby);

	m_MoveP.x = pPos->x;
	m_MoveP.y = pPos->y;
}
////////////////////////////////////////////////////////////////////////////
void CFBCtrlBar::DrawSizeFlag()
{
	RECT rc;
	if(m_nSizeFlag == SIZEFLAG_WE)
	{
		rc.left = m_rcSizer.left + m_nSized;
		rc.right = rc.left + 4;
		rc.top = m_rcSizer.top;
		rc.bottom = m_rcSizer.bottom;
	}
	else
	{
		rc.left = m_rcSizer.left;
		rc.right = m_rcSizer.right;
		rc.top = m_rcSizer.top + m_nSized;
		rc.bottom = rc.top + 4;
	}

	ClientToScreen(m_hWnd,&rc);
	
	DrawDragRect(GetDC(NULL),&rc,2);
}
////////////////////////////////////////////////////////////////////////////
BOOL CFBCtrlBar::GetFlybySide(UINT flag)
{
	RECT rc;
	POINT pos;
	GetWindowRect(m_pOwner->m_hWnd,&rc);
	GetCursorPos(&pos);

	UINT FlyState = 0;

	if(PtInRect(&rc,pos))
	{
		switch(flag)
		{
		case MOUSEMOVE_VER:
			{
				if((pos.y-rc.top)<m_nHeight)
					FlyState = CB_DOCK_TOP;
				if((rc.bottom-pos.y)<m_nHeight)
					FlyState = CB_DOCK_BOTTOM;
			}
			break;
		case MOUSEMOVE_HOR:
			{
				if((pos.x - rc.left)<m_nWidth)
					FlyState = CB_DOCK_LEFT;
				if((rc.right - pos.x)<m_nWidth)
					FlyState = CB_DOCK_RIGHT;
			}
			break;
		case MOUSEMOVE_ALL:
			{
				if((pos.y-rc.top)<m_nHeight)
				{
					if(((pos.x - rc.left)<m_nWidth) && ((pos.y-rc.top)>(pos.x - rc.left)))
						FlyState = CB_DOCK_LEFT;
					else if(((rc.right - pos.x)<m_nWidth) && ((pos.y-rc.top)>(rc.right - pos.x)))
						FlyState = CB_DOCK_RIGHT;
					else
						FlyState = CB_DOCK_TOP;
				}
				else if((rc.bottom-pos.y)<m_nHeight)
				{
					if(((pos.x - rc.left)<m_nWidth) && ((rc.bottom-pos.y)>(pos.x - rc.left)))
						FlyState = CB_DOCK_LEFT;
					else if(((rc.right - pos.x)<m_nWidth) && ((rc.bottom-pos.y)>(rc.right - pos.x)))
						FlyState = CB_DOCK_RIGHT;
					else
						FlyState = CB_DOCK_BOTTOM;
				}
				else
				{
					if((pos.x - rc.left)<m_nWidth)
						FlyState = CB_DOCK_LEFT;
					if((rc.right - pos.x)<m_nWidth)
						FlyState = CB_DOCK_RIGHT;
				}
			}
			break;
		default:
			FlyState = CB_DOCK_NON;
			break;
		}
	}

	if(m_nFlyState == FlyState)
		return FALSE;

	m_nFlyState = FlyState;
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////
//停靠状态改变，必须重新安排窗口位置
void CFBCtrlBar::DockStateChange(UINT state)
{
	if(m_nDockState != state)
	{
		m_nPreState = m_nDockState;
		if(m_nDockState == CB_DOCK_NON)
		{
			ModifyWndStyle(WS_OVERLAPPEDWINDOW,WS_CHILD);
			SetParent(m_hWnd,m_pOwner->m_hWnd);
			m_bDock = TRUE;
		}
		m_nDockState = state;
		if(state == CB_DOCK_NON)
		{
			ModifyWndStyle(WS_CHILD,WS_OVERLAPPEDWINDOW);
			SetParent(m_hWnd,NULL);
			m_bDock = FALSE;
			SetWindowPos(m_hWnd,HWND_TOPMOST,m_rcOver.left,
							m_rcOver.top,
							m_rcOver.right - m_rcOver.left,
							m_rcOver.bottom - m_rcOver.top,
							SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOCOPYBITS);
		}
		SendMessage(m_pOwner->m_hWnd,FBWM_SETSIZE,0,0);
	}
	else if(m_nDockState == CB_DOCK_NON)
	{
		RECT rc;
		GetWindowRect(m_hWnd,&rc);
		if(rc.left!=m_rcFlyby.left || rc.top!=m_rcFlyby.top)
			SetWindowPos(m_hWnd,HWND_TOPMOST,m_rcOver.left,
							m_rcOver.top,
							m_rcOver.right - m_rcOver.left,
							m_rcOver.bottom - m_rcOver.top,
							SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOCOPYBITS);
	}
}
////////////////////////////////////////////////////////////////////////////
LONG CFBCtrlBar::HitTest(LPPOINT pPos)
{
	if(PtInRect(&m_rcGripper,*pPos))
		return HITTEST_GRIPPER;
	if(PtInRect(&m_rcSizer,*pPos))
		return HITTEST_SIZER;

	POINT p;
	p.x = pPos->x;
	p.y = pPos->y;
	ClientToScreen(m_hWnd,&p);
	if(SendMessage(m_hWnd,WM_NCHITTEST,0,MAKELPARAM(p.x,p.y)) == HTCAPTION)
		return HITTEST_GRIPPER;

	return 0;
}

