var myMoveDiv = {};
myMoveDiv.inf = function(){
	var v_blDraggableDIV = "v0.1.0";
	var i2do  ="DraggableDIV";
	var s = v_blDraggableDIV;
	s += "\r\n";
	s += i2do;
    var show = function()
    {
    	alert(s);
    }
    show();
}; 
myMoveDiv.blDiv = function (oBoss,id,html){
    var r = document.getElementById(id);
    if(!r){
        r = document.createElement("div");
        r.id = id; 
    }
    r.innerHTML = html; 
     
    oBoss.appendChild(r);
    return r;
} 
myMoveDiv.blBtn = function (oBoss,id,html){
    var r = document.getElementById(id);
    if(!r){
        r = document.createElement("button");
        r.id = id; 
    }
    r.innerHTML = html; 
     
    oBoss.appendChild(r);
    return r;
}
myMoveDiv.blLink = function (oBoss,id,html,href,bkClr){
        var r = document.getElementById(id);
        if(!r){
            r = document.createElement("a");
    	    var t = document.createTextNode(html);
    	    r.setAttribute("href", href);
    	    r.setAttribute("target", "_blank");
            r.id = id; 
    	    r.style.backgroundColor = bkClr?bkClr:"blue";
        }
        r.innerHTML = html; 
        oBoss.appendChild(r);
        return r;
    }
myMoveDiv.showObj2Div = function (oDivBoss,obj)
    {
        
        var oBoss = oDivBoss;
        if(!oBoss) {
           oBoss = document.createElement("div");
           oBoss.id = "divBlShowObj";
           oBoss.style.border = "green 1px solid";
           document.body.appendChild(oBoss);
        } 
        if(!oBoss){
            alert("boss error!");return;
        }
      //  oBoss.innerHTML = "";
        for(i in obj)
        {
          var b = document.createElement("button");
          b.id = b.innerHTML = i;
          if(i[0]=="b"&&i[1]=="l") b.style.backgroundColor = "yellow";
          oBoss.appendChild(b);
          var d = document.createElement("div");
          d.innerHTML = obj[i];
          d.style.border = "blue 1px solid";
          d.style.backgroundColor = "green";
          d.style.color = "yellow";
          oBoss.appendChild(d);
        }
    }  
//Make the DIV element draggagle: 

myMoveDiv.dragElement = function (elmnt) {
  var pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
  if (document.getElementById(elmnt.id + "header")) {
    /* if present, the header is where you move the DIV from:*/
    document.getElementById(elmnt.id + "header").onmousedown = dragMouseDown;
  } else {
    /* otherwise, move the DIV from anywhere inside the DIV:*/
    elmnt.onmousedown = dragMouseDown;
  }

  function dragMouseDown(e) {
    e = e || window.event;
    // get the mouse cursor position at startup:
    pos3 = e.clientX;
    pos4 = e.clientY;
    document.onmouseup = closeDragElement;
    // call a function whenever the cursor moves:
    document.onmousemove = elementDrag;
  }

  function elementDrag(e) {
    e = e || window.event;
    // calculate the new cursor position:
    pos1 = pos3 - e.clientX;
    pos2 = pos4 - e.clientY;
    pos3 = e.clientX;
    pos4 = e.clientY;
    // set the element's new position:
    elmnt.style.top = (elmnt.offsetTop - pos2) + "px";
    elmnt.style.left = (elmnt.offsetLeft - pos1) + "px";
  }

  function closeDragElement() {
    /* stop moving when mouse button is released:*/
    document.onmouseup = null;
    document.onmousemove = null;
  }
}
myMoveDiv.run = function()
{
	var main = myMoveDiv.blDiv(document.body,"moveDivBody","");
	var win = myMoveDiv.blDiv(document.body,"win","myMoveDiv");
    
	var av = myMoveDiv.blLink (win,"av","v0.0.5","https://github.com/littleflute/blog/edit/master/js/blDraggableDIV.js","#fb3"); 
	var a1 = myMoveDiv.blLink (win,"a1","dev1","http://www.w3school.com.cn/tiy/t.asp?f=ajax_get","#abc");
	var a2 = myMoveDiv.blLink (win,"a2","dev2","http://www.w3school.com.cn/tiy/t.asp?f=ajax_get","#fab");
myMoveDiv.showObj2Div(win,this);

	var style ="position: absolute;";
	style += "z-index: 9;";
	style += "background-color: #f1f1f1;";
	style += "text-align: center;";
	style += "border: 1px solid #d3d3d3;";
	style += "left: 400px";
	style += "top: 140px";
	main.style =style;
	var title = myMoveDiv.blDiv(main,"moveDivHeader","header");
	style ="padding: 10px;";
	style += "z-index: 10;";
	style += "cursor: move;";
	style += "text-align: center;";
	style += "border: 1px solid #fff;";
	style += "background-color: #2196F3;";
	title.style =style;
	var d1 = myMoveDiv.blDiv(main,"d1","d1");
	var d2 = myMoveDiv.blDiv(main,"d2","d2");
	var btn1 = myMoveDiv.blBtn(d2,"btn1","about");
	btn1.onclick = function(){ 
    	myMoveDiv.inf();
	}
    myMoveDiv.dragElement(main);
}
myMoveDiv.run();
