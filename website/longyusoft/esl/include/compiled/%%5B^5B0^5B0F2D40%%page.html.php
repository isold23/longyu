<?php /* Smarty version 2.6.22, created on 2011-09-16 15:46:55
         compiled from page.html */ ?>
<div id = "pages">
	<div id = "pages-text">
		<a href="<?php echo $this->_tpl_vars['page_url']; ?>
?pg=1&cat=<?php echo $this->_tpl_vars['cat_id']; ?>
" title="<?php echo $this->_tpl_vars['first_page']; ?>
">< < <?php echo $this->_tpl_vars['first_page']; ?>
</a> 
		<a href="<?php echo $this->_tpl_vars['page_url']; ?>
?pg=<?php echo $this->_tpl_vars['pre']; ?>
&cat=<?php echo $this->_tpl_vars['cat_id']; ?>
" title="<?php echo $this->_tpl_vars['previous_page']; ?>
">< <?php echo $this->_tpl_vars['previous_page']; ?>
</a> 
		<a href="<?php echo $this->_tpl_vars['page_url']; ?>
?pg=<?php echo $this->_tpl_vars['next']; ?>
&cat=<?php echo $this->_tpl_vars['cat_id']; ?>
" title="<?php echo $this->_tpl_vars['next_page']; ?>
"><?php echo $this->_tpl_vars['next_page']; ?>
 ></a> 
		<a href="<?php echo $this->_tpl_vars['page_url']; ?>
?pg=<?php echo $this->_tpl_vars['page_count']; ?>
&cat=<?php echo $this->_tpl_vars['cat_id']; ?>
" title="<?php echo $this->_tpl_vars['last_page']; ?>
"><?php echo $this->_tpl_vars['last_page']; ?>
 > ></a>
	</div>
</div>