<?php 
define('IN_PBBLOG', true);
require(dirname(__FILE__) . '/include/core.php');

$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
//$type = 
$page_size=!empty($page_size)?$page_size:'15';

$search_text=process_text($_POST['search_text']);
	
$sql='SELECT count(*) FROM '. table('blog')." WHERE title LIKE '%".$search_text."%'"." OR tag LIKE '%".$search_text."%'"." OR description LIKE '%".$search_text."%'";

$blog_count=$db->getone($sql);
$page_count=intval(($db->getone($sql)-1)/$page_size)+1;	
$page_arr=create_page($page_count,$pg,0);
$page_url='blog.php';	
$start=($pg-1)*$page_size;
$cache_id = md5("blog_list".$pg);

$sql = "select a.id,a.cat_id,a.title,a.post_time,a.tag,a.author,a.description,a.content,a.comment_count,a.trackback_count,a.view_count,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id WHERE a.title LIKE '%".$search_text."%'"." OR a.tag LIKE '%".$search_text."%'"." OR a.description LIKE '%".$search_text."%' ORDER BY a.post_time DESC LIMIT ".$start.' , '.$page_size;

$blog_list=$db->getall($sql);
	$smarty->assign('blog_list',$blog_list);
	
	$smarty->assign('page_url',$page_url);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$pre=$pg-1; 
	if($pre <= 0)
	{
		$pre = 1;
	}
	$smarty->assign('pre',$pre);
	$next=$pg+1;
	if($next >= $page_count)
	{
		$next = $page_count;
	}
	$smarty->assign('next',$next);	
	$smarty->assign('cat_id',$cat_id);
	
	$blog_category=file_get_contents($domain.'blog_category.php');
	$smarty->assign('blog_category', $blog_category);
	
	$last_blog=file_get_contents($domain.'last_blog.php');
	$smarty->assign('last_blog', $last_blog);
	
	$web_link = file_get_contents($domain.'web_link.php');
	$smarty->assign('web_link',$web_link);
	$smarty->assign('blog_count', $blog_count);
	
	$smarty->display('blog_list.html', $cache_id);
?>


