var v_blDraggableDIV = "v0.0.6";
var i2do  ="DraggableDIV";
var s = v_blDraggableDIV;
s += "\r\n";
s += i2do;
 
var myMoveDiv = {}; 
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
var main = myMoveDiv.blDiv(document.body,"moveDivBody","");
var style ="position: absolute;";
style += "z-index: 9;";
style += "background-color: #f1f1f1;";
style += "text-align: center;";
style += "border: 1px solid #d3d3d3;";
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
dragElement(main);


//Make the DIV element draggagle: 

function dragElement(elmnt) {
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
