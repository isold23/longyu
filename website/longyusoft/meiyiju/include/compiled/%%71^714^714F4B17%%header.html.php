<?php /* Smarty version 2.6.22, created on 2011-07-17 15:47:58
         compiled from header.html */ ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta name="google-site-verification" content="lfjbQk5SKAEgwpNRyX9DsmIG_9eieZ0WFsyWiTJzpLA" />
    <meta name="keywords" content="野牛艺术品, 非洲艺术品, fzyn, fzyn.net, 艺术品, 非洲,木雕,石雕,古董" />
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
                <div id="login-item">
                    <?php if ($this->_tpl_vars['user_id'] == -1): ?> <a href="#logindialog" name="modal">登录</a> &nbsp&nbsp| <?php else: ?> <span>欢迎</span>&nbsp <?php echo $this->_tpl_vars['user_name']; ?>
 &nbsp&nbsp <a href="user.php?act=logout">登出</a> &nbsp&nbsp| <?php endif; ?> &nbsp 
                    <?php if ($this->_tpl_vars['user_id'] == -1): ?> <a href="#regdialog" name="modal">注册</a> &nbsp&nbsp| <?php else: ?> <a href="user.php?act=profile">用户信息</a> &nbsp&nbsp| <?php endif; ?> &nbsp
                        	<a href="javascript:;" onclick="javascript:addfavor('http://www.fzyn.net','野牛非洲艺术馆');">收藏本站</a>&nbsp&nbsp&nbsp|&nbsp&nbsp
                        	<a href="#helpdialog" name="modal"">帮助</a>
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
                    <li><a href="index.php">首页</a></li>
                    <li><a href="about.php">关于我们</a></li>
                    <li><a href="blog.php">装修知识</a></li>
                    <li><a href="resource.php">精品案例</a></li>
                    <li><a href="message.php">留言簿</a></li>
                    <li><a href="contactus.php">联系我们</a></li>
                </ul>
                <div id="hot_line">
                	热线电话：<?php echo $this->_tpl_vars['hot_line']; ?>

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
                <div id="unit-header">
                    <h1>
                        用户登录</h1>
                    <h2>
                        <a href="#" class="close">close</a></h2>
                </div>
                <div id="unit-body">
                    <p>
                        用户名：<br />
                        <input name="name" type="text" id="name" size="25" />
                    </p>
                    <p>
                        密码：<br />
                        <input name="password" type="password" id="password" size="25" />
                    </p>
                    <p>
                        <input name="safe_url" type="hidden" value="<?php echo $this->_tpl_vars['safe_url']; ?>
" />
                        <input type="submit" name="button" id="button" value="登录" />
                    </p>
                </div>
                </form>
            </div>
            <!-- End of Login Dialog -->
            <!-- Start of reg Dialog -->
            <div id="regdialog" class="window">
            <form action="user.php?act=act_reg" method="post">
            	
                <div id="unit-header">
                    <h1>
                        新用户注册</h1>
                    <h2>
                        <a href="#" class="close">close</a></h2>
                </div>
                <div id="unit-body">
                    <p>
                        用户名：<br />
                        <input name="user_name" type="text" id="user_name" />
                    </p>
                    <p>
                        密码：<br />
                        <input type="password" name="password" id="password" />
                    </p>
                    <p>
                        密码确认：<br />
                        <input type="password" name="re_password" id="re_password" />
                    </p>
                    <p>
                        EMAIL：<br />
                        <input name="email" type="text" id="email" size="50" />
                        <span id="email_notice"></span>
                    </p>
                    <p>
                        个人主页地址：<br />
                        <input name="homepage" type="text" id="homepage" size="50" />
                    </p>
                    <p>
                        <input type="submit" name="button" id="button" value="注册" />
                    </p>
                </div>
                </form>
            </div>
            <!-- End of reg Dialog -->
            
           <!-- Start of help Dialog -->
            <div id="helpdialog" class="window">
                <form action="admin/admin.php?act=login" method="post">
                <div id="unit-header">
                    <h1>
                        帮助</h1>
                    <h2>
                        <a href="#" class="close">close</a></h2>
                </div>
                <div id="unit-body">
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
<input type="submit" name="button" id="button" class="close" value="关闭" />
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