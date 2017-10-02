#1.建立本博客站。
#2.建立伦敦金现价实时跟踪分析工具。
### [v0.0.3](https://github.com/littleflute/blog/edit/master/docs/2017/04/19/readme.md)


```js



<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<script type="text/javascript">
var gTimes = 0;
function loadXMLDoc()
{
var xmlhttp;
if (window.XMLHttpRequest)
  {// code for IE7+, Firefox, Chrome, Opera, Safari
  xmlhttp=new XMLHttpRequest();
  }
else
  {// code for IE6, IE5
  xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
  }
xmlhttp.onreadystatechange=function()
  {
  if (xmlhttp.readyState==4 && xmlhttp.status==200)
    {
      document.getElementById("myDiv").innerHTML=xmlhttp.responseText;
      gTimes++;
      document.getElementById("gTimesDiv").innerHTML=gTimes;
      showData(xmlhttp.responseText);
      loadXMLDoc();
    }
  }
xmlhttp.open("GET","http://api.baidao.com/api/hq/npdata.do?ids=201",true);
xmlhttp.send();
}

function newVer(strV)
{
	var b = document.getElementById("myBtn");
	b.innerHTML = strV;
}

function xdClrCanvas(color)
{ 
	var c = document.getElementById("myCanvas");
	var ctx = c.getContext("2d");
	ctx.fillStyle = color;
	ctx.fillRect(0, 0, 500, 800);
}

function xdStr(str,color,x,y)
{
	var c = document.getElementById("myCanvas");
	var ctx = c.getContext("2d"); 
	ctx.fillStyle = color;
	ctx.font="20px Georgia";
	ctx.fillText(str,x,y);
}


function xdShow1(id,s)
{
  var strData = "";
  var s2 = s.split("{");
  var s3 = s2[1].split("}");
  var s4 = s3[0].split(",");
  var i;
  var n = 20;
  for(i=0;i<n;i++)
  {
    var strTmp = s4[i];
    if(10==i) strTmp = strTmp.fontcolor("Red");
    if(11==i) strTmp = strTmp.fontcolor("Blue");
    strData += (i+1) + "-> " + strTmp + "<br />";
  }
  document.getElementById(id).innerHTML=strData;
}
function xdGetNow(s)
{
  var r = 0;
  var strData = "";
  var s2 = s.split("{");
  var s3 = s2[1].split("}");
  var s4 = s3[0].split(",");
  var i;
  var n = 20;
  for(i=0;i<n;i++)
  {
    if(11==i) 
	r = s4[i];
  }
  return r;
}
function xdGetUpdatetime(s)
{
  var r = 0;
  var strData = "";
  var s2 = s.split("{");
  var s3 = s2[1].split("}");
  var s4 = s3[0].split(",");
  var i;
  var n = 20;
  for(i=0;i<n;i++)
  {
    if(2==i) 
	r = s4[i];
  }
  return r;
}



function showData(s)
{
  xdShow1("showDataDiv",s);
  xdClrCanvas('black');
  xdStr(xdGetNow(s),"red",10,50);
  xdStr(xdGetUpdatetime(s),"green",10,80);
}

</script>
</head>
<body>
<a href="../../">主页</a> | <a href="http://www.w3school.com.cn/tiy/t.asp?f=ajax_get" target="_blank">ref</a>->
<button id="myBtn" type="button" onclick="loadXMLDoc()">最新数据
</button>
 
<div id="gTimesDiv"></div>
<div id="myDiv"></div>
<div id="showDataDiv" style="border: solid 1px red;"></div>

<canvas id="myCanvas" width="800" height="150" style="border:1px solid #d3d3d3;">
Your browser does not support the HTML5 canvas tag.</canvas>

<script>
newVer("最新数据 v2.7.7");  

</script>


</body>
</html>
```
