// MyPrpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BlXAU.h"
#include "MyPrpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPrpDlg dialog



CMyPrpDlg::CMyPrpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyPrpDlg::IDD, pParent),m_hWnd(NULL)
{
	//{{AFX_DATA_INIT(CMyPrpDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	for(int j = 0; j<100; j ++)
		m_pAllCtrl[j] = NULL;
}

void CMyPrpDlg::pvDestroyAllCtrl()
{
	for (int i=0;i<100;i++)
    {
		if(NULL!=m_pAllCtrl[i]){

			if(m_pAllCtrl[i]->nType==1&&m_pAllCtrl[i]->pCtrl!=NULL){
				CSliderCtrl *pSlider = (CSliderCtrl *)m_pAllCtrl[i]->pCtrl;
				pSlider->DestroyWindow();
				
				delete pSlider;
				pSlider=NULL;
			}
			else if (m_pAllCtrl[i]->nType==2&&m_pAllCtrl[i]->pCtrl!=NULL)
			{
				CStatic *pStatic = (CStatic *)m_pAllCtrl[i]->pCtrl;
				pStatic->DestroyWindow();
				delete pStatic;
				pStatic=NULL;
			}
			else if (m_pAllCtrl[i]->nType==3&&m_pAllCtrl[i]->pCtrl!=NULL)
			{
				CEdit *pEdit = (CEdit *)m_pAllCtrl[i]->pCtrl;
				pEdit->DestroyWindow();
				delete pEdit;
				pEdit=NULL;
			}
			else if (m_pAllCtrl[i]->nType==4&&m_pAllCtrl[i]->pCtrl!=NULL)
			{
				CButton *pBut = (CButton *)m_pAllCtrl[i]->pCtrl;
				pBut->DestroyWindow();
				delete pBut;
				pBut=NULL;
			}
			else if (m_pAllCtrl[i]->nType==5&&m_pAllCtrl[i]->pCtrl!=NULL)
			{
				CButton *pBut = (CButton *)m_pAllCtrl[i]->pCtrl;
				pBut->DestroyWindow();
				delete pBut;
				pBut=NULL;
			}
			else if (m_pAllCtrl[i]->nType==6&&m_pAllCtrl[i]->pCtrl!=NULL)
			{
				CComboBox *pCombox = (CComboBox *)m_pAllCtrl[i]->pCtrl;
				pCombox->DestroyWindow();
				delete pCombox;
				pCombox=NULL;
			}
			else if (m_pAllCtrl[i]->nType==7&&m_pAllCtrl[i]->pCtrl!=NULL)
			{
				CButton *pBut = (CButton *)m_pAllCtrl[i]->pCtrl;
				pBut->DestroyWindow();
				delete pBut;
				pBut=NULL;
			}
			
			
			delete m_pAllCtrl[i];
			m_pAllCtrl[i] = NULL;
		}
    }
	
}
void CMyPrpDlg::pvCreateAllCtrl()
{
	if (1) 
	{
			m_nCtl=Ctrl_NUMBER_SV1310FC;
			for(int i = 0; i<m_nCtl ; i++)
			{
				if (m_pAllCtrl[i]==NULL)
				{
					m_pAllCtrl[i]=new CAllCtrl;
				}
				
				sscanf(g_strPreCtrl_SV1310FC[i],"%d [%d,%d,%d,%d] %d %s %s ",
					&m_pAllCtrl[i]->nType,
					&m_pAllCtrl[i]->x,
					&m_pAllCtrl[i]->y,
					&m_pAllCtrl[i]->w,
					&m_pAllCtrl[i]->h,
					&m_pAllCtrl[i]->nID,
					&m_pAllCtrl[i]->ch,
					&m_pAllCtrl[i]->chX);
			}
			
		}
	
    for(int j = 0; j<m_nCtl; j++){
		
		m_pAllCtrl[j]->CreateMe(this);
		 
	}
}
LRESULT CMyPrpDlg::DefWindowProc(UINT m, WPARAM w, LPARAM l) 
{ 	
	if(WM_CREATE==m)
	{
		pvCreateAllCtrl();
	} 
	pvDefWindowProc(m,w,l);  
	
	return CDialog::DefWindowProc(m, w, l);
}
 
void CMyPrpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyPrpDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyPrpDlg, CDialog)
	//{{AFX_MSG_MAP(CMyPrpDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPrpDlg message handlers
