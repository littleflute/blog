//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���FBWnd.h

	��Ȩ��Firebird Software Workroom ����

	��������Դ����İ�Ȩ�ܡ��л����񹲺͹�����Ȩ�����Լ���
		  ����ط��ɺ���Լ�ı������κ��л���õ���Դ�����
		  ���˺ͻ�����δ��������ȷ��Ȩ�����ý���Դ��������
		  �κ���ҵĿ��(ֱ�ӵĻ��ӵ�)�����ڷ���ҵĿ�ĵ�ʹ
		  �� (�������ơ�������������޸�)�� ԭ����û���ر�
		  �������������������ĵ���˵������Դ��������ԭ
		  ���ߵ�����Ȩ��

	��д���ش���(chings)	1999.12 - 2000.5

	���磺Tel��(0792)6323086	E_mail��chings@163.net
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
//	  ��: CFBWnd
//	˵��: ��CFBWnd��װ�˴��ڴ��������ʹ��ڹ���, �κ������������
//		  �麯��WindowProc(UINT,WPARAM,LPARAM) �Դ�������Ϣ.
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
//		�ࣺCWndList
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
