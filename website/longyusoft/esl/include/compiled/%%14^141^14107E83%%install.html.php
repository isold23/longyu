<?php /* Smarty version 2.6.22, created on 2011-09-06 18:17:50
         compiled from install.html */ ?>
<!DOCTYPE>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>网站安装---北京龙宇软件工作室</title>
<!-- <?php echo ' -->
<style>
@charset "utf-8";
body,h1,h2,h3,p,blockquote,dl,dt,dd,ul,ol,li,button,input,textarea {margin: 0; padding: 0;}
body {font:13px Tahoma, Helvetica, Arial, sans-serif;}
img {border: 0;}
a, a:link, a:visited {text-decoration: none;}
#container {width:80%; margin:auto auto;}
#header { clear:both;overflow:auto;padding-top: 25px; }
#header .logo {float: left;}
#header .logo a {font-size: 25px; height:35px;}

#nav {height:34px; line-height:34px;margin-top:20px;background: #999;border-bottom:1px solid #e6e6e6; border-top:1px solid #fff;}
#nav ul {list-style-type: none;}
#nav ul li {float: left;text-transform: uppercase;font-weight: normal;font-size: 12px; height:35px; overflow:hidden; font-family:\'微软雅黑\',Tahoma, Arial; }
#nav ul li a {color: #ececec;display:inline-block;padding: 0 12px; height:35px; line-height:33px; }

#content {width: 100%;float: right;padding-bottom: 20px;padding-top: 15px;}

#install {border-top:1px dashed #ccc; padding-top:15px;}
#install p{padding-top:5px;}
#install input{ height:27px;font-size: 16px;overflow:hidden; font-family:\'微软雅黑\',Tahoma, Arial;}
#install textarea{font-size: 16px;overflow:hidden; font-family:\'微软雅黑\',Tahoma, Arial;}
.line{font-weight: normal;font-size: 18px;overflow:hidden; font-family:\'微软雅黑\',Tahoma, Arial;padding-bottom:10px;border-bottom:1px dashed #ccc;}

#footer {clear: both;background: #999;color: #ececec;padding: 10px 15px; margin-top: 10px; margin-bottom:15px;text-align: center;font-family:\'微软雅黑\',Tahoma, Arial;font-size: 12px;}
#footer a {color: #ececec;}
#footer a:hover {color: #ccc;}
.clearfloat { font-size: 0; height: 0; width: 0; clear: both; overflow:hidden;}
</style>
<!-- '; ?>
 -->
<script src="include/js/jquery.js"></script>
</head>
<body>
<div id="container">
  <div id="header">
  <div class="logo">
  <a href="./index.php">网站安装</a>
  </div>
  </div>  <!-- end #header -->

  <div id="nav">
<ul>
    <li <?php if ($this->_tpl_vars['id'] == 1): ?>class="current"<?php endif; ?>><a href="install.php?act=check">系统检测</a></li>
    <li <?php if ($this->_tpl_vars['id'] == 2): ?>class="current"<?php endif; ?>><a>参数配置</a></li>
    <li <?php if ($this->_tpl_vars['id'] == 3): ?>class="current"<?php endif; ?>><a>安装完成</a></li>
</ul>
</div>

<div id="content">

<?php if ($this->_tpl_vars['id'] == 1): ?>
<form action="install.php" method="post"  name="install" id="install">
<p class="line">服务器信息</p>
<p>服务器信息：<?php echo $this->_tpl_vars['SERVER_SOFTWARE']; ?>
</p>
<p>PHP版本：<?php echo $this->_tpl_vars['php_version']; ?>
</p>
<br /><br />
<p class="line">文件权限检测</p>

<?php $_from = $this->_tpl_vars['file_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['file']):
?>
<p><?php echo $this->_tpl_vars['file']; ?>
</p>
<?php endforeach; endif; unset($_from); ?>
<?php if ($this->_tpl_vars['set'] == 1): ?>
<br />
<p><input type="submit" name="button" id="button" value="下一步" disabled/></p>
<?php else: ?>
<p>文件权限设置正确
</p><br />
<p><input type="submit" name="button" id="button" value="下一步" /></p>
<?php endif; ?>
<input name="setup" type="hidden" value="config">
</form>
<?php elseif ($this->_tpl_vars['id'] == 2): ?>
<form action="install.php" method="post"  name="install" id="install">

<p class="line">数据库配置</p>
 <p>数据库地址：(一般为localhost) <br />
  <input name="host" type="text" id="host" value="localhost"  />
   </p>
   <p>
 数据库名：<br />
    <input type="text" name="dbname" id="dbname" value="dbname" /> 
</p>
     <p>
 数据库用户名：<br />
    <input type="text" name="dbuser" id="dbuser" value="user name"/> 
 </p>
   <p>
 数据库密码：<br />
    <input name="dbpass" type="text" id="dbpass" /> 
  </p>
    <p>
 数据库前缀（默认为longyu_）：<br />
    <input name="dbprefix" type="text" id="dbprefix" /> 
  </p>
  
  <p class="line">网站信息配置</p>
  <p>
 管理员用户名：<br />
    <input name="admin_user" type="text" id="admin_user" />
  </p>
  <p>
 管理员密码：<br />
    <input name="admin_pass" type="text" id="admin_pass" />
  </p>
  <p>
 网站名字：<br />
    <input name="webname" type="text" id="webname" />
  </p>
    <p>
 网站简介：<br />
 <textarea name="webdesc" cols="40" rows="5" id="webdesc"></textarea>
  </p>

  <p>
    <input name="setup" type="hidden" value="finish"><input type="submit" name="button" id="button" value="开始安装" />
  </p>
</form>
<?php else: ?>
<form action="install.php" method="post"  name="install" id="install">

<?php if ($this->_tpl_vars['error']): ?>
<p class="line">错误信息</p>
<?php $_from = $this->_tpl_vars['error']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['e']):
?>
<p><?php echo $this->_tpl_vars['e']; ?>
</p>
<?php endforeach; endif; unset($_from); ?>
<?php endif; ?>

<?php if ($this->_tpl_vars['success'] == 1): ?>
<p class="line">安装成功</p>
<p>管理员用户名：<?php echo $this->_tpl_vars['admin_user']; ?>
</p>
<p>管理员密码：<?php echo $this->_tpl_vars['admin_pass']; ?>
</p>
<p><a href="./admin/">前往后台</a></p>
<p><a href="./index.php">前往前台</a></p>
<?php endif; ?>
</form>

<?php endif; ?>

<div id="footer">
            Copyright 版权所有 2009-2011 <a href="http://www.longyusoft.com" target="_parent">龙宇网</a>
            | <a href="http://www.longyusoft.com/about.php" target="_parent">北京龙宇软件工作室</a>
            All Rights Reserved
</div>