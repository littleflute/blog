//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���ImageView.h	��CImageView��ͷ�ļ�

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
#ifndef _IMAGEVIEW_H__
#define _IMAGEVIEW_H__

#include "FBView.h"

#define FB_IVN_SELECTED		0xB301
//#####################################################################
typedef struct tagIMAGE_INFO{
	HBITMAP		hBmp;
	int			cx,cy;
	int			nPixelFmt;
}IMAGE_INFO,*LPIMAGE_INFO;
//#####################################################################
class CImageView : public CFBView
{
public:
	CImageView();
	~CImageView();

	BOOL LoadFormBMPFile(LPTSTR szFileName);
	BOOL LoadFromHandle(HBITMAP hBmp);
	BOOL SaveToBMPFile(LPTSTR szFileName);
	void SetEmpty();
	void CalcSize();
	BOOL Draw();
	BOOL Crop();

	BOOL IsEmpty(){
		return (m_ImgInfo.hBmp == NULL);}

	LPBITMAPINFO GetBitmapInfo(HBITMAP hBmp);

	LPIMAGE_INFO GetImageInfo(){
		return &m_ImgInfo;}

	void ResetPos(){
		m_xSrc = m_ySrc = 0;}

	static HBITMAP CopyBitmap(HDC hDC,HBITMAP hBmp);

	BOOL			m_bCanSel;
	RECT			m_rcSel;
protected:

	IMAGE_INFO		m_ImgInfo;
	RECT			m_rcDest;
	int				m_xSrc,m_ySrc;
	BOOL			m_xFlag,m_yFlag;
	POINT			m_ptBegin;
	BOOL			m_bMouseDown,m_bCanMove;

	static HCURSOR	m_hDownCur,m_hUpCur,m_hSelCur;

	void			OnLButtonDown(POINT& pt,UINT key);
	void			OnMouseMove(POINT& pt,UINT key);
	void			OnLButtonUp();
	BOOL			OnSetCursor();
	virtual void	OnDraw(HDC hDC);
	virtual BOOL	DrawBackground(HDC hDC);
	virtual LRESULT WindowProc(UINT msg,WPARAM wParam,LPARAM lParam);
};
//#####################################################################
#endif//_IMAGEVIEW_H__