[Home](..)
#[v0.4.3](https://github.com/littleflute/blog/edit/master/docs/readme.md) | [showme](https://littleflute.github.io/blog/docs)

<div id="blog"></div>
 
<script>

//<
function blogJS()
{
	this.fname	= "John";
  
	this.lname	= "Doe";
	this.age	= 25;
	this.home	= "home"; 
	this.songIndex	= 0;
	 
	this.songStr	= "";
	this.createHome = function (){
		var b = document.getElementById("blog");
		var h = document.createElement("div");
		h.id = this.home;
		b.appendChild(h);
    };

	this.createSongDbg = function(){
		var b = document.getElementById("blog");
		var s = document.createElement("div");
		s.id = "songDbg";
		b.appendChild(s);
	};
	this.createSongList = function (){
		var b = document.getElementById("blog");
		var s = document.createElement("div");
		s.id = "songList";
		b.appendChild(s);
    };
	this.setHome = function (){
		var h = document.getElementById(this.home);
		if(!h) return;
		h.style.border = "solid 1px red";
		h.style.color = "green";

    };
    this.onBtnTest = function(o)
    {
    	var id = "x" + o.parentElement.id;
      	var x = document.getElementById(id);
    	if(x.style.display == "none")
    	{
    		x.style.display = "block";
        	o.innerHTML = "-";
       	 o.style.color = "red";
    	}
    	else
    	{
    		x.style.display = "none";
        	o.innerHTML = "+";
        	o.style.color = "green";
    	}
    };
	this.showMe = function()
	{
		var x;
		var h = document.getElementById(this.home);
		if(!h) return; 
        var nID = 0;
		for(x in this)
		{
        	nID++;
            
			var d = document.createElement("div");
			d.id = nID;
            d.onFun = this.onBtnTest;
            d.innerHTML = x;
            var bt= "<button onclick='this.parentElement.onFun(this)'>";
            bt += "+</button>";
			d.innerHTML += bt;
            d.style.border = "solid 1px blue";
			d.style.color = "red";
			h.appendChild(d); 
            
			var v = document.createElement("div");
            v.id = "x" + nID;
			v.innerHTML = this[x];
			v.style.border = "solid 1px green";
			v.style.color = "black";
            v.style.display = "none";
			d.appendChild(v); 
		} 
	};
	this.showMe1 = function()
	{
		var x;
		var h = document.getElementById(this.home);
		if(!h) return;
		var s = "";
		for(x in this)
		{
			s += x + ":" +this[x] + "<br>";
		}
		h.innerHTML = s;
	};
	this.getSongSrc = function (n)
	{
		this.songIndex = n;
		var s = "https://littleflute.github.io/blog/html/songs/s00" + n + ".html";
		return s;
	};
	this.loadASong = function (src,p) {
		var xhttp = new XMLHttpRequest();
		xhttp.onreadystatechange = function() 
		{
			if (this.readyState == 4 && this.status == 200) 
			{
				p.parseSong(this.responseText,src);
			}
		};
		xhttp.open("GET", src, true);
		xhttp.send();
	};
	this.parseSong = function (txt,src)
	{
				var str = txt;
   				var pos = str.indexOf("scale=1.165199");
      
				document.getElementById("songDbg").innerHTML = pos;
				if(pos !=-1)
				{
					 this.songStr += this.songIndex;
					 this.songStr += ": ";
				     this.songStr += "<a href=' ";
					 this.songStr += src;
					 this.songStr += "'> ";
					 this.songStr += this.songIndex;
					 this.songStr += "</a>";
					 this.songStr += "<br>";
				     document.getElementById("songList").innerHTML = this.songStr;
					 this.loadASong(this.getSongSrc(this.songIndex+1),this);
				} 
	};
 
	this.v		= "0.0.9";
};
//>==class: blogJS==
 
var bj = new blogJS();
bj.createHome();
bj.createSongList();
bj.createSongDbg();
bj.setHome();
bj.showMe();

bj.loadASong(bj.getSongSrc(1),bj);
</script>

## [最新文章]
<div id="test" style="border:1px red solid;width:500px;height:220px;">test
</div>
<script>
getData("https://littleflute.github.io/blog/docs/2017/04/23");
function showData(s)
{	  
	document.getElementById("test").innerHTML=s;
}
function getData(src)
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
			showData(xmlhttp.responseText); 
		}
	}
	xmlhttp.open("GET",src,true);
	xmlhttp.send();
}
</script>

#[2014.04.18: My to Do List](2017/04/18)
#[2014.04.19: 伦敦金实时数据](2017/04/19)

## 漂泊者乐园
#[官网](http://www.beautifullover.org)

#2017.4.19 1:51AM bjt
建立本博客站。
