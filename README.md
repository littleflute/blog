## Xd Demo
<div id="debug"></div>
<div id="demo">
<h2>The XMLHttpRequest Object</h2>
<button type="button" onclick="loadDoc(songSrc(1))">Change Content</button>
</div>

## [Home](https://littleflute.github.io/blog/) 

##[docs](https://littleflute.github.io/blog/docs)
 
## Welcome to GitHub Pages

You can use the [editor on GitHub](https://github.com/littleflute/blog/edit/master/README.md) to maintain and preview the content for your website in Markdown files.

Whenever you commit to this repository, GitHub Pages will run [Jekyll](https://jekyllrb.com/) to rebuild the pages in your site, from the content in your Markdown files.

### Markdown

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/littleflute/blog/settings). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://help.github.com/categories/github-pages-basics/) or [contact support](https://github.com/contact) and we’ll help you sort it out.


<!-- xd script-->
<script>
var x = document.getElementsByTagName("h1")[0];
x.innerHTML = "LittleFlute's Blog V0.2.0";
var b	= document.getElementById("banner");
var s = b.innerHTML;
s += "<a href='docs' class='button downloads'>docs</a>";
s += "<a href='html' class='button downloads'>html</a>";
b.innerHTML = s;

var gN   = 0;
var gStr = "";
function songSrc(n)
{
    var s = "html/songs/s00" + n + ".html";
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
         gStr += src;
         gStr += "%<br%>";
         document.getElementById("demo").innerHTML = gStr;
      }
     //*/
    }
  };
  xhttp.open("GET", src, true);
  xhttp.send();
}

</script>
<!-- end xd script-->
