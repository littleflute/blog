 
 B1Mng.dll
 depends:	MFC	
			BlAPI.h 

../../Bin/Chk/BlW32Main.exe
../../Bin/Chk/B1Mng.dll 

下一版(V:034x)需求：
1)插件目录可设置
2)Mouse 点在枚举列表外不做非选择动作


--2017.05.03 11:54 bjt--HYL-2149 Alfred,STL,MO. USA-- 
4. B1Mng.dll V:0346   
	//		std::vector<CB1Dll *>				m_VectorSet,&xdv;
	//		std::vector<CB1Dll *>::iterator		vi;
		CB1Dll	*							m_pDlls[100];
		int									m_nDlls;


--2016.04.15 Fri 08:02bj--HYL-2149 Alfred,STL,MO. USA-- 
4. B1Mng.dll V:0336   

3. B1Mng.dll V:0316  M: void CB1Dll::pv2DoInCB(BYTE *p)  
2. B1Mng.dll V:0306  debug: 程序退出时，确保等待下层线程先退出
						A: SetEvent(pL->GetMyThread()->m_hDisplayOver);
1. B1Mng.dll V:0296  debug: 程序退出时，确保等待下层线程先退出
						A: case WM_CLOSE:
	

--2016.04.13 Wed 00:00bj--HYL-2149 Alfred,STL,MO. USA--  
2. B1Mng.dll V:0286  M：通过 callback 方式从下层取图
					A: BLSTATUS pl2Init(HWND h,UINT m, WPARAM w, LPARAM l)
					A: void pv2DoInCB(BYTE *p)

1. B1Mng.dll V0266	点击显示选择插件 （有bug: 有时点击会死，待解决）
					A: BL_ID_B1_MNG

--2016.04.12 Tue 06:16bj--HYL-2149 Alfred,STL,MO. USA-- 
1. B1Mng.dll V0256 ->枚举[B1]DLLs   
					A: pL->plShowDlls(l);
			 		   plSelectDll(2);
					A: class CB1DllMng
					M: CMyDll -> CB1Dll

--2016.04.10 Sun 06:16bj--HYL-2149 Alfred,STL,MO. USA-- 
1. B1Mng.dll V0236 

--2016.04.09 Sat 02:16bj--HYL-2149 Alfred,STL,MO. USA-- 
1. B1Mng.dll V0216 
			case WM_KEYUP: 
			case WM_DEADCHAR:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			case WM_SYSCHAR:
			case WM_SYSDEADCHAR: 
			case WM_CHAR:

--2016.04.06 Wed 04:29bj--HYL-2149 Alfred,STL,MO. USA-- 
1. 定版：V0206 

--2016.04.05 Tue 00:06bj--HYL-2149 Alfred,STL,MO. USA-- 
3. v0136 B1Mng.dll	A: BL_WM_B1_PRP_1
2. V0112 B1Mng.dll  A: BL_WM_CMD_B0_2_B1_01
1. V0111 B1Mng.dll //	if (rc.PtInRect(pt))

--2016.04.04 Mon 12:07bj--HYL-2149 Alfred,STL,MO. USA-- 
5. V0110 B1Mng.dll	Sleep(10);
4. V0109 B1Mng.dll	*注：已经升级 BlAPI.h (V0103)
3. V0108 B1Mng.dll	m_pLib->GetDll()->OnBlCallLibFun(h,m,w,l); //WM_CHAR
2. V0107 B1Mng.dll m_pLib->GetDll()->OnBlCallLibFun(h,m,w,l); //WM_LBUTTONDOWN
1. V0106 B1Mng.dll（调用下层BlMusic.dll传图）

--2016.04.03 Sun 11:50bj--Jiapeng---China-- 
实现需求：V0105
注: 接收上层的 WM_LBUTTONDOWN 消息时,从LPARAM l解析出的是图像坐标(x1,y1),
    这就表示上层传递的是图像坐标而非设备坐标

--2016.04.02 Sat 05:22bj--HYL-2149 Alfred,STL,MO. USA-- 
2. V0105 升级需求：//点红框时，弹出消息框

			case WM_LBUTTONDOWN:
				{ 
					//点红框时，弹出消息框
				//	::MessageBox(h,"lbtn","test",IDOK);
				}
				break;

1. V: 0.1.0.4 B1Mng.dll 例行升级
		（响应上层窗口消息）

--2016.03.31 Thu 23:04bj--HYL-2149 Alfred,STL,MO. USA-- 
1. V: 0.1.0.3 B1Mng.dll 例行升级
 
--2016.03.31 Thu 19:30bj--Jiapeng-2149 Alfred,STL,MO. China-- 
V: 0.1.0.2

--2016.03.30 Wed 21:58bj--HYL-2149 Alfred,STL,MO. USA-- 
3. V: 0.1.0.1
2. F: extern "C" BLSTATUS __stdcall OnBlApi()
1. A: Create Prj 