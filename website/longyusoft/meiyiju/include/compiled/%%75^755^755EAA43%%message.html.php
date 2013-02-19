<?php /* Smarty version 2.6.22, created on 2011-07-16 16:37:41
         compiled from message.html */ ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "header.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
<div id = "subpage">
<div id="subpage-item">

<div id = "subcontent_no_background">
        <div id="message_list">
                <?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "page.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?><?php $_from = $this->_tpl_vars['message_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['message']):
?>
                <div id="message_item">
                    <div id="message_item_content">
                        <p><?php echo $this->_tpl_vars['message']['content']; ?>
</p>
                    </div>
                    <div id="message_item_author">
                            <p>发表者: <?php echo $this->_tpl_vars['message']['user_name']; ?>
 时间：<?php echo $this->_tpl_vars['message']['post_time']; ?>
</p>
                    </div>
                </div>
               <?php endforeach; endif; unset($_from); ?>
        </div>
            <!-- message list end -->
            
            <div id="post_message">
            	            <form action="message.php?act=post_message" method="post">
								<div id="unit">
									                <div id="unit-header">
                    <h1>
                        发表留言</h1>
                </div>
                <div id="unit-body">
                	<?php if ($this->_tpl_vars['user_id'] == -1): ?>
                    <p>
                        用户名：<br />
                        <input name="name" type="text" id="name" />
                    </p>
                    <p>
                        电子邮箱：<br />
                        <input name="email" type="text" id="email" size="50" />
                        <span id="email_notice"></span>
                    </p>
                    <?php else: ?>
                    <p>
                        用户名：<?php echo $this->_tpl_vars['user_name']; ?>

                    </p>
                  <?php endif; ?>
                    <p>
                        <textarea name="message_content" id="message_content" cols="45" rows="5"></textarea>
                    </p>
                    <p>
                        <input type="submit" name="button" id="button" value="发送" />
                    </p>
                </div>
              </div>
                </form>
            </div>
            
</div><!-- subcontent -->


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
	yigao_width = 160;
	yigao_height = 600;
	yigao_sid = "477fb82134867094";
	yigao_msid = "0da419b24f38185d";
	yigao_uid = 72924;
	yigao_zid = 122734;
	yigao_pid = 5;
	yigao_type = 1;
	yigao_adamount = 1;
	yigao_cols = 1;
</script>
<script language="javascript" src="http://monitor.yigao.com/info.js"></script>
	</div><!-- sidebar item end -->
</div><!-- sidebar end -->


</div><!-- subpage item end -->
</div><!-- subpage end -->
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "footer.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>