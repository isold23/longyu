<?php /* Smarty version 2.6.22, created on 2011-09-10 16:23:16
         compiled from user.html */ ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "header.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>

<div id="subpage">
    <div id="subpage-item">
 
        <div id="subcontent_no_background">
<center>
<div id="user-login">

<form action="user.php?act=edit_profile" method="post"  name="user_reg" id="user_reg">
<?php if ($this->_tpl_vars['notice'] != ''): ?>
<div id="home-item-header"><h1><?php echo $this->_tpl_vars['notice']; ?>
</h1></div>
<?php endif; ?>
<div id="home-item-content">
<p>
 用户名：<br />
 <input name="name" type="text" id="name" value="<?php echo $this->_tpl_vars['user']['name']; ?>
" /></p>
   <p>
 密码：<br />
    <input type="password" name="password" id="password" />
   (如果不需要修改，请保留为空)</p>
    <p>
 电子邮箱：<br />
    <input name="email" type="text" id="email" value="<?php echo $this->_tpl_vars['user']['email']; ?>
" size="50" />
  </p>
  <p>
 个人主页地址：<br />
    <input name="home" type="text" id="home" value="<?php echo $this->_tpl_vars['user']['homepage']; ?>
" size="50" />
  </p>

  <p>
    <input type="submit" name="button" id="button" value="提交" />
  </p>
</div>
</form>
</div>
<center>
        </div>
        <!-- subcontent end -->
        
        
        
               <div id="sidebar">
            <div id="sidebar-item">
                <script type="text/javascript">
                    alimama_pid = "mm_13906600_2165521_8942780";
                    alimama_titlecolor = "000033";
                    alimama_descolor = "3D81EE";
                    alimama_bgcolor = "FFFFFF";
                    alimama_bordercolor = "6C82B5";
                    alimama_linkcolor = "FFFF66";
                    alimama_bottomcolor = "FFFFFF";
                    alimama_anglesize = "0";
                    alimama_bgpic = "16";
                    alimama_icon = "0";
                    alimama_sizecode = "37";
                    alimama_width = 300;
                    alimama_height = 250;
                    alimama_type = 2;
                </script>
                <script src="http://a.alimama.cn/inf.js" type="text/javascript">
                </script>
            </div>
            <!-- sidebar item end -->
            <?php echo $this->_tpl_vars['resource_category']; ?>

			  <?php echo $this->_tpl_vars['last_resource']; ?>

        </div>
        <!-- sidebar -->
    </div>
    <!-- sub page item -->
</div>
<!-- sub page end -->



<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "footer.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>