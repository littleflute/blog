//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���FBView.h	��CFBView��ͷ�ļ�

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
#ifndef _FBVIEW_H__
#define _FBVIEW_H__
//####################################################################
#include "FBWnd.h"
//####################################################################
class CFBView : public CFBWnd
{
public:
	CFBView();
	~CFBView();

	BOOL Create(CFBWnd* pParent,UINT uID,UINT style = 0);

	void SetBkColor(COLORREF clr);
	void SetBkImage(HBITMAP hBmp);
	void SetBkImage(LPTSTR pszFilename);

protected:

	int			m_nBkMode;//����ģʽ,0:Ĭ��;1:��ɫ;2:λͼ
	int			m_cxBkBmp,m_cyBkBmp;
	HDC			m_hBkBmpDC;
	HBRUSH		m_hBkBrush;

	virtual BOOL DrawBackground(HDC hDC);
	virtual void OnDraw(HDC hDC);
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};
//####################################################################
#endif//_FBVIEW_H__