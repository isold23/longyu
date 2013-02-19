<?php 
define('IN_PBBLOG', true);
require(dirname(__FILE__) . '/include/core.php');
$cache_id = md5("blog_category");
$sql = "select id,name,blog_count from ".table('blog_category')." ORDER BY id DESC";
$blog_category_list=$db->getall($sql);
$smarty->assign('blog_category_list',$blog_category_list);
$smarty->display('blog_category.html', $cache_id);
?>