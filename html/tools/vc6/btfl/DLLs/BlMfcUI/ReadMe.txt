 
 BlMfcUI.dll
 depends:	MFC	
			BlAPI.h 

../../Bin/Chk/BlW32Main.exe
../../Bin/Chk/BlMfcUI.dll
 
下一版 [V0.2] 需求：
1)enhancement:  FPS 依然不够直观，例如从Sleep time 从 1ms 变到 15000ms FPS响应太慢
2)enhancement: 图像显示方式要提高
    不能出现这样的场景：当 Sleep time = 15000ms时，图像View被盖后再露出时应该和被盖前一样(现在不一样)。
 

--2016.04.15 Fri 08:02bj--HYL-2149 Alfred,STL,MO. USA--  
5. BlMfcUI.dll V0326  debug: Mouse 点击未响应,下层未实现

4. BlMfcUI.dll V0316  debug: 初始不要显示“烫”
						BL_WM_INIT 
						//	m_StaticClient.SetWindowText(szText);

3. BlMfcUI.dll V0306  debug: 左右分界线功能恢复
						M: void CMyMsg::pvLBtnDown(HWND h,UINT m, WPARAM w, LPARAM l)
2. BlMfcUI.dll V0296  debug: 内存不足
						M: void pvMouseMove(int x,int y) 

1. BlMfcUI.dll V0286  debug: 程序退出时，确保等待下层线程先退出
						A: case WM_CLOSE:

	

--2016.04.13 Wed  00:07bj--HYL-2149 Alfred,STL,MO. USA-- 
3. BlMfcUI.dll V0276    BL_ID_B1_MNG (产生Bug: 左右分界线失效了)
2. BlMfcUI.dll V0266  BlApi.h( V0.1.3.6 )
1. BlMfcUI.dll V0256  B1管理器窗口响应 WM_LBUTTONDOW
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
1. 定版：V0206  

--2016.04.05 Tue 00:30bj--HYL-2149 Alfred,STL,MO. USA-- 
3. V0122 
2. V0121 WM_KEYDOWN
1. V0120 BlMusic.dll ID_TOOL_BTN_1 调出当前插件的属性调节界面
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
2.  V0116 需求说明： 
	3) Show FPS(帧率) at status bar.
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
2.实现需求V0114(1,2,4), 将需求3,"左右视图上方加一个工具条视图"移至V0115实现
1.C:
pParent->m_StaticClient.GetIMGPos(x,y,x1,y1);
//给下层接口传递图像坐标(x1,y1)
DWORD dwV=x1;
dwV = dwV | (y1<<16);
pParent->m_MyDll.OnBlCallLibFun(pParent->m_hWnd,m,w,dwV);

--2016.04.03 Thu 01:13bj--Jiapeng---China-- 

2. 实现需求V0114
1. Add: CMyStatic::MyGetPixel

--2016.04.02 Sat 05:50bj--HYL-2149 Alfred,STL,MO. USA-- 
2. V0114 需求说明： 
    1)status bar 显示的坐标更改为显示下层传上来的图像的坐标。 
	2)status bar 除了显示图像坐标，再加显示坐标点处的RGB值。
	3)左右视图上方加一个工具条视图。
	4)调节左右分界线时，不要让图像闪烁。

1. V0113 BlMfcUI.dll例行升级
		(下层可响应本层的消息)

--2016.04.01 Thu 18:33bj--Jiapeng---China-- 
Update for requirement V0112


--2016.03.31 Thu 22:53bj--HYL-2149 Alfred,STL,MO. USA-- 
2. V0112 需求说明： 
    1)修改BUG: V0111 设备列表出现乱码
	2)修改BUG: 调节分界线到最左边,绘图视图的图超出了左视图。

1. V0111 BlMfcUI.dll例行升级
	(显示下层传来的图像数据,以自定义窗口消息的方式)


--2016.03.31 Thu 13:50bj--Jiapeng-2149 Alfred,STL,MO. China--
实现需求V0110.
注：设备列表中的文字从下层接口库B1Mng.dll中的WPARAM w获取.(参考绘图视图从LPARAM l)
    是否应该设计结构体来获取数据???


--2016.03.30 Thu 22:17bj--HYL-2149 Alfred,STL,MO. USA-- 
2. V0110 需求说明： 
    1)"绘图视图：\n 从中间调节分界线到最左边再调节回中间，显示内容不应该变化";
 	2)"设备列表：\n 从中间调节分界线到最右边再调节回中间，显示内容不应该变化";
	3) 架构设计: 把 [设备列表]的文字内容由 下层 B1Mng.dll 决定(像[绘图视图]所做的那样)

	*注：已经升级 BlAPI.h (V0102) & BlW32Main.exe(V0104)
	     架构设计上在下层加了一个新的 B1Mng.dll。

1. V: 0.1.0.9 


--2016.03.30 Wed 01:20bj--Jiapeng-2149 Alfred,STL,MO. China--
为庆祝中国足球队艰难进军12强，我难以入睡，实现需求V0108 
V0108 需求说明： 
1）程序初始化时，绘图视图&设备列表视图就自动根据窗口大小布满整个窗口，左右并列，有一垂直边界 
2）Mouse移到垂直边界可同时调节左右窗口大小（不是V0107这样的单独调节）

--2016.03.29 Tue 17:50bj--Jiapeng-2149 Alfred,STL,MO. China-- 

V0107 需求说明： 
1）绘图视图高度固定住，自动跟随窗口大小变化（只有右边界可调，下边界不可调） 
2）设备列表视图右边界不可动，固定在窗口右边（只有左边界可调图宽度） 
3）status bar: [column 1] show correct version number when update version, [column 2] show correct time(the time is running correct).


--2016.03.28 Mon 18:00bj--Jiapeng-2149 Alfred,STL,MO. China-- 
1. Finished the requirement V0106.
2. V: 0.1.0.6.

--2016.03.28 Mon 00:46bj--HYL-2149 Alfred,STL,MO. USA-- 
1. V0106 需求说明：
	1）绘图视图宽度可调（当Mouse移到右边界时,Cursor Changed）
	2）when mouse moving in drawing view, show x,y position at status bar.

--2016.03.26 Sat 08:38bj--HYL-2149 Alfred,STL,MO. USA-- 
3. V: 0.1.0.1
2. F: extern "C" BLSTATUS __stdcall OnBlApi()
1. A: Create Prj 