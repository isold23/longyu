<?php /* Smarty version 2.6.22, created on 2011-10-26 13:04:55
         compiled from blog_list.html */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('modifier', 'truncate', 'blog_list.html', 84, false),)), $this); ?>
	<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "header.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
	<div id="subpage">
	<div id="subpage-item">

	<div id="subcontent_with_border">
	<div id="blog-list">
	    <?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "page.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?><?php $_from = $this->_tpl_vars['blog_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['blog']):
?>
	    <div id="blog-item">
	        <div id="blog-item-title">
	            <a href="detail.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
&id=<?php echo $this->_tpl_vars['blog']['id']; ?>
"><?php echo $this->_tpl_vars['blog']['title']; ?>
</a>
	        </div>
	        <div id="blog_item_author">
	            <span>
	              <?php echo $this->_tpl_vars['post_time']; ?>
: <?php echo $this->_tpl_vars['blog']['post_time']; ?>
 <?php echo $this->_tpl_vars['author']; ?>
: <?php echo $this->_tpl_vars['blog']['author']; ?>
</span>
	        </div>
	        <div id="blog-item-content">
	        	
	            <?php echo $this->_tpl_vars['blog']['description']; ?>

	            <br />
	            <a href="detail.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
&id=<?php echo $this->_tpl_vars['blog']['id']; ?>
"><?php echo $this->_tpl_vars['detail']; ?>
</a>
	        </div>
	        <div id="blog-item-botton-side">
	            <p>
	                <?php echo $this->_tpl_vars['comments']; ?>
: <?php echo $this->_tpl_vars['blog']['comment_count']; ?>

	                &nbsp;&nbsp;|&nbsp;&nbsp; <?php echo $this->_tpl_vars['references']; ?>
: <?php echo $this->_tpl_vars['blog']['trackback_count']; ?>
 &nbsp;&nbsp;|&nbsp;&nbsp;
	                <?php echo $this->_tpl_vars['view_times']; ?>
: <?php echo $this->_tpl_vars['blog']['view_count']; ?>
</p>
	        </div>
	        <br />
	    </div>
	   <?php endforeach; endif; unset($_from); ?>
	</div>
	<!-- blog list end -->
	</div>
	<!-- subcontent end -->
	
		<div id="sidebar">
	<div id="sidebar-item">
	<ul>
	
	<li>
	<a href="http://fusion.google.com/add?feedurl=<?php echo $this->_tpl_vars['feed_url']; ?>
" target="_blank"><img border="0" src="./themes/default/images/icon_subshot02_google.gif" alt="google reader" vspace="2" style="margin-right:8px;" ></a>
	<a href="http://www.zhuaxia.com/add_channel.php?url=<?php echo $this->_tpl_vars['feed_url']; ?>
" target="_blank"><img border="0" src="./themes/default/images/icon_subshot02_zhuaxia.gif" alt="&#25235;&#34430;" vspace="2" ></a>
	</li>
	
	<li>
	<a href="http://www.newsgator.com/ngs/subscriber/subfext.aspx?url=<?php echo $this->_tpl_vars['feed_url']; ?>
" target="_blank"><img border="0" src="./themes/default/images/icon_subshot02_newsgator.gif" alt="newsgator" vspace="2" style="margin-right:8px;" ></a>
	<a href="http://mail.qq.com/cgi-bin/feed?u=<?php echo $this->_tpl_vars['feed_url']; ?>
" target="_blank"><img border="0" src="./themes/default/images/icon_subshot02_qq.gif" alt="qq mail" vspace="2" ></a>
	</li>
	<li>
	<a href="http://www.rojo.com/add-subscription?resource=<?php echo $this->_tpl_vars['feed_url']; ?>
" target="_blank"><img border="0" src="./themes/default/images/icon_subshot02_rojo.gif" alt="rojo" vspace="2" style="margin-right:8px;" ></a>
	<a href="http://www.xianguo.com/subscribe.php?url=<?php echo $this->_tpl_vars['feed_url']; ?>
" target="_blank"><img border="0" src="./themes/default/images/icon_subshot02_xianguo.gif" alt="xianguo" vspace="2" ></a>
	</li>
	
	<li>
	<a href="http://reader.yodao.com/#url=<?php echo $this->_tpl_vars['feed_url']; ?>
" target="_blank"><img border="0" src="./themes/default/images/icon_subshot02_youdao.gif" alt="&#26377;&#36947;" vspace="2"  style="margin-right:8px;" ></a>
	<a href="http://www.pageflakes.com/subscribe.aspx?url=<?php echo $this->_tpl_vars['feed_url']; ?>
" target="_blank"><img border="0" src="./themes/default/images/icon_subshot02_pageflakes.gif" alt="pageflakes" vspace="2"></a>
	</li>
	
	<li>
	<a href="http://add.my.yahoo.com/rss?url=<?php echo $this->_tpl_vars['feed_url']; ?>
" target="_blank"><img border="0" src="./themes/default/images/icon_subshot02_yahoo.gif" alt="my yahoo" vspace="2"  style="margin-right:8px;"></a>
	<a href="http://www.580k.com/myLook/NewStakeOut_Submit.aspx?cm=1&WebUrl=<?php echo $this->_tpl_vars['feed_url']; ?>
" target="_blank"><img border="0" src="./themes/default/images/icon_subshot02_580k.gif" alt="580k" vspace="2" ></a>
	</li>
	
	<li>
	<a href="http://www.netvibes.com/subscribe.php?url=<?php echo $this->_tpl_vars['feed_url']; ?>
" target="_blank"><img border="0" src="./themes/default/images/icon_subshot02_netvibes.gif" alt="netvibes" vspace="2"  style="margin-right:8px;"></a>
	<a href="http://www.bloglines.com/sub/<?php echo $this->_tpl_vars['feed_url']; ?>
" target="_blank"><img border="0" src="./themes/default/images/icon_subshot02_bloglines.gif" alt="bloglines" vspace="2" ></a>
	</li>

	
	
	
	</ul>

	</div>
            <div id="sidebar-item">
                <div class="unit">
                    <div class="unit-header unit_header2">
                        <h1 class="unit_header">
                            <?php echo $this->_tpl_vars['travel_blog']; ?>
</h1>
                    </div>
                    <div class="unit-body">
                        <ul>
                        	<?php $_from = $this->_tpl_vars['last_blog_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['last_blog']):
?>
                            <li><a href="detail.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
&id=<?php echo $this->_tpl_vars['last_blog']['id']; ?>
"><?php echo ((is_array($_tmp=$this->_tpl_vars['last_blog']['title'])) ? $this->_run_mod_handler('truncate', true, $_tmp, 50, "...", true) : smarty_modifier_truncate($_tmp, 50, "...", true)); ?>
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
                            <?php echo $this->_tpl_vars['travel_advice']; ?>
</h1>
                    </div>
                    <div class="unit-body">
                        <ul>
                        	<?php $_from = $this->_tpl_vars['last_trave_blog_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['last_travel_blog']):
?>
                            <li><a href="detail.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
&id=<?php echo $this->_tpl_vars['last_travel_blog']['id']; ?>
"><?php echo ((is_array($_tmp=$this->_tpl_vars['last_travel_blog']['title'])) ? $this->_run_mod_handler('truncate', true, $_tmp, 50, "...", true) : smarty_modifier_truncate($_tmp, 50, "...", true)); ?>
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