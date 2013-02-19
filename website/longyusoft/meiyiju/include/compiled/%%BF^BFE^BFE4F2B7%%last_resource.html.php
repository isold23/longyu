<?php /* Smarty version 2.6.22, created on 2011-07-17 19:26:37
         compiled from last_resource.html */ ?>
            <div id="sidebar-item">
                <div id="unit">
                    <div id="unit-header">
                        <h1>
                            最新案例</h1>
                    </div>
                    <div id="unit-body">
                        <ul>
                        	<?php $_from = $this->_tpl_vars['last_resource_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['last_resource']):
?>
                            <li><a href="resource.php?id=<?php echo $this->_tpl_vars['last_resource']['id']; ?>
"><?php echo $this->_tpl_vars['last_resource']['name']; ?>
</a> </li>
                         <?php endforeach; endif; unset($_from); ?>
                        </ul>
                    </div>
                </div>
            </div>
            <!-- sidebar item end -->