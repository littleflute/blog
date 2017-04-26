//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���ChildView.h	��CChildView��ͷ�ļ�

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

#ifndef _CHILDVIEW_H__
#define _CHILDVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FBCtrls.h"

class CChildView : public CFBTabCtrl  
{
public:
	CChildView();
	virtual ~CChildView();

	int AddImage(HBITMAP hBmp,LPTSTR pszCaption);
	int AddImage(LPTSTR szFileName);
	void EnableSelect(BOOL bEnable);
	BOOL SaveCurrentImage(LPTSTR szFile);
	void ChangeBkColor(COLORREF clr);

	COLORREF	m_clrBack;
protected:

	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};

#endif //_CHILDVIEW_H__
