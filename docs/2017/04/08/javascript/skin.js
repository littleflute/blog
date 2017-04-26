function $(obj){
	return document.getElementById(obj);
}

var skin={};

skin.addEvent=function(){
	var skins =$("skin").getElementsByTagName("li");
	for (i=0;i<skins.length;i++)
	{
		skins[i].onclick=function(){skin.setSkin(this.id.substring(5))};
	}
}

skin.setCookie=function(n){
	var expires=new Date();
	expires.setTime(expires.getTime()+24*60*60*365*1000);
	var flag="Skin_Cookie="+n;
	document.cookie=flag+";expires="+expires.toGMTString();
}

skin.readCookie=function(){
	var skin=0
	var mycookie=document.cookie;
	var name="Skin_Cookie";
	var start1=mycookie.indexOf(name+"=");
	if(start1==-1){
		skin=0;
	}
	else{
		var start=mycookie.indexOf("=",start1)+1;
		var end=mycookie.indexOf(";",start);
		if(end=-1){
			end=mycookie.length;
		}
		var values= unescape(mycookie.substring(start,end));
		if (values!=null)
		{
			skin=values;
		}
	}
	return skin;
	
}

skin.setSkin=function(n){
	var skins =$("skin").getElementsByTagName("li");
	for (i=0;i<skins.length;i++)
	{
		skins[i].className="";
	}
	skin.setCookie(n);
	$("skin_"+n).className="selected";
	$("cssfile").href="css/main"+n+".css";
}

window.onload=function(){
	skin.setSkin(skin.readCookie());
	skin.addEvent();
}