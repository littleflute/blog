//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���MainWnd.h

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
	int			nStartMode;		//������ʽ: 0-���洰��;1-����ͼ��
	int			nToolBarBackMod;//����������ģʽ: 0-��;1-�ݶ�ɫ;2-λͼ
	int			nDefaultFmt;	//Ĭ�ϱ����ʽ: 0-BMP;1-JPG;2-GIF
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
