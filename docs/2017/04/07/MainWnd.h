//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：MainWnd.h

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
#ifndef _MAINWND_H__
#define _MAINWND_H__
//////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////
#include "FBFrameWnd.h"
#include "FBCtrlBar.h"
#include "FBCtrls.h"
#include "ChildView.h"
#include "ImageView.h"
#include "TrayIcon.h"
/////////////////////////////////////////////////////////////////////
typedef struct tagAPP_SETINGS{
	int			nStartMode;		//启动方式: 0-常规窗口;1-托盘图标
	int			nToolBarBackMod;//工具栏背景模式: 0-无;1-梯度色;2-位图
	int			nDefaultFmt;	//默认保存格式: 0-BMP;1-JPG;2-GIF
	int			nGradStyle;
	COLORREF	clrGradHi;
	COLORREF	clrGradLo;
	COLORREF	clrViewBack;
	BOOL		bAutoShowWnd;
	UINT		uHotkeyMod;
	char		chKey;
}APP_SETINGS,*LPAPP_SETINGS;
/////////////////////////////////////////////////////////////////////
class CMainWnd : public CFBFrameWnd  
{
public:
	CMainWnd();
	virtual ~CMainWnd();

	CImageView*	GetCurrentImage(){
		return (CImageView*)m_wndChildView.GetActiveView();}
	LPAPP_SETINGS GetSetings(){
		return &m_setings;}

	WINDOWPLACEMENT m_WndPlm;
	char			m_strDefDir[MAX_PATH];
	char			m_strBackFile[MAX_PATH];

protected:

	CMenuBar		m_wndMenuBar;
	CFBCoolBar		m_wndCoolBar;
	CFBToolBar		m_wndToolBar;
	CFBStatusBar	m_wndStatusBar;
	CChildView		m_wndChildView;
	CTrayIcon		m_TrayIcon;

	BOOL			m_bIconMode;
	int				m_nNewCount;
	APP_SETINGS		m_setings;
	BOOL			m_bHotkey;

	void InitUI();
	void UpdateUI();
	void OnFileOpen();
	void OnFileSave();
	void OnSaveAs();
	void OnCapScreen();
	void OnCapObject();
	void OnCapSelect();
	void OnCrop();
	void OnCopy();
	void OnCut();
	void OnPaste();
	void OnFilePrint();
	void OnSetBackColor();
	void OnSetings();
	void CaptureRect(HDC hdcScreen,LPRECT prc,BOOL bFullScreen = FALSE);
	void ShowStateChange(BOOL bShow);
	void VersionTip();
	virtual void ReCalcLayout();
	virtual BOOL OnCreate();
	virtual void OnClose();
	virtual void OnCustomNotify(UINT code,UINT uID,LPARAM lParam);
	virtual void OnCommand(UINT uCode,UINT uID,HWND hwndCtrl);
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};
/////////////////////////////////////////////////////////////////////
#endif //_MAINWND_H__
