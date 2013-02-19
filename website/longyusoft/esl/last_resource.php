<?php 

define('IN_PBBLOG', true);
require(dirname(__FILE__) . '/include/core.php');

$cache_id = md5("last_resource");

$sql = "select id,name,lang from ".table('resource')." WHERE cat_id=10 AND lang='".$lan."' ORDER BY upload_time DESC LIMIT 10";
$last_resource_list=$db->getall($sql);
$smarty->assign('last_resource_list',$last_resource_list);


$sql = "select id,name,lang from ".table('resource')." WHERE cat_id=11 AND lang='".$lan."' ORDER BY upload_time DESC LIMIT 10";
$last_resource_tour_list=$db->getall($sql);
$smarty->assign('last_resource_tour_list',$last_resource_tour_list);

$smarty->display('last_resource.html', $cache_id);
?>