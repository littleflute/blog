//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	�ļ���FBApp.h	��CFBApp��ͷ�ļ�

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

	CFBWnd*			m_pMainWnd;			//������ָ��
	HINSTANCE		m_hInstance;		//ʵ�����
	LPCTSTR			m_pszAppName;		//������
	LPSTR			m_strCmdLine;		//�����в���

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

	HACCEL		m_hAccel;			//���ټ�
	DWORD		m_dwVersion;		//�汾��
	MSG			m_msgCur;			//��ǰ��Ϣ
	char		m_pszRegKey[256];	//ע������

	void SetRegistryKey(LPCTSTR lpszRegKey);
	BOOL RegGetVal(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,DWORD dwType,LPBYTE buff,DWORD cbSize);
	void RegSetVal(LPCTSTR lpszKeyName,LPCTSTR lpszValueName,DWORD dwType,LPBYTE buff,DWORD cbSize);

	virtual BOOL OnIdle(){return FALSE;}
};

#endif //_FBAPP_H__
