//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：FBFrameWnd.h

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
#ifndef _FBFRAMEWND_H__
#define _FBFRAMEWND_H__
//#####################################################################
#include "FBWnd.h"
//#####################################################################
class CFBFrameWnd : public CFBWnd
{
public:
	CFBFrameWnd();
	~CFBFrameWnd();
	
	BOOL Create(HINSTANCE hInst,LPCTSTR szCaption,HMENU hMenu,HICON hIcon,UINT exStyle = NULL);
protected:

	virtual void ReCalcLayout(){}
	virtual void OnClose(){}
	virtual void OnCommand(UINT code,UINT uID,HWND hwndCtrl){}
	virtual void OnCustomNotify(UINT code,UINT uID,LPARAM lParam){}
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};
//#####################################################################
#endif//_FBFRAMEWND_H__