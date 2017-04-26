//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：FBFrameWnd.cpp

	版权：Firebird Software Workroom 保留

	声明：本源程序的版权受《中华人民共和国著作权法》以及其
		  它相关法律和条约的保护。任何有机会得到本源程序的
		  个人和机构，未经作者明确授权，不得将本源程序用于
		  任何商业目的(直接的或间接的)。对于非商业目的的使
		  用 (包括复制、传播、编译和修改)， 原则上没有特别
		  的限制条款，但请在相关文档中说明其来源，并尊重原
		  作者的署名权。

	编写：秦传安(chings)	2000.5

	联络：Tel：(0792)6323086	E_mail：chings@163.net
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
	case FBWM_SETSIZE://这条自定义消息极为重要，每当主窗口尺寸改变，
					  //就发这条消息给相关子窗口，让子窗口自己各就
					  //各位。子窗口有什么变化也发这条消息给主窗口
					  //以调整布局。这个消息的lParam是客户区的RECT
					  //指针，子窗口就位后，必须从这个RECT中扣除自
					  //己所占据的区域。
		if(IsShow())
			ReCalcLayout();
		break;
	case WM_DESTROY:
		OnClose();
		PostQuitMessage(0);
		break;
	case WM_ERASEBKGND://框架窗口不需要画背景
		lResult = 1;
		break;
	case WM_COMMAND:
		if(LOWORD(wParam) == IDW_COMBOBOX)
			//十分奇怪的是：windows公共控件的报告消息基本上都是
			//随WM_NOTIFY发出，唯有这个ComboBox是随WM_COMMAND发出的。
			SendMessage((HWND)lParam,msg,wParam,lParam);
		else
			OnCommand(HIWORD(wParam),LOWORD(wParam),(HWND)lParam);
		break;
	case WM_NOTIFY://对于Notify消息，原则上是哪里来哪里去，
				   //也就是说控件必须自己处理WM_NOTIFY消息。
				   //确实需要框架窗口处理的，就发自定义消息。
		{
			LPNMHDR pnm = (LPNMHDR)lParam;
			if(pnm->hwndFrom != m_hWnd)
				SendMessage(pnm->hwndFrom,msg,wParam,lParam);
		}
		break;
	case FBWM_NOTIFY://为了减少自定义消息的数量，大部分自定义消息
					 //都随这条消息发出。
		OnCustomNotify(HIWORD(wParam),LOWORD(wParam),lParam);
		break;
	case WM_DRAWITEM://自画控件由控件自画
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
