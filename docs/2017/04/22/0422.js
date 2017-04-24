var v0422 = "0.9.1";

var vvv	= document.getElementById("demo").innerHTML;

var eXdMouseMove	=	1;
var eXdMouseDown	=	2;

addHandler("myDiv",eXdMouseMove); 
  
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
    v.style.left	= (myX-2) + "px";
    v.style.width 	= 1+ "px";
    v.style.height	= x.style.height;
    
    var h = document.getElementById("hDiv");
    var myY = e.clientY -parseFloat(x.style.top);
    h.style.top		= (myY-2) + "px";
    h.style.height	= 1+"px";
    h.style.width	= x.style.width;
    
    var vv = document.getElementById("valueDiv"); 
    vv.style.top	= (myY-2) + "px";
    vv.innerHTML	= myY;
 
 	
    
    var tt = document.getElementById("ttDiv");
    tt.style.left	= (myX-2) + "px";
    tt.innerHTML	= myX;
    
}