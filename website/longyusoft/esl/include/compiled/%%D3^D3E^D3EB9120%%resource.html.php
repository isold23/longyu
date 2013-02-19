<?php /* Smarty version 2.6.22, created on 2011-10-26 13:01:44
         compiled from resource.html */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('modifier', 'truncate', 'resource.html', 14, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "header.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
<div id="subpage">
<div id="subpage-item">

<div id="subcontent">
<div id="resource-list">
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "page.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?><?php $_from = $this->_tpl_vars['resource_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['resource']):
?>
<ul>
<li>
	
<div id="resource_list_item">
	
<a href="resource.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
&id=<?php echo $this->_tpl_vars['resource']['id']; ?>
" target="_blank">
	<img src = "<?php echo $this->_tpl_vars['domain']; ?>
upload/<?php echo $this->_tpl_vars['resource']['image_path']; ?>
" alt="<?php echo ((is_array($_tmp=$this->_tpl_vars['resource']['aname'])) ? $this->_run_mod_handler('truncate', true, $_tmp, 20, "") : smarty_modifier_truncate($_tmp, 20, "")); ?>
" onload="AutoResizeImage(198,200,this)" />
</a>

<h1>
<a href="resource.php?id=<?php echo $this->_tpl_vars['resource']['id']; ?>
" title="<?php echo $this->_tpl_vars['resource']['aname']; ?>
"><?php echo $this->_tpl_vars['resource']['aname']; ?>
</a>
</h1>

</div>

</li>
</ul>

<?php endforeach; endif; unset($_from); ?>
</div>
<!-- resource list end -->
</div>
<!-- subcontent end -->

<div id="sidebar">
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