<?php /* Smarty version 2.6.22, created on 2011-10-26 11:09:23
         compiled from last_resource.html */ ?>
            <div id="sidebar-item">
                <div class="unit">
                    <div class="unit-header unit_header2">
                        <h1 class="unit_header">
                            <?php echo $this->_tpl_vars['top_destinations']; ?>
</h1>
                    </div>
                    <div class="unit-body">
                        <ul>
                        	<?php $_from = $this->_tpl_vars['last_resource_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['last_resource']):
?>
                            <li><a href="resource.php?lan=<?php echo $this->_tpl_vars['last_resource']['lang']; ?>
&id=<?php echo $this->_tpl_vars['last_resource']['id']; ?>
"><?php echo $this->_tpl_vars['last_resource']['name']; ?>
</a> </li>
                         <?php endforeach; endif; unset($_from); ?>
                        </ul>
                    </div>
                </div>
            </div>
            <!-- sidebar item end -->
            
                        <div id="sidebar-item">
                <div class="unit">
                    <div class="unit-header unit_header2">
                        <h1 class="unit_header">
                            <?php echo $this->_tpl_vars['top_tours']; ?>
</h1>
                    </div>
                    <div class="unit-body">
                        <ul>
                        	<?php $_from = $this->_tpl_vars['last_resource_tour_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['last_resource_tour']):
?>
                            <li><a href="resource.php?lan=<?php echo $this->_tpl_vars['last_resource']['lang']; ?>
&id=<?php echo $this->_tpl_vars['last_resource_tour']['id']; ?>
"><?php echo $this->_tpl_vars['last_resource_tour']['name']; ?>
</a> </li>
                         <?php endforeach; endif; unset($_from); ?>
                        </ul>
                    </div>
                </div>
            </div>
            <!-- sidebar item end -->