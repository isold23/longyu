<?php 
  define('IN_PBBLOG', true);
	require(dirname(__FILE__) . '/include/core.php');

	$type_id=isset($_GET['type']);
	$blog_id=isset($_GET['id'])?intval($_GET['id']):1;
	if($type_id == 1){
		$db->query('UPDATE ' . table('blog') . " SET ding = ding + 1 WHERE id = '$blog_id'");
	}else if($type_id == 2){
		$db->query('UPDATE ' . table('blog') . " SET cai = cai + 1 WHERE id = '$blog_id'");
	}else{

	$cache_id = md5("blog_list_detail".$id);
	$sql = "select a.id,a.title,a.cat_id,a.key_word,a.ding,a.cai,a.post_time,a.tag,a.author,a.description,a.content,a.comment_count,a.trackback_count,a.view_count,b.name from ".table('blog')." AS a  INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id where a.id=".$blog_id;
	$blog=$db->getrow($sql);
	$blog['content']=htmlspecialchars_decode($blog['content']);
	$smarty->assign('blog',$blog);
	assign_page_info($blog['title']);
	$smarty->assign('domain', $domain);
	$db->query('UPDATE ' . table('blog') . " SET view_count = view_count + 1 WHERE id = '$blog_id'");
	
	$blog_category=file_get_contents($domain.'blog_category.php');
	$smarty->assign('blog_category', $blog_category);
	
	$last_blog=file_get_contents($domain.'last_blog.php');
	$smarty->assign('last_blog', $last_blog);
	
	$web_link = file_get_contents($domain.'web_link.php');
	$smarty->assign('web_link',$web_link);
	
	$sql = "select id,title,tag from ".table('blog')." where id != ".$blog['id']." and title like '%".$blog['key_word']."%' ORDER BY post_time DESC LIMIT 8";
	$about_list=$db->getall($sql);
	if($about_list ==  false){
		$sql = "select id,title,tag from ".table('blog')." where cat_id = ".$blog['cat_id']." ORDER BY post_time DESC LIMIT 8";
		$about_list=$db->getall($sql);
	}
	$smarty->assign('about_list',$about_list);
	
	//select top 3 *, (case when user_id = 10055 then 1 else 0 end) as c
//from member..t_user_member with(nolock)
//order by c desc, e_dt desc

	$current_time=date("H");
	$is_late=0;
	if($current_time >= 0 && $current_time <= 5){
		$is_late=1;
		$smarty->assign('is_late',$is_late);
	}
	$sql = "select id,name,image_path from ".table('resource')." WHERE blog_id=".$blog_id." ORDER BY upload_time DESC LIMIT 4";
	$resource_list=$db->getall($sql);
	if($resource_list ==  false){
	$sql = "select id,name,image_path from ".table('resource')." ORDER BY upload_time DESC LIMIT 4";
	$resource_list=$db->getall($sql);
	}
	$smarty->assign('resource_list',$resource_list);

	$smarty->display('detail.html', $cache_id);
	}
?>