//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	文件：FBCtrlBar.h

	版权：Firebird Software Workroom 保留

	声明：本源程序的版权受《中华人民共和国著作权法》以及其
		  它相关法律和条约的保护。任何有机会得到本源程序的
		  个人和机构，未经作者明确授权，不得将本源程序用于
		  任何商业目的(直接的或间接的)。对于非商业目的的使
		  用 (包括复制、传播、编译和修改)， 原则上没有特别
		  的限制条款，但请在相关文档中说明其来源，并尊重原
		  作者的署名权。

	编写：秦传安(chings)	1999.12 - 2000.5

	联络：Tel：(0792)6323086	E_mail：chings@163.net
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
//本文件包含下列各类：
	//class CFBWnd
			class CFBCtrlBar;
					class CFBCoolBar;
					class CSizeBar;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//控件栏的风格
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
//控件栏的停靠位置
#define CB_DOCK_NON			0x0000
#define CB_DOCK_TOP			0x0001
#define CB_DOCK_LEFT		0x0002
#define CB_DOCK_RIGHT		0x0004
#define CB_DOCK_BOTTOM		0x0008
////////////////////////////////////////////////////////////////////////////////
//HitTest的结果
#define HITTEST_SIZER		0x0001
#define HITTEST_GRIPPER		0x0002
////////////////////////////////////////////////////////////////////////////////
//拖动大小时的标志
#define SIZEFLAG_NON		0x0000
#define SIZEFLAG_WE			0x0001//东西方向
#define SIZEFLAG_NS			0x0002//南北方向
////////////////////////////////////////////////////////////////////////////////
#define FB_CBN_CLOSE		WM_USER+701//关闭时向父窗口报告的消息	
									   //以便使父窗口更新菜单项目等。
////////////////////////////////////////////////////////////////////////////////
//	class CFBCtrlBar
//  说明：一般来说不要直接用本类构造对象，因为本类的计算子窗口矩形
//		  的函数是个空的函数，你没有办法在它上面放置子窗口。
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
	UINT			m_nStyle;				//风格
	UINT			m_nDockState;			//停靠状态
	UINT			m_nFlyState;			//拖动时的状态
	UINT			m_nPreState;			//上一次的停靠状态
	UINT			m_nSizeFlag;			//拖动大小时的标志
	BOOL			m_bDock;				//是否停靠
	long			m_nWidth;				//初始宽
	long			m_nHeight;				//初始高
	long			m_nSized;				//拖动大小的尺寸
	BOOL			m_bDown;				//鼠标是否按下
	POINT			m_BeginP,m_MoveP;		//鼠标开始和鼠标移动时的点
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
#define		_BAND_MAXNUM	12//最多可以加上12个band
#define		_LINE_MAXNUM	4 //最多可以有4行
//////////////////////////////////////////////////////////////////////
typedef struct tagCB_BANDINFO{//band的数据
	HWND	hWnd;				//窗口句柄
	int		cyMinSize;			//最小高
	int		cxMinSize;			//最小宽
	UINT	uID;				//标识符
	BOOL	bShow;				//是否显示
	RECT	rcBand;				//band矩形
	int		nLines;				//所在行
	int		nIndex;				//索引号
	LPCTSTR	pText;				//标题
	int		cchText;			//标题字节数
	int		cxText;				//标题所占宽
	int		cyText;				//标题所占高
}CB_BANDINFO,FAR* LPCB_BANDINFO;
//////////////////////////////////////////////////////////////////////////
typedef struct tagCB_LINEINFO{//行的数据
	int		nBandCount;			//本行band计数
	int		nVisibleCount;		//本行可视band的计数
	int		nHeight;			//行高
}CB_LINEINFO,*LPCB_LINEINFO;
//////////////////////////////////////////////////////////////////////
class CFBCoolBar : public CFBCtrlBar  
{
public:
	CFBCoolBar();
	virtual ~CFBCoolBar();

	void AddBand(LPCB_BANDINFO pbi);
	void ShowBand(UINT uID,BOOL bShow);
	void SetBkBitmap(HBITMAP hBmp,int type = 1);		//置背景位图
	void SetBkMode(int mode){
		m_nBkFlag = mode;}
	int	 IdToIndex(UINT uID);

	void UseGradientBk(COLORREF clr1,COLORREF clr2,int style);
	virtual void GetChildWndRect(LPRECT pRect);

protected:
	int				m_nBandCount;				//band计数
	LPCB_BANDINFO	m_pBandInfo[_BAND_MAXNUM];
	LPCB_LINEINFO	m_pLineInfo[_LINE_MAXNUM];
	int				m_nLineCount;				//行计数
	int				m_nBkFlag;
	int				m_nBkBmpWidth,m_nBkBmpHeight;//背景位图的宽高
	HDC				m_hBkBmpDC;					 //背景位图DC

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
