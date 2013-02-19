<?php 
  define('IN_PBBLOG', true);
	require(dirname(__FILE__) . '/include/core.php');

	$blog_id=isset($_GET['id'])?intval($_GET['id']):1;
	$cache_id = md5("blog_list_detail".$id);
	$sql = "select a.id,a.title,a.cat_id,a.post_time,a.author,a.description,a.content,a.comment_count,a.trackback_count,a.view_count,b.name from ".table('blog')." AS a  INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id where a.id=".$blog_id;
	$blog=$db->getrow($sql);
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

	$smarty->display('detail.html', $cache_id);
	?>