// BlW32Main.cpp : Defines the entry point for the application.
//

#include "stdafx.h" 

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	/*
	CBlConsole c;
	c.InitConsole();
	//*/

	CMyDll d;
	BLSTATUS r = d.OnBlCallLibFun(); 

	char szCaption[1000];
	switch(r)
	{
	case BL_STATUS_OK:
		break;
	case BL_STATUS_PARAMETER_INVALID:
		{
			sprintf(szCaption,"BlW32Main_%s",MY_VERSION);
			::MessageBox(NULL,"BL_STATUS_PARAMETER_INVALID!",szCaption,0);
		}
		break;
	case BL_STATUS_NOT_FOUND_LIBARY:
		{ 
			sprintf(szCaption,"BlW32Main_%s",MY_VERSION);
			::MessageBox(NULL,"UI 库文件 加载失败!\n请确认文件存在!",szCaption,0);
		}
		break;  
	default:
		{ 
			sprintf(szCaption,"BlW32Main_%s",MY_VERSION);
			::MessageBox(NULL,"default error!!!",szCaption,0);
		}
		break; 
	}

	return 0;
}



