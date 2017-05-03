// File: BlApi.h( V0.1.5.6 )
/*

--2016.04.13 Wed 02:23 bj--HYL-2149 Alfred,STL,MO. USA-- 
2. B1Api.h (V0.1.4.6)
		A: typedef int (CALLBACK* BL_CBP_PROC)(BL_CB_INF *pInfo);
		A: BL_LPARAM_CONTEXT

1. BlApi.h (V0.1.2.6) 
		M: BL_WM_INIT									= WM_USER+0xB000, 
*/
#if !defined(_BEAUTIFULLOVER_WIN32_DLL_API_)         
#define _BEAUTIFULLOVER_WIN32_DLL_API_

/* By C++ language compiler */
#ifdef __cplusplus
extern "C" {
#endif    
//-------------------------------------------------------------------------

typedef enum tagBLWM{
		BL_WM_INIT									= WM_USER+0xB000, 
		BL_WM_B0_0XB001								= WM_USER+0xB001, 

		BL_WM_B0_0XB100								= WM_USER+0xB100, 
		BL_WM_B1_0XB101								= WM_USER+0xB101, 
		BL_WM_B1_0XB102								= WM_USER+0xB102, 

		BL_WM_CMD_B0_2_B1_01						= WM_USER+0xC001,
		BL_WM_B1_PRP_1								= WM_USER+0xCB01,

}BLWM;
	
typedef enum tagBLSTATUS{
		BL_STATUS_OK								= 0,
		BL_STATUS_NOT_SUPPORT_INTERFACE				= -1,
		BL_STATUS_NOT_FOUND_LIBARY					= -2, 
		BL_STATUS_PARAMETER_INVALID					= -3,
}BLSTATUS;
	

typedef enum tagBLID{
		BL_ID_G_00									= 0xB000,
		BL_ID_G_01									= 0xB001, //BlW32Main.exe
		BL_ID_G_02									= 0xB002, //MfcDlgMain.exe

		BL_ID_G_0A									= 0xB00A, //BlMfcUI.dll
		BL_ID_B1_MNG								= 0xB100, //B1Mng.dll
		BL_ID_B1_01									= 0xB101, //BlMusic.dll
		BL_ID_B1_02									= 0xB102, //
		BL_ID_B1_03									= 0xB103,
		BL_ID_B1_04									= 0xB104,
		BL_ID_B1_05									= 0xB105, 
		BL_ID_B1_ALL								= 0xB1FF, 
}BLID;
	

typedef BLSTATUS (__stdcall	OnBLAPI) (HWND h,UINT m, WPARAM w, LPARAM l);


///  �ص������Ĳ���
typedef struct tagBL_CB_INFO{ 
	void			*pCaller;
	void			*pParam;
}BL_CB_INF;

//////////////////////////////////////////////////////////////////////////
/// �ص�����������, 
typedef int (CALLBACK* BL_CBP_PROC)(BL_CB_INF *pInfo);

typedef struct tagBL_LPARAM_CONTEXT 
{ 
	//----ȷ��ֵ-------------------------------------------------------------------
	char						szVerify[16];	// ֵΪ��Ϊ: "BEAUTIFULLOVER"
	BLWM						m;				// ����ʱ�ٴ�ȷ��WMֵ 
	BLID						idFrom;			// ������ID
	BLID						idTo;			// ��������ID
	char						*pszExtra;			
 
	
	//----[ȷ��ֵ]��ȷ�Ϻ󣬲���ʹ������ֵ----------------------------------------- 
	//--CMD_BEAUTIFULLOVER_0001,2 ����--
	union tag_LPARAM{ 
		LPARAM					l;
		struct{
			DWORD				t1;			//��ʱt1
			DWORD				t2;			//��ʱt2
		}Init;  
		struct{ 
			DWORD				t		:16; //�������� 24-RGB,
			DWORD				l		:16; //���ݴ�С
			BYTE*				p;			 //����ָ��
		}DWxH;                               //2άλͼ����
		struct{
				BL_CBP_PROC		pFun;		//�ص�����
				void			*pParam;    //�ص�����
		}CallBack;

		struct{
			DWORD				t1;			//��ʱt1
			DWORD				t2;			//��ʱt2
		}TMP;  
	}LPARAM; 	
}BL_LPARAM_CONTEXT;

//=====================================================================
	/* extern "C" { */
#ifdef __cplusplus
}
#endif

#endif
