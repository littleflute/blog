 BlXAU.dll
 depends:	MFC	
			BlAPI.h  

../../Bin/Chk/MfcDlgMain.exe
../../Bin/Chk/BlW32Main.exe
../../Bin/Chk/B1/BlXAU.dll 
 

--2017.05.03 12:46pm bjt --HYL-2149 Alfred,STL,MO. USA--  
1. V0096
	
	2Do: 
		v_GetLowMin

--2016.07.07 Thu  04:27 bj --HYL-2149 Alfred,STL,MO. USA--  
1. BlXAU.dll (V0086) #define MY_VERSION		"V:0086"   
	void CMyView::pvDrawKlines(HDC hdc,int w,int h)
 	pvCreate(pv2CreateBmpDataFun,p);
	pvCreate(pvGetJSONFun,p); 

--2016.07.06 Wed  10:12 bj --HYL-2149 Alfred,STL,MO. USA--  
1. BlXAU.dll (V0076) #define MY_VERSION		"V:0076"   
 
	void CMyView::pvGetOHLCFromJSONTxt(CString strJSONTxt)

--2016.06.21 Tue  11:14 bj --HYL-2149 Alfred,STL,MO. USA--  
1. BlXAU.dll (V0056) 
	CString strXAU = pvUpdateXAU(fSell);

--2016.04.23 sat  00:12bj--HYL-2149 Alfred,STL,MO. USA--  
1. BlXAU.dll (V0046)  void CMyThread::plUpdateXAU()
	1) ��ȡ�׶ؽ����߷�ʱ����
	http://api.baidao.com/api/hq/mtdata.do?quotationType=201&id=201&JSONP=?&ran=

	 http://api.baidao.com/api/hq/npdata.do?ids=201	(XAU �׶ؽ�)
	 http://api.baidao.com/api/hq/npdata.do?ids=202	(XAG �׶���)
	 http://api.baidao.com/api/hq/npdata.do?ids=203	(XPD �׶��ٽ�)
	 http://api.baidao.com/api/hq/npdata.do?ids=204	(XAP �׶ز���)
	 http://api.baidao.com/api/hq/npdata.do?ids=301	(USD	��Ԫָ��) 
	 http://api.baidao.com/api/hq/npdata.do?ids=302	(CONC	��Ԫָ��) 
	 301	USD 
	 http://api.baidao.com/api/hq/npdata.do?ids=1   �ֻ�����
	 http://api.baidao.com/api/hq/npdata.do?ids=5	�ֻ��ٽ�
	 http://api.baidao.com/api/hq/npdata.do?ids=6	�ֻ�����
	 http://api.baidao.com/api/hq/npdata.do?ids=7	�ֻ���
	 http://api.baidao.com/api/hq/npdata.do?ids=8	�ֻ�ͭ
	 http://api.baidao.com/api/hq/npdata.do?ids=9	�ֻ���
	  4001	LMCI
	  4002	LMAI
	  4003	LMNI
	  4004	LMPI
	  4005	LMZI
	  4006	LMAC
	  4007	LMSI


--2016.04.22 Fri  23:41bj--HYL-2146 Alfred,STL,MO. USA--  
1. BlXAU.dll (V0036*) 
	1)M: ����Դ �����ļ� Data/HXCUA_60M.txt

--2016.04.21 Thu 03:42bj--HYL-2146 Alfred,STL,MO. USA--  
1. BlXAU.dll (V0026*) 
	4)A: void pvDrawKlines(HDC hdc)
	3)A: class CXdKLine  
	2)A: ����Դ �����ļ� Data/data2a.txt
	1)M: class CMyView

--2016.04.20 Wed 11:08bj--HYL-2146 Alfred,STL,MO. USA--  
1. A: Create Prj BlXAU.dll (V0016)