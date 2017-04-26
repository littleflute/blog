//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���FBCtrlBar.h

	��Ȩ��Firebird Software Workroom ����

	��������Դ����İ�Ȩ�ܡ��л����񹲺͹�����Ȩ�����Լ���
		  ����ط��ɺ���Լ�ı������κ��л���õ���Դ�����
		  ���˺ͻ�����δ��������ȷ��Ȩ�����ý���Դ��������
		  �κ���ҵĿ��(ֱ�ӵĻ��ӵ�)�����ڷ���ҵĿ�ĵ�ʹ
		  �� (�������ơ�������������޸�)�� ԭ����û���ر�
		  �������������������ĵ���˵������Դ��������ԭ
		  ���ߵ�����Ȩ��

	��д���ش���(chings)	1999.12 - 2000.5

	���磺Tel��(0792)6323086	E_mail��chings@163.net
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#ifndef _FBCTRLBAR_H__
#define _FBCTRLBAR_H__
//////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////
#include "FBWnd.h"
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//���ļ��������и��ࣺ
	//class CFBWnd
			class CFBCtrlBar;
					class CFBCoolBar;
					class CSizeBar;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//�ؼ����ķ��
#define CBS_GRIPPER			0x0001
#define CBS_FLYBY			0x0002
#define CBS_TOOLTIPS		0x0004
#define CBS_CLOSEBTN		0x0008
#define	CBS_BORDER_RECT		0x0F00
#define CBS_BORDER_LEFT		0x0100
#define CBS_BORDER_TOP		0x0200
#define CBS_BORDER_RIGHT	0x0400
#define CBS_BORDER_BOTTOM	0x0800
/////////////////////////////////////////////////////////////////////
//�ؼ�����ͣ��λ��
#define CB_DOCK_NON			0x0000
#define CB_DOCK_TOP			0x0001
#define CB_DOCK_LEFT		0x0002
#define CB_DOCK_RIGHT		0x0004
#define CB_DOCK_BOTTOM		0x0008
////////////////////////////////////////////////////////////////////////////////
//HitTest�Ľ��
#define HITTEST_SIZER		0x0001
#define HITTEST_GRIPPER		0x0002
////////////////////////////////////////////////////////////////////////////////
//�϶���Сʱ�ı�־
#define SIZEFLAG_NON		0x0000
#define SIZEFLAG_WE			0x0001//��������
#define SIZEFLAG_NS			0x0002//�ϱ�����
////////////////////////////////////////////////////////////////////////////////
#define FB_CBN_CLOSE		WM_USER+701//�ر�ʱ�򸸴��ڱ������Ϣ	
									   //�Ա�ʹ�����ڸ��²˵���Ŀ�ȡ�
////////////////////////////////////////////////////////////////////////////////
//	class CFBCtrlBar
//  ˵����һ����˵��Ҫֱ���ñ��๹�������Ϊ����ļ����Ӵ��ھ���
//		  �ĺ����Ǹ��յĺ�������û�а취������������Ӵ��ڡ�
///////////////////////////////////////////////////////////////////////
class CFBCtrlBar : public CFBWnd
{
public:
	CFBCtrlBar();
	~CFBCtrlBar();

	BOOL Create(LPSTR		lpszCaption,
				CFBWnd*		pParent,
				UINT		nStyle,
				int			width,
				int			height,
				UINT		uID);

	void Docking(UINT nDockState);
	virtual void GetChildWndRect(LPRECT pRect){};
protected:
	UINT			m_nStyle;				//���
	UINT			m_nDockState;			//ͣ��״̬
	UINT			m_nFlyState;			//�϶�ʱ��״̬
	UINT			m_nPreState;			//��һ�ε�ͣ��״̬
	UINT			m_nSizeFlag;			//�϶���Сʱ�ı�־
	BOOL			m_bDock;				//�Ƿ�ͣ��
	long			m_nWidth;				//��ʼ��
	long			m_nHeight;				//��ʼ��
	long			m_nSized;				//�϶���С�ĳߴ�
	BOOL			m_bDown;				//����Ƿ���
	POINT			m_BeginP,m_MoveP;		//��꿪ʼ������ƶ�ʱ�ĵ�
	RECT			m_rcFlyby,m_rcOver;
	RECT			m_rcSizer,m_rcGripper;

	void DrawGripper(HDC hDC,LPRECT pRect);
	void DrawSizeFlag();
	void OnLButtonDown(LPPOINT pPos,UINT key);
	void OnLButtonUp(LPPOINT pPos,UINT key);
	void OnMouseMove(LPPOINT pPos,UINT key);
	LONG HitTest(LPPOINT pPos);
	BOOL GetFlybySide(UINT flag);
	void DockStateChange(UINT state);

	virtual void OnSize();
	virtual void OnSetSize(LPRECT pRect);
	virtual void OnPaint(HDC hDC,LPRECT prcPaint);
	virtual void OnNotify(LPNMHDR pNMHDR,LRESULT& lResult);

	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};

////////////////////////////////////////////////////////////////////////////////
//
//			class CFBCoolBar
//
///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
#define		_BAND_MAXNUM	12//�����Լ���12��band
#define		_LINE_MAXNUM	4 //��������4��
//////////////////////////////////////////////////////////////////////
typedef struct tagCB_BANDINFO{//band������
	HWND	hWnd;				//���ھ��
	int		cyMinSize;			//��С��
	int		cxMinSize;			//��С��
	UINT	uID;				//��ʶ��
	BOOL	bShow;				//�Ƿ���ʾ
	RECT	rcBand;				//band����
	int		nLines;				//������
	int		nIndex;				//������
	LPCTSTR	pText;				//����
	int		cchText;			//�����ֽ���
	int		cxText;				//������ռ��
	int		cyText;				//������ռ��
}CB_BANDINFO,FAR* LPCB_BANDINFO;
//////////////////////////////////////////////////////////////////////////
typedef struct tagCB_LINEINFO{//�е�����
	int		nBandCount;			//����band����
	int		nVisibleCount;		//���п���band�ļ���
	int		nHeight;			//�и�
}CB_LINEINFO,*LPCB_LINEINFO;
//////////////////////////////////////////////////////////////////////
class CFBCoolBar : public CFBCtrlBar  
{
public:
	CFBCoolBar();
	virtual ~CFBCoolBar();

	void AddBand(LPCB_BANDINFO pbi);
	void ShowBand(UINT uID,BOOL bShow);
	void SetBkBitmap(HBITMAP hBmp,int type = 1);		//�ñ���λͼ
	void SetBkMode(int mode){
		m_nBkFlag = mode;}
	int	 IdToIndex(UINT uID);

	void UseGradientBk(COLORREF clr1,COLORREF clr2,int style);
	virtual void GetChildWndRect(LPRECT pRect);

protected:
	int				m_nBandCount;				//band����
	LPCB_BANDINFO	m_pBandInfo[_BAND_MAXNUM];
	LPCB_LINEINFO	m_pLineInfo[_LINE_MAXNUM];
	int				m_nLineCount;				//�м���
	int				m_nBkFlag;
	int				m_nBkBmpWidth,m_nBkBmpHeight;//����λͼ�Ŀ��
	HDC				m_hBkBmpDC;					 //����λͼDC

	void MoveChildWnd(int nIndex,BOOL bRedraw);
	void OnEraseBkgnd(HDC hDC,LRESULT& lResult);
	virtual void OnPaint(HDC hDC,LPRECT prcPaint);
	virtual void OnSize();
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};

////////////////////////////////////////////////////////////////////////////////
//
//			class CSizeBar
//
///////////////////////////////////////////////////////////////////////
class CSizeBar : public CFBCtrlBar  
{
public:
	CSizeBar();
	virtual ~CSizeBar();

	void SetChild(HWND hChild);
protected:
	HWND		m_hChild;

	virtual void GetChildWndRect(LPRECT pRect);
	virtual void OnPaint(HDC hDC,LPRECT prcPaint);
	virtual void OnSize();
	virtual void OnNotify(LPNMHDR pNMHDR,LRESULT& lResult);
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};

//////////////////////////////////////////////////////////////////////
#endif //_FBCTRLBAR_H__
