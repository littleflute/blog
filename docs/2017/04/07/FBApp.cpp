//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	�ļ���FBApp.h	��CFBApp��ִ���ļ�

	��Ȩ��Firebird Software Workroom ����

	��������Դ����İ�Ȩ�ܡ��л����񹲺͹�����Ȩ�����Լ���
		  ����ط��ɺ���Լ�ı������κ��л���õ���Դ�����
		  ���˺ͻ�����δ��������ȷ��Ȩ�����ý���Դ��������
		  �κ���ҵĿ��(ֱ�ӵĻ��ӵ�)�����ڷ���ҵĿ�ĵ�ʹ
		  �� (�������ơ�������������޸�)�� ԭ����û���ر�
		  �������������������ĵ���˵������Դ��������ԭ
		  ���ߵ�����Ȩ��

	��д���ش���(chings)	1999.12 - 2000.4

	���磺Tel��(0792)6323086	E_mail��chings@163.net
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#include "fclstd.h"
#include "FBApp.h"
//////////////////////////////////////////////////////////////////////
// ���캯������������
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
//	����: InitInstance()
//	˵��: �κ�CFBApp�����඼����������������Խ���Ӧ�ó���ʵ��
//		  �ĳ�ʼ������. 
///////////////////////////////////////////////////////////////////////////////
BOOL CFBApp::InitInstance()
{
	return TRUE;
}
///////////////////////////////////////////////////////////////////////////////	
//		����: ExitInstance()
//		˵��: �˳�ʵ��ʱ���б�Ҫ����ɨ����.
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
//	����: Run()
//	˵��: ������Ϣѭ��, Ӧ�ó�������.
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
//		����: SetRegistryKey(LPSTR lpszRegKey)
//		����: ����Ӧ�ó���ע�������
//		����: LPCTSTR lpszRegKey		ע������(�ַ�����ַ)
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
//	����: RegGetVal
//	����: LPCTSTR lpszKeyName	����
//		  LPCTSTR lpszValueName ֵ��
//		  DWORD	  dwType		����
//		  LPBYTE  buff          �������ݵĻ�������ַ
//		  DWORD   cbSize		��������С
//	˵��: ��ע����еõ�����. ��������Լ�����ĺ���������Ϊ������Ա
//		  �ṩ�������ļ�����дע��������õ�. ����, ����˵�Ķ�дע
//		  �����ָ��дӦ�ó���ע��� (�ɺ���SetRegistryKey����) ��
//		  ������.
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
//	����: RegSetVal
//	����: LPCTSTR lpszKeyName	����
//		  LPCTSTR lpszValueName ֵ��
//		  DWORD	  dwType		����
//		  LPBYTE  buff          �������ݵĻ�������ַ
//		  DWORD   cbSize		��������С
//	˵��: ��ע�����д������.
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
//		����: RegGetLong(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LONG nDefValue)
//		����: ��ע����еõ�һ������ֵ
//		����: LPCTSTR		lpszKeyName		����(�ַ�����ַ, ����ΪNULL)
//			  LPCTSTR		lpszValueName	��ڼ���(�ַ�����ַ)
//			  LONG			nDefValue		Ĭ��ֵ(���ʧ�ܽ����ش�ֵ)
//		��ֵ: LONG
////////////////////////////////////////////////////////////////////////////////////
LONG CFBApp::RegGetLong(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LONG nDefValue)
{
	if(lpszValueName == NULL)return nDefValue;

	LONG val = nDefValue;

	RegGetVal(lpszKeyName,lpszValueName,REG_DWORD,(LPBYTE)&val,sizeof(LONG));

	return val;
}
///////////////////////////////////////////////////////////////////////////////
//		����: SetGetLong(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LONG nDefValue)
//		����: ��ע�����д��һ������ֵ
//		����: LPCTSTR		lpszKeyName		����(�ַ�����ַ, ����ΪNULL)
//			  LPCTSTR		lpszValueName	��ڼ���(�ַ�����ַ)
//			  LONG			nVal			ֵ
/////////////////////////////////////////////////////////////////////////////////
void CFBApp::RegSetLong(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LONG nVal)
{
	if(lpszValueName == NULL)return;

	LONG val = nVal;
	RegSetVal(lpszKeyName,lpszValueName,REG_DWORD,(LPBYTE)&val,sizeof(LONG));
}
/////////////////////////////////////////////////////////////////////////////////////
//		����: RegGetString(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPCTSTR buff,DWORD cbSize)
//		����: ��ע����еõ�һ���ַ���ֵ
//		����: ������RegGetVal��˵��
////////////////////////////////////////////////////////////////////////////////////
BOOL CFBApp::RegGetString(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPCTSTR buff,DWORD cbSize)
{
	if((lpszValueName == NULL) || 
		(buff == NULL) || (cbSize == 0))
		return FALSE;

	return RegGetVal(lpszKeyName,lpszValueName,REG_SZ,(LPBYTE)buff,cbSize);
}
/////////////////////////////////////////////////////////////////////////////////////
//		����: RegSetString(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPCTSTR buff,DWORD cbSize)
//		����: ��ע�����д��һ���ַ���ֵ
//		����: ������RegSetVal��˵��
////////////////////////////////////////////////////////////////////////////////////
void CFBApp::RegSetString(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPCTSTR buff,DWORD cbSize)
{
	if((lpszValueName == NULL) || 
		(buff == NULL) || (cbSize == 0))
		return;

	RegSetVal(lpszKeyName,lpszValueName,REG_SZ,(LPBYTE)buff,cbSize);
}
/////////////////////////////////////////////////////////////////////////////////////
//		����: RegGetString(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPCTSTR buff,DWORD cbSize)
//		˵��: ��ע����еõ�һ��������ֵ. �����������������ĺ���
//			  ���Զ�ע����дһ���ܸ������ݽṹ
//		����: ������RegGetVal��˵��
////////////////////////////////////////////////////////////////////////////////////
BOOL CFBApp::RegGetBinary(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPBYTE buff,DWORD cbSize)
{
	if((lpszValueName == NULL) || 
		(buff == NULL) || (cbSize == 0))
		return FALSE;

	return RegGetVal(lpszKeyName,lpszValueName,REG_BINARY,buff,cbSize);
}
/////////////////////////////////////////////////////////////////////////////////////
//		����: RegSetString(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPCTSTR buff,DWORD cbSize)
//		˵��: ��ע�����д��һ��������ֵ. 
//		����: ������RegSetVal��˵��
////////////////////////////////////////////////////////////////////////////////////
void CFBApp::RegSetBinary(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,LPBYTE buff,DWORD cbSize)
{
	if((lpszValueName == NULL) || 
		(buff == NULL) || (cbSize == 0))
		return;

	RegSetVal(lpszKeyName,lpszValueName,REG_BINARY,buff,cbSize);
}