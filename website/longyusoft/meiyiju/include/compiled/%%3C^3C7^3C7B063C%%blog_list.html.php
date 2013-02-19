<?php /* Smarty version 2.6.22, created on 2011-07-16 16:36:30
         compiled from blog_list.html */ ?>
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
	            <a href="detail.php?id=<?php echo $this->_tpl_vars['blog']['id']; ?>
"><?php echo $this->_tpl_vars['blog']['title']; ?>
</a>
	        </div>
	        <div id="blog_item_author">
	            <span>
	              发布时间：<?php echo $this->_tpl_vars['blog']['post_time']; ?>
 发表者: <?php echo $this->_tpl_vars['blog']['author']; ?>
</span>
	        </div>
	        <div id="blog-item-content">
	        	
	            <?php echo $this->_tpl_vars['blog']['description']; ?>

	            <br />
	            <a href="detail.php?id=<?php echo $this->_tpl_vars['blog']['id']; ?>
">详细内容</a>
	        </div>
	        <div id="blog-item-botton-side">
	            <p>
	                分类：<a href="blog.php?cat=<?php echo $this->_tpl_vars['blog']['cat_id']; ?>
"><?php echo $this->_tpl_vars['blog']['name']; ?>
</a> &nbsp;&nbsp;|&nbsp;&nbsp; 评论：<?php echo $this->_tpl_vars['blog']['comment_count']; ?>

	                &nbsp;&nbsp;|&nbsp;&nbsp; 引用：<?php echo $this->_tpl_vars['blog']['trackback_count']; ?>
 &nbsp;&nbsp;|&nbsp;&nbsp;
	                浏览次数：<?php echo $this->_tpl_vars['blog']['view_count']; ?>
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
	<script language="javascript" type="text/javascript">
	yigao_title_color = "null";
	yigao_content_color = "null";
	yigao_background_color = "null";
	yigao_border_color = "D9D9D9";
	yigao_title_bold = "0";
	yigao_content_bold = "0";
	yigao_title_underline = "0";
	yigao_content_underline = "0";
	yigao_width = 300;
	yigao_height = 250;
	yigao_sid = "6558f213735bb972";
	yigao_msid = "13be9440c2d8cd51";
	yigao_uid = 72924;
	yigao_zid = 122633;
	yigao_pid = 6;
	yigao_type = 1;
	yigao_adamount = 1;
	yigao_cols = 1;
	</script>
	<script language="javascript" src="http://monitor.yigao.com/info.js"></script>
	
	</div>
	<!-- sidebar item end -->
	<?php echo $this->_tpl_vars['blog_category']; ?>

	<?php echo $this->_tpl_vars['last_blog']; ?>

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