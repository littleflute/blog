
#ifndef __________CBlFile_H________________

#define __________CBlFile_H________________


/////////////////////////////////////////////////////////////////////////////

#define		INFO_XD_TITLE		"BlFile V0.0.1"

class CBlFile
{
public:
   /////////////////////////////////////////////////////////////////////////////



	CBlFile() : m_bPrintTime(true)
	{
		m_bEnable = FALSE;
		m_csFileName = "";
		
		m_csAppName = "";
		
		// we'll make sure only one call uses the critical stuff at a time
		
		InitializeCriticalSection(&m_crit);
	}
   ~CBlFile(){
	   DeleteCriticalSection(&m_crit);
   }

   /////////////////////////////////////////////////////////////////////////////

   // call this first!

   void		plInit(const char *pOutputFilename)
   {   
	   m_bEnable = TRUE;
	   
	   // get application path and name
	   
	   char buf[MAX_PATH+1];
	   
	   DWORD res = GetModuleFileName(AfxGetInstanceHandle(), buf, MAX_PATH);
	   
	   CString appDir = pvGetBaseDir(buf);
	   
	   m_csAppName = pvGetBaseName(buf);
	   
	   m_csFileName.Format("%s\\%s", appDir, pOutputFilename);
	   
	   // overwrite the old one!
	   
	   remove(m_csFileName);
   }



   void plTest()
   {  
	   ShellExecute(NULL,"open","notepad.exe",m_csFileName,NULL,SW_SHOWNORMAL);
   }
   /////////////////////////////////////////////////////////////////////////////

   // output text, just like TRACE or printf

   BOOL	plWrite(const char* fmt, ...)
   {
	   if (m_csFileName.IsEmpty())
		   return FALSE;
	   
	   if (!m_bEnable)
		   return TRUE;
	   
	   if (!AfxIsValidString(fmt, -1))
		   return FALSE;
	   
	   EnterCriticalSection(&m_crit);
	   
	   // parse that string format
	   
	   try
		   
	   {
		   va_list argptr;
		   va_start(argptr, fmt);
		   _vsnprintf(m_tBuf, TBUF_SIZE, fmt, argptr);
		   va_end(argptr);
	   }
	   catch (...)
	   {
		   m_tBuf[0] = 0;
	   }
	   
	   BOOL bOK = FALSE;
	   
	   // output 
	   
	   FILE *fp = fopen(m_csFileName, "a");
	   
	   if (fp)
	   {
		   if (m_bPrintAppName)
		   {
			   fprintf(fp,INFO_XD_TITLE);
			   fprintf(fp," - %s : ", m_csAppName);
		   }
		   
		   if (m_bPrintTime)
		   {
			   CTime ct ; 
			   ct = CTime::GetCurrentTime();
			   fprintf(fp,"%s : ",ct.Format("%m/%d/%Y %H:%M:%S"));
		   }
		   
		   fprintf(fp, "%s\n", m_tBuf);
		   
		   fclose(fp);
		   
		   bOK = TRUE;
	   }
	   
	   LeaveCriticalSection(&m_crit);
	   
	   return bOK;

   }



   /////////////////////////////////////////////////////////////////////////////

   // turn it on or off

   void		Enable(BOOL bEnable)
   {
   }



   /////////////////////////////////////////////////////////////////////////////

   // timestamp each line?

   void     PrintTime(BOOL b) {m_bPrintTime = b;}



   /////////////////////////////////////////////////////////////////////////////

   // print the application name?

   void     PrintAppName(BOOL b) {m_bPrintAppName = b;}



   /////////////////////////////////////////////////////////////////////////////

   // override the default app name, which is the name the EXE (minus the ".exe")

   void     SetAppName(const char *pName) {m_csAppName = pName;}



protected:
   /////////////////////////////////////////////////////////////////////////////

   // work buffer

	enum {TBUF_SIZE = 3000};

   char		m_tBuf[TBUF_SIZE];

   CString  m_csAppName;
	CString	m_csFileName;
	
   /////////////////////////////////////////////////////////////////////////////

   // protection

   CRITICAL_SECTION  m_crit;



   /////////////////////////////////////////////////////////////////////////////

   // controlling stuff

	BOOL		m_bEnable;

   BOOL     m_bPrintTime;
   BOOL     m_bPrintAppName;

   /////////////////////////////////////////////////////////////////////////////

   // string utils

private:
   CString pvGetBaseDir(const CString & path)
   {
	   CString out = "";
	   int iSlashPos = path.ReverseFind('\\');
	   if (iSlashPos !=-1) 
	   {
		   out = path.Left(iSlashPos);
	   } 
	   else
	   {
		   iSlashPos = path.ReverseFind('/');
		   if (iSlashPos !=-1) 
		   {
			   out = path.Left(iSlashPos);
		   } 
	   }
	   
	   return out;
   }

   CString pvGetBaseName(const CString & path)
   {
	   CString out = path;
	   
	   int iSlashPos = path.ReverseFind('\\');
	   if (iSlashPos !=-1) 
	   {
		   out = out.Mid(iSlashPos+1);
	   }
	   else
	   {
		   iSlashPos = path.ReverseFind('/');
		   if (iSlashPos !=-1) 
		   {
			   out = out.Mid(iSlashPos+1);
		   }
	   }
	   
	   int iDotPos = out.ReverseFind('.');
	   if (iDotPos>0)
	   {
		   out = out.Left(iDotPos);
	   }
	   
	   return out;
   }

};

#endif
