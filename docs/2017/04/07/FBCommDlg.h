//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：FBCommDlg.h

	版权：Firebird Software Workroom 保留

	声明：本源程序的版权受《中华人民共和国著作权法》以及其
		  它相关法律和条约的保护。任何有机会得到本源程序的
		  个人和机构，未经作者明确授权，不得将本源程序用于
		  任何商业目的(直接的或间接的)。对于非商业目的的使
		  用 (包括复制、传播、编译和修改)， 原则上没有特别
		  的限制条款，但请在相关文档中说明其来源，并尊重原
		  作者的署名权。

	编写：秦传安(chings)	2000.5

	联络：Tel：(0792)6323086	E_mail：chings@163.net
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#ifndef _FBCOMMDLG_H__
#define _FBCOMMDLG_H__


#include <commdlg.h>
#include "FBDialog.h"

//#####################################################################
//本文件包含以下类，这些类封装了Windows部分公共对话框：
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
	BOOL	m_bFlag;//TRUE:打开对话框; FALSE:保存对话框

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