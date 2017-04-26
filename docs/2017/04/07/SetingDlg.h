//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：SetingDlg.h 类CSetingDlg的头文件

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

#ifndef _SETINGDLG_H__
#define _SETINGDLG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MainWnd.h"
#include "FBDialog.h"

class CSetingDlg : public CModalDlg  
{
public:
	CSetingDlg();
	virtual ~CSetingDlg();

	LPAPP_SETINGS GetSetings(){
		return m_pas;}

	char		m_strDefDir[MAX_PATH];
	char		m_strBackFile[MAX_PATH];
protected:
	LPAPP_SETINGS		m_pas;
	RECT				rc1,rc2,rc3;

	void DrawColorRect();
	void OnLButtonDblclk(POINT& pt);
	void OnSelDir();
	void OnSelBkFile();
	void OnBtnClicked(UINT uID);
	void OnOk();

	virtual void OnInitDialog();
	virtual void OnCommand(UINT uCmdID,UINT code);
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};

#endif //_SETINGDLG_H__
