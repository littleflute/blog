//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���FBDialog.h

	��Ȩ��Firebird Software Workroom ����

	��������Դ����İ�Ȩ�ܡ��л����񹲺͹�����Ȩ�����Լ���
		  ����ط��ɺ���Լ�ı������κ��л���õ���Դ�����
		  ���˺ͻ�����δ��������ȷ��Ȩ�����ý���Դ��������
		  �κ���ҵĿ��(ֱ�ӵĻ��ӵ�)�����ڷ���ҵĿ�ĵ�ʹ
		  �� (�������ơ�������������޸�)�� ԭ����û���ر�
		  �������������������ĵ���˵������Դ��������ԭ
		  ���ߵ�����Ȩ��

	��д���ش���(chings)	2000.4

	���磺Tel��(0792)6323086	E_mail��chings@163.net
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#include "fclstd.h"
#include "FBDialog.h"
//////////////////////////////////////////////////////////////////////
BOOL CALLBACK FBDlgProc(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == WM_INITDIALOG)
	{
		CModalDlg* pDlg = (CModalDlg*)lParam;
		if(!pDlg)return 0;

		pDlg->m_hWnd = hdlg;
		CFBWnd::m_pWndList->Add(pDlg);

		return pDlg->WindowProc(msg,wParam,lParam);
	}

	CModalDlg* pDlg = (CModalDlg*)CFBWnd::FromHandle(hdlg);
	if(pDlg == NULL)
		return 0;
	else
		return pDlg->WindowProc(msg,wParam,lParam);
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModalDlg::CModalDlg()
{
	m_pszTemplate = NULL;
}

CModalDlg::~CModalDlg()
{

}
//////////////////////////////////////////////////////////////////////
BOOL CModalDlg::Create(CFBWnd* pParent,UINT idTemplate)
{
	m_pOwner = pParent;

	m_pszTemplate = MAKEINTRESOURCE(idTemplate);

	return TRUE;
}
//////////////////////////////////////////////////////////////////////
int CModalDlg::DoModal()
{
	HINSTANCE hInst;

	if(m_pOwner)
		hInst = m_pOwner->GetInstance();
	else
		hInst = GetModuleHandle(NULL);

	return DialogBoxParam(hInst,m_pszTemplate,
		m_pOwner? m_pOwner->m_hWnd : NULL,
		(DLGPROC)FBDlgProc,(LPARAM)this);
}
//////////////////////////////////////////////////////////////////////
LRESULT CModalDlg::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lRet = 0;

	if(msg == WM_INITDIALOG)
	{
		OnInitDialog();
		lRet = 1;
	}
	else if(msg == WM_COMMAND)
	{
		OnCommand(LOWORD(wParam),HIWORD(wParam));
		if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			EndDialog(m_hWnd,LOWORD(wParam));
	}
	else if(msg == WM_NOTIFY)
		OnNotify((LPNMHDR)lParam,lRet);

	return lRet;
}