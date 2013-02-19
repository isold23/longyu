<?php /* Smarty version 2.6.22, created on 2011-10-27 17:12:53
         compiled from header.html */ ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta name="google-site-verification" content="lfjbQk5SKAEgwpNRyX9DsmIG_9eieZ0WFsyWiTJzpLA" />
    <meta name="keywords" content="爱德曼旅游, 肯尼亚, 旅游" />
    <meta name="description" content="<?php echo $this->_tpl_vars['page_title']; ?>
" />
    
    <title><?php echo $this->_tpl_vars['page_title']; ?>
</title>
    	
    
    <link rel="icon" href="<?php echo $this->_tpl_vars['domain']; ?>
<?php echo $this->_tpl_vars['templates_dir']; ?>
images/favicon.ico" type="image/x-icon" />
    <link rel="shortcut icon" href="<?php echo $this->_tpl_vars['domain']; ?>
<?php echo $this->_tpl_vars['templates_dir']; ?>
images/favicon.ico" type="image/x-icon" />
    	
    <link href="<?php echo $this->_tpl_vars['domain']; ?>
<?php echo $this->_tpl_vars['templates_dir']; ?>
style.css" type="text/css" rel="stylesheet" />
	<link rel="stylesheet" type="text/css" href="<?php echo $this->_tpl_vars['domain']; ?>
<?php echo $this->_tpl_vars['templates_dir']; ?>
scrollable-horizontal.css">
	<link rel="stylesheet" type="text/css" href="<?php echo $this->_tpl_vars['domain']; ?>
<?php echo $this->_tpl_vars['templates_dir']; ?>
scrollable-buttons.css">
	<link rel="stylesheet" type="text/css" href="<?php echo $this->_tpl_vars['domain']; ?>
<?php echo $this->_tpl_vars['templates_dir']; ?>
boxed-02.css">
		
	<link rel="alternate" type="application/rss+xml" title="RSS 2.0" href="{$domain}feed.php" />
    
    <script type="text/javascript" language="javascript" src="<?php echo $this->_tpl_vars['domain']; ?>
res/jquery.js"></script>
    <script type="text/javascript" src="<?php echo $this->_tpl_vars['domain']; ?>
res/jquery.cycle.js"></script>
    <script type="text/javascript" src="<?php echo $this->_tpl_vars['domain']; ?>
res/s3Slider.js"></script>
    	
	<script src="<?php echo $this->_tpl_vars['domain']; ?>
res/reflection.js"></script>
		
<script language="javascript" type="text/javascript">
// Load this script when page loads
$(document).ready(function(){

 // Set up a listener so that when anything with a class of 'tab' 
 // is clicked, this function is run.
 $('.tab').click(function () {

  // Remove the 'active' class from the active tab.
  $('#tabs_container > .tabs > li.active')
	  .removeClass('active');
	  
  // Add the 'active' class to the clicked tab.
  $(this).parent().addClass('active');

  // Remove the 'tab_contents_active' class from the visible tab contents.
  $('#tabs_container > .tab_contents_container > div.tab_contents_active')
	  .removeClass('tab_contents_active');

  // Add the 'tab_contents_active' class to the associated tab contents.
  $(this.rel).addClass('tab_contents_active');

 });
});
    </script>
			
		<script type="text/javascript">
    $(document).ready(function() {
        $('#slider1').s3Slider({
            timeOut: 4000 
        });
    });
</script>
    
    <script language="javascript" type="text/javascript">

function AutoResizeImage(maxWidth,maxHeight,objImg){
var img = new Image();
img.src = objImg.src;
var hRatio;
var wRatio;
var Ratio = 1;
var w = img.width;
var h = img.height;
wRatio = maxWidth / w;
hRatio = maxHeight / h;
if (maxWidth ==0 && maxHeight==0){
Ratio = 1;
}else if (maxWidth==0){//
if (hRatio<1) Ratio = hRatio;
}else if (maxHeight==0){
if (wRatio<1) Ratio = wRatio;
}else if (wRatio<1 || hRatio<1){
Ratio = (wRatio<=hRatio?wRatio:hRatio);
}
if (Ratio<1){
w = w * Ratio;
h = h * Ratio;
}
objImg.height = h;
objImg.width = w;
objImg.style.marginTop = ((maxHeight-objImg.height)/2)+"px";
}

</script>




    
</head>
<body>
				<div id="top">
        <div id="header">
            <div id="login">
            	<div id="language">
            		<a href="main.php?lan=cn">中文</a>
            		&nbsp&nbsp
            		<a href="main.php?lan=en">English</a>
            	</div>
                <div id="login-item">
                    <?php if ($this->_tpl_vars['user_id'] == -1): ?> <a href="#logindialog" name="modal"><?php echo $this->_tpl_vars['login']; ?>
</a> &nbsp&nbsp| <?php else: ?> <span><?php echo $this->_tpl_vars['welcome']; ?>
</span>&nbsp <?php echo $this->_tpl_vars['user_name']; ?>
 &nbsp&nbsp <a href="user.php?lan=cn&act=logout"><?php echo $this->_tpl_vars['logout']; ?>
</a> &nbsp&nbsp| <?php endif; ?> &nbsp 
                    <?php if ($this->_tpl_vars['user_id'] == -1): ?> <a href="#regdialog" name="modal"><?php echo $this->_tpl_vars['register']; ?>
</a> &nbsp&nbsp| <?php else: ?> <a href="user.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
&act=profile"><?php echo $this->_tpl_vars['user_info']; ?>
</a> &nbsp&nbsp| <?php endif; ?> &nbsp
                        	<a href="javascript:;" onclick="javascript:addfavor('http://www.erdemannsafari.com','<?php echo $this->_tpl_vars['web_name']; ?>
');"><?php echo $this->_tpl_vars['bookmark']; ?>
</a>&nbsp&nbsp&nbsp|&nbsp&nbsp
                        	<a href="#helpdialog" name="modal""><?php echo $this->_tpl_vars['help']; ?>
</a>
                </div>
                <!--end login-item-->
            </div>
            <!--end login-->
            <div id="logo-item">
                <div id="logo">
   
                </div>
            </div>
            <!--end log-item-->
                        <div id="menu-item">
                <ul id="menu-one" class="menu">
                    <li><a href="main.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
"><?php echo $this->_tpl_vars['menu_home']; ?>
</a></li>
                    <li><a href="about.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
"><?php echo $this->_tpl_vars['menu_about_us']; ?>
</a></li>
                    <li><a href="blog.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
&cat=3"><?php echo $this->_tpl_vars['menu_travel_blog']; ?>
</a></li>
                    <li><a href="resource.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
&cat=10"><?php echo $this->_tpl_vars['menu_destinations']; ?>
</a></li>
                    <li><a href="resource.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
&cat=11"><?php echo $this->_tpl_vars['menu_tours']; ?>
</a></li>
                    <li><a href="blog.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
&cat=4"><?php echo $this->_tpl_vars['menu_advice']; ?>
</a></li>
                    <li><a href="message.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
"><?php echo $this->_tpl_vars['menu_message']; ?>
</a></li>
                    <li><a href="contactus.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
"><?php echo $this->_tpl_vars['menu_contact_us']; ?>
</a></li>
                </ul>
                                <div id="hot_line">
                	<?php echo $this->_tpl_vars['hot_line_key']; ?>
：<?php echo $this->_tpl_vars['hot_line']; ?>

                </div>
            </div>
            <!--end menu-item-->
        </div>
        <!--end header-->
      </div>
      <!--end top-->
        <div id="boxes">
            <!-- Start of Login Dialog -->
            <div id="logindialog" class="window">
                <form action="user.php?act=act_login" method="post">
                <div class="unit-header unit_header3">
                    <h1 class="unit_header">
                        <?php echo $this->_tpl_vars['login']; ?>
</h1>
                    <h2 class="unit_header">
                        <a href="#" class="close">close</a></h2>
                </div>
                <div class="unit-body">
                    <p>
                        <?php echo $this->_tpl_vars['user_name_key']; ?>
: <br />
                        <input name="name" type="text" id="name" size="25" />
                    </p>
                    <p>
                        <?php echo $this->_tpl_vars['user_password_key']; ?>
: <br />
                        <input name="password" type="password" id="password" size="25" />
                    </p>
                    <p>
                        <input name="safe_url" type="hidden" value="<?php echo $this->_tpl_vars['safe_url']; ?>
" />
                        <input type="submit" name="button" id="button" value="<?php echo $this->_tpl_vars['login']; ?>
" />
                    </p>
                </div>
                </form>
            </div>
            <!-- End of Login Dialog -->
            <!-- Start of reg Dialog -->
            <div id="regdialog" class="window">
            <form action="user.php?act=act_reg" method="post">
            	
                <div class="unit-header unit_header3">
                    <h1 class="unit_header">
                        <?php echo $this->_tpl_vars['register']; ?>
</h1>
                    <h2 class="unit_header">
                        <a href="#" class="close">close</a></h2>
                </div>
                <div class="unit-body">
                    <p>
                        <?php echo $this->_tpl_vars['user_name_key']; ?>
: <br />
                        <input name="user_name" type="text" id="user_name" />
                    </p>
                    <p>
                        <?php echo $this->_tpl_vars['user_password_key']; ?>
: <br />
                        <input type="password" name="password" id="password" />
                    </p>
                    <p>
                        <?php echo $this->_tpl_vars['confirm_password_key']; ?>
: <br />
                        <input type="password" name="re_password" id="re_password" />
                    </p>
                    <p>
                        <?php echo $this->_tpl_vars['email_key']; ?>
: <br />
                        <input name="email" type="text" id="email" size="50" />
                        <span id="email_notice"></span>
                    </p>
                    <p>
                        <?php echo $this->_tpl_vars['user_website_key']; ?>
: <br />
                        <input name="homepage" type="text" id="homepage" size="50" />
                    </p>
                    <p>
                        <input type="submit" name="button" id="button" value="<?php echo $this->_tpl_vars['register']; ?>
" />
                    </p>
                </div>
                </form>
            </div>
            <!-- End of reg Dialog -->
            
           <!-- Start of help Dialog -->
            <div id="helpdialog" class="window">
                <form action="admin/admin.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
&act=login" method="post">
                <div class="unit-header unit_header3">
                    <h1 class="unit_header">
                        <?php echo $this->_tpl_vars['help']; ?>
</h1>
                    <h2 class="unit_header">
                        <a href="#" class="close">close</a></h2>
                </div>
                <div class="unit-body">
                    <p>
帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助
                    </p>
                    <p>
帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助
                    </p>
                    <p>
帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助
                    </p>
                    <p>
帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助
                    </p>
                    <p>
帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助
                    </p>
                    <p>
帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助帮助
                    </p>
	            <p>
<input type="submit" name="button" id="button" class="close" value="<?php echo $this->_tpl_vars['close']; ?>
" />
	            </p>
                </div>
                </form>
            </div>
            <!-- End of help Dialog -->
            
            <!-- Mask to cover the whole screen -->
            <div id="mask">
            </div>
        </div>
        <!-- boxes end -->
            <div id="wrapper">
        <div id="content">