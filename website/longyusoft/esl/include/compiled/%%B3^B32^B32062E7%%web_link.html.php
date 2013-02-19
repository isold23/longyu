<?php /* Smarty version 2.6.22, created on 2011-09-10 16:24:00
         compiled from web_link.html */ ?>
                       <div id="sidebar-item">
                <div id="unit">
                    <div id="unit-header">
                        <h1>
                            网站链接</h1>
                    </div>
                    <div id="unit-body">
                        <ul>
                        	<?php $_from = $this->_tpl_vars['web_link_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['web_link']):
?>
                            <li><a href="<?php echo $this->_tpl_vars['web_link']['link_url']; ?>
"><?php echo $this->_tpl_vars['web_link']['name']; ?>
</a> </li>
                         <?php endforeach; endif; unset($_from); ?>
                        </ul>
                    </div>
                </div>
            </div>
            <!-- sidebar item end -->