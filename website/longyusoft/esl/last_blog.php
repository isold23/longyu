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

$smarty->display('last_blog.html', $cache_id);
?>