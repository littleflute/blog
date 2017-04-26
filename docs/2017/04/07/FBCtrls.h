//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���FBCtrls.h

	��Ȩ��Firebird Software Workroom

	��������Դ����İ�Ȩ�ܡ��л����񹲺͹�����Ȩ�����Լ���
		  ����ط��ɺ���Լ�ı������κ��л���õ���Դ�����
		  ���˺ͻ�����δ��������ȷ��Ȩ�����ý���Դ��������
		  �κ���ҵĿ��(ֱ�ӵĻ��ӵ�)�����ڷ���ҵĿ�ĵ�ʹ
		  �� (�������ơ�������������޸�)�� ԭ����û���ر�
		  �������������������ĵ���˵������Դ��������ԭ
		  ���ߵ�����Ȩ��

	��д���ش���(chings)	1999.12 - 2000.4

	���磺Tel��(0792)6323086	E_mail��chings@163.net
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#ifndef _FBCTRLS_H__
#define _FBCTRLS_H__
//////////////////////////////////////////////////////////////////////
#include "FBWnd.h"

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ļ��������и��ࣺ
	//class CFBWnd
			class CToolBar;					//������
					class CMenuBar;			//�˵���
			class CFBStatusBar;				//״̬��
			class CFBComboBox;				//��Ͽ�
			class CFBTabCtrl;				//��ҳ�ؼ�
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define FB_CBN_SELCHANGED		0xB101
#define FB_TTN_SHOWING			0xB131
#define FB_TTN_HIDEN			0xB132
#define FB_TABN_SELCHANGED		0xB141
//////////////////////////////////////////////////////////////////////

/********************************************************************
*	class CFBToolBar
*	������
********************************************************************/

class CFBToolBar : public CFBWnd
{
public:
	CFBToolBar();
	virtual ~CFBToolBar();

	virtual BOOL Create(CFBWnd*		pParent,	//�����ھ��
						UINT		nStyle,		//�ؼ����
						UINT		nID);		//��ʶ��

	BOOL LoadToolBar(UINT nID);
	BOOL AddButtons(UINT uNumBtns,LPTBBUTTON pBtn);
	int AddString(UINT uID);
	int AddString(LPTSTR pStr);
	int GetButtonCount();
	void CheckedButton(UINT uID,BOOL bCheck);
	void SetDropDowmBtn(UINT nID,HMENU hMenu);
	void SetButtonSize(int cx,int cy);
	void SetImageSize(int cx,int cy);
	void GetButtonRect(int nIndex,LPRECT pRc);
	void PressButton(UINT uID,BOOL bPressed);
	void EnableButton(UINT uID,BOOL bEnable);
	UINT GetButtonState(UINT uDC);
	int GetHotItem();

protected:
	char		m_pText[80];
	int			m_nHotItem;

	void OnToolTip(LPTOOLTIPTEXT ptt);
	virtual BOOL OnCreate();
	virtual void OnNotify(LPNMHDR pNMHDR,LRESULT& lResult);
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};

//#####################################################################
inline BOOL CFBToolBar::AddButtons(UINT uNumBtns,LPTBBUTTON pBtn){
	return SendMessage(m_hWnd,TB_ADDBUTTONS,(WPARAM)uNumBtns,(LPARAM)pBtn);}

inline BOOL CFBToolBar::AddString(LPTSTR pStr){
	return SendMessage(m_hWnd,TB_ADDSTRING,(WPARAM)NULL,(LPARAM)pStr);}

inline int CFBToolBar::AddString(UINT uID){
	return SendMessage(m_hWnd,TB_ADDSTRING,(WPARAM)GetInstance(),MAKELPARAM(uID,0));}

inline int CFBToolBar::GetButtonCount(){
	return SendMessage(m_hWnd,TB_BUTTONCOUNT,0,0);}

inline void CFBToolBar::GetButtonRect(int nIndex,LPRECT pRc){
	SendMessage(m_hWnd,TB_GETITEMRECT,(WPARAM)nIndex,(LPARAM)pRc);}

inline void CFBToolBar::SetButtonSize(int cx,int cy){
	SendMessage(m_hWnd,TB_SETBUTTONSIZE,0,MAKELPARAM(cx,cy));}

inline void CFBToolBar::SetImageSize(int cx,int cy){
	SendMessage(m_hWnd,TB_SETBITMAPSIZE,0,MAKELPARAM(cx,cy));}

inline void CFBToolBar::PressButton(UINT uID,BOOL bPress){
	SendMessage(m_hWnd,TB_PRESSBUTTON,(WPARAM)uID,MAKELPARAM(bPress,0));}

inline void CFBToolBar::EnableButton(UINT uID,BOOL bEnable){
	SendMessage(m_hWnd,TB_ENABLEBUTTON,(WPARAM)uID,MAKELPARAM(bEnable,0));}

inline int CFBToolBar::GetHotItem(){
	return SendMessage(m_hWnd,TB_GETHOTITEM,0,0);}

inline UINT CFBToolBar::GetButtonState(UINT uID){
	return SendMessage(m_hWnd,TB_GETSTATE,(WPARAM)uID,0);}
/********************************************************************
*	class CMenuBar
*	�˵���
********************************************************************/

class CMenuBar : public CFBToolBar  
{
public:
	CMenuBar();
	virtual ~CMenuBar();

	HMENU		m_hMenu;

	BOOL LoadMenu(HMENU hMenu,BOOL bRemove = FALSE);

	void TrackPopup();
	void CheckMenuItem(UINT uID,BOOL bCheck);
	BOOL GetMenuItemCheckState(UINT uID);
	BOOL EnableMenuItem(UINT uID,BOOL bEnable);
	void PressButton(int nIndex,BOOL bPress){
		CFBToolBar::PressButton(nIndex+1,bPress);}

protected:
	int			m_nItemCount;
	int			m_nPressed;
	POINT		m_ptMouse;
	BOOL		m_bTrack;

	BOOL OnMenuInput(MSG* pMsg);
	void OnMenuSelect(WPARAM,LPARAM);
	void OnPopupMenu();
	void OnLButtonDown(UINT fwKey,LONG x,LONG y);
	virtual LRESULT WindowProc(UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK MenuInputFilter(int nCode, WPARAM wParam, LPARAM lParam);
};
//////////////////////////////////////////////////////////////////////
/********************************************************************
*	class CFBStatusBar
*	״̬��
********************************************************************/

class CFBStatusBar : public CFBWnd
{
public:
	CFBStatusBar();
	virtual ~CFBStatusBar();

	virtual BOOL Create(CFBWnd* pParent,UINT uID);

	void SetText(int nIndex,LPCTSTR strText);
	void SetParts(int nParts,LPINT lpParts);
protected:
	int			m_nParts;

	void OnSetSize(LPRECT pRect);
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};


/********************************************************************
*	class CFBComboBox
*	��Ͽ�
********************************************************************/

class CFBComboBox : public CFBWnd 
{
public:
	CFBComboBox();
	virtual ~CFBComboBox();

	virtual BOOL Create(CFBWnd* pParent,UINT nID,UINT nStyle = NULL);

	void AddString(LPTSTR pszText);
	void InsertString(int nIndex,LPTSTR pszText);
	void SetCurSel(int nIndex);
	int GetCurSel();
	void GetLBText(int index,LPTSTR pText);
	int Find(LPTSTR pText,int nStart = 0);
	void SetTop(int index);

protected:
	virtual BOOL OnCreate();
	virtual LRESULT WindowProc(UINT msg, WPARAM wParam, LPARAM lParam);
};
///////////////////////////////////////////////////////////////////////
inline void CFBComboBox::AddString(LPTSTR pszText){
	SendMessage(m_hWnd,CB_ADDSTRING,0,(LPARAM)pszText);}

inline void CFBComboBox::InsertString(int nIndex,LPTSTR pszText){
	SendMessage(m_hWnd,CB_INSERTSTRING,(WPARAM)nIndex,(LPARAM)pszText);}

inline void CFBComboBox::SetCurSel(int nIndex){
	SendMessage(m_hWnd,CB_SETCURSEL,(WPARAM)nIndex,0);}

inline int CFBComboBox::GetCurSel(){
	return SendMessage(m_hWnd,CB_GETCURSEL,0,0);}

inline void CFBComboBox::GetLBText(int index,LPTSTR pText){
	SendMessage(m_hWnd,CB_GETLBTEXT,(WPARAM)index,(LPARAM)pText);}

inline int CFBComboBox::Find(LPTSTR pText,int nStart){
	return SendMessage(m_hWnd,CB_FINDSTRING,(WPARAM)nStart,(LPARAM)pText);}

inline void CFBComboBox::SetTop(int index){
		SendMessage(m_hWnd,CB_SETTOPINDEX,(WPARAM)index,0);}

/********************************************************************
*	class CFBTabCtrl
*	��ҳ�ؼ�
********************************************************************/


class CFBTabCtrl : public CFBWnd  
{
public:
	CFBTabCtrl();
	virtual ~CFBTabCtrl();

	virtual BOOL Create(CFBWnd* pParent,UINT nID,UINT style);

	int AddView(CFBWnd* pChildWnd,LPSTR pszCaption,BOOL bEnableImg = FALSE);
	void SetActiveView(int nIndex);
	void SetCaption(int index,LPTSTR szCaption);
	void GetCaption(int index,LPTSTR szCaption,int cbSize);
	CFBWnd* GetActiveView(){
		return m_pActiveView;}

	void SetImageList(HIMAGELIST himl);
	BOOL GetItem(int index,LPTCITEM ptci);
	int GetItemCount();
	int GetCurSel();
	int SetCurSel(int index);
	CFBWnd* GetAt(int index);
	void Remove(int index);
	void RemoveAll();

protected:

	CFBWnd*		m_pActiveView;
	UINT		m_uStyle;

	virtual void OnSize();
	void GetChildRect(LPRECT prc);
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};
//########################################################################

inline void CFBTabCtrl::SetImageList(HIMAGELIST himl){
	SendMessage(m_hWnd,TCM_SETIMAGELIST,0,(LPARAM)himl);}

inline BOOL CFBTabCtrl::GetItem(int index,LPTCITEM ptci){
	return SendMessage(m_hWnd,TCM_GETITEM,(WPARAM)index,(LPARAM)ptci);}

inline int CFBTabCtrl::GetItemCount(){
	return SendMessage(m_hWnd,TCM_GETITEMCOUNT,0,0);}

inline int CFBTabCtrl::GetCurSel(){
	return SendMessage(m_hWnd,TCM_GETCURSEL,0,0);}

inline int CFBTabCtrl::SetCurSel(int index){
	return SendMessage(m_hWnd,TCM_SETCURSEL,(WPARAM)index,0);}
//########################################################################
#endif//_FBCTRLS_H__