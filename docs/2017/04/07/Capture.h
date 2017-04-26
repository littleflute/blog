//Download by http://www.NewXing.com

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CAPTURE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CAPTURE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef CAPTURE_EXPORTS
#define CAPTURE_API __declspec(dllexport)
#else
#define CAPTURE_API __declspec(dllimport)
#endif

CAPTURE_API BOOL BeginCapture(HWND hOwner);;
CAPTURE_API void EndCapture();;
