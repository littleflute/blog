// JavaScript Document

//CapsLockçŠ¶æ€
var _capslk			= 0;		//Caps LockçŠ¶æ€
var art_line		= 1;		//å½“å‰æ˜¾ç¤ºæ•°ç»„
var art_num			= 0;		//å½“å‰æ•°ç»„ä¸­è‡ªå·±ä¸ªå­—
var last_code		= 0;		//æœ€åŽä¸€ä¸ªé”™è¯¯code
var start_time		= 0;		//å¼€å§‹æ—¶é—´
var time_cha		= 0;		//æ—¶é—´å·®æ¯«ç§’æ•°
var typing_num		= 0; 		//æ‰“å­—æ€»æ•°
var all_num			= 0; 		//æ‰“å­—æ€»æ•°
var error_num		= 0; 		//é”™è¯¯å­—æ•°
var right_num		= '--';		//åˆå§‹æ­£ç¡®çŽ‡
var jindu			= 0;		//åˆå§‹è¿›åº¦
var sudu_num		= '--';		//åˆå§‹é€Ÿåº¦
var _jishi			= null;		//è®¡æ—¶æ ‡è®°
//charCodeAt(0)

//alert(key_data);
if(key_data !=''){
	show_key();
	jishi();
	for(var i=1; i<key_data.length; i++){
		all_num	+=key_data[i].length;
	}
}

//è®¡æ—¶
function jishi(){
	if(start_time >0){
		time_cha	= get_time()-start_time;
		sudu_num	= Math.round(typing_num/time_cha*60000);
	}
	if(typing_num >0){
		right_num	= Math.round((1-error_num/typing_num)*10000)/100;
		jindu		= Math.round((typing_num-error_num)/all_num*10000)/100;
	}
	document.getElementById('shijian').innerHTML = 'æ—¶é—´ï¼š'+get_date(time_cha);
	document.getElementById('sudu').innerHTML = 'é€Ÿåº¦ï¼š'+sudu_num+' KMP';
	document.getElementById('right_num').innerHTML = 'æ­£ç¡®çŽ‡ï¼š'+right_num+' %';
	document.getElementById('jindu').innerHTML = 'è¿›åº¦ï¼š'+jindu+' %';
	_jishi	= setTimeout("jishi()",100);
}

//æ ¼å¼åŒ–æ—¶é—´
function get_date(time){
	var t	= new Date(time);
	return t.getMinutes()+'åˆ†'+t.getSeconds()+'ç§’';
}

//èŽ·å–æ—¶é—´æˆ³
function get_time(){
	var t		= new Date();
	return t.getTime();
}

//æ˜¾ç¤ºé”®ç›˜æŒ‰é”®
function show_key(){
	if(key_data[art_line]){
		var key_code	= key_data[art_line].charCodeAt(art_num);
		show_text();
		set_on(key_code,'on',1);
		set_shift(key_code);		//è®¾ç½®SHIFT
	}else{
		clearTimeout(_jishi);
		var art_text	= document.getElementById('art_text');
		art_text.style.paddingLeft = '0px';
		art_text.innerHTML='<h3>O(âˆ©_âˆ©)Oå“ˆå“ˆ~ æ­å–œä½ å·²ç»å®Œæˆæœ¬æ¬¡æµ‹è¯•ï¼</h3>';
		document.getElementById('jindu').innerHTML = 'è¿›åº¦ï¼š100 %';
	}
}

//æ˜¾ç¤ºé€Ÿåº¦ï¼Œè¿›åº¦ï¼Œæ­£ç¡®çŽ‡ç­‰
function show_sudu(){
	var shijian	= document.getElementById('shijian');
}

//è®¾ç½®shiftçŠ¶æ€
function set_shift(code){
	var left	= /^(126|33|64|35|36|37|81|87|69|82|84|65|83|68|70|71|90|88|67|86|66)$/;
	var right	= /^(94|38|42|40|41|95|43|89|85|73|79|80|123|125|124|72|74|75|76|58|34|78|77|60|62|63)$/;
	set_on('991',null);
	set_on('992',null);
	if(code >=97 && code <=122){
		//å°å†™å­—æ¯
		if(_capslk ==1){
			code -=32;
			if(left.test(code)){
				set_on('992','on',1);
			}else if(right.test(code)){
				set_on('991','on',1);
			}
		}
	}else if(code >=65 && code <=90){
		//å¤§å†™å­—æ¯
		if(_capslk !=1){
			if(left.test(code)){
				set_on('992','on',1);
			}else if(right.test(code)){
				set_on('991','on',1);
			}
		}
	}else{
		if(left.test(code)){
			set_on('992','on',1);
		}else if(right.test(code)){
			set_on('991','on',1);
		}
	}
}

//æ˜¾ç¤ºæ–‡æœ¬
function show_text(){
	if(key_data[art_line]){
		var art_text	= document.getElementById('art_text');
		art_text.style.paddingLeft = Math.round((990-key_data[art_line].length*65)/2)+'px';
		var data_html	= '';
		for(var i=0; i<key_data[art_line].length; i++){
			data_html += '<div class="b_'+(i==art_num?'on':'alt')+'"><ul><li>'+key_data[art_line].substr(i,1)+'</li></ul></div>';
		}
		art_text.innerHTML = data_html;
	}
}

//èŽ·å–æŒ‰é”®Code
function checkKey(evt) {
	if(key_data[art_line]){
		var code =  get_keyCode(evt);
		var key_code	= key_data[art_line].charCodeAt(art_num);
		//è®¡æ—¶
		if(start_time ==0){
			start_time	= get_time();
		}
		set_on(last_code,null);
		last_code	= 0;
		typing_num++;
		if(code == key_code){
			//æ­£ç¡®
			set_on(code,null);
			if(art_num < key_data[art_line].length-1){
				art_num++;
			}else{
				art_num=0;
				art_line++;
			}
		}else{
			//é”™è¯¯
			error_num++;
			if(code_code(code) != code_code(key_code)){
				last_code	= code;
				set_on(code,'err',1);
			}
		}
		show_key();
	}
	return false;
}


//æ£€æŸ¥é”®ç›˜æŒ‰ä¸‹
function checkDown(evt){
	var evt = evt ? evt : (window.event ? window.event : null);
	var code = evt.which ? evt.which :evt.keyCode;
	if(code == 8 || code == 9|| code == 32){
		//ç¦æ­¢BackSpace Tab ç©ºæ ¼
		checkKey(evt);
		return false;
	}
	if(code == 20){
		if(_capslk == 1){
			_capslk = 0;
			set_on(20,null);
		}else{
			_capslk = 1;
			set_on(20,'on',1)
		}
	}
}

//èŽ·å–æŒ‰é”®codeï¼Œå¹¶è®¾ç½®CapsLockçŠ¶æ€
function get_keyCode(evt){
	var evt = evt ? evt : (window.event ? window.event : null);
	var code = evt.which ? evt.which :evt.keyCode;
	var valueShiftã€€= evt.shiftKey ? evt.shiftKey:((codeã€€== ã€€16 ) ? true : false );
	//è®¾ç½®CapsLockçŠ¶æ€
	if((code >=65 && code <=90 && !valueShift)||(code >=97 && code <=122 && valueShift)){
		_capslk	= 1;
		set_on(20,'on',1);
	}else if((code >=65 && code <=90)||(code >=97 && code <=122)){
		_capslk	= 0;
		set_on(20,null);
	}
	return code;
}

//è®¾ç½®æŒ‰é”®é¢œè‰²
function set_on(key_code,on,keep){
	key_code	= code_code(key_code);
	var a = document.getElementById('a_'+key_code);
	if(on == 'on' ||on == 'err'){
		if(a){
			if(on == 'on'){
				var class_test = /(_on)+$/i;
				if(!class_test.test(a.className)){
					a.className += '_on';
				}
			}else{
				var class_test = /(_err)+$/i;
				if(!class_test.test(a.className)){
					a.className += '_err';
				}
			}
			if(!keep){
				setTimeout(function(){set_on(key_code,null)},150);
			}
		}
	}else{
		if(a){
			a.className = a.className.replace(/(_on|_err)+$/i,'');
		}
	}
	return true;
}

//å°†ä¸¤é”®ä½codeè½¬æ¢ä¸ºä¸€ä¸ª
function code_code(key_code){
	if(key_code >=65 && key_code <=90){
		key_code += 32;
	}
	var replace_1	= new Array(126	,33	,64	,35	,36	,37	,94	,38	,42	,40	,41	,95	,43	,60	,62	,63	,58	,34	,123,125,124)
	var replace_2	= new Array(96	,49	,50	,51	,52	,53	,54	,55	,56	,57	,48	,45	,61	,44	,46	,47	,59	,39	,91	,93	,92);
	for(var i=0; i<replace_1.length; i++){
		key_code = key_code == replace_1[i] ? replace_2[i]:key_code;
	}
	return key_code;
}

//è·³è½¬èœå•
function MM_jumpMenu(obj){ //v3.0
  document.location = obj.value;
}
