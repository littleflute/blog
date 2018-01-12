var s = "<div id='id_div_list_toolbar'></div>";
var listUI= blo0.blMDiv(document.body,"id_mdiv_list5",s,50,200,500,800,blColor[5]); 
listUI.tb = bl$('id_div_list_toolbar');
listUI.tb.b1 = blo0.blBtn(listUI.tb,listUI.tb.id+"b1","b1","grey"); 
listUI.tb.b1.onclick = function(){
    this.parentElement.parentElement.style.backgroundColor="red";
}
