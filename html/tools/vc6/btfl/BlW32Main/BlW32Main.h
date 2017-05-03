//File BlW32Main.h
//------------------------------------------------

#if !defined(_BEAUTIFULLOVER_W32_MAIN_)
#define _BEAUTIFULLOVER_W32_MAIN_

#include "stdio.h"
#include "../common/inc/BlAPI.h"  
//#include "../common/inc/BlClass.h"  

#define    	MY_VERSION		"V:0136" 

#include <io.h>
#include <fcntl.h>
class CBlConsole
{
public:
	void CBlConsole::InitConsole()
	{
		int hCrt; 
		FILE *hf; 
		AllocConsole(); 
		hCrt = _open_osfhandle( 
			(long)GetStdHandle(STD_OUTPUT_HANDLE), 
			_O_TEXT ); 
		hf = _fdopen( hCrt, "w" ); 
		*stdout = *hf; 
		setvbuf( stdout, NULL, _IONBF, 0 ); 
		printf("InitConsoleWindow OK!\n\n"); 
	}
}; 
class CMyDll
{
public:
	CMyDll(){}
	~CMyDll(){}
	BLSTATUS OnBlCallLibFun()
	{
		BLSTATUS r = prCallLibFun();
		return r;
	}
private:
	BLSTATUS pvCallLibFun(char *szLib,char *szFun)
	{
		BLSTATUS r = BL_STATUS_NOT_SUPPORT_INTERFACE;
		HMODULE h = LoadLibrary(szLib);
		
		if(NULL != h)
		{
			FARPROC pFunc = GetProcAddress(h, szFun);
			if (pFunc ) 
			{
				char sz[155];
				sprintf(sz,"BlW32Main %s",MY_VERSION);
				BL_LPARAM_CONTEXT c = {0};
				c.m					= BL_WM_INIT; 
				sprintf(c.szVerify,"BEAUTIFULLOVER");
				c.pszExtra = sz;
				r = (* (OnBLAPI *)pFunc)(NULL,BL_WM_INIT,0,(LPARAM)&c);  
				FreeLibrary (h);
			}
		}
		else
		{
			r = BL_STATUS_NOT_FOUND_LIBARY;
		}
		return r;
	}
	BLSTATUS prCallLibFun()
	{
		BLSTATUS r = BL_STATUS_NOT_SUPPORT_INTERFACE;
		printf(" load BlMfcUI.dll r=0x%x\n",r);
		r = pvCallLibFun("BlMfcUI.dll","OnBlApi");
		return r;
	} 
};
//================================================
#endif // _BEAUTIFULLOVER_W32_MAIN_