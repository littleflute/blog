//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	�ļ���CapForm.h	��CCapForm��ͷ�ļ�

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

#ifndef _CAPFORM_H__
#define _CAPFORM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FBDialog.h"
//#####################################################################
class CCapForm : public CModalDlg  
{
public:
	CCapForm();
	virtual ~CCapForm();

	HCURSOR m_hCursor;
	POINT	m_ptBegin,m_ptEnd;
	RECT	m_rcSel;
	HDC		m_hScreenDC;
	UINT	m_nCapFlag;

protected:
	BOOL	m_bDown;

	virtual void OnInitDialog();
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};

//#####################################################################
#endif //_CAPFORM_H__
