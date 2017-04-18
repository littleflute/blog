<!DOCTYPE html>
<html>
<body>
<style>
.borderRed{
	border:1px solid red;
}
.borderGreen{
	border:1px solid green;
}
.borderBlue{
	border:1px solid blue;
}
.xdwh1{
	width:500px;height:100px;
}
.xdwh2{
	width:500px;height:100px;
}
</style>
<script>
 function myFunction() {
	eval(document.getElementById("s").value);
}
function myCopy() {
    var s = document.getElementById("sample");
    var me = document.getElementById("s");
    me.value = s.innerHTML;
}
function myClear(id) {
    var o = document.getElementById(id);
    o.value = "";
}
</script>

<p>Javascript实时运行器 jsr:1.0.7</p>
<button onclick="myFunction()">Run</button>
<button onclick="myCopy()">Sample</button>
<button onclick="myClear('s')">清空</button><br>
<textarea id="s" class="borderGreen xdwh1"></textarea>
<p id="demo" class="borderBlue xdwh2"></p>
<p id="demo1" class="borderRed xdwh2"></p>

<div id="sample">
//<br>
function f1(a,b)//<br>
{//<br>
	return a+b;//<br>
}//<br>
var me = document.getElementById("s");//<br>
var d1 = document.getElementById("demo1");//<br>
var d = document.getElementById("demo");//<br>
d1.innerHTML=s.value;//<br>
d.innerHTML = f1(1,2);//<br>
</div>
</body>
</html>
