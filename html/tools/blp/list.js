var v = "v0.0.13"; 
function _listClass(){
 var ls = [];
 ls.push("https://littleflute.github.io/bible/ABibleExperience/NewTestament/list.js");
 ls.push("https://littleflute.github.io/bible/ABibleExperience/NewTestament/list.js");
 this.v = "v0.0.3";
 this.blr_List1 = function(b,d){
  d.innerHTML = ;
  if(!d.view){
    d.tb = blo0.blDiv(listUI,listUI.id+"tb","tb:",blColor[4]);
    d.view = blo0.blDiv(listUI,listUI.id+"view","view:",blColor[4]);
    for(i in ls){
       var b = blo0.blBtn(d.tb,d.tb.id+"btn_"+i,"list"+i,blGrey[0]);
       b.onclick = function(_s){
            return function(){
                d.view.innerHTML = _s;
            }
       }(ls[i]);
    }
  }
  _on_off_div(b,d);
 }
}
var l = new _listClass;

var s0 = '<div id="id_div_list_toolbar">';
 s0 += '<a target="_blank" href="list.js">' + v + '</a>-';
  s0 += '<a target="_blank" href="https://github.com/littleflute/blog/edit/master/html/tools/blp/list.js">' + v + '*</a>';
  s0 += '</div>';

var listUI= blo0.blMDiv(document.body,"id_mdiv_list5",s0,50,200,500,800,blColor[5]); 
listUI.view = blo0.blDiv(listUI,listUI.id+"view","view:",blColor[4]);
listUI.tb = bl$('id_div_list_toolbar');
listUI.tb.b1 = blo0.blBtn(listUI.tb,listUI.tb.id+"b1","b1","grey"); 
listUI.tb.b1.onclick = function(){
    blo0.blShowObj2Div(listUI.view,l);
}
