//alert("i");
var v 		= bl$("id_div_" + "plxName-i.js"); 
v.innerHTML 	= "i.js test v0.0. 113 ";
v.fV		= "https://github.com/littleflute/newTed/releases/download/1-30/blTed001.mkv";
v.fVPath	= "https://github.com/littleflute/blog/releases/download/i1069/";
v.fVs		=[
		"VTS_01_1.mp4",
		"VTS_01_2.mp4",
		"VTS_01_3.mp4",
		"VTS_01_4.mp4",
		"VTS_01_5.mp4",
		"VTS_01_6.mp4",
		"VTS_01_7.mp4",
		"VTS_01_8.mp4",
		"VTS_02_1.mp4",
		"VTS_03_1.mp4",
		
];

var b1	=  blo0.blBtn( v , v.id + "b1" , "b1", "gold" );
 
b1.n = 0;
b1.v1 = blo0.blDiv(v, v.id + "v1" , "v1", "lightgreen");
b1. onclick = function(){
	b1.n++;
	b1.v1.innerHTML = b1.n;	
}

var btnMyVideo	=  blo0.blBtn( v , v.id + " btnMyVideo	" , "btnMyVideo", blGrey[0] );

btnMyVideo.onclick = function(){ 	play(v.fV); 	}


b1.v4Vs = blo0.blDiv(v, v.id + "v4Vs" , "v4Vs", blGrey[0]);
for(i in v.fVs){
	var _v=b1.v4Vs;
	var btn = blo0.blBtn(_v, _v.id + i, "f"+i, blGrey[1]); 
	btn.onclick = function(_i){
		return function(){ 
			play( v.fVPath + v.fVs[_i]); 
		}
	}(i);
}


var btnTitle	=  blo0.blBtn( v , v.id + "btnTitle	" , "title", "brown" );
btnTitle. onclick  = function(){
	this.v= blo0.blDiv(v, this.id + "v" , "v", "lightblue");
	this.v.innerHTML = ftnI;
	var a = this.v.innerHTML;
	var b = a.split("/*");
	var c = b[1].split(";;");
	this.v.innerHTML = c[0];	
	this.v.onclick = function(){		b1.v1.innerHTML = btnTitle.v.id;		}
}

var btnBody	=  blo0.blBtn( v , v.id + " btnBody	" , " Body	", "lightRed" );
btnBody	. onclick  = function(){
	this.v= blo0.blDiv(v, this.id + "v" , "v", "lightYellow");
	this.v.innerHTML = ftnI;
	var a = this.v.innerHTML;
	var b = a.split("/*");
	var c = b[1].split(";;");
	this.v.innerHTML = c[1];	

	this.v.onclick = function(){		b1.v1.innerHTML = btnBody.v.id;		}
}


var btnParseBody	=  blo0.blBtn( v , v.id + " btnParseBody	" , " ParseBody	", "purple" );
btnParseBody	. onclick  = function(){
	b1.v1.innerHTML = btnBody	.v.innerHTML;
	var m = document.getElementsByTagName("textarea"); 
	var p = m[0]; 
	p.value = this.id;
}

//=======================================================================================================
var ftnI = function(){//ftnI;
/*
--title--

Cole Porter, 1891-1964: He Wrote Songs for Broadway Musicals and Movies That Are Still Popular Today
==title==

;;



--body--

By Shelley Gollust
2008-2-16
VOICE ONE:

This is Faith Lapidus.

VOICE TWO:
==body==

*/
}