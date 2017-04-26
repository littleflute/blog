//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���FBFrameWnd.cpp

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
#include "FBFrameWnd.h"

//#####################################################################
CFBFrameWnd::CFBFrameWnd()
{
}

CFBFrameWnd::~CFBFrameWnd()
{
}
//#####################################################################
BOOL CFBFrameWnd::Create(HINSTANCE hInst,LPCTSTR szCaption,HMENU hMenu,HICON hIcon,UINT exStyle)
{
	return CFBWnd::Create(CLS_FBSTDWNDCLASS,
						  szCaption,
						  hInst,
						  NULL,
						  WS_OVERLAPPEDWINDOW,
						  exStyle,
						  hMenu,
						  hIcon);
}
//#####################################################################
LRESULT CFBFrameWnd::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lResult = 0;

	switch(msg)
	{
	case WM_SIZE:
	case FBWM_SETSIZE://�����Զ�����Ϣ��Ϊ��Ҫ��ÿ�������ڳߴ�ı䣬
					  //�ͷ�������Ϣ������Ӵ��ڣ����Ӵ����Լ�����
					  //��λ���Ӵ�����ʲô�仯Ҳ��������Ϣ��������
					  //�Ե������֡������Ϣ��lParam�ǿͻ�����RECT
					  //ָ�룬�Ӵ��ھ�λ�󣬱�������RECT�п۳���
					  //����ռ�ݵ�����
		if(IsShow())
			ReCalcLayout();
		break;
	case WM_DESTROY:
		OnClose();
		PostQuitMessage(0);
		break;
	case WM_ERASEBKGND://��ܴ��ڲ���Ҫ������
		lResult = 1;
		break;
	case WM_COMMAND:
		if(LOWORD(wParam) == IDW_COMBOBOX)
			//ʮ����ֵ��ǣ�windows�����ؼ��ı�����Ϣ�����϶���
			//��WM_NOTIFY������Ψ�����ComboBox����WM_COMMAND�����ġ�
			SendMessage((HWND)lParam,msg,wParam,lParam);
		else
			OnCommand(HIWORD(wParam),LOWORD(wParam),(HWND)lParam);
		break;
	case WM_NOTIFY://����Notify��Ϣ��ԭ����������������ȥ��
				   //Ҳ����˵�ؼ������Լ�����WM_NOTIFY��Ϣ��
				   //ȷʵ��Ҫ��ܴ��ڴ���ģ��ͷ��Զ�����Ϣ��
		{
			LPNMHDR pnm = (LPNMHDR)lParam;
			if(pnm->hwndFrom != m_hWnd)
				SendMessage(pnm->hwndFrom,msg,wParam,lParam);
		}
		break;
	case FBWM_NOTIFY://Ϊ�˼����Զ�����Ϣ���������󲿷��Զ�����Ϣ
					 //����������Ϣ������
		OnCustomNotify(HIWORD(wParam),LOWORD(wParam),lParam);
		break;
	case WM_DRAWITEM://�Ի��ؼ��ɿؼ��Ի�
		{
			CFBWnd* pWnd = m_pWndList->LookAtID((UINT)wParam);
			if(pWnd)
				SendMessage(pWnd->m_hWnd,msg,wParam,lParam);
		}
		break;
	default:
		lResult = CFBWnd::WindowProc(msg,wParam,lParam);
		break;
	}

	return lResult;
}
