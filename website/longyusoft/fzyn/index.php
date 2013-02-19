<?php 
  define('IN_PBBLOG', true);
  require(dirname(__FILE__) . '/include/core.php');
  
  //获取公告内容
  $cache_announcement=md5("index_announcement");
	$sql="select * from ".table('announcement');
	$announcement_list=$db->getall($sql);
	$smarty->assign('announcement_list',$announcement_list);
	
	//获取首页图片地址
  $cache_index_pic=md5("index_pic");
	$sql="select * from ".table('index_pic');
	$index_pic_list=$db->getall($sql);
	$smarty->assign('index_pic_list',$index_pic_list);
	
	
	//获取最新日志
	$cache_id = md5("last_blog");
	$sql = "select a.id,a.title,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id ORDER BY post_time DESC LIMIT 8";
	$last_blog_list=$db->getall($sql);
	$smarty->assign('last_blog_list',$last_blog_list);
	
	//获取热门日志
	$cache_id = md5("hot_blog_list");
	$sql = "select a.id,a.title,a.view_count,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id  ORDER BY view_count DESC LIMIT 8";
	$hot_blog_list=$db->getall($sql);
	$smarty->assign('hot_blog_list',$hot_blog_list);
	
	//日志分类
	$cache_id = md5("blog_category_list");
	$sql = "select id,name,blog_count from ".table('blog_category')." ORDER BY blog_count DESC LIMIT 8";
	$blog_category_list=$db->getall($sql);
	$smarty->assign('blog_category_list',$blog_category_list);
	
	//获取最新资源
	$cache_id = md5("last_resource_list");
	$sql = "select a.id,a.name as aname,a.image_path, b.name as bname from ".table('resource')." AS a INNER JOIN ".table('resource_category')." AS b ON a.cat_id = b.id WHERE is_fine = 1 ORDER BY upload_time DESC LIMIT 6";
	$last_resource_list=$db->getall($sql);
	$smarty->assign('last_resource_list',$last_resource_list);
	
	//获取最新资源
	$cache_id = md5("hot_resource_list");
	$sql = "select a.id,a.name as aname,a.image_path, b.name as bname from ".table('resource')." AS a INNER JOIN ".table('resource_category')." AS b ON a.cat_id = b.id WHERE is_fine = 1 AND a.cat_id = 2 ORDER BY view_time DESC LIMIT 6";
	$hot_resource_list=$db->getall($sql);
	$smarty->assign('hot_resource_list',$hot_resource_list);
	
	//资源分类
	$cache_id = md5("resource_category_list");
	$sql = "select id,name,resource_count from ".table('resource_category')." ORDER BY list_order ASC LIMIT 8";
	$resource_category_list=$db->getall($sql);
	$smarty->assign('resource_category_list',$resource_category_list);
	
	//友情链接
	$cache_id = md5("friend_link_list");
	//$sql = "select id,name,link_url from ".table('friendlink')." ORDER BY id DESC LIMIT 8";
	$sql = "select id,name,link_url from ".table('friendlink');
	$friend_link_list=$db->getall($sql);
	$smarty->assign('friend_link_list',$friend_link_list);
	
	//最新注册用户
	$cache_id = md5("new_user_list");
	$sql = "select id,name from ".table('user')." ORDER BY reg_time DESC LIMIT 4";
	$new_user_list=$db->getall($sql);
	$smarty->assign('new_user_list',$new_user_list);
	
	//注册用户数
	$cache_user_count=md5("web_site_reg_user_count");
	$sql="select count(*) from ".table('user');
	$reg_user_count=intval(($db->getone($sql)));
	$smarty->assign('reg_user_count',$reg_user_count);
	
	//获取最新资源18个用来图片展示
	$cache_id = md5("last_resource_list");
	$sql = "select * from ".table('resource')." ORDER BY upload_time DESC LIMIT 18";
	$last_resource_list_18=$db->getall($sql);
	$smarty->assign('last_resource_list_18',$last_resource_list_18);
	
	
	//获取最新留言
	$cache_id = md5("last_message_list");
	$sql = "select * from ".table('message')." ORDER BY post_time DESC LIMIT 4";
	$last_message_list=$db->getall($sql);
	
		foreach ($last_message_list as $key=>$val){
				$last_message_list[$key]['content'] = pbsubstr($last_message_list[$key]['content'], 55);
	}
	
	$smarty->assign('last_message_list',$last_message_list);
	
	$smarty->display('index.html');
	
	
	?>