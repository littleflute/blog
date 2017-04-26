//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	文件：FBApp.h	类CFBApp的头文件

	版权：Firebird Software Workroom 保留

	声明：本源程序的版权受《中华人民共和国著作权法》以及其
		  它相关法律和条约的保护。任何有机会得到本源程序的
		  个人和机构，未经作者明确授权，不得将本源程序用于
		  任何商业目的(直接的或间接的)。对于非商业目的的使
		  用 (包括复制、传播、编译和修改)， 原则上没有特别
		  的限制条款，但请在相关文档中说明其来源，并尊重原
		  作者的署名权。

	编写：秦传安(chings)	1999.12 - 2000.4

	联络：Tel：(0792)6323086	E_mail：chings@163.net
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#ifndef _FBAPP_H__
#define _FBAPP_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////
#include "FBWnd.h"
//////////////////////////////////////////////////////////////////////
//class CFBApp  

class CFBApp  
{
public:
	CFBApp();
	virtual ~CFBApp();

	CFBWnd*			m_pMainWnd;			//主窗口指针
	HINSTANCE		m_hInstance;		//实例句柄
	LPCTSTR			m_pszAppName;		//程序名
	LPSTR			m_strCmdLine;		//命令行参数

	LONG RegGetLong(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LONG nDefValue);
	void RegSetLong(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LONG nVal);
	BOOL RegGetString(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPCTSTR buff,DWORD cbSize);
	void RegSetString(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPCTSTR buff,DWORD cbSize);
	BOOL RegGetBinary(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPBYTE buff,DWORD cbSize);
	void RegSetBinary(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPBYTE buff,DWORD cbSize);

	DWORD GetVersion(){
		return m_dwVersion;}

	int Run();
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:

	HACCEL		m_hAccel;			//加速键
	DWORD		m_dwVersion;		//版本号
	MSG			m_msgCur;			//当前消息
	char		m_pszRegKey[256];	//注册表键名

	void SetRegistryKey(LPCTSTR lpszRegKey);
	BOOL RegGetVal(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,DWORD dwType,LPBYTE buff,DWORD cbSize);
	void RegSetVal(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,DWORD dwType,LPBYTE buff,DWORD cbSize);

	virtual BOOL OnIdle(){return FALSE;}
};

#endif //_FBAPP_H__
