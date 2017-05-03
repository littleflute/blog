[v0.0.1](https://github.com/littleflute/blog/edit/master/docs/2017/04/04/index.md)

~~~C++
//File: BlConsole.h
/*
2017.05.04 2:30 AM bjt
littleflute
*/


#include "stdio.h"
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

~~~
