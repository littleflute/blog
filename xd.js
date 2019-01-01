var x = document.getElementsByTagName("h1")[0];
x.innerHTML = " <a target='_blank' href='https://github.com/littleflute/blog/edit/master/xd.js'>LittleFlute's Blog V0.4.13*</a>";
var b	= document.getElementById("banner");
var s = b.innerHTML;
s += "<a href='docs' class='button downloads'>docs</a>";
s += "<a href='html' class='button downloads'>html</a>";
s += "<a href='html/BlShowWeb' class='button downloads'>BlView</a>"; 
s += "<a href='#' onclick='runJS()' class='button downloads'>runJS</a>";
b.innerHTML = s;

function runJS()
{
    var b = bl$("blrToolBar");
    var p = b.parentElement.parentElement;
    p.style.zIndex = 1000;
}

var gN   = 0;
var gStr = "";
function songSrc(n)
{
	gN = n;
    var s = "https://littleflute.github.io/blog/html/songs/s00" + n + ".html";
    return s;
}
function loadDoc(src) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var str = this.responseText;
   //   document.getElementById("demo").innerHTML =str;
      
      //
      var pos = str.indexOf("scale=1.165199");
      
      document.getElementById("debug").innerHTML = pos;
      if(pos !=-1)
      {
         gStr += gN;
         gStr += ": ";
         gStr += "<a href=' ";
		 gStr += src;
         gStr += "'> ";
		 gStr += gN;
		 gStr += "</a>";
         gStr += "<br>";
         document.getElementById("demo").innerHTML = gStr;
		 loadDoc(songSrc(gN+1));

      }
     //*/
    }
  };
  xhttp.open("GET", src, true);
  xhttp.send();
}
 
loadDoc(songSrc(1));
