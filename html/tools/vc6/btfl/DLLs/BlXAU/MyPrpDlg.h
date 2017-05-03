#if !defined(AFX_MYPRPDLG_H__98B05DEC_15E0_46F9_97B9_DDB5F02ECFE6__INCLUDED_)
#define AFX_MYPRPDLG_H__98B05DEC_15E0_46F9_97B9_DDB5F02ECFE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyPrpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyPrpDlg dialog

#define  MAX_STRING	   100
const char g_strPreCtrl_SV1310FC[][MAX_STRING] = { 
		"7  [3,3,232,80]      9001   ��������		[]",				//Group  �ؼ�
		"2  [10,20,70,15]	  1000   Sleep(ms)		[] ",				//Static �ؼ�
		"1  [80,20,100,20]	  1001   SleepTime		[0,15000,10,1]",	//Slider �ؼ�
		"3  [180,20,44,20]	  1002   SleepTime		[0,15000,10]",		//edit	 �ؼ�
		/*
		"3  [180,60,40,20]	  1008   ��ͨ��       [0,31,14]   ",
		"2  [10,100,70,15]    1009   �ٶȵ�λ     [] ",
		"6  [80,100,100,100]  1010   �ٶȵ�λ     [2,1,US,MS]",
		"2  [10,130,70,15]	  1011   �����ٶ�     [] ",
		"1  [80,130,100,20]   1012   �����ٶ�     [1,1000,60,1]",
		"3  [180,130,40,20]	  1013   �����ٶ�     [1,1000,60] ",
		"6  [260,110,95,100]  1014   �ɼ���ʽ     [2,0,continue,Trigger] ",
		"4  [380,110,60,25]	  1015   ����       []",
		"2  [240,20,70,15]	  1016   ��������     []  ",
		"1  [310,20,120,20]	  1017   ��������     [2500,4096,2500,4]   ",
		"3  [430,20,40,20]	  1018   ��������     [2500,4096,2500]",
		"2  [240,40,70,15]	  1019   ���ȵ���     []  ",
		"1  [310,40,120,20]	  1020   ���ȵ���     [0,255,16,1]  ",
		"3  [430,40,40,20]	  1021   ���ȵ���     [0,255,16]",
		"2  [240,160,90,15]   1022   ����ƿ���   []  ",
		"6  [340,160,100,100] 1023   ����ƿ���   [2,1,Off,On] ",
		"2  [240,190,90,15]   1024   ����Ƽ���   []",
		"6  [340,190,100,100] 1025   ����Ƽ���   [2,1,Low,High]",
		"2  [10,180,90,15]    1026   �Ƿ�֡����   []",
		"5  [100,170,40,30]   1027   ֡����       [0]",
		"7  [3,160,120,50]    1028   ֡��������   []   ",
		"4  [125,180,100,28]  1029   ѡ���ұ��ļ� []",
		"6  [340,160,100,100] 1031   ����ƿ���   [2,1,Off,On]",
		"2  [240,190,90,15]   1032   ����Ƽ���   []",
		"7  [3,83,222,70]     1031   ���ſ���     []",
		"7  [238,83,235,70]   1032   �ɼ���ʽ     []",
		*/
} ;

#define  Ctrl_NUMBER_SV1310FC  ( sizeof(g_strPreCtrl_SV1310FC) / MAX_STRING )
 
class CMyPrpDlg : public CDialog
{
	class CAllCtrl  
	{
	public: 
		void CreateGroupButtonCtrl(CMyPrpDlg *pwnd, CRect rect)
		{
			if(pCtrl==NULL)
			{
				(pCtrl) = new (CButton);
				CButton*p=(CButton*)(pCtrl);
				p->Create(ch,BS_GROUPBOX|WS_CHILD|WS_VISIBLE,
					rect,
					pwnd,
					nID);
				
				::SendMessage(p->m_hWnd,WM_SETFONT,(DWORD)hFont,TRUE);  
				p->Invalidate(TRUE);
			}
			
		}
		
		void CAllCtrl::CreateComboBoxCtrl(CMyPrpDlg *pwnd, CRect rect)
		{
			if(pCtrl==NULL)
			{
				(pCtrl) = new (CComboBox);
				CComboBox*p=(CComboBox*)(pCtrl);
				p->Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_HSCROLL|WS_HSCROLL|CBS_AUTOHSCROLL |CBS_DROPDOWNLIST,//CBS_SORT|
					rect,
					pwnd,
					nID);
				
				
				::SendMessage(p->m_hWnd,WM_SETFONT,(DWORD)hFont,TRUE);  
				p->Invalidate(TRUE);
				
				chX;
				int n = 0;
				int idx = 0;
				
				//[4,1,continue,Trigger,TriggerLevel,TriggerEdge]
				
				char *pc=chX;
				
				pc++;
				
				int nn=0;
				char w[100];
				int nw=0;
				int dn=0;
				while((*pc!=']')){
					if(*pc==','){
						dn++;
						w[nw]='\0';
						if(dn==1){
							sscanf(w,"%d",&n);   // Item Num
							nw=0;
						}
						else if(dn==2){
							sscanf(w,"%d",&idx); // Item Idx
							nw=0;
						}
						else{
							p->AddString(w);
							nw=0;
						}
					}
					else{
						w[nw]=*pc;
						nw++;
					}
					pc++;
					
				}
				w[nw]='\0';
				p->AddString(w);
				p->SetCurSel(idx);
			}
			
			
		}
		
		void CreateCheckButtonCtrl(CMyPrpDlg *pwnd, CRect rect)
		{
			if(pCtrl==NULL)
			{
				(pCtrl) = new (CButton);
				CButton*p=(CButton*)(pCtrl);
				p->Create("",WS_CHILD|BS_AUTOCHECKBOX|BS_CHECKBOX|WS_VISIBLE,
					rect,
					pwnd,
					nID);
				
				::SendMessage(p->m_hWnd,WM_SETFONT,(DWORD)hFont,TRUE);  
				p->Invalidate(TRUE);
				
				if(strcmp(ch,"�ڵ�ƽ����") == 0)
				{
					pwnd->CheckDlgButton(nID,1);
					TRACE("CAllCtrl::CreateCheckButtonCtrl CheckDlgButton");
				}
				
			}
			
		}
		
		void CAllCtrl::CreateButtonCtrl(CMyPrpDlg *pwnd, CRect rect)
		{
			if(pCtrl==NULL)
			{
				(pCtrl) = new (CButton);
				CButton*p=(CButton*)(pCtrl);
				p->Create(ch,BS_DEFPUSHBUTTON|WS_VISIBLE|WS_CHILD,
					rect,
					pwnd,
					nID);
				//CFont *font=pwnd->GetFont();//��ȡ�Ի�������
				//p->SetFont(font);//���ÿؼ�����
				
				::SendMessage(p->m_hWnd,WM_SETFONT,(DWORD)hFont,TRUE);  
				p->Invalidate(TRUE);
				
				if (strcmp(ch,"����") == 0)
				{
					p->EnableWindow(0);
				}
			}
			
		} 
		
		void CreateEditCtrl(CMyPrpDlg *pwnd, CRect rect)
		{
			int nMin,nMax,nCur;
			sscanf(chX,"[%d,%d,%d] ",&nMin,&nMax,&nCur);
			if(pCtrl==NULL)
			{
				(pCtrl) = new (CEdit);
				CEdit*p=(CEdit*)(pCtrl);
				p->CreateEx(WS_EX_CLIENTEDGE, 
					_T("EDIT"), 
					NULL,
					ES_AUTOHSCROLL|
					ES_LEFT|ES_NOHIDESEL|
					WS_CHILD,
					rect, pwnd,
					nID);
				
				p->SetFocus();
				p->ShowWindow(SW_SHOW);
				
				::SendMessage(p->m_hWnd,WM_SETFONT,(DWORD)hFont,TRUE);  
				p->Invalidate(TRUE);
				
				CString strCur;
				strCur.Format("%d",nCur);
				p->SetWindowText(strCur);
			}
		}
		
		void CreateStaticCtrl(CMyPrpDlg *pwnd, CRect rect)
		{			
			if(pCtrl==NULL)
			{
				(pCtrl) = new (CStatic);
				CStatic*p=(CStatic*)(pCtrl);
				p->Create(ch,WS_VISIBLE|WS_GROUP,
					rect,
					pwnd,
					nID
					);
				p->ShowWindow(SW_SHOW);
				p->SetFocus();
				
				::SendMessage(p->m_hWnd,WM_SETFONT,(DWORD)hFont,TRUE);  
				p->Invalidate(TRUE);
				
			}
		}
		
		void CAllCtrl::CreateSliderCtrl(CMyPrpDlg *pwnd, CRect rect)
		{
			int nMin,nMax,nCur,nLineSize;//�����ؼ�����: �ɵ���Χ, ��ǰֵ, ����
			sscanf(chX,"[%d,%d,%d,%d] ",&nMin,&nMax,&nCur,&nLineSize);
			if(pCtrl==NULL)
			{
				(pCtrl) = new (CSliderCtrl);
				CSliderCtrl*p=(CSliderCtrl*)(pCtrl);
				
				
				p->Create( TBS_HORZ|TBS_TOP|TBS_BOTTOM|TBS_NOTICKS,
					rect,
					pwnd,
					nID
					);
				p->ShowWindow(SW_SHOW);
				p->SetFocus();
				p->SetRange(nMin,nMax);
				p->SetLineSize(nLineSize);//���ò���
				p->SetPos(nCur);
				if (strcmp(ch,"�����ٶ�") == 0)
				{
					//					pwnd->m_nShutterSpeed=nCur;
					//					TRACE("CAllCtrl::CreateSliderCtrl m_nShutterSpeed=%d",pwnd->m_nShutterSpeed);
				}
				
				::SendMessage(p->m_hWnd,WM_SETFONT,(DWORD)hFont,TRUE);  
				p->Invalidate(TRUE);
			}
		}
		
		
		
		
		
		void CreateMe(CMyPrpDlg* pwnd)
		{ 	
			CRect rect;
			rect=CRect(x,y,x+w,y+h);
			switch(nType) {
			case 1://Slider�ؼ�
				CreateSliderCtrl(pwnd,rect);
				break;
			case 2://Static�ؼ�
				CreateStaticCtrl(pwnd,rect);
				break;
			case 3://edit�ؼ�
				CreateEditCtrl(pwnd,rect);
				break;
			case 4://CButton�ؼ�
				CreateButtonCtrl(pwnd,rect);
				break;
			case 5://check Button�ؼ�
				CreateCheckButtonCtrl(pwnd,rect);
				break;
			case 6://CComboBox�ؼ�
				CreateComboBoxCtrl(pwnd,rect);
				break;
			case 7://Group�ؼ�
				CreateGroupButtonCtrl(pwnd,rect);
				break;
			default:
				break;
			}
			
		}
		
		
		CAllCtrl(){			
			pCtrl = NULL;			
			hFont   =   CreateFont(12,   0,   0,   0,   400,  
				0,   0,   0,   ANSI_CHARSET,   
				OUT_DEFAULT_PRECIS,   CLIP_DEFAULT_PRECIS,  
				DEFAULT_QUALITY,   
				DEFAULT_PITCH   ||   FF_DONTCARE,   "����"); 
		};
		virtual ~CAllCtrl(){};
		
		int nType,x,y,w,h,nID;//�ؼ����͡����ꡢID
		
		char ch[100];//��;
		void *pCtrl; //�ؼ����
		char chX[100];//�ؼ����Ե�һЩ����
		
		HFONT hFont;//�ؼ�������
		
	};
	// Construction
public:
	CMyPrpDlg(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CMyPrpDlg)
	enum { IDD = IDD_DLG_PRP };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPrpDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CMyPrpDlg)
	// NOTE: the ClassWizard will add member functions here
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP() 
public:
	~CMyPrpDlg(){
		pvDestroyAllCtrl();
	}
	void plSetParam(HWND h)
	{
		m_hWnd = h;
	}
private:
	
    int			m_nCtl;   //�ؼ�����	
    CAllCtrl    *m_pAllCtrl[100]; 
	HWND		m_hWnd; 

	void pvCreateAllCtrl();
	void pvDestroyAllCtrl();
	
	int prUpdateFriend(CAllCtrl *pCt, int nPos)
	{
		if (pCt==NULL)
			return 0;
		
		int k;
		int nId;
		CString str;
		int OldV;
		for (k=0;k<100;k++)
		{
			if (m_pAllCtrl[k]!=NULL)
			{
				if ((strcmp(m_pAllCtrl[k]->ch, pCt->ch) == 0)&&m_pAllCtrl[k]->nType==3&&m_pAllCtrl[k]!=pCt)
				{
					nId=m_pAllCtrl[k]->nID;
					CEdit *pEd = (CEdit *)GetDlgItem(nId);
					pEd->GetWindowText(str);
					sscanf(str.GetBuffer(str.GetLength()),"%d",&OldV);
					
					if(OldV!=nPos){
						str.Format(" %d", nPos);
						pEd->SetWindowText(str);
						//HVAGCControl(m_hhvCam,AGC_GAIN,nPos);
					}
					
				}
				else if ((strcmp(m_pAllCtrl[k]->ch, pCt->ch) == 0)&&m_pAllCtrl[k]->nType==1&&m_pAllCtrl[k]!=pCt)
				{	
					nId=m_pAllCtrl[k]->nID;
					CSliderCtrl *pSlider = (CSliderCtrl *)GetDlgItem(nId);
					OldV = pSlider->GetPos();
					if(OldV!=nPos){
						pSlider->SetPos(nPos);
						//HVAGCControl(m_hhvCam,AGC_GAIN,nPos);
					}
					
					str.Format("asdf %d", nPos);
					TRACE(str);
				}
				
			}
		}
		
		return nId;
		
	}
	
	void prOnHScroll(int nCurID)
	{
		int k;
		for (k=0;k<100;k++)
		{
			if (m_pAllCtrl[k]!=NULL)
			{
				int nid=m_pAllCtrl[k]->nID;
				CSliderCtrl *pSlider=(CSliderCtrl*)GetDlgItem(nid);
				if (nid==nCurID)
				{
					int nPos=pSlider->GetPos(); 
					TRACE("============================================%d",k);
					if (strcmp(m_pAllCtrl[k]->ch, "SleepTime") == 0)
					{
						TRACE("HVCommand(SetGain,%d)",nPos);
						//						HVAGCControl(m_hhvCam,AGC_GAIN,nPos);
						TRACE("m_hWnd=0x%x\n",m_hWnd);
						::SendMessage(m_hWnd,BL_WM_B1_PRP_1,nid,nPos);
						prUpdateFriend(m_pAllCtrl[k],nPos);
						
					}
					else if (strcmp(m_pAllCtrl[k]->ch, "��ͨ��") == 0)
					{
						TRACE("HVCommand(SetRedGain,%d)",nPos);
						//						HVAGCControl(m_hhvCam,AGC_GAIN_RED_CHANNEL,nPos);
						prUpdateFriend(m_pAllCtrl[k],nPos);
					}
					else if (strcmp(m_pAllCtrl[k]->ch, "��ͨ��") == 0)
					{
						TRACE("HVCommand(SetBlueGain)",nPos);
						//						HVAGCControl(m_hhvCam,AGC_GAIN_BLUE_CHANNEL,nPos);
						prUpdateFriend(m_pAllCtrl[k],nPos);
					}
					
					else if (strcmp(m_pAllCtrl[k]->ch, "���ȵ���") == 0)
					{
						TRACE("HVADCControl(SetBrightness)",nPos);
						////						HVADCControl(m_hhvCam,ADC_BRIGHTNESS,nPos);
						prUpdateFriend(m_pAllCtrl[k],nPos);
					}
					else if (strcmp(m_pAllCtrl[k]->ch, "�ӳ�ʱ��") == 0)
					{
						
					}
					else if (strcmp(m_pAllCtrl[k]->ch, "��������") == 0)
					{ 
					}
					else if (strcmp(m_pAllCtrl[k]->ch, "�ڵ�ƽ����") == 0)
					{
						TRACE("HVADCControl(SetBlackLevel)",nPos);
						prUpdateFriend(m_pAllCtrl[k],nPos);
					}
				} 
			}
		}	
		
	}
	void pvDefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{ 
		switch(message){
			
		case WM_HSCROLL:
			{
				long id = GetWindowLong ((HWND) lParam, GWL_ID) ; 
				prOnHScroll(id); 
			}
			break;
		case WM_COMMAND: 
			
			break;
		case WM_MOUSEACTIVATE:
			
			break;
		}
		
		
	}
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPRPDLG_H__98B05DEC_15E0_46F9_97B9_DDB5F02ECFE6__INCLUDED_)
