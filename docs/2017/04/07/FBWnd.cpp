//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���FBWnd.cpp

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
//		�� CFBWnd
//
//////////////////////////////////////////////////////////////////////
//CWndList��һ�����������ݵ�˳�������ʵֻ�����������ݣ�
//CFBWnd*�ʹ��ھ�����κδ�CFBWnd�̳еĴ������ڴ���ʱ������
//����m_pWndList�ĺ���Add(CFBWnd* pWnd)���Ѹô��ڵ���������
//���ݼӵ����˳�����,ͬʱ��Ҫ���ô��ڵ�WNDPROC�޸�ΪFBWndProc��
//�ٽ��ϵ�WNDPROC�����ڱ���DefWndProc�У��������WindowProc
//����麯���Żᱻ���á������׵İ취�ǣ��������غ���Createʱ��
//���ɴ�return CFBWnd::Create(...)��

CWndList* CFBWnd::m_pWndList = new CWndList();

//////////////////////////////////////////////////////////////////////
// ���캯������������
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
//���ڹ���
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
//	����: Create
//	˵��: ��������
/////////////////////////////////////////////////////////////////////////
BOOL CFBWnd::Create(LPCTSTR		lpszClassName,	//��������
					LPCTSTR		lpszCaption,	//������
					HINSTANCE	hInst,			//ʵ�����
					CFBWnd*		pParent,		//������ָ��
					UINT		style,			//���
					UINT		exStyle,		//��չ���
					HMENU		hMenu,			//�˵����
					HICON		hIcon,			//ͼ����
					int			x,				//���Ͻ�x����
					int			y,				//���Ͻ�y����
					int			width,			//��
					int			height,			//��
					HBRUSH		hbrBack)		//����ˢ�Ӿ��
{
	if(!hInst)return FALSE;//�����ṩ����ʵ�����

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
//����˵�����ǣ����m_pOwner��һ���Ǳ����ڵ������ĸ����ڣ�
//���ǽ��ܱ�������Ϣ�Ĵ��ڡ���������������û�в���MFC
//��������Ϣӳ�����(������һ���Ӵ�����˿ֲ��Ķ���), ��
//�Ժܶ���Ϣ�����Լ������ݡ���������������(��MFC���˿�
//�º���ʹ��SendMessage�������, ��������Ҫ��������)����
//��������һ���������б�Ҫ�ġ���������������µ�m_pOwner
//ʱ������ԭ�ȵ�m_pOwner��
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
	if(index != -1)//�пյĵ�Ԫ
	{
		memcpy(m_pHeader + index*8,&fd,8);
		return TRUE;
	}

	if(m_pHeader == NULL)//ÿһ�η���ʮ��FBWND_DATA��Ԫ
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