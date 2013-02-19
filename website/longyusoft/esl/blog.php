<?php 

define('IN_PBBLOG', true);
require(dirname(__FILE__) . '/include/core.php');


$cache_id = md5("last_blog");
$sql = "select id,title,post_time from ".table('blog')." WHERE cat_id=3 AND lang='".$lan."' ORDER BY post_time DESC LIMIT 10";
$last_blog_list=$db->getall($sql);
$smarty->assign('last_blog_list',$last_blog_list);

$sql = "select id,title,post_time from ".table('blog')." WHERE cat_id=4 AND lang='".$lan."' ORDER BY post_time DESC LIMIT 10";
$last_trave_blog_list=$db->getall($sql);
$smarty->assign('last_trave_blog_list',$last_trave_blog_list);


$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
$cat_id=isset($_GET['cat'])?intval($_GET['cat']):0;

	$page_size=!empty($page_size)?$page_size:'15';
	
	
	
	if($cat_id > 0)
	{
		$sql='SELECT count(*) FROM '. table('blog')." WHERE cat_id=".$cat_id;
	}
	else
	{
		$sql='SELECT count(*) FROM '. table('blog');
	}
	
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	
	$page_arr=create_page($page_count,$pg,0);
	
	$page_url='blog.php';
	
	$start=($pg-1)*$page_size;
	
	$cache_id = md5("blog_list".$pg);
	if($cat_id > 0)
	{
		$sql = "select a.id,a.cat_id,a.title,a.post_time,a.author,a.description,a.content,a.comment_count,a.trackback_count,a.view_count,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id WHERE a.cat_id=".$cat_id." ORDER BY a.post_time DESC LIMIT ".$start.' , '.$page_size;
	}
	else
	{
		$sql = "select a.id,a.cat_id,a.title,a.post_time,a.author,a.description,a.content,a.comment_count,a.trackback_count,a.view_count,b.name from ".table('blog')." AS a INNER JOIN ".table('blog_category')." AS b ON a.cat_id = b.id ORDER BY a.post_time DESC LIMIT ".$start.' , '.$page_size;
	}
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
	
	$smarty->display('blog_list.html', $cache_id);
	?>


