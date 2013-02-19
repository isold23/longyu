<?php
define('IN_PBBLOG', true);

define('PBBLOG_ROOT', str_replace('admin','',str_replace("\\", '/', dirname(__FILE__))));
require_once(PBBLOG_ROOT.'/include/core.php');
$u=dirname($url);
if ($_SESSION['user_id']>0) 
{
	header("location: admin.php?act=index");
}
else 
{
	header("location: admin.php?act=pre_login");
}
?>