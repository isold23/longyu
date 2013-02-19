<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <title>&#40857;&#23431;&#32593;-&#36335;&#28459;&#28459;&#20854;&#20462;&#36828;&#20846;&#65292;&#21566;&#23558;&#19978;&#19979;&#32780;&#27714;&#32034;</title>
  <link rel="icon" href="images/favicon.ico" type="image/x-icon" />
  <link rel="shortcut icon" href="images/favicon.ico" type="image/x-icon" /> 
  <link href="res/longyunet.css" type="text/css" rel="stylesheet" />
  <script type="text/javascript" language="javascript" src="res/jquery.js"></script>
  <script type="text/javascript" src="http://cloud.github.com/downloads/malsup/cycle/jquery.cycle.all.2.72.js"></script>


  <script type="text/javascript"> 
$(document).ready(function(){

  $("ul.subnav").parent().append("<span></span>"); //Only shows drop down trigger when js is enabled - Adds empty span tag after ul.subnav
  
  $("ul.topnav li span").hover(function() { //When trigger is clicked...
    
    //Following events are applied to the subnav itself (moving subnav up and down)
    $(this).parent().find("ul.subnav").slideDown('fast').show(); //Drop down the subnav on click

    $(this).parent().hover(function() {
    }, function(){  
      $(this).parent().find("ul.subnav").slideUp('slow'); //When the mouse hovers out of the subnav, move it back up
    });

    //Following events are applied to the trigger (Hover events for the trigger)
    }).hover(function() { 
      $(this).addClass("subhover"); //On hover over, add class "subhover"
    }, function(){  //On Hover Out
      $(this).removeClass("subhover"); //On hover out, remove class "subhover"
  });

});
</script>
<script type="text/javascript">
$(function() {
    $('#slideshow').cycle({
        fx:     'all',
        speed:  'fast',
        timeout: 3000,
        pager:  '#nav',
		slideExpr: 'img'
    });
});
</script>

<script>

$(document).ready(function() {	

	//select all the a tag with name equal to modal
	$('a[name=modal]').click(function(e) {
		//Cancel the link behavior
		e.preventDefault();
		
		//Get the A tag
		var id = $(this).attr('href');
	
		//Get the screen height and width
		var maskHeight = $(document).height();
		var maskWidth = $(window).width();
	
		//Set heigth and width to mask to fill up the whole screen
		$('#mask').css({'width':maskWidth,'height':maskHeight});
		
		//transition effect		
		$('#mask').fadeIn(1000);	
		$('#mask').fadeTo("slow",0.8);	
	
		//Get the window height and width
		var winH = $(window).height();
		var winW = $(window).width();
              
		//Set the popup window to center
		$(id).css('top',  winH/2-$(id).height()/2);
		$(id).css('left', winW/2-$(id).width()/2);
	
		//transition effect
		$(id).fadeIn(2000); 
	
	});
	
	//if close button is clicked
	$('.window .close').click(function (e) {
		//Cancel the link behavior
		e.preventDefault();
		
		$('#mask').hide();
		$('.window').hide();
	});		
	
	//if mask is clicked
	$('#mask').click(function () {
		$(this).hide();
		$('.window').hide();
	});			
	
});

</script>

	<script type="text/javascript">
	  $(document).ready(function(){
			$("#menu-one li").hover(
				function(){ $("ul", this).fadeIn("fast"); }, 
				function() { } 
			);
	  	if (document.all) {
				$("#menu-one li").hoverClass ("sfHover");
			}
	  });
	  
		$.fn.hoverClass = function(c) {
			return this.each(function(){
				$(this).hover( 
					function() { $(this).addClass(c);  },
					function() { $(this).removeClass(c); }
				);
			});
		};	  
	</script>
	    <script type="text/javascript">
	$(function()
	{			
		var $this  =  $("#scroll");
		var start_hand = "url(start_hand.cur),pointer";  
		var end_hand = "url(end_hand.cur),pointer";
		var y = 0;

		$this
			.css({"cursor":start_hand , overflow: "hidden"})
			.mousedown(startDrag)
			.mouseup(endDrag)
			.mouseleave(endDrag);

		function startDrag(e)
		{
			$this.css("cursor", end_hand)
				 .stop(true, false)
				 .mousemove(moveDrag);
			y = e.pageY;
			return false;
		}
		
		function moveDrag(e)
		{
			var pos_y = e.pageY - y;
			$this.animate({scrollTop : "-="+pos_y},20);
			y = e.pageY;
			return true;
		}

		function endDrag(e)
		{
			$this
				.css("cursor", start_hand)
				.unbind("mousemove",moveDrag);
			return true;
		}

	});
	</script>
			<script type="text/javascript">
			$(document).ready(function(){
				//Full Caption Sliding (Hidden to Visible)
				$('.boxgrid.captionfull').hover(function(){
					$(".cover", this).stop().animate({top:'310px'},{queue:false,duration:60});
				}, function() {
					$(".cover", this).stop().animate({top:'310px'},{queue:false,duration:60});
				});
			});
		</script>
</head>
<body>
	<div id="wrapper">
		<div id="page-header">
			<div id = "header-login">
				<div id = "login">
					<?php
					if($_SESSION['user_id']<1) 
					{
						$output='<a href="#logindialog" name="modal">µȂ¼</a>';
					}
					else
					{
						$output='<a href="user.php?act=logout">µǳ�>';
					}
					?>
					&nbsp
					<a href="#regdialog" name="modal">ע²�a>
					&nbsp
					<a href="">°𐗺</a>
				</div>
			</div>
			
			<div id="header-memu">

		  <ul  id="menu-one" class="menu">
		  <li><a href="main.php">˗ҳ</a></li>
		  <li><a href="blog.php">²©¿˼/a>
		    <ul>
		    <li><a href="blog.php">²©¿Ίؒ³</a></li>
		    <li><a href="blog.php">Ά¼�¾</a></li>
		    <li><a href="blog.php">´Ҕ²¾</a></li>
		    </ul>
		  </li>
		  <li><a href="baby.php">¼ӓб¦±´</a></li>
		  <li><a href="#">ºԮɭ¼�/li>
		  <li><a href="daily.php">³ɳ¤ɕ¼ż/a></li>
		  <li><a href="resourcedownload.php">؊Ђ՘</a></li>
		  <li><a href="contactus.php">jϵϒć</a></li>
		</ul>

			</div>
			
						<div id = "header-logo">
				<div id = "logo">
				</div>
				<div id = "search">
				</div>
			</div>
		</div>

<div id="boxes">
<!-- Start of Login Dialog -->  
<div id="logindialog" class="window">
	<form action="admin/admin.php?act=login" method="post">
	<div id="home-item-header">
		<h1>ԃ»§µȂ¼</h1>
		<p><a href="#" class="close">close</a></p>
	</div>
	<div id="home-item-content">
		 <p>ԃ»§Ļ£º<br />
 <input name="username" type="text" id="name" size="25"/></p>
   </p>
 <p>Ĝë£º<br />
    <input name="password" type="password" id="password" size="25" />
   </p>

   <p>
   <input name="safe_url" type="hidden" value="{$safe_url}" /> <input type="submit" name="button" id="button" value="µȂ¼" />
  </p>
	</div>
	</form>
</div>
<!-- End of Login Dialog -->  

<!-- Start of reg Dialog -->  
<div id="regdialog" class="window">
	<div id="home-item-header">
		<h1>тԃ»§ע²�h1>
		<p><a href="#" class="close">close</a></p>
	</div>
	<div id="home-item-content">
		 <p>ԃ»§Ļ£º<br />
  <input name="name" type="text" id="name"  /> <span id="name_notice"></span>
   </p>
   <p>
 Ĝë£º<br />
    <input type="password" name="password" id="password" /> <span id="pass_notice"></span>
  </p>
     <p>
 Ĝëȷɏ£º<br />
    <input type="password" name="re_password" id="re_password" /> <span id="re_pass_notice"></span>
  </p>
   <p>
 EMAIL£º<br />
    <input name="email" type="text" id="email" size="50" /> <span id="email_notice"></span>
  </p>
  <p>
 ¸��ٖ·£º<br />
    <input name="home" type="text" id="home" size="50" />
  </p>

  <p>
    <input type="submit" name="button" id="button" value="ע²�/>
  </p>
	</div>
</div>
<!-- End of reg Dialog -->

<!-- Mask to cover the whole screen -->
  <div id="mask"></div>
</div>
</div>

