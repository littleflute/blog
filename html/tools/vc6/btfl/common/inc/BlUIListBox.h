// File: BlUIListBox.h( V0.0.1.6 )
/* 
--2016.04.18 Mon 11:10bj--HYL-2149 Alfred,STL,MO. USA-- 
1.  BlUIListBox.h( V0.0.1.6 )	 
*/
#if !defined(_BEAUTIFULLOVER_UI_LISTBOX_H_)         
#define _BEAUTIFULLOVER_UI_LISTBOX_H_

/* By C++ language compiler */
#ifdef __cplusplus
extern "C" {
#endif    
//--------------------------------------------------------------------- 
	
	
	
	struct ItemInfo
	{
		int	     type;
		int      index;
		CString  text;
		COLORREF color;
		HICON    icon;
	};
	
	class CIconBtn 
	{
	public:
		CIconBtn::CIconBtn()
			: m_rSize(CRect(0, 0, 0, 0)), m_bFocusedState(false),m_bSelectMe(0)
		{
		} 
		virtual ~CIconBtn(){}
		void plSetSelected(bool b)
		{
			m_bSelectMe = b;
		}
		
		void CIconBtn::SetFocusedState(bool bFocused)
		{ 
			m_bFocusedState = bFocused;
			Draw();
		}
		
	public:
		void SetSize(const CRect& rect)				{ m_rSize = rect;						}
		
		bool GetFocusedState() const				{ return m_bFocusedState;				}
		BOOL TestInArea(const CPoint& point) const	
		{ 
			BOOL b = m_rSize.PtInRect(point); 
			return b;
		}
		
		virtual void Draw()  = 0;
		virtual void Click() = 0;
		virtual void plBlFun(UINT m, WPARAM w, LPARAM l) = 0;
		
	protected:
		CRect	m_rSize;
		bool	m_bFocusedState;
		bool	m_bSelectMe;
		
	};
	
	
	class CPuckerBtn : public CIconBtn  
	{
	public:  
		CPuckerBtn::CPuckerBtn(CWnd* pWnd,UINT id)
			: m_pWnd(pWnd), m_bPressState(false),m_id(id)
		{
		}
		virtual ~CPuckerBtn(){}
		
		virtual void CPuckerBtn::plBlFun(UINT m,WPARAM w,LPARAM l)
		{
		}
		virtual void CPuckerBtn::Draw()
		{
			if(m_pWnd == NULL)
				return;
			
			
			CDC* pDC = m_pWnd->GetDC();
			
			CBrush brush;
			brush.CreateSolidBrush(RGB(203, 203, 203));
			CRect rectFill(m_rSize);
			rectFill.bottom += 1;
			rectFill.right  += 1;
			pDC->FillRect(&rectFill, &brush);
			brush.DeleteObject();
			
			CRect rect(m_rSize);
			if(GetFocusedState())
			{
				CPen pen;
				pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
				CPen* pOldPen = pDC->SelectObject(&pen);
				pDC->MoveTo(rect.left,  rect.top);
				pDC->LineTo(rect.right, rect.top);
				pDC->MoveTo(rect.left,  rect.top);
				pDC->LineTo(rect.left,  rect.bottom);
				pDC->SelectObject(pOldPen);
				
				pDC->MoveTo(rect.left,  rect.bottom); 
				pDC->LineTo(rect.right, rect.bottom);
				pDC->MoveTo(rect.right, rect.top);	  
				pDC->LineTo(rect.right, rect.bottom);
			}
			
			CPoint point = rect.CenterPoint();
			if(!m_bPressState)
			{
				pDC->MoveTo(point.x,     point.y - 1);
				pDC->LineTo(point.x + 4, point.y - 5);
				pDC->MoveTo(point.x,     point.y - 1);
				pDC->LineTo(point.x - 4, point.y - 5);
				pDC->MoveTo(point.x,	 point.y + 3);
				pDC->LineTo(point.x + 4, point.y - 1);
				pDC->MoveTo(point.x,	 point.y + 3);
				pDC->LineTo(point.x - 4, point.y - 1);
			}
			else
			{
				pDC->MoveTo(point.x,	 point.y - 4);
				pDC->LineTo(point.x + 4, point.y);
				pDC->MoveTo(point.x,	 point.y - 4);
				pDC->LineTo(point.x - 4, point.y);
				pDC->MoveTo(point.x,	 point.y);
				pDC->LineTo(point.x + 4, point.y + 4);
				pDC->MoveTo(point.x,	 point.y);
				pDC->LineTo(point.x - 4, point.y + 4);
			}
		}
		
		void CPuckerBtn::Click()
		{	
			m_bPressState = !m_bPressState;
			
			if(m_pWnd == NULL)
				return;
			
			if(ID_XD_2==m_id)
			{	
				m_pWnd->GetParent()->SendMessage(WM_TASKCLICK, 0, m_id);
				return;
			}
			Draw();
			
			if(m_bPressState)
			{
				if(m_pWnd == NULL) 
					return;
				m_pWnd->GetWindowRect(&m_wndRect);
				m_pWnd->GetParent()->ScreenToClient(&m_wndRect);
				
				CRect rect(m_wndRect);
				rect.bottom = rect.top + 28;
				DWORD dwStyle = m_pWnd->GetExStyle();
				DWORD dwNewStyle = WS_EX_DLGMODALFRAME|WS_EX_CLIENTEDGE;
				if((dwStyle & dwNewStyle) == dwNewStyle)
				{
					rect.bottom += 10;
				}
				else if((dwStyle & WS_EX_CLIENTEDGE) == WS_EX_CLIENTEDGE)
				{
					rect.bottom += 4;
				}
				else if((dwStyle & WS_EX_DLGMODALFRAME) == WS_EX_DLGMODALFRAME)
				{
					rect.bottom += 6;
				}
				else if((dwStyle & WS_EX_STATICEDGE) == WS_EX_STATICEDGE)
				{
					rect.bottom += 2;
				}
				m_pWnd->MoveWindow(&rect);
			}
			else
				m_pWnd->MoveWindow(&m_wndRect);
			
		}
		
		
		bool GetPuckerState() const	   { return m_bPressState;					}
		
private:
	CWnd* m_pWnd;
	bool  m_bPressState;
	CRect m_wndRect;
	UINT	m_id;
};



class CTaskFrame
{
public: 
	virtual ~CTaskFrame(){}
	CTaskFrame::CTaskFrame(const CString& title) 
		: m_rSize(CRect(0, 0, 0, 0)), m_strTitle(title)
	{
		m_FrmColor = RGB(203, 203, 203);
		m_BKColor  = RGB(255, 255, 255);
		
		LOGFONT logFont;
		logFont.lfHeight         = 12;
		logFont.lfEscapement     = 0;
		logFont.lfOrientation    = 0;
		logFont.lfWeight	     = FW_BOLD;
		logFont.lfItalic         = FALSE;
		logFont.lfUnderline	     = FALSE;
		logFont.lfStrikeOut	     = FALSE;
		logFont.lfOutPrecision   = OUT_STROKE_PRECIS;
		logFont.lfClipPrecision  = CLIP_STROKE_PRECIS;
		logFont.lfQuality		 = DEFAULT_QUALITY;
		logFont.lfPitchAndFamily = VARIABLE_PITCH|FF_MODERN;
		logFont.lfCharSet	     = GB2312_CHARSET;
		strcpy(logFont.lfFaceName, "ËÎÌו");
		m_Font.CreateFontIndirect(&logFont);
		
		m_nTitleHeight  = 28;
		m_nLeftMargin   = 10;
		m_nRightMargin  = 10;
		m_nTopMargin    = 4;
		m_nBottomMargin = 5;
	}
	
	void CTaskFrame::Draw(CDC* pDC)
	{
		CRect rect(m_rSize);
		
		CBrush brush;
		brush.CreateSolidBrush(m_BKColor);
		pDC->FillRect(&rect, &brush);
		brush.DeleteObject();
		
		rect.bottom = m_nTitleHeight;
		brush.CreateSolidBrush(m_FrmColor);
		pDC->FillRect(&rect, &brush);
		brush.DeleteObject();
		
		LOGBRUSH logBrush = { BS_NULL, NULL, NULL };
		brush.CreateBrushIndirect(&logBrush);
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, m_FrmColor);
		CBrush* pOldBrush = pDC->SelectObject(&brush);
		CPen* pOldPen = pDC->SelectObject(&pen);
		pDC->Rectangle(&m_rSize);
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
		
		CFont* pOldFont = pDC->SelectObject(&m_Font);
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOut(6, (m_nTitleHeight - 12) / 2, m_strTitle.Left(14));
		pDC->SetBkMode(OPAQUE);
		pDC->SelectObject(pOldFont);
	}
	
	
	CRect CTaskFrame::GetWorkRect() const
	{
		CRect rect(m_rSize);
		rect.top     = m_nTopMargin + m_nTitleHeight;
		rect.left    = m_nLeftMargin;
		rect.right  -= m_nRightMargin;
		rect.bottom -= m_nBottomMargin;
		
		return rect;
	}
	
	
	
	void SetSize(const CRect& rect)		{ m_rSize = rect;						}
	
	int LMargin() const					{ return m_nLeftMargin;					}
	int TMargin() const					{ return m_nTopMargin;					}
	int BMargin() const					{ return m_nBottomMargin;				}		
	int TitleHeight() const				{ return m_nTitleHeight;				}
	
	
private:
	CRect m_rSize;
	
	CString m_strTitle;
	
	COLORREF m_FrmColor;
	COLORREF m_BKColor;
	CFont    m_Font;
	
	int	m_nTitleHeight;
	int m_nLeftMargin;
	int m_nRightMargin;
	int m_nTopMargin;
	int m_nBottomMargin;
	
	
};
class CItem : public CIconBtn
{
public: 
	CItem::CItem()
		: m_pWnd(NULL), m_nCtrlId(NULL)
	{
	}
	
	CItem::CItem(CWnd* pWnd, UINT id)
		: m_pWnd(pWnd), m_nCtrlId(id)	
	{
	}
	
	virtual ~CItem(){}
	virtual CItem* Clone() = 0;
	
	void CItem::SetItem(const ItemInfo& item)
	{
		if(item.type < II_ICONTEXT || item.type > II_COLOR)
		{
			m_ItemInfo.type = -1;
			return;
		}
		
		m_ItemInfo.type  = item.type;
		m_ItemInfo.index = item.index;
		m_ItemInfo.text  = item.text;
		m_ItemInfo.color = item.color;
		m_ItemInfo.icon  = CopyIcon(item.icon);
	}
	
	ItemInfo GetInf();
	
protected:
	CWnd*    m_pWnd;
	UINT     m_nCtrlId;
	ItemInfo m_ItemInfo;
};

class CTaskList
{
public:
	void plBlFun(UINT m, WPARAM w, LPARAM l)
	{
		std::vector<CItem*>::iterator theIt;
		int i = 0;
		for(theIt = m_vecItems.begin(); theIt != m_vecItems.end(); ++theIt, i++)
		{
			CIconBtn* pItem = (*theIt);
			pItem->plBlFun(m,w,l); 
		}
	}
	void CTaskList::OnXdLButtonDown(const CPoint& point)
	{
		if(m_pPuckerBtn == NULL)
			return;
		
		if(m_pPuckerBtn->TestInArea(point))
		{
			m_pPuckerBtn->Click();
			m_pFocusBtn = m_pPuckerBtn;
			return;
		}
		if(NULL!=m_pXdBtn&&m_pXdBtn->TestInArea(point))
		{
			m_pXdBtn->Click();
			m_pFocusBtn = m_pXdBtn;
			return;
		}
		
		
		if(!m_pPuckerBtn->GetPuckerState())
		{
			std::vector<CItem*>::iterator theIt;
			int i = 0;
			for(theIt = m_vecItems.begin(); theIt != m_vecItems.end(); ++theIt, i++)
			{
				CIconBtn* pItem = (*theIt);
				if(pItem->TestInArea(point))
				{
					pItem->Click();
					m_pFocusBtn = pItem;
					m_pSelectBtn = pItem;
				}
				else
				{  
					pItem->plSetSelected(false); 
				}
			}
		}
		else
		{ 
			m_pFocusBtn = NULL;	
		}
		if(m_pSelectBtn)
		{
			m_pSelectBtn->plSetSelected(true); 
		}
	}
	void CTaskList::OnMouseMove(const CPoint& point)
	{
		if(m_pWnd == NULL)
			return;
		
		if(m_pFocusBtn != NULL)
		{
			if(m_pFocusBtn->TestInArea(point))
				return;
			
			m_pFocusBtn->SetFocusedState(false);
		}
		
		if(NULL!=m_pXdBtn&&m_pXdBtn->TestInArea(point))
		{
			m_pXdBtn->SetFocusedState(true);
			m_pFocusBtn = m_pXdBtn;
			SetCursor(LoadCursor(NULL, IDC_HAND));
			return;
		}
		
		if(m_pPuckerBtn == NULL)
			return;
		
		if(m_pPuckerBtn->TestInArea(point))
		{
			m_pPuckerBtn->SetFocusedState(true);
			m_pFocusBtn = m_pPuckerBtn;
			SetCursor(LoadCursor(NULL, IDC_HAND));
			return;
		}
		
		if(!m_pPuckerBtn->GetPuckerState())
		{
			std::vector<CItem*>::iterator theIt;
			for(theIt = m_vecItems.begin(); theIt != m_vecItems.end(); ++theIt)
			{
				CIconBtn* pItem = (*theIt);
				if(pItem->TestInArea(point))
				{
					pItem->SetFocusedState(true);
					m_pFocusBtn = pItem;
					SetCursor(LoadCursor(NULL, IDC_HAND));
					return;
				}
			}
		}
		
		m_pFocusBtn = NULL;	
		SetCursor(LoadCursor(NULL, IDC_ARROW));
	}
	
	
	CItem* OnXdGetItem(int index);void CTaskList::plReSize()
	{
		CRect rc;
		m_pWnd->GetWindowRect(&rc);
		m_pWnd->GetParent()->ScreenToClient(&rc);
		rc.bottom  = rc.top;
		rc.bottom += m_pFrame->TMargin();
		rc.bottom += m_pFrame->TitleHeight();
		rc.bottom += m_pFrame->BMargin();
		rc.bottom += m_vecItems.size() * (16 + 4);
		
		DWORD dwStyle = m_pWnd->GetExStyle();
		DWORD dwNewStyle = WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE;
		if((dwStyle & dwNewStyle) == dwNewStyle)
		{
			rc.bottom += 10;
		}
		else if((dwStyle & WS_EX_CLIENTEDGE) == WS_EX_CLIENTEDGE)
		{
			rc.bottom += 4;
		}
		else if((dwStyle & WS_EX_DLGMODALFRAME) == WS_EX_DLGMODALFRAME)
		{
			rc.bottom += 6;
		}
		else if((dwStyle & WS_EX_STATICEDGE) == WS_EX_STATICEDGE)
		{
			rc.bottom += 2;
		}
		
		m_pWnd->MoveWindow(&rc);
	}
	
	
	void CTaskList::AddItem(const ItemInfo& item)
	{
		CItem* pItem = m_pCloneItem->Clone();
		pItem->SetItem(item);
		m_vecItems.push_back(pItem);
	}
	
	CTaskList(CWnd* pParent,
		      CTaskFrame* pFrm,
			  CPuckerBtn* pPucker, 
			  CPuckerBtn* pXdBtn, 
			  CItem* pItem) 
			  : m_pWnd(pParent), m_rSize(CRect(0, 0, 0, 0)),m_pSelectBtn(NULL)
	{
		m_pFrame		= pFrm;
		m_pPuckerBtn	= pPucker;
		m_pXdBtn		= pXdBtn;
		m_pFocusBtn		= NULL;
		m_pCloneItem	= pItem;
	}
	virtual CTaskList::~CTaskList()
	{
		m_pFocusBtn = NULL;
		
		std::vector<CItem*>::iterator theIt;
		for(theIt = m_vecItems.begin(); theIt != m_vecItems.end(); ++theIt)
		{
			CItem* pItem = *theIt;	
			m_vecItems.erase(theIt);
			theIt--; 
			delete pItem;
		}
		
		if(m_pCloneItem != NULL)
			delete m_pCloneItem;
		
		if(m_pPuckerBtn != NULL)
			delete m_pPuckerBtn;
		
		if(m_pFrame != NULL)
			delete m_pFrame;
	}
	
	void CTaskList::plSetSize(const CRect& rect)
	{
		m_rSize = rect;
		
		if(m_pFrame != NULL)
			m_pFrame->SetSize(rect);
		else
			return;
		
		if(m_pPuckerBtn != NULL)
		{
			CRect rect(m_rSize);
			int len = 17;
			rect.top    = (m_pFrame->TitleHeight() - len) / 2;
			rect.left   = rect.right - len - 6;
			rect.right  = rect.left + len;
			rect.bottom = rect.top  + len;
			m_pPuckerBtn->SetSize(rect);
		}
		
		if(m_pXdBtn != NULL)
		{
			CRect rect(m_rSize);
			int len = 17;
			rect.top    = (m_pFrame->TitleHeight() - len) / 2;
			rect.left   = rect.right - len - 6;
			rect.right  = rect.left + len;
			rect.bottom = rect.top  + len;
			
			rect.left   -= 20; 
			rect.right  -= 20;
			m_pXdBtn->SetSize(rect);
		}
		
		CRect rc(m_pFrame->GetWorkRect());
		std::vector<CItem*>::iterator theIt;
		for(theIt = m_vecItems.begin(); theIt != m_vecItems.end(); ++theIt)
		{
			rc.bottom = rc.top + 16;
			(*theIt)->SetSize(rc);
			rc.top += (16 + 4);
		}
	}
	
	void CTaskList::OnDraw(CDC* pDC)
	{
		if(m_pFrame != NULL)
			m_pFrame->Draw(pDC);
		
		if(m_pPuckerBtn != NULL)
			m_pPuckerBtn->Draw();
		if(m_pXdBtn != NULL)
			m_pXdBtn->Draw();
		
		if(!m_pPuckerBtn->GetPuckerState())
		{
			std::vector<CItem*>::iterator theIt;
			for(theIt = m_vecItems.begin(); theIt != m_vecItems.end(); ++theIt)
				(*theIt)->Draw();
		}
	}
	
	void RemoveLastItem(); 
	
private:
	CWnd*			m_pWnd;
	CRect			m_rSize;
	CTaskFrame*		m_pFrame;
	CPuckerBtn*		m_pPuckerBtn;
	CPuckerBtn*		m_pXdBtn;
	CItem*			m_pCloneItem;
	CIconBtn*		m_pFocusBtn;
	CIconBtn*		m_pSelectBtn;
	
	vector<CItem*>	m_vecItems;
};

//=====================================================================
/* extern "C" { */
#ifdef __cplusplus
}
#endif

#endif
