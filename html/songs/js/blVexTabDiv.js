var sTB = "<div id='id_div_toolBar'>v0.0.155";
sTB += "</div>";

var md = blo0.blMDiv(document.body,"id_mdiv_4_vextab",sTB,50,50,900,200,blGrey[0]); 
md.tb = bl$('id_div_toolBar');

md.tb.b1 = blo0.blBtn(md.tb,md.tb.id+"b1","b1",blGrey[1]); 
md.tb.b1.onclick = function(){
	var o = this.parentElement;
	if(!o.m1){
		var sTB = "<div id='id_div_toolBar_4_b1'>";
		sTB += "</div>";
		o.m1 = blo0.blMDiv(o,o.id+"mdiv",sTB,110,1,110,10,blGrey[0]); 
		o.m1.style.zIndex = 100;
		o.m1.main.style.display = "none";
		o.m1.handle.style.display = "none";
		o.m1.tb = bl$('id_div_toolBar_4_b1');
		o.m1.tb.b1 = blo0.blBtn(o.m1.tb,o.m1.tb.id+"b1","b1",blGrey[1]); 
		o.m1.tb.b1.onclick = function(){
			var d = this.parentElement.parentElement.parentElement.parentElement; 
			_on_off_div(this,d.main);
			_on_off_div(this,d.handle);		
		}
		o.m1.tb.b1.click();
	}
	_on_off_div(this,o.m1);	
};

md.d1 = blo0.blDiv(md,md.id+"d1","d1",blGrey[1]); 

var s = "";
		s += "<a target='_blank' href='js/blVexTabDiv.js'"
		s += " style='color:green;'";
		s +=">";
		s += " blVexTabDiv.js ";
		s += "</a>"; 
		s += "<a target='_blank' href='https://github.com/littleflute/blog/edit/master/html/songs/js/blVexTabDiv.js'"
		s += " style='color:blue;'";
		s +=">";
		s += " blVexTabDiv.js* ";
		s += "</a>"; 

var s1 = '<div id="div4Vextab" style="border:1px blue solid" class="vex-tabdiv" width=680 scale=1.0 editor="true" editor_width=680 editor_height=130>xd1</div>';
md.d1.innerHTML = s + s1;

bl$('div4Vextab').innerHTML = bl$('myID').innerHTML;


md.tb.b1.click();

