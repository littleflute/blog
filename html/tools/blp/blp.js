var v = "v0.0.31" 
var s0 = '<div id="id_div_toolbar">';
  s0 += '<a target="_blank" href="blp.js">' + v + '</a>-';
  s0 += '<a target="_blank" href="https://github.com/littleflute/blog/edit/master/html/tools/blp/blp.js">' + v + '*</a>';
  s0 += '</div>';

var dUI = blo0.blMDiv(document.body,"id_mdiv_blplayer",s0,650,200,500,800,blColor[2]);  
dUI.d1 = blo0.blDiv(dUI,dUI.id+"d1","d1",blGrey[0]);

dUI.d1.ta = blo0.blTextarea(dUI.d1, "id_ta_4_run" , "alert(1);" , blGrey[3]);
dUI.d1.ta.style.width = "98%";
dUI.d1.ta.style.height = "200px";
dUI.d1.btnRun = blo0.blBtn(dUI.d1,"id_btn_run","run","green");
dUI.d1.btnRun.onclick = function(){
  eval(dUI.d1.ta.value);
}
      

dUI.d1.btnLoadList = blo0.blBtn(dUI.d1,"id_btn_LoadList","run","green");
dUI.d1.btnLoadList.onclick = function(){
  dUI.d1.ta.value = 'blo0.blScript("id_script_list","list.js")';
  eval(dUI.d1.ta.value);
}
      
