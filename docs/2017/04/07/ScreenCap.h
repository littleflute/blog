//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���ScreenCap.h

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