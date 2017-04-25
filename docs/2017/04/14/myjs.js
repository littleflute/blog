function Win()
{
	this.Create = function(title, wbody, size, w, h, l, t)
	{
		Winid++;
		title = title || "æ–°çª—å£ - åŠ è½½ä¸­...";
		wbody = wbody || "&nbsp;<p align='center'><img src='win/Loader.gif' align='top' style='margin-top:-10px;margin-right:4px' />æ­£åœ¨è½½å…¥çŽ¯å¢ƒé¡¹â€¦</p>";
		w = w || 350;
		h = h || 150;
		l = l || parseInt(Math.random() * 500);
		t = t || parseInt(Math.random() * 300);
		if (size == null) size = 1;
		var mywin = document.createElement("DIV");
		mywin.setAttribute("id", "win"+ Winid);
		mywin.setAttribute("Max", 0);
		mywin.setAttribute("Min", 0);
		mywin.className = "win";
		mywin.onmousedown = function(){ MyWin.Show(this.getAttribute("id")) };
		mywin.style.cssText = "width:"+ w +"px;height:"+ h +"px;left:0px;top:0px"
		mywin.style.zIndex = ++zIndex;
		document.body.appendChild(mywin);
		var mytie = document.createElement("DIV");
		var myboy = document.createElement("DIV");
		var mybom = document.createElement("DIV");
		mytie.className = "tie";
		myboy.className = "boy";
		mybom.className = "bom";
		mywin.appendChild(mytie);
		mywin.appendChild(myboy);
		mywin.appendChild(mybom);
		var wintag = [[mytie, 30, 15, "t1"], [mytie, 30, w-30, "t2"], [mytie, 30, 15, "t3"], [myboy, h-45, 15, "l1"], [myboy, h-47, w-32], [myboy, h-45, 15, "r1"], [mybom, 15, 15, "l2"], [mybom, 15, w-30, "b1"], [mybom, 15, 15, "r2"]];
		for (var i = 0; i < 9; i++)
		{
			var temp = document.createElement("DIV");
			temp.setAttribute("Fid", "win"+ Winid);
			wintag[i][0].appendChild(temp);
			if (i == 8)
			{
				temp.style.cssText = "float:left;height:"+ wintag[i][1] +"px;width:"+ wintag[i][2] +"px;filter:progid:DXImageTransform.Microsoft.AlphaImageLoader(src='win/"+ wintag[i][3] +".png', sizingMethod='scale');background:url('win/"+ wintag[i][3] +".png') !important;background:;cursor:se-resize";
			}
			else if (wintag[i][3])
			{
				temp.style.cssText = "float:left;height:"+ wintag[i][1] +"px;width:"+ wintag[i][2] +"px;filter:progid:DXImageTransform.Microsoft.AlphaImageLoader(src='win/"+ wintag[i][3] +".png', sizingMethod='scale');background:url('win/"+ wintag[i][3] +".png') !important;background:;";
			}
			else
			{
				temp.style.cssText = "float:left;filter:alpha(Opacity=95,style=0);opacity:0.95;height:"+ wintag[i][1] +"px;width:"+ wintag[i][2] +"px;background:#f7f7f7;border:1px solid #666;overflow:hidden;padding:0px";
			}
			if (i == 8)
			{
				if (size)
					temp.onmousedown = function(e){ MyWin.Move(this.getAttribute("Fid"), e ? e : window.event) };
				else
					temp.style.cursor = "default";
			}
			else if (i != 4)
			{
				temp.onmousedown = function(e){ MyWin.Move(this.getAttribute("Fid"), e ? e : window.event, 1) };
			}
		}
		mytie.childNodes[1].innerHTML = "<div style=\"position:absolute;overflow:hidden;height:15px;top:12px;padding-left:4px;padding-right:4px;filter:progid:DXImageTransform.Microsoft.AlphaImageLoader(src='win/tt.png', sizingMethod='scale');background:url('win/tt.png') !important;background:;\"></div><div class=\"wmin\" onclick=\"MyWin.Min('win"+ Winid +"')\" title=\"æœ€å°åŒ–\"></div><div class=\"wmax\" onclick=\"MyWin.Max('win"+ Winid +"',this)\" title=\"æœ€å¤§åŒ–\"></div><div class=\"wclo\" title=\"å…³é—­çª—å£\" onclick=\"MyWin.Close('win"+ Winid +"',100)\"></div>";
		this.Title("win"+ Winid, title);
		this.Body("win"+ Winid, wbody);
		this.Move_e("win"+ Winid, l, t, 0, 0);
		return(mywin);
	}
	this.Title = function(Id, title)
	{
	    if (Id == null) return;
	    var o = $(Id);
	    if (!o) return;
	    o.childNodes[0].childNodes[1].childNodes[0].innerHTML = title;
	}
	this.Body = function(Id, wbody)
	{
	    if (Id == null) return;
	    var o = $(Id);
        if (!o) return;
        if (wbody.slice(0, 4) == "[pg]")
            o.childNodes[1].childNodes[1].innerHTML = "<iframe onfocus=\"MyWin.Show('"+ Id +"',this)\" src='"+ wbody.slice(4) +"' frameBorder='0' marginHeight='0' marginWidth='0' width='100%' height='100%'></iframe>";
        else
            o.childNodes[1].childNodes[1].innerHTML = wbody;
	}
	this.Show = function(Id)
    {	    
	    if (Id == null) return;
	    var o = $(Id);
        if (!o) return;
	    o.style.zIndex = ++zIndex;
    }
    this.Move = function(Id, evt, T)
    {
	    if (Id == null) return;
	    var o = $(Id);
        if (!o) return;
        if (o.getAttribute("Max") != 0 || o.getAttribute("Min") != 0) return;
	    evt = evt ? evt : window.event;
	    o.style.position = "absolute";
	    o.style.zIndex = ++zIndex;
	    var obj = evt.srcElement ? evt.srcElement : evt.target;
	    if (obj.className == "wmin" || obj.className == "wmax" || obj.className == "wclo") return;
	    var w = o.offsetWidth;
	    var h = o.offsetHeight;
	    var l = o.offsetLeft;
	    var t = o.offsetTop;
	    var div = document.createElement("DIV");
	    document.body.appendChild(div);
	    div.style.cssText = "filter:alpha(Opacity=10,style=0);opacity:0.2;width:"+w+"px;height:"+h+"px;top:"+t+"px;left:"+l+"px;position:absolute;background:#000";
	    div.setAttribute("id", Id +"temp");
	    if (T)
		    this.Move_r(Id, evt);
	    else
		    this.Resize(Id, evt)
    }
    this.Resize = function(Id, evt)
    {
	    var o = $(Id +"temp");
        if (!o) return;
	    o.style.zIndex = ++zIndex;
	    evt = evt ? evt : window.event;
	    var l = o.offsetLeft;
	    var t = o.offsetTop;
    	if (!window.captureEvents)
		    o.setCapture(); 
	    else
	    	window.captureEvents(Event.MOUSEMOVE|Event.MOUSEUP);
    	document.onmousemove = function(e)
	    {
		    if (!o) return;	
		    e = e ? e : window.event;
		    var w = e.clientX - l;
		    var h = e.clientY - t;
	    	if (!Ie) h -= 2;
	    	if (w - 40 > 180 && e.clientX < document.documentElement.clientWidth)
	    	{
		    	o.style.width = w +"px";
	    	}
		    if (h - 55 > 10 && e.clientY < document.documentElement.clientHeight - 28)
	    	{
			    o.style.height = h +"px";
	    	}
	    }
	    document.onmouseup = function()
	    {
		    if (!o) return;
		    if (!window.captureEvents)
		    	o.releaseCapture();
		    else
		    	window.releaseEvents(Event.MOUSEMOVE|Event.MOUSEUP);
		    var o1 = $(Id);
		    if (!o1) return;
		    var w = o1.offsetWidth;
		    var h = o1.offsetHeight;
		    MyWin.Resize_e(Id, o.offsetWidth, o.offsetHeight, w, h);
		    document.body.removeChild(o);
		    o = null;
	    }
    }
    this.Move_r = function(Id, evt)
    {
	    var o = $(Id +"temp");
	    if (!o) return;
	    evt = evt ? evt : window.event;
	    var relLeft = evt.clientX - o.offsetLeft;
	    var relTop = evt.clientY - o.offsetTop;
	    if (!window.captureEvents)
	    	o.setCapture(); 
	    else
	    	window.captureEvents(Event.MOUSEMOVE|Event.MOUSEUP);
	    document.onmousemove = function(e)
	    {
	    	if (!o) return;
		    e = e ? e : window.event;
		    if (e.clientX - relLeft <= 0)
			    o.style.left = 0 +"px";
		    else if (e.clientX - relLeft >= document.documentElement.clientWidth - o.offsetWidth - 2)
			    o.style.left = (document.documentElement.clientWidth - o.offsetWidth - 2) +"px";
		    else
			    o.style.left = e.clientX - relLeft +"px";
		    if (e.clientY - relTop <= 1)
			    o.style.top = 1 +"px";
		    else if (e.clientY - relTop >= document.documentElement.clientHeight - o.offsetHeight - 30)
			    o.style.top = (document.documentElement.clientHeight - o.offsetHeight - 30) +"px";
		    else
			    o.style.top = e.clientY - relTop +"px";
	    }
	    document.onmouseup = function()
	    {
	    	if (!o) return;
	    	if (!window.captureEvents)
		    	o.releaseCapture(); 
	    	else
		    	window.releaseEvents(Event.MOUSEMOVE|Event.MOUSEUP);
		    var l0 = o.offsetLeft;
		    var t0 = o.offsetTop;
		    var o1 = $(Id);
		    if (!o1) return;
		    var l = o1.offsetLeft;
		    var t = o1.offsetTop;		
		    MyWin.Move_e(Id, l0 , t0, l, t);
		    document.body.removeChild(o);
		    o = undefined;
	    }
    }
    this.Move_e = function(Id, l0 , t0, l, t)
    {
	    if (typeof(window["ct"+ Id]) != "undefined") clearTimeout(window["ct"+ Id]);
	    var o = $(Id);
	    if (!o) return;
	    var sl = st = 8;
	    var s_l = Math.abs(l0 - l);
	    var s_t = Math.abs(t0 - t);
	    if (s_l - s_t > 0)
		    if (s_t)
			    sl = Math.round(s_l / s_t) > 8 ? 8 : Math.round(s_l / s_t) * 6;
		    else
			    sl = 0;
	    else
		    if (s_l)
		    	st = Math.round(s_t / s_l) > 8 ? 8 : Math.round(s_t / s_l) * 6;
		    else
			    st = 0;
	    if (l0 - l < 0) sl *= -1;
	    if (t0 - t < 0) st *= -1;
	    if (Math.abs(l + sl - l0) < 52 && sl) sl = sl > 0 ? 2 : -2;
	    if (Math.abs(t + st - t0) < 52 && st) st = st > 0 ? 2 : -2;
	    if (Math.abs(l + sl - l0) < 16 && sl) sl = sl > 0 ? 1 : -1;
	    if (Math.abs(t + st - t0) < 16 && st) st = st > 0 ? 1 : -1;
	    if (s_l == 0 && s_t == 0) return;
	    if (Math.abs(l + sl - l0) < 2)
		    o.style.left = l0 +"px";
	    else
		    o.style.left = l + sl +"px";
	    if (Math.abs(t + st - t0) < 2) 
		    o.style.top = t0 +"px";
	    else
		    o.style.top = t + st +"px";
	    window["ct"+ Id] = window.setTimeout("MyWin.Move_e('"+ Id +"', "+ l0 +" , "+ t0 +", "+ (l + sl) +", "+ (t + st) +")", 1);
    }
    this.Resize_e = function(Id, w0, h0, w, h)
    {
	    if (typeof(window["dt"+ Id]) != "undefined") clearTimeout(window["dt"+ Id]);
	    if (Id == null) return;
		var o = $(Id);
	    if (!o) return;
	    var sw = sh = 14;
	    var s_w = Math.abs(w0 - w);
	    var s_h = Math.abs(h0 - h);
	    if (s_w - s_h > 0)
		    if (s_w)
			    sh = Math.round(s_h / s_w) > 8 ? 8 : Math.round(s_h / s_w) * 14;
		    else
			    sh = 0;
	    else
		    if (s_h)
			    sw = Math.round(s_w / s_h) > 8 ? 8 : Math.round(s_w / s_h) * 14;
		    else
			    sw = 0;
	    if (w0 - w < 0) sw *= -1;
	    if (h0 - h < 0) sh *= -1;
	    if (Math.abs(w + sw - w0) < 117 && sw) sw = sw > 0 ? 6 : -6;
	    if (Math.abs(h + sh - h0) < 117 && sh) sh = sh > 0 ? 6 : -6;
	    if (Math.abs(w + sw - w0) < 12 && sw) sw = sw > 0 ? 1 : -1;
	    if (Math.abs(h + sh - h0) < 12 && sh) sh = sh > 0 ? 1 : -1;
	    if (s_w == 0 && s_h == 0) 
	    {
		    this.Show(Id);
		    return;
	    }
	    var xw = xh = 0;
	    if (Math.abs(w + sw - w0) < 2)
	    {
		    xw = w0;
	    }
	    else
		    xw = w + sw;
	    if (Math.abs(h + sh - h0) < 2) 
		    xh = h0;
	    else
		    xh = h + sh;
	    o.style.height = xh +"px";
	    o.childNodes[1].childNodes[0].style.height = (xh - 45) +"px";
	    o.childNodes[1].childNodes[1].style.height = (xh - 47) +"px";
	    o.childNodes[1].childNodes[2].style.height = (xh - 45) +"px";
	    o.style.width = xw +"px";
        o.childNodes[0].childNodes[1].style.width = (xw - 30) +"px";
    	o.childNodes[2].childNodes[1].style.width = (xw - 30) +"px";
	    o.childNodes[1].childNodes[1].style.width = (xw - 32) +"px";
	    window["dt"+ Id] = window.setTimeout("MyWin.Resize_e('"+ Id +"', "+ w0 +" , "+ h0 +", "+ (w + sw) +", "+ (h + sh) +")", 1);
    }
    this.Close = function(Id, Opacity)
    {
	    if (typeof(window["et"+ Id]) != "undefined") clearTimeout(window["et"+ Id]);
	    var o = $(Id);
	    if (!o) return;
	    if (Opacity == 100) o.childNodes[0].childNodes[1].innerHTML = "";
	    if (Ie)
	    {
		    o.style.filter = "alpha(opacity="+ Opacity +",style=0)";
	    }
	    else
	    {
		    o.style.opacity = Opacity / 100;
	    }
	    if (Opacity > 20)
		    Opacity -= 10;
	    else
		    Opacity--;
	    if (Opacity <= 0)
	    {
	        //é‡Šæ”¾IFRAMEï¼Œå¦åˆ™ä¼šé€ æˆè¾“å…¥æ ç„¦ç‚¹ä¸¢å¤±æƒ…å†µ
	        if (o.getElementsByTagName("IFRAME").length != 0)
	        {
	            o.getElementsByTagName("IFRAME").src = "about:blank";
	        }
	        o.innerHTML = "";
		    document.body.removeChild(o);
		    return;
	    }
	    window["et"+ Id] = window.setTimeout("MyWin.Close('"+ Id +"', "+ Opacity +")", 10);
    }
    this.Min = function(Id)
    {
	    var o = $(Id);
	    if (!o) return;
	    var State = o.getAttribute("Min");
	    var l = o.offsetLeft;
	    var t = o.offsetTop;	
    	var w = o.offsetWidth;
	    var h = o.offsetHeight;	
	    if (State == 0)
	    {
	        //è¿™é‡Œè¦å¾—åˆ°ä»»åŠ¡æ ä¸Šçš„ä½ç½®
		    this.Move_e(Id, 0 , 0, l, t);
		    this.Resize_e(Id, 220, 65, w, h);
		    o.setAttribute("Min", l +","+ t +","+ w +","+ h);
	    }
	    else
	    {
		    State = State.split(",");
		    this.Move_e(Id, State[0] , State[1], l, t);
		    this.Resize_e(Id, State[2], State[3], w, h);
		    o.setAttribute("Min", 0);
	    }
    }
    this.Max = function(Id, This)
    {
	    var o = $(Id);
	    if (!o) return;
	    if (o.getAttribute("Min") != 0) return;
	    var State = o.getAttribute("Max");
	    var l = o.offsetLeft;
	    var t = o.offsetTop;
	    var w = o.offsetWidth;
	    var h = o.offsetHeight;
	    if (State == 0)
	    {		
		    this.Move_e(Id, 0 , 0, l, t);
		    this.Resize_e(Id, document.documentElement.clientWidth, document.documentElement.clientHeight - 28, w, h);
	    	o.setAttribute("Max", l +","+ t +","+ w +","+ h);
		    This.title = "æ¢å¤";
	    }
	    else
	    {
		    State = State.split(",");
		    this.Move_e(Id, State[0] , State[1], l, t);
		    this.Resize_e(Id, State[2], State[3], w, h);
		    o.setAttribute("Max", 0);
		    This.title = "æœ€å¤§åŒ–";
	    }
    }
}
var MyWin = new Win();
