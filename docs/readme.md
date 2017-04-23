## [Home](..)
#[v0.4.1](https://github.com/littleflute/blog/edit/master/docs/readme.md) | [showme](https://littleflute.github.io/blog/docs)

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
