var v = "v0.0.3"; 
var s0 = '<div id="id_div_list_toolbar">';
 s0 += '<a target="_blank" href="list.js">' + v + '</a>-';
  s0 += '<a target="_blank" href="https://github.com/littleflute/blog/edit/master/html/tools/blp/list.js">' + v + '*</a>';
  s0 += '</div>';

var listUI= blo0.blMDiv(document.body,"id_mdiv_list5",s0,50,200,500,800,blColor[5]); 
listUI.tb = bl$('id_div_list_toolbar');
listUI.tb.b1 = blo0.blBtn(listUI.tb,listUI.tb.id+"b1","b1","grey"); 
listUI.tb.b1.onclick = function(){
    this.parentElement.parentElement.style.backgroundColor="gray";
}
