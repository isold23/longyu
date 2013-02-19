<?php /* Smarty version 2.6.22, created on 2011-10-26 13:49:13
         compiled from detail.html */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('insert', 'comments_name', 'detail.html', 109, false),array('modifier', 'truncate', 'detail.html', 137, false),)), $this); ?>
	<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "header.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
	<div id="subpage">
	    <div id="subpage-item">
	        <div id="subcontent_with_border">
	            <div id="blog-detail">
	                <div id="blog-item">
	                    <center>
	                        <div id="blog_detail_title">
	                            <h1><?php echo $this->_tpl_vars['blog']['title']; ?>
<h1>
	                        </div>
	                        <div id="blog_item_author">
	                            <span>
	                                <a href="<?php echo $this->_tpl_vars['web_url']; ?>
"><?php echo $this->_tpl_vars['web_domain']; ?>
</a> <?php echo $this->_tpl_vars['blog']['post_time']; ?>

	                              <?php echo $this->_tpl_vars['author']; ?>
: <?php echo $this->_tpl_vars['blog']['author']; ?>
</span>
	                        </div>
	                    </center>
	                    	                    <div id="blog_item_detail_des">
	                    	<span><?php echo $this->_tpl_vars['summary']; ?>
: </span><?php echo $this->_tpl_vars['blog']['description']; ?>

	                    </div>
	                    <div id="blog-item-detail-content">
	                        <?php echo $this->_tpl_vars['blog']['content']; ?>

	                    </div>
	                    <div id="blog-item-botton-side">
	                        <p> <?php echo $this->_tpl_vars['comments']; ?>
: <?php echo $this->_tpl_vars['blog']['comment_count']; ?>

	                            &nbsp;&nbsp;|&nbsp;&nbsp; <?php echo $this->_tpl_vars['references']; ?>
: <?php echo $this->_tpl_vars['blog']['trackback_count']; ?>
 &nbsp;&nbsp;|&nbsp;&nbsp;
	                            <?php echo $this->_tpl_vars['view_times']; ?>
: <?php echo $this->_tpl_vars['blog']['view_count']; ?>
</p>
	                       
	                    </div>
	                    <br/>
	                    <div id="blog-item-botton-side">
	  
	                        <p> 
	                        	
	            <?php echo $this->_tpl_vars['share']; ?>
:              	
	                        	
	                        	
	 <script src="http://rest.kaixin001.com/api/Repaste_js.php" type="text/javascript"></script>
<div id="kx001_btn_repaste"></div>
<script type="text/javascript">
KX001_REPASTE_LINK.init(1,"","#336699","#3366CC");
</script>
	                        	
	 <script type="text/javascript" charset="utf-8">
(function(){
  var _w = 16 , _h = 16;
  var param = {
    url:location.href,
    type:'3',
    count:'', /**是否显示分享数，1显示(可选)*/
    appkey:'', /**您申请的应用appkey,显示分享来源(可选)*/
    title:'', /**分享的文字内容(可选，默认为所在页面的title)*/
    pic:'', /**分享图片的路径(可选)*/
    ralateUid:'', /**关联用户的UID，分享微博会@该用户(可选)*/
    rnd:new Date().valueOf()
  }
  var temp = [];
  for( var p in param ){
    temp.push(p + '=' + encodeURIComponent( param[p] || '' ) )
  }
  document.write('<iframe allowTransparency="true" frameborder="0" scrolling="no" src="http://hits.sinajs.cn/A1/weiboshare.html?' + temp.join('&') + '" width="'+ _w+'" height="'+_h+'"></iframe>')
})()
</script>
	
<a href="javascript:void((function(s,d,e){if(/renren\.com/.test(d.location))return;var f='http://share.renren.com/share/buttonshare?link=',u=d.location,l=d.title,p=[e(u),'&title=',e(l)].join('');function%20a(){if(!window.open([f,p].join(''),'xnshare',['toolbar=0,status=0,resizable=1,width=626,height=436,left=',(s.width-626)/2,',top=',(s.height-436)/2].join('')))u.href=[f,p].join('');};if(/Firefox/.test(navigator.userAgent))setTimeout(a,0);else%20a();})(screen,document,encodeURIComponent));" title="分享到人人"><img src="http://a.xnimg.cn/imgpro/share/share-tinybtn.png" title="分享到人人"/></a>
	
	<a href="javascript:void(0);" onclick="window.open('http://sns.qzone.qq.com/cgi-bin/qzshare/cgi_qzshare_onekey?url='+encodeURIComponent(document.location.href));return false;" title="分享到QQ空间"><img src="http://qzonestyle.gtimg.cn/ac/qzone_v5/app/app_share/qz_logo.png" alt="分享到QQ空间" /></a>
	<a href="javascript:void(0);" onclick="window.open('http://sns.qzone.qq.com/cgi-bin/qzshare/cgi_qzshare_onekey?to=pengyou&url='+encodeURIComponent(document.location.href));return false;" title="分享到腾讯朋友"><img src="http://qzonestyle.gtimg.cn/ac/qzone_v5/app/qzshare/xy-icon.png" alt="分享到腾讯朋友" /></a>




<a href="javascript:void(function(){var d=document,e=encodeURIComponent,s1=window.getSelection,s2=d.getSelection,s3=d.selection,s=s1?s1():s2?s2():s3?s3.createRange().text:'',r='http://www.douban.com/recommend/?url='+e(d.location.href)+'&title='+e(d.title)+'&sel='+e(s)+'&v=1',x=function(){if(!window.open(r,'douban','toolbar=0,resizable=1,scrollbars=yes,status=1,width=450,height=330'))location.href=r+'&r=1'};if(/Firefox/.test(navigator.userAgent)){setTimeout(x,0)}else{x()}})()"><img src="http://img2.douban.com/pics/fw2douban_s.png" alt="推荐到豆瓣" /></a>




	</p>
	                        
	                    </div>
	                  </br>
	                </div>
	                <!-- blog detail end -->
	            </div>
	            <!-- blog detail end -->
	            <?php if ($this->_tpl_vars['open_comment'] == 1): ?>
	            <div class="new_notice">
	                网站已经关闭评论</div>
	            <?php elseif ($this->_tpl_vars['blog']['open_type'] == 1): ?>
	            <div class="new_notice">
	                此日志评论已经关闭</div>
	            <?php else: ?>
	            <div class="pl">
	                <p class="p_list">
	                    <a  onclick="javascript:post()"><?php echo $this->_tpl_vars['comments']; ?>
</a></p>
	                <div id="load_comments_notice" style="display: none; padding-left:10px; font-size: 13px; font-family: verdana,arial;
	                    color: #FF0000">
	                    评论数据加载中......
	                  </br></br>
	                    </div>
	                <ol id="comments_list">
	                </ol>
	                <div id="replay">
	                    <a name="pl"><?php echo $this->_tpl_vars['post_comment']; ?>
</a>
	                    <div id="replay_box">
	                        <form action="post.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
&act=pl_post" method="post" name="post_comment" id="post_comment">
	                        <div id="post_comments_notice" style="display: none; padding-bottom: 5px; padding-left:10px; clear: both;
	                            font-size: 13px; font-family: verdana,arial; color: #FF0000">
	                            评论数据提交中......</div>
	                        <?php require_once(SMARTY_CORE_DIR . 'core.run_insert_handler.php');
echo smarty_core_run_insert_handler(array('args' => array('name' => 'comments_name', 'p1' => $this->_tpl_vars['name'], 'p2' => $this->_tpl_vars['user_website_key'])), $this); ?>

	                        <p>
	                            <?php echo $this->_tpl_vars['comments']; ?>
: <br/>
	                            <textarea name="content" cols="60" rows="5"></textarea>
	                        </p>
	                        <p>
	                            <input type="button" name="button" id="comment_button1" value="<?php echo $this->_tpl_vars['post']; ?>
" onclick="post()" />
	                        </p>
	                        </form>
	                    </div>
	                </div>
	                <?php endif; ?>
	            </div>
	 
	        </div>
	        <!-- subcontent end -->
	        
	        
	        	        <div id="sidebar">
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
	
	
	           <script language="javascript" type="text/javascript">
	
		var id=<?php echo $this->_tpl_vars['blog']['id']; ?>
;
	var u='<?php echo $this->_tpl_vars['domain']; ?>
';
	var geturl=u+"post.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
&act=comments_list&id="+id;
	
	$('#load_comments_notice').css("display","block");
	
	$.getJSON(geturl,
	function(data){
	  $('#comments_list').html(data.content); 
	  $('#load_comments_notice').css("display","none"); 
	}); 
	
	function post()
	{
		 comment_id=$('#post_comments_id').html();
		 $('#post_comments_notice').show();
	     var params=$('input').serialize(); 
		 p=params+'&content='+$('textarea').val();
		 var ajaxurl=u+'post.php?lan=<?php echo $this->_tpl_vars['lang']; ?>
&act=post_comment&id='+id+'&comment_id='+comment_id;
	     $.ajax({url:ajaxurl,type:'post', dataType:'json',data:p,success:update_comments});
	}
	
	function update_comments(data)
	{
		$('#post_comments_notice').css("display","block"); 
		if(data.error!='no')
		{
			$('#post_comments_notice').html(data.error);
		}
		else
		{
			$('#post_comments_notice').html('评论发布成功');
			var post_form=$('#replay_box').html();
			$('#replay').html('<div id="replay_box">'+post_form+'</div>');
			$('#comments_list').html(data.content); 
			$('textarea').val('');
			$('#post_comments_id').remove(); //请客回复id
		}
	}
	
	function replay(comment_id)
	{
		$('#post_comments_notice').html('');
		$('#post_comments_id').remove(); //请客回复id
		var post_form=$('#replay_box').html();
		$("#replay_box").remove();
		$('#box-'+comment_id).append('<div id="replay_box">'+post_form+'<div id="post_comments_id" style="display:none;">'+comment_id+'</div></div>');
	}
	            </script>