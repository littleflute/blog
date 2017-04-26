//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	文件：FBApp.h	类CFBApp的执行文件

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
#include "fclstd.h"
#include "FBApp.h"
//////////////////////////////////////////////////////////////////////
// 构造函数和析构函数
//////////////////////////////////////////////////////////////////////
CFBApp::CFBApp()
{
	m_pszAppName		= NULL;
	m_hInstance			= NULL;
	m_pMainWnd			= NULL;
	m_hAccel			= NULL;
	m_dwVersion			= 0x00010000;

	ZeroMemory(m_pszRegKey,256);
}

CFBApp::~CFBApp()
{
}
////////////////////////////////////////////////////////////////////////////////
//	函数: InitInstance()
//	说明: 任何CFBApp的子类都必须重载这个函数以进行应用程序实例
//		  的初始化工作. 
///////////////////////////////////////////////////////////////////////////////
BOOL CFBApp::InitInstance()
{
	return TRUE;
}
///////////////////////////////////////////////////////////////////////////////	
//		函数: ExitInstance()
//		说明: 退出实例时进行必要的清扫工作.
//
//////////////////////////////////////////////////////////////////////////////////
int CFBApp::ExitInstance()
{
	int nResult = m_msgCur.wParam;
	if(m_pMainWnd)
		delete m_pMainWnd;
	return nResult;
}
////////////////////////////////////////////////////////////////////////////////
//	函数: Run()
//	说明: 进入消息循环, 应用程序运行.
//
///////////////////////////////////////////////////////////////////////////////////
int CFBApp::Run()
{
	BOOL bNeetIdle = TRUE;
	while (TRUE)
	{
        while (PeekMessage(&m_msgCur, NULL, 0, 0, PM_NOREMOVE))
		{ 
            if (GetMessage(&m_msgCur, NULL, 0, 0) )
			{ 
				if(m_pMainWnd && m_hAccel)
					if(TranslateAccelerator(m_pMainWnd->m_hWnd,m_hAccel,&m_msgCur))
						continue;
				TranslateMessage(&m_msgCur);
				DispatchMessage(&m_msgCur); 
            }
			else
				return ExitInstance();
		} 
		if(bNeetIdle)
			bNeetIdle = OnIdle();
	}

	return ExitInstance();
}
/////////////////////////////////////////////////////////////////////////////////
//		函数: SetRegistryKey(LPSTR lpszRegKey)
//		功能: 创建应用程序注册表主键
//		参数: LPCTSTR lpszRegKey		注册表键名(字符串地址)
//////////////////////////////////////////////////////////////////////////////////
void CFBApp::SetRegistryKey(LPCTSTR lpszRegKey)
{
	HKEY hKey;

	strcpy(m_pszRegKey,"Software\\");
	strcat(m_pszRegKey,lpszRegKey);
	strcat(m_pszRegKey,"\\");
	strcat(m_pszRegKey,m_pszAppName);

	if(RegCreateKeyEx(HKEY_CURRENT_USER,m_pszRegKey,NULL,NULL,
					REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,
					NULL,&hKey,NULL) == ERROR_SUCCESS)
		RegCloseKey(hKey);
}
/////////////////////////////////////////////////////////////////////////////////////////
//	函数: RegGetVal
//	参数: LPCTSTR lpszKeyName	键名
//		  LPCTSTR lpszValueName 值名
//		  DWORD	  dwType		类型
//		  LPBYTE  buff          接收数据的缓冲区地址
//		  DWORD   cbSize		缓冲区大小
//	说明: 从注册表中得到数据. 这个函数以及下面的函数都是作为保护成员
//		  提供给其它的几个读写注册表函数调用的. 另外, 这里说的读写注
//		  册表都是指读写应用程序注册键 (由函数SetRegistryKey创建) 下
//		  的数据.
//////////////////////////////////////////////////////////////////////////////////////////
BOOL CFBApp::RegGetVal(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,DWORD dwType,LPBYTE buff,DWORD cbSize)
{
	DWORD type = dwType;
	DWORD size = cbSize;
	HKEY hKey;
	char str[256];

	ZeroMemory(str,256);
	strcpy(str,m_pszRegKey);

	if(lpszKeyName)
	{
		strcat(str,"\\");
		strcat(str,lpszKeyName);
	}
	
	if(RegOpenKeyEx(HKEY_CURRENT_USER,str,NULL,
					KEY_ALL_ACCESS,&hKey) != ERROR_SUCCESS)
		return FALSE;

	LONG lResult = RegQueryValueEx(hKey,lpszValueName,NULL,&type,
						buff,&cbSize);
	RegCloseKey(hKey);

	if(lResult == ERROR_SUCCESS)
		return TRUE;
	else
		return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////
//	函数: RegSetVal
//	参数: LPCTSTR lpszKeyName	键名
//		  LPCTSTR lpszValueName 值名
//		  DWORD	  dwType		类型
//		  LPBYTE  buff          接收数据的缓冲区地址
//		  DWORD   cbSize		缓冲区大小
//	说明: 向注册表中写入数据.
//////////////////////////////////////////////////////////////////////////////////////////
void CFBApp::RegSetVal(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,DWORD dwType,LPBYTE buff,DWORD cbSize)
{
	HKEY hKey;
	char str[256];

	ZeroMemory(str,256);
	strcpy(str,m_pszRegKey);

	if(lpszKeyName)
	{
		strcat(str,"\\");
		strcat(str,lpszKeyName);
	}

	if(RegCreateKeyEx(HKEY_CURRENT_USER,str,NULL,NULL,
					REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,
					NULL,&hKey,NULL)!= ERROR_SUCCESS)
		return;

	RegSetValueEx(hKey,lpszValueName,NULL,dwType,buff,cbSize);
	RegCloseKey(hKey);
}
/////////////////////////////////////////////////////////////////////////////////////
//		函数: RegGetLong(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LONG nDefValue)
//		功能: 从注册表中得到一个整数值
//		参数: LPCTSTR		lpszKeyName		键名(字符串地址, 可以为NULL)
//			  LPCTSTR		lpszValueName	入口键名(字符串地址)
//			  LONG			nDefValue		默认值(如果失败将返回此值)
//		返值: LONG
////////////////////////////////////////////////////////////////////////////////////
LONG CFBApp::RegGetLong(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LONG nDefValue)
{
	if(lpszValueName == NULL)return nDefValue;

	LONG val = nDefValue;

	RegGetVal(lpszKeyName,lpszValueName,REG_DWORD,(LPBYTE)&val,sizeof(LONG));

	return val;
}
///////////////////////////////////////////////////////////////////////////////
//		函数: SetGetLong(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LONG nDefValue)
//		功能: 向注册表中写入一个整数值
//		参数: LPCTSTR		lpszKeyName		键名(字符串地址, 可以为NULL)
//			  LPCTSTR		lpszValueName	入口键名(字符串地址)
//			  LONG			nVal			值
/////////////////////////////////////////////////////////////////////////////////
void CFBApp::RegSetLong(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LONG nVal)
{
	if(lpszValueName == NULL)return;

	LONG val = nVal;
	RegSetVal(lpszKeyName,lpszValueName,REG_DWORD,(LPBYTE)&val,sizeof(LONG));
}
/////////////////////////////////////////////////////////////////////////////////////
//		函数: RegGetString(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPCTSTR buff,DWORD cbSize)
//		功能: 从注册表中得到一个字符串值
//		参数: 见函数RegGetVal的说明
////////////////////////////////////////////////////////////////////////////////////
BOOL CFBApp::RegGetString(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPCTSTR buff,DWORD cbSize)
{
	if((lpszValueName == NULL) || 
		(buff == NULL) || (cbSize == 0))
		return FALSE;

	return RegGetVal(lpszKeyName,lpszValueName,REG_SZ,(LPBYTE)buff,cbSize);
}
/////////////////////////////////////////////////////////////////////////////////////
//		函数: RegSetString(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPCTSTR buff,DWORD cbSize)
//		功能: 向注册表中写入一个字符串值
//		参数: 见函数RegSetVal的说明
////////////////////////////////////////////////////////////////////////////////////
void CFBApp::RegSetString(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPCTSTR buff,DWORD cbSize)
{
	if((lpszValueName == NULL) || 
		(buff == NULL) || (cbSize == 0))
		return;

	RegSetVal(lpszKeyName,lpszValueName,REG_SZ,(LPBYTE)buff,cbSize);
}
/////////////////////////////////////////////////////////////////////////////////////
//		函数: RegGetString(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPCTSTR buff,DWORD cbSize)
//		说明: 从注册表中得到一个二进制值. 利用这个函数及下面的函数
//			  可以对注册表读写一个很复杂数据结构
//		参数: 见函数RegGetVal的说明
////////////////////////////////////////////////////////////////////////////////////
BOOL CFBApp::RegGetBinary(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPBYTE buff,DWORD cbSize)
{
	if((lpszValueName == NULL) || 
		(buff == NULL) || (cbSize == 0))
		return FALSE;

	return RegGetVal(lpszKeyName,lpszValueName,REG_BINARY,buff,cbSize);
}
/////////////////////////////////////////////////////////////////////////////////////
//		函数: RegSetString(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPCTSTR buff,DWORD cbSize)
//		说明: 向注册表中写入一个二进制值. 
//		参数: 见函数RegSetVal的说明
////////////////////////////////////////////////////////////////////////////////////
void CFBApp::RegSetBinary(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPBYTE buff,DWORD cbSize)
{
	if((lpszValueName == NULL) || 
		(buff == NULL) || (cbSize == 0))
		return;

	RegSetVal(lpszKeyName,lpszValueName,REG_BINARY,buff,cbSize);
}