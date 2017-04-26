//Download by http://www.NewXing.com
/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	�ļ���MainWnd.cpp

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
#include "fclstd.h"
#include "resource.h"
#include "ScreenCap.h"
#include "FBCommDlg.h"
#include "CapForm.h"
#include "ResizeDlg.h"
#include "SetingDlg.h"
#include "MainWnd.h"
#include "about.h"

#define IDW_TABCTRLBAR		0xE851
#define IDW_COOLBAR			0xE852

#define ID_TRAYICON			9201//����ͼ��ı�ʶ��
#define ID_HOTKEY			9202//�ȼ��ı�ʶ��
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMainWnd::CMainWnd()
{
	m_WndPlm.flags = WPF_RESTORETOMAXIMIZED;
	m_WndPlm.length = sizeof(WINDOWPLACEMENT);

	m_bIconMode = FALSE;//����ͼ��ı�־��TRUE��ͼ��������FALSE��δ����
	m_nNewCount = 0;
	m_strDefDir[0] = '\0';
	m_strBackFile[0] = '\0';
	m_bHotkey = FALSE;
}

CMainWnd::~CMainWnd()
{
}
////////////////////////////////////////////////////////////////////////////////////////
LRESULT CMainWnd::WindowProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	LRESULT lResult = 0;

	switch(msg)
	{
	case FBNM_TRAYICON://����ͼ�����Ϣ��ʶ��
		{
			if(wParam != ID_TRAYICON)//���Ǳ������������ͼ�꣬�򷵻ء�
				return 0;

			if(lParam == WM_RBUTTONUP)//�Ҽ��������˵�
				m_TrayIcon.PopupMenu();
			else if(lParam == WM_LBUTTONDBLCLK)//���˫��������������
			{
				if(IsShow())
					ShowWindow(m_hWnd,SW_HIDE);
				else
					ShowWindow(m_hWnd,SW_SHOW);
			}

			lResult = 1;
		}
		break;
	case WM_SHOWWINDOW:
		ShowStateChange((BOOL)wParam);
		break;
	//�û�������С����ť������������ͼ�ꡣ
	case WM_SYSCOMMAND:
		if(wParam == SC_MINIMIZE)
		{
			ShowWindow(m_hWnd,SW_HIDE);
			if(!m_bIconMode)
			{
				m_bIconMode = TRUE;
				m_TrayIcon.SetIcon(LoadIcon(GetInstance(),
								   MAKEINTRESOURCE(IDI_MAINICON)));
				m_TrayIcon.Open();
				m_wndToolBar.CheckedButton(ID_ICONMODE,TRUE);
			}
		}
		else if(wParam == SC_CLOSE)
		{
			PostQuitMessage(0);
		}
		else
			lResult = DefWindowProc(m_hWnd,msg,wParam,lParam);
		break;
	case WM_DRAWCLIPBOARD:
		{
			int fmt = CountClipboardFormats();
			if(fmt == CF_BITMAP)
			{
				m_wndToolBar.EnableButton(ID_EDITPASTE,TRUE);
				m_wndMenuBar.EnableMenuItem(ID_EDITPASTE,TRUE);
			}
			else
			{
				m_wndToolBar.EnableButton(ID_EDITPASTE,FALSE);
				m_wndMenuBar.EnableMenuItem(ID_EDITPASTE,FALSE);
			}
		}
		break;
	case WM_CLOSE:
		GetWindowPlacement(m_hWnd,&m_WndPlm);
	case WM_HOTKEY:
		if(wParam == ID_HOTKEY)
			OnCapScreen();
		break;
	default:
		lResult = CFBFrameWnd::WindowProc(msg,wParam,lParam);
		break;
	}

	return lResult;
}
////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainWnd::OnCreate()
{
	//����CoolBar�����ڼ��ع������Ͳ˵�����
	if(!m_wndCoolBar.Create(NULL,this,CBS_BORDER_RECT|CBS_GRIPPER,26,26,IDW_COOLBAR))
		return FALSE;

	//���������ز˵�����
	if(!m_wndMenuBar.Create(this,NULL,IDW_MAINMENU))
		return FALSE;
	HMENU hMenu = LoadMenu(GetInstance(), MAKEINTRESOURCE(IDM_MAINMENU));
	if(!m_wndMenuBar.LoadMenu(hMenu,FALSE))
		return FALSE;

	CB_BANDINFO cbif;
	cbif.bShow = TRUE;
	cbif.cxMinSize = 300;
	cbif.cyMinSize = 20;
	cbif.nLines = 0;
	cbif.hWnd = m_wndMenuBar.m_hWnd;
	cbif.uID = IDM_MAINMENU;
	cbif.cchText = 0;
	m_wndCoolBar.AddBand(&cbif);

	//���������ع�����
	if(!m_wndToolBar.Create(this,NULL,IDW_TOOLBAR))
		return FALSE;

	if(!m_wndToolBar.LoadToolBar(IDT_TOOLBAR))
		return FALSE;

	cbif.cchText = 0;
	cbif.cxMinSize = 300;
	cbif.cxText = NULL;
	cbif.cyMinSize = 22;
	cbif.hWnd = m_wndToolBar.m_hWnd;
	cbif.nLines = 1;
	cbif.uID = IDW_TOOLBAR;
	m_wndCoolBar.AddBand(&cbif);

	m_wndCoolBar.Docking(CB_DOCK_TOP);
	
	//����״̬��
	if(!m_wndStatusBar.Create(this,IDW_STATUSBAR))
		return FALSE;
	int pParts[4];
	pParts[0] = 180;
	pParts[1] = 240;
	pParts[2] = 300;
	pParts[3] = 420;
	m_wndStatusBar.SetParts(4,pParts);
	m_wndStatusBar.SetText(0,"����");

	//�����ͻ���ͼ
	if(!m_wndChildView.Create(this,IDW_TABCTRLBAR,CCS_TOP|TCS_FOCUSNEVER))
		return FALSE;

	HICON hIcon = LoadIcon(GetInstance(),MAKEINTRESOURCE(IDI_MAINICON));
	m_TrayIcon.Create(this,ID_TRAYICON,hIcon,"��Ļ����");
	m_TrayIcon.SetMenu(IDR_POPUP);

	CScreenCap* pApp = GetApp();

	if(!pApp->RegGetBinary("Config","Setings",(LPBYTE)&m_setings,sizeof(APP_SETINGS)))
	{
		m_setings.bAutoShowWnd = TRUE;
		m_setings.chKey = 'K';
		m_setings.clrGradHi = RGB(203,185,156);
		m_setings.clrGradLo = RGB(158,139,117);
		m_setings.clrViewBack = RGB(0,128,128);
		m_setings.nDefaultFmt = 0;
		m_setings.nStartMode = 0;
		m_setings.nToolBarBackMod = 1;
		m_setings.uHotkeyMod = MOD_CONTROL;
		m_setings.nGradStyle = 3;
	}

	if(!pApp->RegGetString("Config","DefaultSaveDir",m_strDefDir,MAX_PATH))
		lstrcpy(m_strDefDir,"c:\\windows\\temp\\");

	if(m_setings.nToolBarBackMod == 1)
		m_wndCoolBar.UseGradientBk(m_setings.clrGradLo,m_setings.clrGradHi,m_setings.nGradStyle);
	else if(m_setings.nToolBarBackMod == 2)
	{
		if(pApp->RegGetString("Config","ToolBarBkFile",m_strBackFile,MAX_PATH))
		{
			HBITMAP hbmp = (HBITMAP)LoadImage(NULL,m_strBackFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
			if(hbmp)
				m_wndCoolBar.SetBkBitmap(hbmp);
			else
				m_setings.nToolBarBackMod = 0;
		}
		else
			m_setings.nToolBarBackMod = 0;
	}

	m_wndChildView.m_clrBack = m_setings.clrViewBack;

	SetClipboardViewer(m_hWnd);

	InitUI();

	m_bHotkey = RegisterHotKey(m_hWnd,ID_HOTKEY,
						m_setings.uHotkeyMod,m_setings.chKey);

	return TRUE;
}
///////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::InitUI()
{
	m_wndToolBar.EnableButton(ID_FILECLOSE,FALSE);
	m_wndToolBar.EnableButton(ID_FILE_CLOSEALL,FALSE);
	m_wndToolBar.EnableButton(ID_FILESAVE,FALSE);
	m_wndToolBar.EnableButton(ID_FILE_SAVEAS,FALSE);
	m_wndToolBar.EnableButton(ID_FILEPRINT,FALSE);
	m_wndToolBar.EnableButton(ID_EDITCOPY,FALSE);
	m_wndToolBar.EnableButton(ID_EDITCUT,FALSE);
	m_wndToolBar.EnableButton(ID_SELECT,FALSE);
	m_wndToolBar.EnableButton(ID_CROP,FALSE);
	m_wndToolBar.EnableButton(ID_RESIZE,FALSE);

	m_wndMenuBar.EnableMenuItem(ID_FILECLOSE,FALSE);
	m_wndMenuBar.EnableMenuItem(ID_FILE_CLOSEALL,FALSE);
	m_wndMenuBar.EnableMenuItem(ID_FILESAVE,FALSE);
	m_wndMenuBar.EnableMenuItem(ID_FILE_SAVEAS,FALSE);
	m_wndMenuBar.EnableMenuItem(ID_FILEPRINT,FALSE);
	m_wndMenuBar.EnableMenuItem(ID_EDITCOPY,FALSE);
	m_wndMenuBar.EnableMenuItem(ID_EDITCUT,FALSE);
	m_wndMenuBar.EnableMenuItem(ID_SELECT,FALSE);
	m_wndMenuBar.EnableMenuItem(ID_CROP,FALSE);
	m_wndMenuBar.EnableMenuItem(ID_RESIZE,FALSE);
	m_wndMenuBar.EnableMenuItem(ID_FILEPRINTPREVIEW,FALSE);
	m_wndMenuBar.EnableMenuItem(ID_FILEPRINTSETUP,FALSE);

	m_wndToolBar.CheckedButton(ID_SELECT,FALSE);
	m_wndMenuBar.CheckMenuItem(ID_SELECT,FALSE);

	m_wndStatusBar.SetText(0,"����");
	m_wndStatusBar.SetText(1,"");
	m_wndStatusBar.SetText(2,"");
	m_wndStatusBar.SetText(3,"");
}
///////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::UpdateUI()
{
	CImageView* pImg = (CImageView*)m_wndChildView.GetActiveView();
	if((!pImg)? TRUE : pImg->IsEmpty())
	{
		InitUI();
		return;
	}

	m_wndToolBar.EnableButton(ID_FILECLOSE,TRUE);
	m_wndToolBar.EnableButton(ID_FILE_CLOSEALL,TRUE);
	m_wndToolBar.EnableButton(ID_FILESAVE,TRUE);
	m_wndToolBar.EnableButton(ID_FILE_SAVEAS,TRUE);
	m_wndToolBar.EnableButton(ID_FILEPRINT,TRUE);
	m_wndToolBar.EnableButton(ID_EDITCOPY,TRUE);
	m_wndToolBar.EnableButton(ID_EDITCUT,TRUE);
	m_wndToolBar.EnableButton(ID_SELECT,TRUE);
	m_wndToolBar.EnableButton(ID_RESIZE,TRUE);

	m_wndMenuBar.EnableMenuItem(ID_FILECLOSE,TRUE);
	m_wndMenuBar.EnableMenuItem(ID_FILE_CLOSEALL,TRUE);
	m_wndMenuBar.EnableMenuItem(ID_FILESAVE,TRUE);
	m_wndMenuBar.EnableMenuItem(ID_FILE_SAVEAS,TRUE);
	m_wndMenuBar.EnableMenuItem(ID_FILEPRINT,TRUE);
	m_wndMenuBar.EnableMenuItem(ID_EDITCOPY,TRUE);
	m_wndMenuBar.EnableMenuItem(ID_EDITCUT,TRUE);
	m_wndMenuBar.EnableMenuItem(ID_SELECT,TRUE);
	m_wndMenuBar.EnableMenuItem(ID_RESIZE,TRUE);
	m_wndMenuBar.EnableMenuItem(ID_FILEPRINTPREVIEW,TRUE);
	m_wndMenuBar.EnableMenuItem(ID_FILEPRINTSETUP,TRUE);

	if(pImg->m_bCanSel && !IsRectEmpty(&pImg->m_rcSel))
	{
		m_wndToolBar.EnableButton(ID_CROP,TRUE);
		m_wndMenuBar.EnableMenuItem(ID_CROP,TRUE);
	}
	else
	{
		m_wndToolBar.EnableButton(ID_CROP,FALSE);
		m_wndMenuBar.EnableMenuItem(ID_CROP,FALSE);
	}

	m_wndToolBar.CheckedButton(ID_SELECT,pImg->m_bCanSel);
	m_wndMenuBar.CheckMenuItem(ID_SELECT,pImg->m_bCanSel);

	char str[16];
	char tmp[8];
	LPIMAGE_INFO pii = pImg->GetImageInfo();

	ltoa(pii->cx,tmp,10);
	lstrcpy(str,"��");
	lstrcat(str,tmp);
	m_wndStatusBar.SetText(1,str);

	ltoa(pii->cy,tmp,10);
	lstrcpy(str,"�ߣ�");
	lstrcat(str,tmp);
	m_wndStatusBar.SetText(2,str);

	ltoa(pii->nPixelFmt,tmp,10);
	lstrcpy(str,"���ظ�ʽ��");
	lstrcat(str,tmp);
	lstrcat(str," λ");
	m_wndStatusBar.SetText(3,str);

	m_wndStatusBar.SetText(0,"����");
}
///////////////////////////////////////////////////////////////////////////////////////
//�ر�ͼ�갴ť
void CMainWnd::OnClose()
{
	if(m_bIconMode)
		m_TrayIcon.Close();

	m_setings.clrViewBack = m_wndChildView.m_clrBack;
	CScreenCap* pApp = GetApp();
	pApp->RegSetBinary("Config","Setings",(LPBYTE)&m_setings,sizeof(APP_SETINGS));
	pApp->RegSetString("Config","DefaultSaveDir",m_strDefDir,MAX_PATH);
	pApp->RegSetString("Config","ToolBarBkFile",m_strBackFile,MAX_PATH);
}
///////////////////////////////////////////////////////////////////////////////////////
//���㴰�ڲ���
void CMainWnd::ReCalcLayout()
{
	RECT rc;
	GetClientRect(m_hWnd,&rc);

	SendMessage(m_wndCoolBar.m_hWnd,FBWM_SETSIZE,0,(LPARAM)&rc);
	SendMessage(m_wndStatusBar.m_hWnd,FBWM_SETSIZE,0,(LPARAM)&rc);
	SendMessage(m_wndChildView.m_hWnd,FBWM_SETSIZE,0,(LPARAM)&rc);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//����������Ϣ
void CMainWnd::OnCommand(UINT uCode,UINT uID,HWND hwndCtrl)
{
	switch(uID)
	{
	case ID_VIEWTOOLBAR://��ʾ�����ع�����
		{
			BOOL flag = m_wndMenuBar.GetMenuItemCheckState(uID);
			m_wndMenuBar.CheckMenuItem(uID,!flag);
			m_wndCoolBar.ShowBand(IDW_TOOLBAR,!flag);
		}
		break;
	case ID_VIEWSTATUSBAR://��ʾ�����״̬��
		{
			BOOL flag = m_wndMenuBar.GetMenuItemCheckState(uID);
			m_wndMenuBar.CheckMenuItem(uID,!flag);
			int show = SW_SHOW;
			if(flag)
				show = SW_HIDE;
			ShowWindow(m_wndStatusBar.m_hWnd,show);
			ReCalcLayout();
		}
		break;
	case ID_ABOUT: 
		{
			CAboutDlg About;
			About.Create(this,IDD_ABOUTBOX);
			About.DoModal();
		}
		break;
	case ID_APP_EXIT: 
		GetWindowPlacement(m_hWnd,&m_WndPlm);
		PostQuitMessage(0);
		OnClose();
		break;
	case ID_FILEOPEN:
		OnFileOpen();
		break;
	case ID_FILESAVE:
		OnFileSave();
		break;
	case ID_FILE_SAVEAS:
		OnSaveAs();
		break;
	case ID_FILECLOSE:
		m_wndChildView.Remove(m_wndChildView.GetCurSel());
		UpdateUI();
		break;
	case ID_FILE_CLOSEALL:
		m_wndChildView.RemoveAll();
		UpdateUI();
		break;
	case ID_FILEPRINT:
		OnFilePrint();
		break;
	case ID_CAPSCREEN:
		OnCapScreen();
		break;
	case ID_CAPOBJECT:
		OnCapObject();
		break;
	case ID_CAPSELECT:
		OnCapSelect();
		break;
	case ID_OPENMAINWND:
		{
			if(IsShow())
				ShowWindow(m_hWnd,SW_HIDE);
			else
				ShowWindow(m_hWnd,SW_SHOW);
		}
		break;
	case ID_ICONMODE:
		{
			if(m_bIconMode)
			{
				ShowWindow(m_hWnd,SW_SHOW);
				m_TrayIcon.Close();
				m_bIconMode = FALSE;
			}
			else
			{
				m_bIconMode = TRUE;
				m_TrayIcon.Open();
				ShowWindow(m_hWnd,SW_HIDE);
			}
			m_wndToolBar.CheckedButton(uID,m_bIconMode);
			m_wndMenuBar.CheckMenuItem(uID,m_bIconMode);
		}
		break;
	case ID_SELECT:
		if(m_wndToolBar.GetButtonState(ID_SELECT) & TBSTATE_CHECKED)
		{
			m_wndChildView.EnableSelect(FALSE);
			m_wndToolBar.CheckedButton(uID,FALSE);
			m_wndMenuBar.CheckMenuItem(uID,FALSE);
		}
		else
		{
			m_wndChildView.EnableSelect(TRUE);
			m_wndToolBar.CheckedButton(uID,TRUE);
			m_wndMenuBar.CheckMenuItem(uID,TRUE);
		}
		break;
	case ID_CROP:
		OnCrop();
		break;
	case ID_RESIZE:
		{
			CImageView* pImg = (CImageView*)m_wndChildView.GetActiveView();
			if(!pImg)
				break;

			CResizeDlg dlg;
			dlg.Create(this,IDD_RESIZE);
			if(dlg.DoModal() == IDOK)
			{
				pImg->LoadFromHandle(dlg.m_hBmpTemp);
				UpdateUI();
			}
			else
			{
				pImg->CalcSize();
				DeleteObject(dlg.m_hBmpTemp);
			}

			pImg->Invalidate();
		}
		break;
	case ID_EDITPASTE:
		OnPaste();
		break;
	case ID_EDITCOPY:
		OnCopy();
		break;
	case ID_EDITCUT:
		OnCut();
		break;
	case ID_SETBACKCOLOR:
		OnSetBackColor();
		break;
	case ID_SETINGS:
		OnSetings();
		break;
	default:
		break;
	}
}
/////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnCustomNotify(UINT code,UINT uID,LPARAM lParam)
{
	switch(code)
	{
	case FB_TTN_SHOWING://ToolTip��ʾ��ʱ�򷢴���Ϣ
		m_wndStatusBar.SetText(0,(LPSTR)lParam);
		break;
	case FB_TTN_HIDEN://ToolTip��ʧ��ʱ�򷢴���Ϣ
		m_wndStatusBar.SetText(0,"����");
		break;
	case FB_TABN_SELCHANGED:
		UpdateUI();
		break;
	case FB_IVN_SELECTED:
		m_wndToolBar.EnableButton(ID_CROP,TRUE);
		m_wndMenuBar.EnableMenuItem(ID_CROP,TRUE);
		break;
	}
}
/////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnFileOpen()
{
	CFileDlg *pDlg = new CFileDlg();
	LPTSTR szFilter = "����֧���ļ�\0*.bmp;*.jpg;*.jpeg;*.gif\0";
	
	pDlg->Create(this,szFilter,TRUE);
	if(pDlg->DoModal() != IDOK)return;

	LPTSTR szFile = pDlg->GetFileFullPath();

	int n = lstrlen(szFile);
	int i;
	for(i=n-1;i>0;i--)
	{
		if(szFile[i] == '.')
			break;
	}

	if(lstrcmpi(szFile+i+1,"BMP") == 0)
		m_wndChildView.AddImage(szFile);
	else
	{
		if(GetApp()->GetVersion() == 0)
			VersionTip();
		else
		{
			HBITMAP hbmp = LoadFromFile(szFile);
			m_wndChildView.AddImage(hbmp,pDlg->GetFileName());
		}
	}
	delete pDlg;
	UpdateUI();
}
/////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnFileSave()
{
	CImageView* pImg = (CImageView*)m_wndChildView.GetActiveView();
	if(!pImg)return;

	CFileDlg OpenDlg;
	LPTSTR strFilter;
	if(m_setings.nDefaultFmt == 0)
	{
		strFilter = "λͼ�ļ�\0*.bmp\0";
		OpenDlg.m_OpenData.lpstrDefExt = "bmp";
	}
	else if(m_setings.nDefaultFmt == 1)
	{
		strFilter = "JPG�ļ�\0*.jpg\0";
		OpenDlg.m_OpenData.lpstrDefExt = "jpg";
	}
	else if(m_setings.nDefaultFmt == 2)
	{
		strFilter = "GIF�ļ�\0*.gif\0";
		OpenDlg.m_OpenData.lpstrDefExt = "gif";
	}

	OpenDlg.m_OpenData.lpstrInitialDir = m_strDefDir;
	OpenDlg.Create(this,strFilter,FALSE);
	if(OpenDlg.DoModal() != IDOK)return;

	LPTSTR szFile = OpenDlg.GetFileFullPath();
	BOOL bRet;

	if(GetApp()->GetVersion() != 0)
	{
		LPIMAGE_INFO pii = pImg->GetImageInfo();
		bRet = SaveToFile(pii->hBmp,szFile);
	}
	else
		bRet = m_wndChildView.SaveCurrentImage(szFile);

	if(bRet)
		m_wndChildView.SetCaption(m_wndChildView.GetCurSel(),OpenDlg.GetFileName());
}
/////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnSaveAs()
{
	if(GetApp()->GetVersion() == 0)
		VersionTip();
	else
	{
		CFileDlg *pDlg = new CFileDlg();
		LPTSTR szFilter = "λͼ�ļ�\0*.bmp\0JPG�ļ�\0*.jpg;*.jpeg\0GIF�ļ�\0*.gif\0";
	
		pDlg->Create(this,szFilter,FALSE);
		if(pDlg->DoModal() != IDOK)return;

		LPTSTR szFile = pDlg->GetFileFullPath();

		CImageView* pImg = (CImageView*)m_wndChildView.GetActiveView();
		LPIMAGE_INFO pii = pImg->GetImageInfo();
		SaveToFile(pii->hBmp,szFile);
	}
}
/////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnFilePrint()
{
	CPrintDlg dlg;
	dlg.Create(this,PD_RETURNDC);
	if(dlg.DoModal() != IDOK)return;

	if(!(GetDeviceCaps(dlg.m_ptd.hDC, RASTERCAPS) & RC_BITBLT))
	{
		MessageBox(NULL,"��ӡ����֧��λͼ��ӡ","����",MB_OK|MB_ICONWARNING);
		return;
	}

	int cx = GetDeviceCaps(dlg.m_ptd.hDC,HORZRES);
	int cy = GetDeviceCaps(dlg.m_ptd.hDC,VERTRES);
	int x,y,ratio;

	CImageView* pImg = (CImageView*)m_wndChildView.GetActiveView();
	LPIMAGE_INFO pii = pImg->GetImageInfo();

	if((pii->cx <= cx) && (pii->cy <= cy))
	{
		x = (int)(cx - pii->cx)/2;
		y = (int)(cy - pii->cy)/2;
	}
	else
	{
		if(pii->cx > pii->cy)
			ratio = (int)cx/pii->cx;
		else
			ratio = (int)cy/pii->cy;
		cx = pii->cx*ratio;
		cy = pii->cy*ratio;
	}

	char filename[_MAX_FNAME];
	m_wndChildView.GetCaption(m_wndChildView.GetCurSel(),filename,_MAX_FNAME);

	HDC hdc = CreateCompatibleDC(dlg.m_ptd.hDC);
	SelectObject(hdc,pii->hBmp);

	DOCINFO di;
	di.cbSize = sizeof(DOCINFO);
	di.fwType = 0;
	di.lpszDocName = filename;
	di.lpszOutput = NULL;
	di.lpszDatatype = NULL;

	if(StartDoc(dlg.m_ptd.hDC,&di) > 0)
		StretchBlt(dlg.m_ptd.hDC,x,y,cx,cy,hdc,0,0,pii->cx,pii->cy,SRCCOPY);
	else
		MessageBox(NULL,"ִ�д�ӡ��ҵʱ�������󣬿����Ǵ�ӡ��û׼���á�","����",MB_OK|MB_ICONWARNING);
	EndDoc(dlg.m_ptd.hDC);
}
/////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnCopy()
{
	CImageView* pImg = (CImageView*)m_wndChildView.GetActiveView();
			
	if(!pImg)return;
	if(pImg->IsEmpty())return;
	if(!OpenClipboard(m_hWnd))return;

	LPIMAGE_INFO pii = pImg->GetImageInfo();
	HDC hdc = GetDC(NULL);
	HBITMAP hbmp = CImageView::CopyBitmap(hdc,pii->hBmp);

	EmptyClipboard();
	SetClipboardData(CF_BITMAP,(HANDLE)hbmp);
	CloseClipboard();

	ReleaseDC(NULL,hdc);
}
/////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnCut()
{
	OnCopy();

	CImageView* pImg = (CImageView*)m_wndChildView.GetActiveView();
	if(!pImg)return;

	pImg->SetEmpty();
	UpdateUI();
}
/////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnPaste()
{
	if(CountClipboardFormats() != CF_BITMAP)
		return;

	if(!OpenClipboard(m_hWnd))
		return;

	HBITMAP hbmp = (HBITMAP)GetClipboardData(CF_BITMAP);
	if(!hbmp)return;

	HDC hdc = GetDC(NULL);
	HBITMAP hBitmap = CImageView::CopyBitmap(hdc,hbmp);

	CImageView* pImg = (CImageView*)m_wndChildView.GetActiveView();
	if((!pImg)? FALSE : pImg->IsEmpty())
	{
		pImg->LoadFromHandle(hBitmap);
		pImg->Invalidate();
		UpdateUI();
	}
	else
	{
		char name[_MAX_FNAME];
		char tmp[8];
		ltoa(m_nNewCount+1,tmp,10);
		lstrcpy(name,"��ͼƬ");
		lstrcat(name,tmp);

		if(m_wndChildView.AddImage(hBitmap,name) != -1)
		{
			m_nNewCount++;
			UpdateUI();
		}
	}

	CloseClipboard();
}
/////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnSetBackColor()
{
	CColorDlg dlg;
	dlg.Create(this,m_wndChildView.m_clrBack);
	if(dlg.DoModal() == IDOK)
		m_wndChildView.ChangeBkColor(dlg.GetSelColor());
}
/////////////////////////////////////////////////////////////////////////////////////
//ץȡָ������
void CMainWnd::CaptureRect(HDC hdcScreen,LPRECT prc,BOOL bFullScreen)
{
	HDC hdc = CreateCompatibleDC(hdcScreen);
	HBITMAP hbmp = CreateCompatibleBitmap(hdcScreen,prc->right - prc->left,
									 prc->bottom - prc->top);
	SelectObject(hdc,hbmp);

	BitBlt(hdc,0,0,prc->right - prc->left,prc->bottom - prc->top,
		   hdcScreen,prc->left,prc->top,SRCCOPY);

	char name[_MAX_FNAME];
	char tmp[8];
	ltoa(m_nNewCount+1,tmp,10);
	lstrcpy(name,"��ͼƬ");
	lstrcat(name,tmp);

	if(m_wndChildView.AddImage(hbmp,name) != -1)
	{
		m_nNewCount++;
		UpdateUI();
	}
	DeleteDC(hdc);

	if(!bFullScreen || m_setings.bAutoShowWnd || !m_bIconMode)
	{
		ShowWindow(m_hWnd,SW_SHOW);
		BringWindowToTop(m_hWnd);
	}
}
/////////////////////////////////////////////////////////////////////////////////////
//ץȫ��
void CMainWnd::OnCapScreen()
{
	HWND hWnd = GetWindow(m_hWnd,GW_HWNDNEXT);
	ShowWindow(m_hWnd,SW_HIDE);
	BringWindowToTop(hWnd);
	EnableWindow(hWnd,TRUE);

	Sleep(100);

	HDC hDeskDC = GetDC(NULL);
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = rc.left + GetSystemMetrics(SM_CXSCREEN);
	rc.bottom = rc.top + GetSystemMetrics(SM_CYSCREEN);

	CaptureRect(hDeskDC,&rc,TRUE);
}
/////////////////////////////////////////////////////////////////////////////////////
//ץָ������
void CMainWnd::OnCapObject()
{
	HWND hWnd = GetWindow(m_hWnd,GW_HWNDNEXT);
	ShowWindow(m_hWnd,SW_HIDE);
	BringWindowToTop(hWnd);
	EnableWindow(hWnd,TRUE);

	Sleep(100);

	CCapForm form;

	char WinPath[MAX_PATH];
	GetWindowsDirectory(WinPath, MAX_PATH);
	lstrcat(WinPath,"\\winhlp32.exe");
	HMODULE hModule = LoadLibrary(WinPath);
	if (hModule) {
		HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
		if (hHandCursor)
			form.m_hCursor = CopyCursor(hHandCursor);
	}
	FreeLibrary(hModule);

	form.Create(NULL,IDD_CAPFORM);
	form.m_nCapFlag = 1;
	form.DoModal();

	HWND hwnd = WindowFromPoint(form.m_ptEnd);
	RECT rc;
	GetWindowRect(hwnd,&rc);
	CaptureRect(form.m_hScreenDC,&rc);
	DeleteDC(form.m_hScreenDC);
}
/////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnCapSelect()
{
	HWND hWnd = GetWindow(m_hWnd,GW_HWNDNEXT);
	ShowWindow(m_hWnd,SW_HIDE);
	BringWindowToTop(hWnd);
	EnableWindow(hWnd,TRUE);

	Sleep(100);

	CCapForm form;

	form.m_hCursor = LoadCursor(NULL,IDC_CROSS);
	form.m_nCapFlag = 2;
	form.Create(this,IDD_CAPFORM);
	form.DoModal();

	if(!IsRectEmpty(&form.m_rcSel))
		CaptureRect(form.m_hScreenDC,&form.m_rcSel);
	DeleteDC(form.m_hScreenDC);
}
/////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnCrop()
{
	CImageView* pImg = (CImageView*)m_wndChildView.GetActiveView();
	if(!pImg)
		return;

	if(IsRectEmpty(&pImg->m_rcSel))
	{
		MessageBox(NULL,"��δѡ��ü�������","��ʾ",MB_OK);
		return;
	}

	pImg->Crop();

	UpdateUI();
}
/////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::ShowStateChange(BOOL bShow)
{
	if(m_bIconMode)
	{
		LPTSTR pText;
		HICON hIcon;
		if(!bShow)
		{
			pText = "��������(&M)";
			hIcon = LoadIcon(GetInstance(),MAKEINTRESOURCE(IDI_MAINICON));
		}
		else
		{
			pText = "�ر�������(&M)";
			hIcon = LoadIcon(GetInstance(),MAKEINTRESOURCE(IDI_ICON1));
		}

		m_TrayIcon.ModifyIcon(hIcon);

		HMENU hMenu = m_TrayIcon.GetMenu();
		HMENU hSub = GetSubMenu(hMenu,0);
		ModifyMenu(hSub,ID_OPENMAINWND,MF_BYCOMMAND|MF_STRING,ID_OPENMAINWND,pText);
	}
}
/////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::OnSetings()
{
	CSetingDlg dlg;
	dlg.Create(this,IDD_SETINGDLG);
	if(dlg.DoModal() != IDOK)
		return;

	LPAPP_SETINGS pas = dlg.GetSetings();

	if(pas->nToolBarBackMod == 1)
	{
		if((pas->clrGradHi != m_setings.clrGradHi) ||
		   (pas->clrGradLo != m_setings.clrGradLo) ||
		   (pas->nGradStyle != m_setings.nGradStyle) ||
		   (pas->nToolBarBackMod != m_setings.nToolBarBackMod))
		{
		   m_wndCoolBar.UseGradientBk(pas->clrGradLo,
									  pas->clrGradHi,
									  pas->nGradStyle);
		   m_wndCoolBar.Invalidate();
		}
	}
	else if(pas->nToolBarBackMod == 0)
	{
		m_wndCoolBar.SetBkMode(0);
		m_wndCoolBar.Invalidate();
	}
	else if(pas->nToolBarBackMod == 2)
	{
		if((pas->nToolBarBackMod != m_setings.nToolBarBackMod) ||
			(lstrcmpi(m_strBackFile,dlg.m_strBackFile) != 0))
		{
			lstrcpy(m_strBackFile,dlg.m_strBackFile);
			if(m_strBackFile[0] != '\0')
			{
				HBITMAP hbmp = (HBITMAP)LoadImage(NULL,m_strBackFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
				if(hbmp)
					m_wndCoolBar.SetBkBitmap(hbmp);
				else
					m_wndCoolBar.SetBkMode(0);
			}
			else
				m_wndCoolBar.SetBkMode(0);

			m_wndCoolBar.Invalidate();
		}
	}

	m_wndChildView.ChangeBkColor(pas->clrViewBack);

	if((pas->uHotkeyMod != m_setings.uHotkeyMod) ||
		(pas->chKey != m_setings.chKey))
	{
		if(m_bHotkey)
			UnregisterHotKey(m_hWnd,ID_HOTKEY);
		RegisterHotKey(m_hWnd,ID_HOTKEY,pas->uHotkeyMod,pas->chKey);
	}

	memcpy(&m_setings,pas,sizeof(APP_SETINGS));
	lstrcpy(m_strDefDir,dlg.m_strDefDir);
}
/////////////////////////////////////////////////////////////////////////////////////
void CMainWnd::VersionTip()
{
	char szText[] = "�װ����û���"
		"\n    ��õ�����Ļ������һ����ʾ�棬���ź�"
		"\n��ֻ��֧��λͼ�ļ�(BMP��ʽ )��Ҫ��ʹ����"
		"\nΪ��ʽ�沢���ѣ���ֻҪ��������Ҫһ��DLL "
		"\n(��̬���ӿ�)����(��ȫ���)��"
		"\n    ��ϵ�취�ɲο����ڶԻ���";
	MessageBox(NULL,szText,"�ر���ʾ",MB_OK);
}
