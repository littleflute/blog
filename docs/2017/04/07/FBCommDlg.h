//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���FBCommDlg.h

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
#ifndef _FBCOMMDLG_H__
#define _FBCOMMDLG_H__


#include <commdlg.h>
#include "FBDialog.h"

//#####################################################################
//���ļ����������࣬��Щ���װ��Windows���ֹ����Ի���
//CFBWnd
		//CModalDlg
				class CFileDlg;
				class CColorDlg;
				class CPrintDlg;
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		class CFileDlg

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
class CFileDlg : public CModalDlg
{
public:
	CFileDlg();
	~CFileDlg();

	OPENFILENAME	m_OpenData;

	BOOL Create(CFBWnd		*pOwner,
				LPTSTR		szFilter,
				BOOL		bOpen,
				DWORD		Flags = 0,
				LPTSTR		szTemplate = NULL);
	LPTSTR GetFileFullPath(){
		return m_OpenData.lpstrFile;}
	LPTSTR GetFileName(){
		return m_OpenData.lpstrFileTitle;}

	virtual int DoModal();
protected:
	BOOL	m_bFlag;//TRUE:�򿪶Ի���; FALSE:����Ի���

	static UINT APIENTRY FileDlgProc(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam);
};

/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		class CColorDlg

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
class CColorDlg : public CModalDlg
{
public:
	CColorDlg();
	~CColorDlg();

	BOOL Create(CFBWnd* pOwner,
				COLORREF rgbInit = 0,
				DWORD Flags = 0,
				LPTSTR szTemplate = NULL);

	COLORREF GetSelColor(){
		return m_ccl.rgbResult;}

	virtual int DoModal();
protected:
	CHOOSECOLOR		m_ccl;

	static UINT APIENTRY ColorDlgProc(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam);
};
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		class CPrintDlg

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
class CPrintDlg : public CModalDlg
{
public:
	CPrintDlg();
	~CPrintDlg();

	PRINTDLG		m_ptd;

	BOOL Create(CFBWnd* pOwner,DWORD Flags = 0,LPTSTR szTemplate = NULL);

	virtual int DoModal();
protected:

	static UINT APIENTRY PrintDlgProc(HWND hdlg,UINT msg,WPARAM wParam,LPARAM lParam);
};
//#####################################################################
#endif//_FBCOMMDLG_H__