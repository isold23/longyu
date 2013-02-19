<?php 
define('IN_PBBLOG', true);
require(dirname(__FILE__) . '/include/core.php');
$cache_id = md5("resource_category");
$sql = "select id,name,resource_count from ".table('resource_category')." ORDER BY id DESC";
$resource_category_list=$db->getall($sql);
$smarty->assign('resource_category_list',$resource_category_list);
$smarty->display('resource_category.html', $cache_id);
?>