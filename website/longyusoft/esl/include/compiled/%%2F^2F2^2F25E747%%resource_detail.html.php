<?php /* Smarty version 2.6.22, created on 2011-10-31 14:29:46
         compiled from resource_detail.html */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('insert', 'comments_name', 'resource_detail.html', 175, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "header.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
<div id="subpage">
  <div id="subpage-item">

      <div id="subcontent">
          <div id="resource-detail">
<ul>
<li>
	<p>
		<a href="<?php echo $this->_tpl_vars['domain']; ?>
upload/<?php echo $this->_tpl_vars['resource']['image_path']; ?>
" target="_blank" alt="点击图片查看原图">
			<img src = "<?php echo $this->_tpl_vars['domain']; ?>
upload/<?php echo $this->_tpl_vars['resource']['image_path']; ?>
" alt="点击查看原图" onload="AutoResizeImage(300,300,this)"/>
		</a>	
	</p>
</li>
<li>

	<h1><?php echo $this->_tpl_vars['name']; ?>
: <?php echo $this->_tpl_vars['resource']['aname']; ?>
</h1>
<?php if ($this->_tpl_vars['resource']['cat_id'] == 11): ?>
<h1><?php echo $this->_tpl_vars['travel']; ?>
: <?php echo $this->_tpl_vars['resource']['spec']; ?>
</h1>
<h1><?php echo $this->_tpl_vars['traffic']; ?>
: <?php echo $this->_tpl_vars['resource']['origin']; ?>
</h1>
<h1><?php echo $this->_tpl_vars['stay']; ?>
: <?php echo $this->_tpl_vars['resource']['material']; ?>
</h1>
<h1><?php echo $this->_tpl_vars['price']; ?>
: <?php echo $this->_tpl_vars['resource']['price']; ?>
</h1>
<?php endif; ?>
<h1><?php echo $this->_tpl_vars['author']; ?>
: <?php echo $this->_tpl_vars['resource']['author']; ?>
</h1>
<h1><?php echo $this->_tpl_vars['view_times']; ?>
: <?php echo $this->_tpl_vars['resource']['view_time']; ?>
</h1>
<h1><?php echo $this->_tpl_vars['post_time']; ?>
: <?php echo $this->_tpl_vars['resource']['upload_time']; ?>
</h1>
     
</li>

</ul>


          </div>
          
     
          <!-- resource detail end -->
          
               <?php if ($this->_tpl_vars['resource']['cat_id'] == 11): ?>
        <div class="resource_phone_item">
        	<?php echo $this->_tpl_vars['telephone_consultation']; ?>
: <?php echo $this->_tpl_vars['hot_line']; ?>

        </div>
        
        
   <div class="resource_item">
            <!-- This is the box that all of the tabs and contents of 
         the tabs will reside -->
    <div id="tabs_container">
      
      <!-- These are the tabs -->
      <ul class="tabs">
        <li class="active">
          <a href="javascript:" rel="#tab_1_contents" class="tab">旅游行程</a>
        </li>
        <li><a href="javascript:" rel="#tab_2_contents" class="tab">旅游费用</a></li>
        <li><a href="javascript:" rel="#tab_3_contents" class="tab">行程特色</a></li>
        <li><a href="javascript:" rel="#tab_4_contents" class="tab">注意事项</a></li>
      </ul>
      
      <!-- This is used so the contents don't appear to the 
           right of the tabs -->
      <div class="clear"></div>
      
      <!-- This is a div that hold all the tabbed contents -->
      <div class="tab_contents_container">
    
        <!-- Tab 1 Contents -->
        <div id="tab_1_contents" class="tab_contents tab_contents_active">
          <?php echo $this->_tpl_vars['resource']['remark']; ?>

        </div>
    
        <!-- Tab 2 Contents -->
        <div id="tab_2_contents" class="tab_contents">
          <?php echo $this->_tpl_vars['resource']['travel_price']; ?>

        </div>
    
        <!-- Tab 3 Contents -->
        <div id="tab_3_contents" class="tab_contents">
          <?php echo $this->_tpl_vars['resource']['travel_feature']; ?>

        </div>
        
        <!-- Tab 4 Contents -->
        <div id="tab_4_contents" class="tab_contents">
   <?php echo $this->_tpl_vars['resource']['trave_note']; ?>

        </div>
    
      </div>
    </div>
  </div>
<?php endif; ?>

<?php if ($this->_tpl_vars['resource']['cat_id'] == 10): ?>
          <div id="resource_remark">
          	<div class="unit">
          		<div class="unit_header1 unit-header">
          			<h1 class="unit_header"><?php echo $this->_tpl_vars['detail']; ?>
</h1>
          		</div>
          		<div class="unit-body">
          	<?php echo $this->_tpl_vars['resource']['remark']; ?>

          </div>
          </div>
          </div>
<?php endif; ?>
          
          <div id="resource_share">
          	                      	
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




          </div>
          
          
        <div id="resource_comment">
        		            <?php if ($this->_tpl_vars['open_comment'] == 1): ?>
            <div class="new_notice">
                网站已经关闭评论</div>
            <?php elseif ($this->_tpl_vars['resource']['open_type'] == 1): ?>
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



           <script language="javascript" type="text/javascript">

	var id=<?php echo $this->_tpl_vars['resource']['id']; ?>
;
var u='<?php echo $this->_tpl_vars['domain']; ?>
';
var geturl=u+"post.php?lan="<?php echo $this->_tpl_vars['lang']; ?>
"&act=resource_comments_list&id="+id;

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
&act=post_resource_comment&id='+id+'&comment_id='+comment_id;
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
            