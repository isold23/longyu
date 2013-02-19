<?php 
define('IN_PBBLOG', true);
require(dirname(__FILE__) . '/include/core.php');
$cache_id = md5("web_link");
$sql = "select name,link_url from ".table('blog_link');
$web_link_list=$db->getall($sql);
$smarty->assign('web_link_list',$web_link_list);
$smarty->display('web_link.html', $cache_id);
?>