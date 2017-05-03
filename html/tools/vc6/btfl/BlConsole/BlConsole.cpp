// BlConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" 

class CMyDll
{
public:
	CMyDll(){}
	~CMyDll(){}
	void plPrintConsoleVersion()
	{ 
		pvMyVersion();
	}
	BLSTATUS OnBlCallLibFun()
	{
		BLSTATUS r = prCallLibFun();
		return r;
	}
	void OnPrint(BLSTATUS s)
	{
		switch(s)
		{
		case BL_STATUS_OK:
			printf("BL_STATUS_OK \n");
			break;
		case BL_STATUS_NOT_SUPPORT_INTERFACE:
			printf("BL_STATUS_NOT_SUPPORT_INTERFACE \n");
			break;
		case BL_STATUS_NOT_FOUND_LIBARY:
			printf("BL_STATUS_NOT_FOUND_LIBARY \n");
			break;
		default:
			printf("BLSTATUS: 0x%x(%d) \n",s,s);
			break;
		}
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
				sprintf(sz,"BlConsole.exe");
				BL_LPARAM_CONTEXT c = {0};
				c.m					= BL_WM_INIT; 
				sprintf(c.szVerify,"BEAUTIFULLOVER");
				c.pszExtra			= sz; 
				
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
		r = pvCallLibFun("BlMfcUI.dll","OnBlApi");
		return r;

	} 
	void pvMyVersion()
		{ 
			char szFilePath[256]; 
			memset(szFilePath,0,256); 
			::GetModuleFileName(NULL,szFilePath,256);
		//	PathRemoveFileSpec(szFilePath);  
			char szV[256];
			xdGetModuleVersion(szFilePath,szV);
			printf("BlConsole.exe[%s]\n",szV);
			 
		}
	void xdGetModuleVersion(IN char *szFullPath,OUT char *szV)
	{ 
		DWORD dwVerInfoSize = 0;
		DWORD dwVerHnd;
		VS_FIXEDFILEINFO * pFileInfo;
		
		//	GetModuleFileName(NULL, szFullPath, sizeof(szFullPath));
		dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
		if (dwVerInfoSize)
		{
			// If we were able to get the information, process it:
			HANDLE  hMem;
			LPVOID  lpvMem;
			unsigned int uInfoSize = 0;
			
			hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
			lpvMem = GlobalLock(hMem);
			GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpvMem);
			
			::VerQueryValue(lpvMem, (LPTSTR)_T("\\"), (void**)&pFileInfo, &uInfoSize);
			
			WORD m_nProdVersion[4];
			
			// Product version from the FILEVERSION of the version info resource 
			m_nProdVersion[0] = HIWORD(pFileInfo->dwProductVersionMS); 
			m_nProdVersion[1] = LOWORD(pFileInfo->dwProductVersionMS);
			m_nProdVersion[2] = HIWORD(pFileInfo->dwProductVersionLS);
			m_nProdVersion[3] = LOWORD(pFileInfo->dwProductVersionLS); 
			
			//*
			sprintf(szV,_T("%d.%d.%d.%d"),m_nProdVersion[0],
				m_nProdVersion[1],m_nProdVersion[2],m_nProdVersion[3]);
			//*/
			
			GlobalUnlock(hMem);
			GlobalFree(hMem);
			
			
		}
	}
};
int main(int argc, char* argv[])
{
	
	CMyDll d;
	d.plPrintConsoleVersion();
	BLSTATUS r = d.OnBlCallLibFun(); 
	d.OnPrint(r);
	return 0;
}
