 
 BlMfcUI.dll
 depends:	MFC	
			BlAPI.h 

../../Bin/Chk/BlW32Main.exe
../../Bin/Chk/BlMfcUI.dll
 
��һ�� [V0.2] ����
1)enhancement:  FPS ��Ȼ����ֱ�ۣ������Sleep time �� 1ms �䵽 15000ms FPS��Ӧ̫��
2)enhancement: ͼ����ʾ��ʽҪ���
    ���ܳ��������ĳ������� Sleep time = 15000msʱ��ͼ��View���Ǻ���¶��ʱӦ�úͱ���ǰһ��(���ڲ�һ��)��
 

--2016.04.15 Fri 08:02bj--HYL-2149 Alfred,STL,MO. USA--  
5. BlMfcUI.dll V0326  debug: Mouse ���δ��Ӧ,�²�δʵ��

4. BlMfcUI.dll V0316  debug: ��ʼ��Ҫ��ʾ���̡�
						BL_WM_INIT 
						//	m_StaticClient.SetWindowText(szText);

3. BlMfcUI.dll V0306  debug: ���ҷֽ��߹��ָܻ�
						M: void CMyMsg::pvLBtnDown(HWND h,UINT m, WPARAM w, LPARAM l)
2. BlMfcUI.dll V0296  debug: �ڴ治��
						M: void pvMouseMove(int x,int y) 

1. BlMfcUI.dll V0286  debug: �����˳�ʱ��ȷ���ȴ��²��߳����˳�
						A: case WM_CLOSE:

	

--2016.04.13 Wed  00:07bj--HYL-2149 Alfred,STL,MO. USA-- 
3. BlMfcUI.dll V0276    BL_ID_B1_MNG (����Bug: ���ҷֽ���ʧЧ��)
2. BlMfcUI.dll V0266  BlApi.h( V0.1.3.6 )
1. BlMfcUI.dll V0256  B1������������Ӧ WM_LBUTTONDOW
				 M: void pvLBtnDown(HWND h,UINT m, WPARAM w, LPARAM l)
				 A: BOOL CMyStatic::plIsHitMe(int x, int y)
				 A: void CMyStatic::plGetImgXY(int x, int y, int &x1, int &y1)
 

--2016.04.09 Sat 02:14bj--HYL-2149 Alfred,STL,MO. USA-- 
1. BlMfcUI.dll V0226  
BOOL CDlgMain::PreTranslateMessage(MSG* pMsg) 
{ 
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
	case WM_KEYUP: 
	case WM_DEADCHAR:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	case WM_SYSCHAR:
	case WM_SYSDEADCHAR:
	case WM_CHAR:
		pMsg->hwnd = m_hWnd;
		return FALSE;
	} 
	return CDialog::PreTranslateMessage(pMsg);
}

--2016.04.07 Thu 12:11bj--HYL-2149 Alfred,STL,MO. USA-- 
1. V0216 Sleep(1);

--2016.04.06 Wed 04:33bj--HYL-2149 Alfred,STL,MO. USA-- 
1. ���棺V0206  

--2016.04.05 Tue 00:30bj--HYL-2149 Alfred,STL,MO. USA-- 
3. V0122 
2. V0121 WM_KEYDOWN
1. V0120 BlMusic.dll ID_TOOL_BTN_1 ������ǰ��������Ե��ڽ���
	A: void pt2Cmd(WPARAM w, LPARAM l)

--2016.04.04 Mon 23:31bj--HYL-2149 Alfred,STL,MO. USA-- 
1. V0119 BlMfcUI.dll  WM_CHAR

--2016.04.04 Mon 17:23bj--Jiapeng---China--
2.V: ->V0118
1.Fixed the FPS issue.
  Unit test: The fps will be 1.0 if call Sleep(1000) in the BlMusic.dll and it wil be 0.5 if call Sleep(2000).


--2016.04.04 Mon 14:05bj--HYL-2149 Alfred,STL,MO. USA-- 
1. V0117 BlMfcUI.dll up to // File: BlApi.h( V0.1.0.3 )

--2016.04.04 Mon 09:08bj--Jiapeng---China--
4. V: ->V0116
3. Displaying the FPS on status bar.
   A:ShowFPS()
2. Fixed the position for ToolBar.
   A:#define TOP 30

1. Fixed the memory leak issue when moving mouse to show RGB value.
   C:CMyStatic::MyGetPixel, adding "delete[]pBuffer";

--2016.04.03 Sun 22:24bj--HYL-2149 Alfred,STL,MO. USA-- 
2.  V0116 ����˵���� 
	3) Show FPS(֡��) at status bar.
	2) Need to fix the position of ToolBar.
    1)Bug Fix#: 
	    Still a Memory leak: 
		See it at Windows Task Manager when Mouse move to show RGB Value.


1. V: 0115 (OnBlApi r = BL_STATUS_OK;)
		A: CMyToolBar				m_MyToolBar;
		Bug Fix# Memory leak at : 
		  1)void ptShowBmp(HDC hDC,BYTE* pByte,int n, LPRECT pRect)
		  2)CMyStatic():m_hMyB(NULL)
		 

--2016.04.03 Thu 14:00bj--Jiapeng---China-- 
2.ʵ������V0114(1,2,4), ������3,"������ͼ�Ϸ���һ����������ͼ"����V0115ʵ��
1.C:
pParent->m_StaticClient.GetIMGPos(x,y,x1,y1);
//���²�ӿڴ���ͼ������(x1,y1)
DWORD dwV=x1;
dwV = dwV | (y1<<16);
pParent->m_MyDll.OnBlCallLibFun(pParent->m_hWnd,m,w,dwV);

--2016.04.03 Thu 01:13bj--Jiapeng---China-- 

2. ʵ������V0114
1. Add: CMyStatic::MyGetPixel

--2016.04.02 Sat 05:50bj--HYL-2149 Alfred,STL,MO. USA-- 
2. V0114 ����˵���� 
    1)status bar ��ʾ���������Ϊ��ʾ�²㴫������ͼ������ꡣ 
	2)status bar ������ʾͼ�����꣬�ټ���ʾ����㴦��RGBֵ��
	3)������ͼ�Ϸ���һ����������ͼ��
	4)�������ҷֽ���ʱ����Ҫ��ͼ����˸��

1. V0113 BlMfcUI.dll��������
		(�²����Ӧ�������Ϣ)

--2016.04.01 Thu 18:33bj--Jiapeng---China-- 
Update for requirement V0112


--2016.03.31 Thu 22:53bj--HYL-2149 Alfred,STL,MO. USA-- 
2. V0112 ����˵���� 
    1)�޸�BUG: V0111 �豸�б��������
	2)�޸�BUG: ���ڷֽ��ߵ������,��ͼ��ͼ��ͼ����������ͼ��

1. V0111 BlMfcUI.dll��������
	(��ʾ�²㴫����ͼ������,���Զ��崰����Ϣ�ķ�ʽ)


--2016.03.31 Thu 13:50bj--Jiapeng-2149 Alfred,STL,MO. China--
ʵ������V0110.
ע���豸�б��е����ִ��²�ӿڿ�B1Mng.dll�е�WPARAM w��ȡ.(�ο���ͼ��ͼ��LPARAM l)
    �Ƿ�Ӧ����ƽṹ������ȡ����???


--2016.03.30 Thu 22:17bj--HYL-2149 Alfred,STL,MO. USA-- 
2. V0110 ����˵���� 
    1)"��ͼ��ͼ��\n ���м���ڷֽ��ߵ�������ٵ��ڻ��м䣬��ʾ���ݲ�Ӧ�ñ仯";
 	2)"�豸�б�\n ���м���ڷֽ��ߵ����ұ��ٵ��ڻ��м䣬��ʾ���ݲ�Ӧ�ñ仯";
	3) �ܹ����: �� [�豸�б�]������������ �²� B1Mng.dll ����(��[��ͼ��ͼ]����������)

	*ע���Ѿ����� BlAPI.h (V0102) & BlW32Main.exe(V0104)
	     �ܹ���������²����һ���µ� B1Mng.dll��

1. V: 0.1.0.9 


--2016.03.30 Wed 01:20bj--Jiapeng-2149 Alfred,STL,MO. China--
Ϊ��ף�й�����Ӽ��ѽ���12ǿ����������˯��ʵ������V0108 
V0108 ����˵���� 
1�������ʼ��ʱ����ͼ��ͼ&�豸�б���ͼ���Զ����ݴ��ڴ�С�����������ڣ����Ҳ��У���һ��ֱ�߽� 
2��Mouse�Ƶ���ֱ�߽��ͬʱ�������Ҵ��ڴ�С������V0107�����ĵ������ڣ�

--2016.03.29 Tue 17:50bj--Jiapeng-2149 Alfred,STL,MO. China-- 

V0107 ����˵���� 
1����ͼ��ͼ�߶ȹ̶�ס���Զ����洰�ڴ�С�仯��ֻ���ұ߽�ɵ����±߽粻�ɵ��� 
2���豸�б���ͼ�ұ߽粻�ɶ����̶��ڴ����ұߣ�ֻ����߽�ɵ�ͼ��ȣ� 
3��status bar: [column 1] show correct version number when update version, [column 2] show correct time(the time is running correct).


--2016.03.28 Mon 18:00bj--Jiapeng-2149 Alfred,STL,MO. China-- 
1. Finished the requirement V0106.
2. V: 0.1.0.6.

--2016.03.28 Mon 00:46bj--HYL-2149 Alfred,STL,MO. USA-- 
1. V0106 ����˵����
	1����ͼ��ͼ��ȿɵ�����Mouse�Ƶ��ұ߽�ʱ,Cursor Changed��
	2��when mouse moving in drawing view, show x,y position at status bar.

--2016.03.26 Sat 08:38bj--HYL-2149 Alfred,STL,MO. USA-- 
3. V: 0.1.0.1
2. F: extern "C" BLSTATUS __stdcall OnBlApi()
1. A: Create Prj 