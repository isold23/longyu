<?php /* Smarty version 2.6.22, created on 2011-09-10 21:29:23
         compiled from blog_category.html */ ?>
            <div id="sidebar-item">
                <div class="unit">
                    <div class="unit-header unit_header2">
                        <h1 class="unit_header">
                            日志类别</h1>
                    </div>
                    <div class="unit-body">
                        <ul>
                        	<?php $_from = $this->_tpl_vars['blog_category_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['blog_category']):
?>
                            <li><a href="blog.php?cat=<?php echo $this->_tpl_vars['blog_category']['id']; ?>
"><?php echo $this->_tpl_vars['blog_category']['name']; ?>
[<?php echo $this->_tpl_vars['blog_category']['blog_count']; ?>
]</a> </li>
                         <?php endforeach; endif; unset($_from); ?>
                        </ul>
                    </div>
                </div>
            </div>
            <!-- sidebar item end -->