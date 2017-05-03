[V0.0.3](https://github.com/littleflute/blog/edit/master/docs/2017/04/28/index.md)
[show me](https://littleflute.github.io/blog/docs/2017/04/28/)

<script src="../../../../xd.js"></script>
~~~C++
	
	class CXdDraw
	{
	#pragma warning( disable : 4183 )
	public:
		CXdDraw::CXdDraw(){}
		CXdDraw::~CXdDraw(){}
		CXdDraw::all(HDC &hDC){
			_line(hDC,100,100,200,200);
			_text(hDC,50,50,"CXdDraw V0.0.1",14);
		}
		CXdDraw::onLBtnDow(){}
	private:
		CXdDraw::_line(HDC &hDC,int x1,int y1,int x2,int y2){
			::MoveToEx(hDC,x1,y1,NULL);
			::LineTo(hDC,x2,y2);
		}
		CXdDraw::_text(HDC &hDC,int x,int y,char *ptxt,int nLen){			
			TextOut(hDC, x, y, ptxt, nLen);
		}
	};
~~~
