<?php 
define('IN_PBBLOG', true);
require(dirname(__FILE__) . '/include/core.php');
$cache_id = md5("last_blog");
$sql = "select id,title from ".table('blog')." ORDER BY post_time DESC LIMIT 10";
$last_blog_list=$db->getall($sql);
$smarty->assign('last_blog_list',$last_blog_list);
$smarty->display('last_blog.html', $cache_id);
?>