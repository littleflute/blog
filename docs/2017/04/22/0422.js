var v0422 = "1.0.1";

var vvv	= document.getElementById("demo").innerHTML;

var eXdMouseMove	=	1;
var eXdMouseDown	=	2;

addHandler("myDiv",eXdMouseMove); 

var myKLines		= {
	b			: "0.0.1",
	maxX		: 0,
	minX		: 0,	
	maxY		: 0,
	minY		: 0,	
	numAll		: 0,
	maxVal		: 0,
	minVal		: 0,
	kLines		: "",//1275,1279,1270,1274;",
	DataFromSrc	: "",
	
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
		var x		= 50;
		for(var i = 0; i<a.length-1; i++)
		{
			var ohlc = a[i].split(",");
			var oY = this.getYByVal(ohlc[0]);
			var hY = this.getYByVal(ohlc[1]);
			var lY = this.getYByVal(ohlc[2]);
			var cY = this.getYByVal(ohlc[3]);
			var dXX	= 10;
			x		+= dXX;
			var h = lY - hY;
			if(hY>0)
			{
				this.draw_1_KLine(eID,x,oY,hY,lY,cY);
			}
			sRet += a[i];
			sRet += "    :    "+ this.getYByVal(ohlc[0]) + "-";
			sRet += this.getYByVal(ohlc[1]) + "-";
			sRet += this.getYByVal(ohlc[2]) + "-";
			sRet += this.getYByVal(ohlc[3]);
			sRet += "<br>";
		}
		return sRet;
	},
	drawFrame	: function(eID)
	{
		var p				= document.getElementById(eID);
		var o				= document.createElement("div");
		o.style.border		=	"1px red solid";
		o.style.width		=	"420px";
		o.style.position	= "absolute";
		o.style.left		= "20px";
		o.style.top			= this.minY + "px";
		o.style.height		= this.maxY - this.minY+"px";
		 
		p.appendChild(o);
	},
	draw_1_KLine	: function(eID,x,oY,hY,lY,cY)
	{
		var p				= document.getElementById(eID);
		var oHightLow		= document.createElement("div");
		var	hh				= 0;
		var d			= 2;
		var y;
		var color;
		
		if(cY > oY)
		{
			y		= oY;
			hh		= cY - oY;
			color	= "green";
		}  
		if(cY <= oY)
		{
			y		= cY;
			hh		= oY - cY;
			hh		= hh?hh:1;
			color	= "red";
		}
		oHightLow.style.position	= "absolute";
		oHightLow.style.border		= "0px blue solid";
		oHightLow.style.width		= "1px";
		oHightLow.style.left		= x + "px";
		oHightLow.style.top			= hY + "px";
		oHightLow.style.height		= lY-hY + "px";
		oHightLow.style.background	= color;
		p.appendChild(oHightLow);

		
		var oOpenClose	= document.createElement("div");
		
		oOpenClose.style.position	= "absolute";
		oOpenClose.style.border		= "0px blue solid";
		oOpenClose.style.width		= "5px";
		oOpenClose.style.left		= x - d + "px";
		oOpenClose.style.top		= y + "px";
		oOpenClose.style.height		= hh + "px";
		oOpenClose.style.background	= color; 
		p.appendChild(oOpenClose);

	},
	getDataFromSrc : function (src)
	{
		var xmlhttp;
		if (window.XMLHttpRequest)
		{//"code for IE7+, Firefox, Chrome, Opera, Safari"
			xmlhttp = new XMLHttpRequest();
		}
		else
		{// code for IE6, IE5
			xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
		}
		xmlhttp.onreadystatechange=function()
		{
			if (xmlhttp.readyState==4 && xmlhttp.status==200)
			{
				myKLines.getData(xmlhttp.responseText);
			}
			}
		xmlhttp.open("GET",src,true);
		xmlhttp.send();
	},
	getData		: function(sData)
	{
		var a		= sData.split(";");
	 
		for(var i = 0; i<a.length; i++)
		{
			var d	= a[i].split(" ");
			if(!(d[1]=="undefined" || d[1]==null))
			{
				var ohlc = d[1].split(",");
				this.xdPush(ohlc[0],ohlc[1],ohlc[2],ohlc[3]);
			}
		}
		 

		this.drawAll("myDiv");

	},
	drawAll		: function(eID)
	{
		this.drawFrame(eID);
		this.parseKLines(eID);
	},
	e : "0.0.2" 
}//	___myKlinesEnd:"2017.04.27 9:25am";

myKLines.setMaxMinVal(1295,1195);
myKLines.setMaxMinXY(100,280,10,10);
myKLines.getDataFromSrc("http://www.beautifullover.org/php/xau-days.txt");



  
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
/*
xau-days.txt
20170419 1289.85,1290.95,1274.14,1280.05;
20170420 1280.72,1283.48,1276.75,1281.53;
20170423 1281.80,1288.45,1278.56,1284.47;
20170424 1275.67,1277.65,1265.64,1275.54;
20170425 1276.51,1278.35,1261.71,1263.88;
20170426 1264.42,1270.70,1260.15,1269.03;






*/