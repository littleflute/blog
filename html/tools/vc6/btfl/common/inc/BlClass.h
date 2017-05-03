// File: BlClass.h( V0.1.0.5 )
/*
class CBlDebug
class CBlThread
class CBlFile 

  
--2016.04.13 Wed 00:00bj--HYL-2149 Alfred,STL,MO. USA-- 
1.  BlClass.h( V0.1.0.5 )	A: void plCheckBlStatus(BLSTATUS s)
*/
#if !defined(_BEAUTIFULLOVER_CLASS_H_)         
#define _BEAUTIFULLOVER_CLASS_H_

/* By C++ language compiler */
#ifdef __cplusplus
extern "C" {
#endif    
//-------------------------------------------------------------------------
#include "mmsystem.h"

#pragma comment(lib,"winmm.lib")

class CBlDebug
{
public:
	CBlDebug(){}
	~CBlDebug(){}
	void plCheckBlStatus(HWND h,BLSTATUS s)
	{
		switch(s)
		{
		case BL_STATUS_OK:
			break;
		case BL_STATUS_NOT_SUPPORT_INTERFACE:
			plMsgBox(h,"BL_STATUS_NOT_SUPPORT_INTERFACE");
			break;
		}
	}
	void plPlaySound(TCHAR *szWavFile)
	{
		PlaySound (szWavFile, NULL, SND_FILENAME | SND_ASYNC) ;
	}
	void plMsgBox(HWND h)
	{
		::MessageBox (h, "BlDebug", "Btfl Debug Msg", 0) ;
	}
	void plMsgBox()
	{
		::MessageBox (NULL, "BlDebug", "Btfl Debug Msg", 0) ;
	}
	
	void plMsgBox(int n)
	{
		plMsgBox("bgDebug","%d",n);
	}
	
	void plMsgBox(HWND h,TCHAR *szMsg)
	{
		::MessageBox (h, szMsg,"BlDebug", 0) ;
	}
	
	void plMsgBox(TCHAR *szMsg)
	{
		::MessageBox (NULL, szMsg,"BlDebug", 0) ;
	}
	
	int CDECL plMsgBox (TCHAR * szCaption, TCHAR * szFormat, ...)
	{
		TCHAR   szBuffer [1024] ;
		va_list pArgList ;
		
		// The va_start macro (defined in STDARG.H) is usually equivalent to:
		// pArgList = (char *) &szFormat + sizeof (szFormat) ;
		
		va_start (pArgList, szFormat) ;
		
		// The last argument to wvsprintf points to the arguments
		
		_vsntprintf (szBuffer, sizeof (szBuffer) / sizeof (TCHAR), 
			szFormat, pArgList) ;
		
		// The va_end macro just zeroes out pArgList for no good reason
		
		va_end (pArgList) ;
		
		return MessageBox (NULL, szBuffer, szCaption, 0) ;
	}
};
class CBlThread
{
public:
	
	//! Default constructor 
	CBlThread()
	{
		m_hThread = NULL;
		m_dwID = 0;
		m_bSuspended = false;
	}
	
	//! destructor
	virtual ~CBlThread() 
	{ 
		Release(1000); 
	}
	//! Get the thread's ID
	operator DWORD()
	{
		return m_dwID;
	}
protected:
	//! Creates a thread
	BOOL pvCreate(
		LPTHREAD_START_ROUTINE pProcess,        //!< Thread function
		LPVOID pParam=NULL,                     //!< Parameter handed over to the thread function
		int Priority=THREAD_PRIORITY_NORMAL,    //!< The thread's priority
		DWORD CreationFlags = 0                 //!< Flags controlling the thread's creation
		)
	{
		ASSERT(pProcess);
		m_hThread = ::CreateThread(NULL, 0, pProcess, pParam, CreationFlags, &m_dwID);
		TRACE("CThread.Create(). Handle = %x, ID = %x\n", m_hThread, m_dwID);
		m_bSuspended = CreationFlags && CREATE_SUSPENDED;
		if( m_hThread==NULL ) 
			return FALSE;
		if( !::SetThreadPriority(m_hThread, Priority) ) {
			::CloseHandle(m_hThread);
			return FALSE;
		}
		return TRUE;
	}
	
	//! Close the thread handle and wait for the thread to die
	BOOL Release(DWORD timeout = INFINITE)
	{
		if( m_hThread==NULL ) 
			return TRUE;
		if ( WaitForSingleObject(m_hThread, timeout) != WAIT_OBJECT_0 )
		{
			// The thread didn't die. Terminate it
			TRACE("Must terminate thread. Handle = %x\n", m_hThread);
			Terminate(0);
			WaitForSingleObject(m_hThread, 10000);
		}
		
		return Detach();
	}
	
	//! Close the thread handle, but don't wait for the thread to die
	BOOL Detach()
	{
		if ( m_hThread == NULL )
			return TRUE;
		if( ::CloseHandle(m_hThread)==FALSE ) 
			return FALSE;
		m_hThread = NULL;
		m_dwID = 0;
		return TRUE;
	}
	
	//! Set the thread's priority
	BOOL SetPriority(int Priority)
	{
		ASSERT(m_hThread);
		return ::SetThreadPriority(m_hThread, Priority);
	}
	
	//! Suspend the thread
	BOOL Suspend()
	{
		ASSERT(m_hThread);
		if( m_bSuspended ) 
			return TRUE;
		if( ::SuspendThread(m_hThread)==-1 ) 
			return FALSE;
		m_bSuspended = true;
		return TRUE;
	}
	
	//! Resume the thread
	BOOL Resume()
	{
		ASSERT(m_hThread);
		if( !m_bSuspended ) return TRUE;
		if( ::ResumeThread(m_hThread)==-1 ) return FALSE;
		m_bSuspended = false;
		return TRUE;
	}
	
	//! Terminate the thread (don't...)
	BOOL Terminate(DWORD dwExitCode)
	{
		ASSERT(m_hThread);
		return ::TerminateThread(m_hThread, dwExitCode);
	}
	
	//! Get the thread's exit code
	BOOL GetExitCode(DWORD *pExitCode)
	{
		ASSERT(m_hThread);
		ASSERT(pExitCode);
		return ::GetExitCodeThread(m_hThread, pExitCode);
	}
	
	//! Get the thread's handle
	operator HANDLE() 
	{ 
		return m_hThread; 
	}
	
	
	//! Check if the thread is currently suspended
	bool IsSuspended() 
	{ 
		return m_bSuspended; 
	}
	
	private:
		//! The thread's handle
		HANDLE			m_hThread;
		
		//! The thread's ID
		DWORD			m_dwID;
		
		//! Indicates if the thread is currently suspended
		bool m_bSuspended;
		
	};   ///CBlThread
class CBlFile
{
public:
	CBlFile(){}
	~CBlFile(){}
public:  
	void plGetVersion(OUT char *szV)
	{
		TCHAR szFullPath[MAX_PATH];
		DWORD dwVerInfoSize = 0;
		DWORD dwVerHnd;
		VS_FIXEDFILEINFO * pFileInfo;
		
		GetModuleFileName(NULL, szFullPath, sizeof(szFullPath));
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
			sprintf(szV,_T("V: %d.%d.%d.%d"),m_nProdVersion[0],
				m_nProdVersion[1],m_nProdVersion[2],m_nProdVersion[3]);
			//*/
			
			GlobalUnlock(hMem);
			GlobalFree(hMem);
			
			
		}
	}
};
//=====================================================================
	/* extern "C" { */
#ifdef __cplusplus
}
#endif

#endif
