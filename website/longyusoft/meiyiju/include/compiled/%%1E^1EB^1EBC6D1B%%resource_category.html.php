<?php /* Smarty version 2.6.22, created on 2011-07-17 19:26:37
         compiled from resource_category.html */ ?>
            <div id="sidebar-item">
                <div id="unit">
                    <div id="unit-header">
                        <h1>
                            案例类别</h1>
                    </div>
                    <div id="unit-body">
                        <ul>
                        	<?php $_from = $this->_tpl_vars['resource_category_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['resource_category']):
?>
                            <li><a href="resource.php?cat=<?php echo $this->_tpl_vars['resource_category']['id']; ?>
"><?php echo $this->_tpl_vars['resource_category']['name']; ?>
[<?php echo $this->_tpl_vars['resource_category']['resource_count']; ?>
]</a> </li>
                         <?php endforeach; endif; unset($_from); ?>
                        </ul>
                    </div>
                </div>
            </div>
            <!-- sidebar item end -->