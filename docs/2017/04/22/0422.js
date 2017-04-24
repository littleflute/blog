var v0422 = "0.0.2";

var x = document.getElementById("myDiv");

addHandler();

function addHandler(){

	if (x.addEventListener) {
    	x.addEventListener("mousemove", myMousemove);
	} else if (x.attachEvent) {
    	x.attachEvent("onmousemove", myMousemove);
	}
} 
function myMousemove(e){
	var s = "";
    var o = document.getElementById("demo");
    s += "html:" + x.style.v + " ";
	s += "js:" + v0422; 
    s += "<br>clientX:" + e.clientX;
    s += "screenX:" + e.screenX;
    var myX = e.clientX - parseFloat(x.style.left);
    s += "<br>myX:" + myX;
    o.innerHTML = s;
    
    
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