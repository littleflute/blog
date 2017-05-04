[V0.0.2](https://github.com/littleflute/blog/edit/master/docs/2017/05/02/index.md)

[show me](https://littleflute.github.io/blog/docs/2017/05/02/)
<script src="../../../../js/xdhead.js"></script>

~~~c++
//BlWHotKey.h
/*
*/



class CBlWHotKey
{
public:
	CBlWHotKey::CBlWHotKey(){
		strcpy(m_szV,"V0.0.1");
	}
	CBlWHotKey::~CBlWHotKey(){}
	void onUnRegKey(HWND h,int code)
	{
		::UnregisterHotKey(h,code);
	}
	void onRegKey(HWND h,int code,WORD sysKey,WORD virKey)
	{ 
		UINT ui = 0; 
		if (sysKey & HOTKEYF_ALT)	    ui|= MOD_ALT;
		if (sysKey & HOTKEYF_CONTROL)   ui|= MOD_CONTROL;
		if (sysKey & HOTKEYF_SHIFT) 	ui|= MOD_SHIFT; 	
		
		if(!::RegisterHotKey(h, code, ui, virKey))
		{ 
		}
	}
	void onKey(HWND h,int code)
	{
		if(444==code)
		{
			static int b = 0;
			printf("444 b=%d\n",b);
			b = !b;
			if(b)
			{
				::ShowWindow(h,SW_HIDE);
				onRegKey(h,111,MOD_CONTROL,40);
			}
			else
			{
				::ShowWindow(h,SW_SHOW);
				onUnRegKey(h,111);
			} 
		}
		if(111==code)
		{
			::MessageBox(h,"aaa","xd",IDOK);
		}
	}

private:
	char	m_szV[16];
};

~~~
