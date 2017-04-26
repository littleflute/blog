//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：FBWnd.h

	版权：Firebird Software Workroom 保留

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
#ifndef _FBWND_H__INCLUDED_
#define _FBWND_H__INCLUDED_
////////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
////////////////////////////////////////////////////////////////////////////////
class CFBWnd;
class CWndList;
////////////////////////////////////////////////////////////////////////////////
#define CLS_FBSTDWNDCLASS	"FBStdWndClass"
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
ATOM WINAPI FBRegWindowClass(WNDCLASSEX *pws);
ATOM WINAPI FBRegStdWndClass(HINSTANCE hInst);
///////////////////////////////////////////////////////////////////////////
//
//	  类: CFBWnd
//	说明: 类CFBWnd封装了窗口创建函数和窗口过程, 任何子类可以重载
//		  虚函数WindowProc(UINT,WPARAM,LPARAM) 以处理窗口消息.
//
//////////////////////////////////////////////////////////////////////

class CFBWnd  
{
public:
	CFBWnd();
	~CFBWnd();

    HWND		m_hWnd;

	BOOL Create(LPCTSTR		lpszClassName,
				LPCTSTR		lpszCaption,
				HINSTANCE	hInst,
				CFBWnd		*pParent = NULL,
				UINT		style = WS_OVERLAPPEDWINDOW,
				UINT		exStyle = NULL,
				HMENU		hMenu = NULL,
				HICON		hIcon = NULL,
				int			x = CW_USEDEFAULT,
				int			y = CW_USEDEFAULT,
				int			width = CW_USEDEFAULT,
				int			height = CW_USEDEFAULT,
				HBRUSH		hbrBack = NULL);

	BOOL IsShow(){return IsWindowVisible(m_hWnd);}

	void Invalidate(BOOL bErase = TRUE){
		if(m_hWnd)
			InvalidateRect(m_hWnd,NULL,bErase);}

	void ModifyWndStyle(UINT removeStyle,UINT addStyle);

	HINSTANCE GetInstance();

	UINT GetWndID(){
		if(!m_hWnd)return 0;
		return (UINT)GetWindowLong(m_hWnd,GWL_ID);}

	CFBWnd* SetOwner(CFBWnd* pNewOwner);

    operator HWND() { return m_hWnd; }

	static CFBWnd* FromHandle(HWND hWnd);
	static CWndList *m_pWndList;

protected:

	CFBWnd*		m_pOwner;
	WNDPROC		DefWndProc;

	virtual BOOL PreCreateWnd(CREATESTRUCT& cs){return TRUE;}
	virtual BOOL OnCreate(){return TRUE;}
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);

	static LRESULT CALLBACK FBWndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam);
};
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
inline 	HINSTANCE CFBWnd::GetInstance(){
	return (HINSTANCE)GetWindowLong(m_hWnd,GWL_HINSTANCE);}

//////////////////////////////////////////////////////////////////////
//
//		类：CWndList
//
//////////////////////////////////////////////////////////////////////
class CWndList
{
public:
	CWndList();
	virtual ~CWndList();

	struct FBWND_DATA{
		HWND		hWnd;
		CFBWnd*		pWnd;
	};

	BOOL Add(CFBWnd* pWnd);
	void Delete(CFBWnd* pWnd);
	void Delete(HWND hWnd);
	CFBWnd* LookAtHandle(HWND hWnd);
	CFBWnd* LookAtID(UINT uID);

protected:
	int				m_nCount;
	LPBYTE			m_pHeader;

	int FindEmpty();
};

#endif //_FBWND_H__INCLUDED_
