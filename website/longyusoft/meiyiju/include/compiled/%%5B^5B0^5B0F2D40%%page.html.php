<?php /* Smarty version 2.6.22, created on 2011-07-16 13:22:23
         compiled from page.html */ ?>
<div id = "pages">
	<div id = "pages-text">
		<a href="<?php echo $this->_tpl_vars['page_url']; ?>
?pg=1&cat=<?php echo $this->_tpl_vars['cat_id']; ?>
" title="第一页">< < 第一页</a> 
		<a href="<?php echo $this->_tpl_vars['page_url']; ?>
?pg=<?php echo $this->_tpl_vars['pre']; ?>
&cat=<?php echo $this->_tpl_vars['cat_id']; ?>
" title="上一页">< 上一页</a> 
		<a href="<?php echo $this->_tpl_vars['page_url']; ?>
?pg=<?php echo $this->_tpl_vars['next']; ?>
&cat=<?php echo $this->_tpl_vars['cat_id']; ?>
" title="下一页">下一页 ></a> 
		<a href="<?php echo $this->_tpl_vars['page_url']; ?>
?pg=<?php echo $this->_tpl_vars['page_count']; ?>
&cat=<?php echo $this->_tpl_vars['cat_id']; ?>
" title="最后页">最后页 > ></a>
	</div>
</div>