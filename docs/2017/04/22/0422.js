var v0422 = "1.0.1";

var vvv	= document.getElementById("demo").innerHTML;

var eXdMouseMove	=	1;
var eXdMouseDown	=	2;

addHandler("myDiv",eXdMouseMove); 

var myKLines		= {

	v			: "0.0.1",
	maxX		: 0,
	minX		: 0,	
	maxY		: 0,
	minY		: 0,	
	numAll		: 0,
	maxVal		: 0,
	minVal		: 0,
	kLines		: "1275,1279,1270,1274;",
	
	xdPush		: function(o,h,l,c)
	{
		this.kLines += o + ",";
		this.kLines += h + ",";
		this.kLines += l + ",";
		this.kLines += c + ";";
	},
	setMaxMinXY		: function(maxx,maxy,minx,miny)
	{
		this.maxX = maxx;
		this.maxY = maxy;
		this.minX = minx;
		this.minY = miny;
	},

	setMaxMinVal		: function(maxVal,minVal)
	{
		this.maxVal = maxVal;
		this.minVal = minVal;
	},
	getValAtY			: function(y)
	{
		var vRet = 0;
		var k = (this.maxVal - this.minVal)/(this.minY - this.maxY);
		vRet = k*(y - this.minY) + this.maxVal;
		vRet = vRet.toFixed(2);
		return vRet;
	},
	getYByVal			: function(v)
	{
		var YRet = 0;
		var k = (this.minY - this.maxY)/(this.maxVal - this.minVal);
		YRet = k*(v - this.minVal) + this.maxY;
		YRet = YRet.toFixed(0);
		return YRet;
	},
	getValue	: function(y)
	{
		var sRet = "";
		sRet	+= "val:"+this.getValAtY(y) + "<br>" + y;
		return sRet;
	},
	parseKLines	: function(eID)
	{
		var sRet	= "";
		var a		= this.kLines.split(";");
		
		for(var i = 0; i<a.length-1; i++)
		{
			var ohlc = a[i].split(",");
			sRet += a[i];
			sRet += "    :    "+ this.getYByVal(ohlc[0]) + "-";
			sRet += this.getYByVal(ohlc[1]) + "-";
			sRet += this.getYByVal(ohlc[2]) + "-";
			sRet += this.getYByVal(ohlc[3]);
			sRet += "<br>";
		}
		return sRet;
	},
	drawAll		: function(eID)
	{
		var p				= document.getElementById(eID);
		var o				= document.createElement("div");
		o.style.border		=	"1px red solid";
		o.style.width		=	"420px";
		o.style.position	= "absolute";
		o.style.left		= "20px";
		o.style.top			= this.minY + "px";
		o.style.height		= this.maxY - this.minY+"px";
		o.style.color		= "yellow";
		o.innerHTML			= this.parseKLines(eID);
		p.appendChild(o);
	}
}//	___myKlinesEnd:"2017.04.27 9:25am";

myKLines.setMaxMinVal(1295,1195);
myKLines.setMaxMinXY(100,280,10,10);
myKLines.xdPush(1268,1275,1265,1269);
myKLines.xdPush(1277,1279,1265,1271);
myKLines.xdPush(1267,1275,1265,1260);
myKLines.xdPush(1295,1295,1265,1270);
myKLines.xdPush(1195,1275,1195,1270);
myKLines.drawAll("myDiv");
  
var myVer1Ctx = { 
    id			: "myVer1",
	bHit		: false,
	x1			: 0,
	nClick		: 0,
	mousedown	: function(e,x)
	{
		if(x.id		!= this.id) return;
		if(this.nClick==0)		this.x1		= e.clientX;
		this.nClick++;  
	},
	mouseup		: function(e,x)
	{
		if(x.id != this.id) return;
		this.nClick = 0;

	},
	mouseout	: function(e,x)
	{
		if(x.id != this.id) return;
		this.nClick = 0;

	},
    mousemove	: function(e,x) 
	{
		if(x.id != this.id) return; 
		if(this.nClick==1)
		{
			x.style.left = parseFloat(x.style.left) + e.clientX -this.x1 + "px"; 
		}

	}
};

function addHandler(id,eNo){
	var x	= document.getElementById(id);

	switch(eNo)
	{
	case 1: //eXdMouseMove
		{
			if (x.addEventListener) {
    			x.addEventListener("mousemove",function(e){myMousemove(e,x);});
			} else if (x.attachEvent) {
    			x.attachEvent("onmousemove", function(e){myMousemove(e,x);});
			}
		}
		break;
	case 2: //eXdMouseDown
		{ 
		}
		break;
	}
}  
function whichElement(e) {
    var targ;
    if (!e) {
        var e = window.event;
    }
    if (e.target) {
        targ = e.target;
    } else if (e.srcElement) {
        targ = e.srcElement;
    }
    var tid;
    tid = targ.id;
 //   alert("You clicked on : " + tid + " element.");
	
	myVer1Ctx.mousedown(e,targ);
}
function mousemoveOn(e) {
    var targ;
    if (!e) {
        var e = window.event;
    }
    if (e.target) {
        targ = e.target;
    } else if (e.srcElement) {
        targ = e.srcElement;
    }
	myVer1Ctx.mousemove(e,targ); 
}
function mouseupOn(e) {
    var targ;
    if (!e) {
        var e = window.event;
    }
    if (e.target) {
        targ = e.target;
    } else if (e.srcElement) {
        targ = e.srcElement;
    } 
	myVer1Ctx.mouseup(e,targ);
}
function mouseoutOf(e){
    var targ;
    if (!e) {
        var e = window.event;
    }
    if (e.target) {
        targ = e.target;
    } else if (e.srcElement) {
        targ = e.srcElement;
    } 
	myVer1Ctx.mouseout(e,targ);

}

function myMousemove(e,x){ 
	myDivMousemove(e,x);
}
 
 
function myDivMousemove(e,x){ 
	if(x.id != "myDiv") return;

	var s = "";
    var o = document.getElementById("demo");
    s += "html:" + parseInt(x.style.left) + " ";
	s += "js:" + v0422; 
    s += "<br>clientX:" + e.clientX;
    s += "screenX:" + e.screenX;
    var myX = e.clientX - parseFloat(x.style.left);
    s += "<br>myX:" + myX;
    o.innerHTML = vvv + s ;
    
    
    var v = document.getElementById("vDiv");
    v.style.left	= (myX-0) + "px";
    v.style.width 	= 1+ "px";
    v.style.height	= x.style.height;
    
    var h = document.getElementById("hDiv");
    var myY = e.clientY -parseFloat(x.style.top);
    h.style.top		= (myY-0) + "px";
    h.style.height	= 1+"px";
    h.style.width	= x.style.width;
    
    var vv = document.getElementById("valueDiv"); 
    vv.style.top	= (myY-0) + "px";
    vv.innerHTML	= myKLines.getValue(myY);
 
 	
    
    var tt = document.getElementById("ttDiv");
    tt.style.left	= (myX-2) + "px";
    tt.innerHTML	= myX;
    
}