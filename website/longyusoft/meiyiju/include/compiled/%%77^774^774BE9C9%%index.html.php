<?php /* Smarty version 2.6.22, created on 2011-07-21 16:16:03
         compiled from index.html */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('modifier', 'truncate', 'index.html', 52, false),)), $this); ?>
<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "header.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>
<!-- index page body start -->
<div id="index-page">
    <div id="index-page-item">
        <div id="index_pic">
            <div id="unit">
             	                <div id="slider1">
                	<ul id="slider1Content">        
                        <li class="slider1Image">
               	 					<a href=""><img src = "<?php echo $this->_tpl_vars['domain']; ?>
<?php echo $this->_tpl_vars['templates_dir']; ?>
images/1.png" alt=""/></a>
                         	<span class="right"><strong><?php echo $this->_tpl_vars['web_name']; ?>
</strong><br />客厅效果</span>
                        </li>
                                                <li class="slider1Image">
               	 					<a href=""><img src = "<?php echo $this->_tpl_vars['domain']; ?>
<?php echo $this->_tpl_vars['templates_dir']; ?>
images/2.png" alt=""/></a>
                         	<span class="right"><strong><?php echo $this->_tpl_vars['web_name']; ?>
</strong><br />客厅效果</span>
                        </li>
                                                <li class="slider1Image">
               	 					<a href=""><img src = "<?php echo $this->_tpl_vars['domain']; ?>
<?php echo $this->_tpl_vars['templates_dir']; ?>
images/3.png" alt=""/></a>
                         	<span class="right"><strong><?php echo $this->_tpl_vars['web_name']; ?>
</strong><br /><?php echo $this->_tpl_vars['index_pic']['description']; ?>
</span>
                        </li>
                                                <li class="slider1Image">
               	 					<a href=""><img src = "<?php echo $this->_tpl_vars['domain']; ?>
<?php echo $this->_tpl_vars['templates_dir']; ?>
images/4.png" alt=""/></a>
                         	<span class="right"><strong><?php echo $this->_tpl_vars['web_name']; ?>
</strong><br /><?php echo $this->_tpl_vars['index_pic']['description']; ?>
</span>
                        </li>
                                                <li class="slider1Image">
               	 					<a href=""><img src = "<?php echo $this->_tpl_vars['domain']; ?>
<?php echo $this->_tpl_vars['templates_dir']; ?>
images/5.png" alt=""/></a>
                         	<span class="right"><strong><?php echo $this->_tpl_vars['web_name']; ?>
</strong><br /><?php echo $this->_tpl_vars['index_pic']['description']; ?>
</span>
                        </li>
                    <div class="clear s3sliderImage"></div>
                  </ul>
                </div>
            </div>
            <!-- unit end -->
        </div>
        <!-- left end -->
    </div>
    <!-- index page item end -->
    



        <div id="index-page-item">
        <div id="left">
            <div id="unit">
                <div id="unit-header">
                    <h1>
                        美宜居热门案例</h1>
                </div>
                <div id="unit-body">
                    <ul>
                        	<?php $_from = $this->_tpl_vars['hot_resource_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['hot_resource']):
?>
                            <li><a href="resource.php?id=<?php echo $this->_tpl_vars['hot_resource']['id']; ?>
">【<?php echo $this->_tpl_vars['hot_resource']['bname']; ?>
】&nbsp<?php echo ((is_array($_tmp=$this->_tpl_vars['hot_resource']['aname'])) ? $this->_run_mod_handler('truncate', true, $_tmp, 50, "...", true) : smarty_modifier_truncate($_tmp, 50, "...", true)); ?>
</a> </li>
                         <?php endforeach; endif; unset($_from); ?>
                    </ul>
                </div>
            </div>
        </div>
        <div id="middle">
            <div id="unit">
                <div id="unit-header">
                    <h1>
                        美宜居最新案例</h1>
                    <h2>
                        <a href="resource.php">more</a>
                    </h2>
                </div>
                <div id="unit-body">
                    <ul>
                        	<?php $_from = $this->_tpl_vars['last_resource_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['last_resource']):
?>
                            <li><a href="resource.php?id=<?php echo $this->_tpl_vars['last_resource']['id']; ?>
">【<?php echo $this->_tpl_vars['last_resource']['bname']; ?>
】&nbsp<?php echo ((is_array($_tmp=$this->_tpl_vars['last_resource']['aname'])) ? $this->_run_mod_handler('truncate', true, $_tmp, 78, "...", true) : smarty_modifier_truncate($_tmp, 78, "...", true)); ?>
&nbsp&nbsp&nbsp&nbsp<?php echo ((is_array($_tmp=$this->_tpl_vars['last_resource']['upload_time'])) ? $this->_run_mod_handler('truncate', true, $_tmp, 10, "", true) : smarty_modifier_truncate($_tmp, 10, "", true)); ?>
</a> </li>
                         <?php endforeach; endif; unset($_from); ?>
                    </ul>
                </div>
            </div>
        </div>
        <div id="right">
            <div id="unit">
                <div id="unit-header">
                    <h1>
                        美宜居工作流程</h1>
                </div>
                <div id="unit-body">
                    <ul>
                            <li><a href="#">1、免费量房</a> </li>
                            <li><a href="#">2、免费设计方案</a> </li>
                            <li><a href="#">3、免费预算报价</a> </li>
                            <li><a href="#">4、免费上门服务</a> </li>
                            <li><a href="#">5、签订装修合同</a> </li>
                            <li><a href="#">6、施工</a> </li>
                            <li><a href="#">7、验收</a> </li>
                    </ul>
                </div>
            </div>
        </div>
        <!-- right end -->
    </div>
    <!-- index page item end -->
    
        <div id="index-page-item">
    	<div id="ad_one">
    		<script type="text/javascript"> 
alimama_pid="mm_13906600_2395151_9224623"; 
alimama_titlecolor="000033"; 
alimama_descolor ="3D81EE"; 
alimama_bgcolor="FFFFFF"; 
alimama_bordercolor="6C82B5"; 
alimama_linkcolor="FFFF66"; 
alimama_bottomcolor="FFFFFF"; 
alimama_anglesize="0"; 
alimama_bgpic="6"; 
alimama_icon="0"; 
alimama_sizecode="12"; 
alimama_width=468; 
alimama_height=60; 
alimama_type=2; 
</script> 
<script src="http://a.alimama.cn/inf.js" type="text/javascript"> 
</script>
    	</div>
    	<div id="ad_two">
<script language="javascript" type="text/javascript">
	yigao_title_color = "null";
	yigao_content_color = "null";
	yigao_background_color = "null";
	yigao_border_color = "D9D9D9";
	yigao_title_bold = "0";
	yigao_content_bold = "0";
	yigao_title_underline = "0";
	yigao_content_underline = "0";
	yigao_width = 468;
	yigao_height = 60;
	yigao_sid = "5b79542b34d570c2";
	yigao_msid = "bb15748fb7e46796";
	yigao_uid = 72924;
	yigao_zid = 126034;
	yigao_pid = 3;
	yigao_type = 1;
	yigao_adamount = 1;
	yigao_cols = 1;
</script>
<script language="javascript" src="http://monitor.yigao.com/info.js"></script>


    	</div>
    </div>
    	   <!-- index page item end -->

    
        <div id="index-page-item">
        <div id="left">
            <div id="unit">
                <div id="unit-header">
                    <h1>
                        热门装修知识</h1>
                </div>
                <div id="unit-body">
                    <ul>
                        	<?php $_from = $this->_tpl_vars['hot_blog_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['hot_log']):
?>
                            <li><a href="detail.php?id=<?php echo $this->_tpl_vars['hot_log']['id']; ?>
">【<?php echo $this->_tpl_vars['hot_log']['name']; ?>
】&nbsp<?php echo ((is_array($_tmp=$this->_tpl_vars['hot_log']['title'])) ? $this->_run_mod_handler('truncate', true, $_tmp, 50, "...", true) : smarty_modifier_truncate($_tmp, 50, "...", true)); ?>
</a> </li>
                         <?php endforeach; endif; unset($_from); ?>
                    </ul>
                </div>
            </div>
        </div>
        <div id="middle">
            <div id="unit">
                <div id="unit-header">
                    <h1>
                        最新装修知识</h1>
                    <h2>
                        <a href="blog.php">more</a>
                    </h2>
                </div>
                <div id="unit-body">
                    <ul>
                        	<?php $_from = $this->_tpl_vars['last_blog_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['last_blog']):
?>
                            <li><a href="detail.php?id=<?php echo $this->_tpl_vars['last_blog']['id']; ?>
">【<?php echo $this->_tpl_vars['last_blog']['name']; ?>
】&nbsp<?php echo ((is_array($_tmp=$this->_tpl_vars['last_blog']['title'])) ? $this->_run_mod_handler('truncate', true, $_tmp, 50, "...", true) : smarty_modifier_truncate($_tmp, 50, "...", true)); ?>

                            	&nbsp&nbsp&nbsp&nbsp<span><?php echo ((is_array($_tmp=$this->_tpl_vars['last_blog']['post_time'])) ? $this->_run_mod_handler('truncate', true, $_tmp, 10, "", true) : smarty_modifier_truncate($_tmp, 10, "", true)); ?>

                            	</span>
                            	</a>
                            	 </li>
                         <?php endforeach; endif; unset($_from); ?>
                    </ul>
                </div>
            </div>
        </div>
        <!-- middle end -->
        <div id="right">
            <div id="unit">
                <div id="unit-header">
                    <h1>
                        装修知识分类</h1>
                </div>
                <div id="unit-body">
                    <ul>
                        	<?php $_from = $this->_tpl_vars['blog_category_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['blog_category']):
?>
                            <li><a href="blog.php?cat=<?php echo $this->_tpl_vars['blog_category']['id']; ?>
"><?php echo $this->_tpl_vars['blog_category']['name']; ?>
【<?php echo $this->_tpl_vars['blog_category']['blog_count']; ?>
】</a> </li>
                         <?php endforeach; endif; unset($_from); ?>
                    </ul>
                </div>
                <!--unit body end -->
            </div>
            <!-- unit end -->
        </div>
        <!-- right end -->
    </div>
    <!-- index-page-item end-->
    
             <div id="index-page-item">
    	<div id="ad-longfan">
    		<img src="./ad/ad_longfan.jpg" width="946"/>
    	</div>
    <!-- unit end -->
    </div>
    <!-- index-page-item end-->
    
    <div id="index-page-item">
        <div id="unit">
                <div id="unit-header">
                    <h1>
                        精品案例展示</h1>
                                            <h2>
                        <a href="resource.php">more</a>
                    </h2>
                </div>
                <div id="unit-body">
                	
<div id="photo_list">
    <ol id="scroll">
    	
    		<?php $_from = $this->_tpl_vars['last_resource_list_18']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['last_resource_18']):
?>
 <li> <a href="resource.php?id=<?php echo $this->_tpl_vars['last_resource_18']['id']; ?>
">
                            	<img src = "<?php echo $this->_tpl_vars['domain']; ?>
upload/<?php echo $this->_tpl_vars['last_resource_18']['image_path']; ?>
" alt="" width="150px" height="150px"/>
                            	
                            	</a>
                            	<center>
                            	<h1><a href="resource.php?id=<?php echo $this->_tpl_vars['last_resource_18']['id']; ?>
"><?php echo $this->_tpl_vars['last_resource_18']['name']; ?>
</a></h1>
                            </center>
                            </li>
 <?php endforeach; endif; unset($_from); ?>
                         
 </ol>
</div>

   <script type="text/javascript">
    var id = function(el) {
            return document.getElementById(el);
        },
        c = id('photo_list');
    if(c) {
        var	ol = id('scroll'),
            lis = ol.getElementsByTagName('li'),
            itemCount = lis.length,
            width = lis[0].offsetWidth, //获得每个img容器的宽度
            marquee = function() {
                c.scrollLeft += 2;
                if(c.scrollLeft % width <= 1){  //当 c.scrollLeft 和 width 相等时，把第一个img追加到最后面
                    ol.appendChild(ol.getElementsByTagName('li')[0]);
                    c.scrollLeft = 0;
                };
            },
            speed = 50; //数值越大越慢

        ol.style.width = width*itemCount + 'px'; //加载完后设置容器长度
        
        var timer = setInterval(marquee, speed);
        c.onmouseover = function() {
            clearInterval(timer);
        };
        c.onmouseout = function() {
            timer = setInterval(marquee, speed);
        };
    };
</script>             	
                	
                	
                	
                	</div>
                <!-- unit body end -->
        </div>
        <!-- baby picturte end -->
    </div>
    <!-- index page item end -->
    
        <div id="index-page-item">
        <div id="left">
            <div id="unit">
                <div id="unit-header">
                    <h1>
                        联系我们</h1>
                                            <h2>
                        <a href="contactus.php">more</a>
                    </h2>
                </div>
                <div id="unit-body">
                	<p>咨询热线：<?php echo $this->_tpl_vars['hot_line']; ?>
</p>
                	<p>业务咨询：<?php echo $this->_tpl_vars['hot_line']; ?>
</p>
                	<p>在线咨询：<a target="_blank" href="http://wpa.qq.com/msgrd?v=3&uin=1045781181&site=qq&menu=yes"><img border="0" src="http://wpa.qq.com/pa?p=2:1045781181:41 &r=0.3734641310805096" alt="点击这里给我发消息" title="点击这里给我发消息"></a></p>
                	<p>电子邮件：<?php echo $this->_tpl_vars['email']; ?>
</p>
                	<p>邮编：067000</p>
                	<p>详细地址：<?php echo $this->_tpl_vars['address']; ?>
</p>
                <div id="con">
                </div>
                </div>
            </div>
        </div>
        <div id="middle">
            <div id="unit">
                <div id="unit-header">
                    <h1>
                        美宜居客户留言</h1>
                 <h2>
                        <a href="message.php">more</a>
                    </h2>
                </div>
                <div id="unit-body">
                   
                        	<?php $_from = $this->_tpl_vars['last_message_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['last_message']):
?>
                            <p><?php echo ((is_array($_tmp=$this->_tpl_vars['last_message']['content'])) ? $this->_run_mod_handler('truncate', true, $_tmp, 78, "", true) : smarty_modifier_truncate($_tmp, 78, "", true)); ?>
&nbsp&nbsp&nbsp&nbsp<?php echo ((is_array($_tmp=$this->_tpl_vars['last_message']['post_time'])) ? $this->_run_mod_handler('truncate', true, $_tmp, 10, "", true) : smarty_modifier_truncate($_tmp, 10, "", true)); ?>
</p>
                         <?php endforeach; endif; unset($_from); ?>
                    
                </div>
            </div>
        </div>
        <div id="right">
            <div id="unit">
                <div id="unit-header">
                    <h1>
                        VIP客户</h1>
                </div>
                <div id="unit-body">
               
                        	<?php $_from = $this->_tpl_vars['new_user_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['user']):
?>
                            <p><?php echo $this->_tpl_vars['user']['name']; ?>
</p> 
                         <?php endforeach; endif; unset($_from); ?>
                    
                </div>
            </div>
        </div>
        <!-- right end -->
    </div>
    <!-- index page item end -->
        <div id="index-page-item">
        	        <div id="friend-links">
            <div id="unit">
                <div id="unit-header">
                    <h1>
                        友情链接</h1>
                </div>
                <div id="unit-body">
                	<p>
                	        <?php $_from = $this->_tpl_vars['friend_link_list']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['friend_link']):
?>
                            <a href="<?php echo $this->_tpl_vars['friend_link']['link_url']; ?>
"><?php echo $this->_tpl_vars['friend_link']['name']; ?>
</a>
                         <?php endforeach; endif; unset($_from); ?>
                  </p>
                </div>
            </div>
        </div>
        <!-- friend links end -->
        
                	        <div id="cooperation">
            <div id="unit">
                <div id="unit-header">
                    <h1>
                        合作品牌</h1>
                </div>
                <div id="unit-body">
                	<p>
                	       
             <a href="#">马可波罗瓷砖</a>
             <a href="#">宏宇陶瓷</a>
             <a href="#">蒙地卡罗陶瓷</a>
             <a href="#">先超吊顶</a>
             <a href="#">欧人地板</a>
   
             <a href="#">宏耐地板</a>
             <a href="#">tata木门</a>
             <a href="#">立邦漆</a>
             <a href="#">箭牌卫浴</a>

                  </p>
                </div>
            </div>
        </div>
        <!-- friend links end -->
        
        </div>
        <!-- index page item end -->
</div>
<!--index page body end -->



<?php $_smarty_tpl_vars = $this->_tpl_vars;
$this->_smarty_include(array('smarty_include_tpl_file' => "footer.html", 'smarty_include_vars' => array()));
$this->_tpl_vars = $_smarty_tpl_vars;
unset($_smarty_tpl_vars);
 ?>