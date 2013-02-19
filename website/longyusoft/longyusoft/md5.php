


<?php 
define('IN_PBBLOG', true);
require(dirname(__FILE__) . '/include/core.php');

$action=$_GET['act'];
if($action=='encrypt')
{
	$search_text=$_POST['search_text'];
	$MD5Result=md5($search_text);
	$smarty->assign('MD5Result',$MD5Result);
}
$smarty->display('md5.html');
?>


