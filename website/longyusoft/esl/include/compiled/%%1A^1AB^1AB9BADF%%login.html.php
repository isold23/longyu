<?php /* Smarty version 2.6.22, created on 2011-10-15 07:51:46
         compiled from login.html */ ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "header.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>

<div id = "subpage">
<div id="subpage-item">
<div id = "sidebar">
	<div id = "sidebar-item">
<script language="javascript" type="text/javascript">
	yigao_title_color = "null";
	yigao_content_color = "null";
	yigao_background_color = "null";
	yigao_border_color = "D9D9D9";
	yigao_title_bold = "0";
	yigao_content_bold = "0";
	yigao_title_underline = "0";
	yigao_content_underline = "0";
	yigao_width = 300;
	yigao_height = 250;
	yigao_sid = "6558f213735bb972";
	yigao_msid = "13be9440c2d8cd51";
	yigao_uid = 72924;
	yigao_zid = 122633;
	yigao_pid = 6;
	yigao_type = 1;
	yigao_adamount = 1;
	yigao_cols = 1;
</script>
<script language="javascript" src="http://monitor.yigao.com/info.js"></script>

	</div><!-- sidebar item end -->
</div><!-- sidebar end -->
<div id = "subcontent_no_background">
<center>

<div id="user-login">
<form action="user.php?act=act_login" method="post"  name="form1" id="post_form">
<?php if ($this->_tpl_vars['notice'] != ''): ?>
<div id="home-item-header">
<h1><?php echo $this->_tpl_vars['notice']; ?>
</h1>
</div>
<?php endif; ?>

 <div id="home-item-content">
 <p><?php echo $this->_tpl_vars['user_name_key']; ?>
: <br />
 <input name="name" type="text" id="name" size="25"/></p>
   </p>
 <p><?php echo $this->_tpl_vars['user_password_key']; ?>
: <br />
    <input name="password" type="password" id="password" size="25" />
   </p>

   <p>
   <input name="safe_url" type="hidden" value="<?php echo $this->_tpl_vars['safe_url']; ?>
" /> <input type="submit" name="button" id="button" value="<?php echo $this->_tpl_vars['login']; ?>
" />
  </p>
</div>
</form>
</div>
</center>
</div><!-- subcontent -->
</div><!-- subpage item end -->
</div><!-- subpage end -->
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "footer.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>