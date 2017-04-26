//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：FBWnd.cpp

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
#include "fclstd.h"
#include "FBWnd.h"
///////////////////////////////////////////////////////////////////////////
ATOM WINAPI FBRegWindowClass(WNDCLASSEX *pwc)
{
	ATOM atom = FindAtom(pwc->lpszClassName);

	if(atom == NULL)
	{
		atom = RegisterClassEx(pwc);
		if(atom)
			AddAtom(pwc->lpszClassName);
	}

	return atom;
}
//////////////////////////////////////////////////////////////////////
ATOM WINAPI FBRegStdWndClass(HINSTANCE hInst)
{
	WNDCLASSEX WndCls;

	WndCls.cbSize			= sizeof(WNDCLASSEX);
	WndCls.lpszClassName	= CLS_FBSTDWNDCLASS;
	WndCls.style			= CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	WndCls.cbClsExtra		= 0;
	WndCls.cbWndExtra		= 4;
	WndCls.lpfnWndProc		= DefWindowProc;
	WndCls.hInstance		= hInst;
	WndCls.lpszMenuName		= NULL;
	WndCls.hCursor			= LoadCursor (0, IDC_ARROW);
	WndCls.hIcon			= NULL;
	WndCls.hIconSm			= NULL;
	WndCls.hbrBackground	= (HBRUSH)(COLOR_BTNFACE+1);

	return FBRegWindowClass(&WndCls);
}
//////////////////////////////////////////////////////////////////////
//
//		类 CFBWnd
//
//////////////////////////////////////////////////////////////////////
//CWndList是一个管理窗口数据的顺序表，它其实只管理两个数据：
//CFBWnd*和窗口句柄，任何从CFBWnd继承的窗口类在创建时都必须
//调用m_pWndList的函数Add(CFBWnd* pWnd)来把该窗口的上述两个
//数据加到这个顺序表中,同时还要将该窗口的WNDPROC修改为FBWndProc，
//再将老的WNDPROC保存在变量DefWndProc中，这样你的WindowProc
//这个虚函数才会被调用。最稳妥的办法是：你在重载函数Create时，
//最后干脆return CFBWnd::Create(...)。

CWndList* CFBWnd::m_pWndList = new CWndList();

//////////////////////////////////////////////////////////////////////
// 构造函数和析构函数
CFBWnd::CFBWnd()
{
	m_hWnd		= NULL;
	DefWndProc	= NULL;
	m_pOwner	= NULL;
}

CFBWnd::~CFBWnd()
{
	if(IsWindow(m_hWnd))
	{
		DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}
	m_pWndList->Delete(this);
}
///////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK CFBWnd::FBWndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lResult = 0;
	CFBWnd* pWnd = CFBWnd::FromHandle(hWnd);

	if(pWnd == NULL)
		lResult = DefWindowProc(hWnd,msg,wParam,lParam);
	else
		lResult = pWnd->WindowProc(msg,wParam,lParam);

	if(msg == WM_DESTROY)
		m_pWndList->Delete(hWnd);

	return lResult;
}
//////////////////////////////////////////////////////////////////////
//窗口过程
LRESULT CFBWnd::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(DefWndProc)
		return CallWindowProc(DefWndProc,m_hWnd,msg,wParam,lParam);
	else
		return DefWindowProc(m_hWnd,msg,wParam,lParam);
}
//////////////////////////////////////////////////////////////////////
CFBWnd* CFBWnd::FromHandle(HWND hWnd)
{
	if(!hWnd)return NULL;

	return m_pWndList->LookAtHandle(hWnd);
}
/////////////////////////////////////////////////////////////////////////
//	函数: Create
//	说明: 创建窗口
/////////////////////////////////////////////////////////////////////////
BOOL CFBWnd::Create(LPCTSTR		lpszClassName,	//窗口类名
					LPCTSTR		lpszCaption,	//窗口名
					HINSTANCE	hInst,			//实例句柄
					CFBWnd*		pParent,		//父窗口指针
					UINT		style,			//风格
					UINT		exStyle,		//扩展风格
					HMENU		hMenu,			//菜单句柄
					HICON		hIcon,			//图标句柄
					int			x,				//左上角x坐标
					int			y,				//左上角y坐标
					int			width,			//宽
					int			height,			//高
					HBRUSH		hbrBack)		//背景刷子句柄
{
	if(!hInst)return FALSE;//必须提供程序实例句柄

	m_pOwner = pParent;

	CREATESTRUCT cs;
	cs.lpszClass		= lpszClassName;
	cs.hInstance		= hInst;
	cs.lpszName			= lpszCaption;
	cs.style			= style;
	cs.dwExStyle		= exStyle;
	cs.x				= x;
	cs.y				= y;
	cs.cx				= width;
	cs.cy				= height;
	cs.hMenu			= hMenu;
	cs.lpCreateParams	= NULL;
	if(pParent)
		cs.hwndParent	= pParent->m_hWnd;
	else
		cs.hwndParent	= NULL;

	if(!PreCreateWnd(cs))
		return FALSE;

	if(cs.lpszClass == CLS_FBSTDWNDCLASS ||
		cs.lpszClass == NULL)
	{
		if(FindAtom(lpszClassName) == NULL)
			if(FBRegStdWndClass(hInst) == NULL)
				return FALSE;
	}

	m_hWnd = CreateWindowEx(cs.dwExStyle,
							cs.lpszClass,
							cs.lpszName,
							cs.style,
							cs.x,cs.y,cs.cx,cs.cy,
							cs.hwndParent,
							cs.hMenu,
							cs.hInstance,
							cs.lpCreateParams);

	if(m_hWnd == NULL)
		return FALSE;

	m_pWndList->Add(this);

	DefWndProc = (WNDPROC)SetWindowLong(m_hWnd,GWL_WNDPROC,(LONG)FBWndProc);

	return OnCreate();
}
/////////////////////////////////////////////////////////////////////////
void CFBWnd::ModifyWndStyle(UINT removeStyle,UINT addStyle)
{
	UINT style = GetWindowLong(m_hWnd,GWL_STYLE);

	style &= ~removeStyle;
	style |= addStyle;
	SetWindowLong(m_hWnd,GWL_STYLE,style);
}
/////////////////////////////////////////////////////////////////////////
//必须说明的是：这个m_pOwner不一定是本窗口的真正的父窗口，
//而是接受本窗口消息的窗口。由于我这个框架中没有采用MFC
//那样的消息映射机制(那真是一个庞大得令人恐怖的东西), 所
//以很多消息必须自己来传递、来决定它的走向。(用MFC的人恐
//怕很少使用SendMessage这个函数, 而这里则要常用它。)所以
//设置这样一个变量是有必要的。这个函数在设置新的m_pOwner
//时，返回原先的m_pOwner。
CFBWnd* CFBWnd::SetOwner(CFBWnd *pNewOwner)
{
	CFBWnd *tmp = m_pOwner;
	m_pOwner = pNewOwner;

	return tmp;
}
/////////////////////////////////////////////////////////////////////////
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
//
//			class CWndList
//
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
CWndList::CWndList()
{
	m_nCount = 0;
	m_pHeader = NULL;
}

CWndList::~CWndList()
{
	if(m_pHeader)
		delete [] m_pHeader;
}
/////////////////////////////////////////////////////////////////////////
BOOL CWndList::Add(CFBWnd* pWnd)
{
	if(!pWnd)return FALSE;

	int index;
	FBWND_DATA fd;
	fd.pWnd = pWnd;
	fd.hWnd = pWnd->m_hWnd;

	index = FindEmpty();
	if(index != -1)//有空的单元
	{
		memcpy(m_pHeader + index*8,&fd,8);
		return TRUE;
	}

	if(m_pHeader == NULL)//每一次分配十个FBWND_DATA单元
		m_pHeader = new BYTE[8*10];
	else if(m_nCount%10 == 0)
	{
		LPBYTE tmp = new BYTE[m_nCount*8 + 10*8];
		memcpy(tmp,m_pHeader,m_nCount*8);
		delete [] m_pHeader;
		m_pHeader = tmp;
	}
	
	memcpy(m_pHeader + m_nCount*8,&fd,8);
	m_nCount++;

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////
int CWndList::FindEmpty()
{
	if(!m_pHeader)return -1;

	int i;
	LPDWORD pData;
	for(i=0;i<m_nCount;i++)
	{
		pData = (LPDWORD)(m_pHeader + i*8);
		if(*pData == NULL)
			break;
	}

	if(i>=m_nCount)
		return -1;
	
	return i;
}
/////////////////////////////////////////////////////////////////////////
void CWndList::Delete(CFBWnd* pWnd)
{
	for(int i=0;i<m_nCount;i++)
	{
		FBWND_DATA* pData = (FBWND_DATA*)(m_pHeader + i*8);
		if(pData->pWnd == pWnd)
		{
			memset(pData,0,8);
			break;
		}
	}
}
/////////////////////////////////////////////////////////////////////////
void CWndList::Delete(HWND hWnd)
{
	for(int i=0;i<m_nCount;i++)
	{
		FBWND_DATA* pData = (FBWND_DATA*)(m_pHeader + i*8);
		if(pData->hWnd == hWnd)
		{
			memset(pData,0,8);
			break;
		}
	}
}
/////////////////////////////////////////////////////////////////////////
CFBWnd* CWndList::LookAtHandle(HWND hWnd)
{
	if(m_pHeader == NULL)
		return NULL;

	CFBWnd* pWnd = NULL;

	for(int i=0;i<m_nCount;i++)
	{
		FBWND_DATA* pData = (FBWND_DATA*)(m_pHeader + i*8);
		if(pData->hWnd == hWnd)
		{
			pWnd = pData->pWnd;
			break;
		}
	}

	return pWnd;
}
/////////////////////////////////////////////////////////////////////////
CFBWnd* CWndList::LookAtID(UINT uID)
{
	if(m_pHeader == NULL || uID == 0)
		return NULL;

	CFBWnd* pWnd = NULL;
	UINT id = 0;

	for(int i=0;i<m_nCount;i++)
	{
		FBWND_DATA* pData = (FBWND_DATA*)(m_pHeader + i*8);
		if(pData->hWnd == NULL)
			continue;

		id = (UINT)GetWindowLong(pData->hWnd,GWL_ID);
		if(id == uID)
		{
			pWnd = pData->pWnd;
			break;
		}
	}

	return pWnd;
}