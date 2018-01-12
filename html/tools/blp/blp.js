var v = "v0.0.21" 
var dUI = blo0.blMDiv(document.body,"id_mdiv_blplayer","blplayer::",500,300,500,800,blColor[1]);  
dUI.d1 = blo0.blDiv(dUI,dUI.id+"d1","d1",blGrey[0]);

dUI.d1.ta = blo0.blTextarea(dUI.d1, "id_ta_4_run" , "alert(1);" , blGrey[3]);
dUI.d1.ta.style.width = "98%";
dUI.d1.ta.style.height = "200px";
dUI.d1.btnRun = blo0.blBtn(dUI.d1,"id_btn_run","run","green");
dUI.d1.btnRun.onclick = function(){
  eval(dUI.d1.ta.value);
}
      
