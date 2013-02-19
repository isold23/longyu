<?php /* Smarty version 2.6.22, created on 2011-07-17 15:06:46
         compiled from last_blog.html */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('modifier', 'truncate', 'last_blog.html', 10, false),)), $this); ?>
            <div id="sidebar-item">
                <div id="unit">
                    <div id="unit-header">
                        <h1>
                            最新日志</h1>
                    </div>
                    <div id="unit-body">
                        <ul>
                        	<?php $_from = $this->_tpl_vars['last_blog_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['last_blog']):
?>
                            <li><a href="detail.php?id=<?php echo $this->_tpl_vars['last_blog']['id']; ?>
"><?php echo ((is_array($_tmp=$this->_tpl_vars['last_blog']['title'])) ? $this->_run_mod_handler('truncate', true, $_tmp, 50, "...", true) : smarty_modifier_truncate($_tmp, 50, "...", true)); ?>
</a> </li>
                         <?php endforeach; endif; unset($_from); ?>
                        </ul>
                    </div>
                </div>
            </div>
            <!-- sidebar item end -->