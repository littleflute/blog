//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���FBFrameWnd.h

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