<?php 
  define('IN_PBBLOG', true);
  require(dirname(__FILE__) . '/include/core.php');
  
  
  //获取最新日记
  $cache_announcement=md5("index_daily");
	$sql="select * from ".table('daily')." ORDER BY post_time DESC LIMIT 8";
	$daily_list=$db->getall($sql);
	foreach ($daily_list as $key=>$val){
		$daily_list[$key]['content'] = pbsubstr(strip_tags($daily_list[$key]['content']), 66);
	}
	$smarty->assign('daily_list',$daily_list);
  
  //获取公告内容
  //$cache_announcement=md5("index_announcement");
	//$sql="select * from ".table('announcement');
	//$announcement_list=$db->getall($sql);
	//$smarty->assign('announcement_list',$announcement_list);
	
	//获取最新日志
	$cache_id = md5("last_blog");
	$sql = "select a.id,a.title,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id ORDER BY post_time DESC LIMIT 8";
	$last_blog_list=$db->getall($sql);
	
	foreach ($last_blog_list as $key=>$val){
				$last_blog_list[$key]['title'] = pbsubstr($last_blog_list[$key]['title'], 50);
	}
	$smarty->assign('last_blog_list',$last_blog_list);
	
	$cache_id = md5("service_blog");
	$sql = "select a.id,a.title,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id WHERE a.cat_id = 14 ORDER BY post_time DESC LIMIT 8";
	$service_blog_list=$db->getall($sql);
	
	foreach ($service_blog_list as $key=>$val){
				$service_blog_list[$key]['title'] = pbsubstr($service_blog_list[$key]['title'], 50);
	}
	$smarty->assign('service_blog_list',$service_blog_list);
	
	$cache_id = md5("algorithm_blog");
	$sql = "select a.id,a.title,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id WHERE a.cat_id = 21 ORDER BY post_time DESC LIMIT 8";
	$algorithm_blog_list=$db->getall($sql);
	
	foreach ($algorithm_blog_list as $key=>$val){
				$algorithm_blog_list[$key]['title'] = pbsubstr($algorithm_blog_list[$key]['title'], 50);
	}
	$smarty->assign('algorithm_blog_list',$algorithm_blog_list);
	
	$cache_id = md5("search_blog");
	$sql = "select a.id,a.title,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id WHERE a.cat_id = 13 ORDER BY post_time DESC LIMIT 8";
	$search_blog_list=$db->getall($sql);
	
	foreach ($search_blog_list as $key=>$val){
				$search_blog_list[$key]['title'] = pbsubstr($search_blog_list[$key]['title'], 50);
	}
	$smarty->assign('search_blog_list',$search_blog_list);
	
	$cache_id = md5("learning_blog");
	$sql = "select a.id,a.title,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id WHERE a.cat_id = 7 ORDER BY post_time DESC LIMIT 8";
	$learning_blog_list=$db->getall($sql);
	
	foreach ($learning_blog_list as $key=>$val){
				$learning_blog_list[$key]['title'] = pbsubstr($learning_blog_list[$key]['title'], 50);
	}
	$smarty->assign('learning_blog_list',$learning_blog_list);
	
	$cache_id = md5("design_blog");
	$sql = "select a.id,a.title,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id WHERE a.cat_id = 4 ORDER BY post_time DESC LIMIT 8";
	$design_blog_list=$db->getall($sql);
	
	foreach ($design_blog_list as $key=>$val){
				$design_blog_list[$key]['title'] = pbsubstr($design_blog_list[$key]['title'], 50);
	}
	$smarty->assign('design_blog_list',$design_blog_list);
	
	$cache_id = md5("mobile_blog");
	$sql = "select a.id,a.title,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id WHERE a.cat_id = 16 ORDER BY post_time DESC LIMIT 8";
	$mobile_blog_list=$db->getall($sql);
	
	foreach ($mobile_blog_list as $key=>$val){
				$mobile_blog_list[$key]['title'] = pbsubstr($mobile_blog_list[$key]['title'], 50);
	}
	$smarty->assign('mobile_blog_list',$mobile_blog_list);
	
	
	$cache_id = md5("open_source_blog");
	$sql = "select a.id,a.title,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id WHERE a.cat_id = 2 ORDER BY post_time DESC LIMIT 8";
	$open_source_blog_list=$db->getall($sql);
	
	foreach ($open_source_blog_list as $key=>$val){
				$open_source_blog_list[$key]['title'] = pbsubstr($open_source_blog_list[$key]['title'], 50);
	}
	$smarty->assign('open_source_blog_list',$open_source_blog_list);
	
	$cache_id = md5("sql_blog");
	$sql = "select a.id,a.title,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id WHERE a.cat_id = 5 ORDER BY post_time DESC LIMIT 8";
	$sql_blog_list=$db->getall($sql);
	
	foreach ($sql_blog_list as $key=>$val){
				$sql_blog_list[$key]['title'] = pbsubstr($sql_blog_list[$key]['title'], 50);
	}
	$smarty->assign('sql_blog_list',$sql_blog_list);
	
	//日志分类
	$cache_id = md5("blog_category_list");
	$sql = "select id,name from ".table('blog_category')." ORDER BY blog_count DESC LIMIT 8";
	$blog_category_list=$db->getall($sql);
	$smarty->assign('blog_category_list1',$blog_category_list);
	
	//获取最新资源
	$cache_id = md5("last_resource_list");
	$sql = "select a.id,a.name as aname,b.name as bname from ".table('resource')." AS a INNER JOIN ".table('resource_category')." AS b ON a.cat_id = b.id ORDER BY upload_time DESC LIMIT 8";
	$last_resource_list=$db->getall($sql);
	$smarty->assign('last_resource_list',$last_resource_list);
	
	//获取热门资源
	$cache_id = md5("hot_resource_list");
	$sql = "select a.id,a.image_path,a.name as aname,b.name as bname from ".table('resource')." AS a INNER JOIN ".table('resource_category')." AS b ON a.cat_id = b.id WHERE a.cat_id = 4 ORDER BY view_time DESC LIMIT 7";
	$hot_resource_list=$db->getall($sql);
		foreach ($hot_resource_list as $key=>$val){
				$hot_resource_list[$key]['aname'] = pbsubstr($hot_resource_list[$key]['aname'], 20);
	}
	$smarty->assign('hot_resource_list',$hot_resource_list);
	
	//资源分类
	$cache_id = md5("resource_category_list");
	$sql = "select id,name from ".table('resource_category')." ORDER BY id DESC LIMIT 8";
	$resource_category_list=$db->getall($sql);
	$smarty->assign('resource_category_list',$resource_category_list);
	
	
	$cache_id = md5("last_comment_list");
	$sql = "select * from ".table('blog_comment')." ORDER BY post_time DESC LIMIT 8";
	$last_comment_list=$db->getall($sql);
	
	foreach ($last_comment_list as $key=>$val){
		$last_comment_list[$key]['content'] = pbsubstr(strip_tags($last_comment_list[$key]['content']),58);
	}
	
	$smarty->assign('last_comment_list',$last_comment_list);
	
	//友情链接
	$cache_id = md5("friend_link_list");
	//$sql = "select id,name,link_url from ".table('friendlink')." ORDER BY id DESC LIMIT 8";
	$sql = "select id,name,link_url from ".table('friendlink');
	$friend_link_list=$db->getall($sql);
	$smarty->assign('friend_link_list',$friend_link_list);
	
	//最新注册用户
	$cache_id = md5("new_user_list");
	$sql = "select id,name from ".table('user')." ORDER BY reg_time DESC LIMIT 8";
	$new_user_list=$db->getall($sql);
		foreach ($new_user_list as $key=>$val){
		$new_user_list[$key]['name'] = pbsubstr(strip_tags($new_user_list[$key]['name']),21);
	}
	$smarty->assign('new_user_list',$new_user_list);
	
	$smarty->display('index.html');
	?>