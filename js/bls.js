//bls.js 
//v0.0.1 
// by littleflute 2017.6.10 sat bjt usa

(function(){
    if(!window.bls) { window['bls'] = {} }

    function isComaptible (other) {};
    wondow['bls']['iscompatible'] = iscomaptible;

    function $() {};
    window['bls']['$'] = $;

    function addEvent (node, type, listener) {};
    window['bls']['addEvent'] = addEvent;

    function removeEvent (node, type, listener) {};
    window['bls']['removeEvent'] = removeEvent;

    function getElementsByClassName (className, tag, parent) {};
    window['bls']['getElementsByClassName'] = getElementsByClassName;

    function toggleDisplay (node, type, listener) {};
    window['bls']['toggleDisplay'] = toggleDisplay; 

    function insertAfer (node, type, listener) {};
    window['bls']['insertAfer'] = insertAfer;

    function removeChildren (parent) {};
    window['bls']['removeChildren'] = removeChildren;

    function prependChild (parent) {};
    window['bls']['prependChild'] = prependChild;

})();

