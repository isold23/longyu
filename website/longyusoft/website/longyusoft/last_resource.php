<?php 
define('IN_PBBLOG', true);
require(dirname(__FILE__) . '/include/core.php');
$cache_id = md5("last_resource");
$sql = "select id,name from ".table('resource')." ORDER BY upload_time DESC LIMIT 10";
$last_resource_list=$db->getall($sql);
$smarty->assign('last_resource_list',$last_resource_list);
$smarty->display('last_resource.html', $cache_id);
?>