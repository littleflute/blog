//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：ScreenCap.h

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
#ifndef _SCREENCAP_H__
#define _SCREENCAP_H__

#include "FBApp.h"

//######################################################################
extern HBITMAP (__stdcall *LoadFromFile)(LPCTSTR);
extern BOOL (__stdcall *SaveToFile)(HBITMAP,LPCTSTR);
//######################################################################
class CScreenCap : public CFBApp
{
public:
	CScreenCap();
	~CScreenCap();

	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	HINSTANCE	m_hInstImage;
};

//######################################################################
CScreenCap* WINAPI GetApp();
//######################################################################
#endif//_SCREENCAP_H__