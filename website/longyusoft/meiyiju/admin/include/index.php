<?php
if ($action=='index')
{

	$smarty->assign('user_name',$_SESSION['user_name']);
	$smarty->assign('user_id',$_SESSION['user_id']);
	$smarty->assign('last_time',date('Y-m-d H:i:s',$_SESSION['last_time']));
	$smarty->assign('last_ip',$_SESSION['last_ip']);

	$smarty->assign('user_group',group_name($_SESSION['group_id']));

	//服务器信息
	$smarty->assign('upload_max_filesize',ini_get('upload_max_filesize'));
	$smarty->assign('SERVER_SOFTWARE',$_SERVER['SERVER_SOFTWARE']);
	$smarty->assign('mysql_version',$db->version());
	
	//评论信息
	$today_time=strtotime(date('Y-m-d'));
	$today_comments=12;
	$comments=11;
	$smarty->assign('comments',$comments);
	$smarty->assign('today_comments',$today_comments);

	//版权信息
	$smarty->assign('version',file_get_contents(PBBLOG_ROOT.'include/version.txt'));
	$smarty->assign('u',str_replace("admin", '', dirname($url)));				


	$smarty->assign('admin_title',$web_name.'后台首页');
	$smarty->display('index.html');
}

elseif ($action=='get_version')
{
	require(PBBLOG_ROOT. '/include/json.class.php');
	$json   = new JSON;
	//$notice=file_get_contents('http://www.simple-log.com/api.php?act=version&u='.str_replace("admin", '', dirname($url)));
	$notice='';
	$res=explode('|s|',$notice);
	$res['version']=$res[0];
	$res['notice']=$res[1];
	
	die($json->encode($res));
}
?>