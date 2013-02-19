<?php

//日记列表
if ($action=='daily_list') 
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');
	
	//页数处理
	$pg=isset($_GET['pg'])>0?intval($_GET['pg']):1;
	$page_size=!empty($pager_size)?$pager_size:'20';
	$sql='SELECT count(*) FROM '.table('daily');
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	$page_arr=create_page($page_count,$pg,0);
	
	//获取日记数据
	$start=($pg-1)*$page_size;
	$sql='SELECT * FROM '.table('daily').
			" ORDER BY id ASC  LIMIT ".$start.' , '.$page_size;
	$daily_list=$db->getall($sql);
	
	$smarty->assign('daily_list',$daily_list);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$smarty->assign('url','admin.php?act=daily_list&pg=');
	
	$smarty->display('daily_list.html');
}


elseif ($action=='del_daily')
{
	$daily_id=intval($_GET['id']);
	
	$sql='DELETE FROM '.table('daily')." WHERE id='".$daily_id."'";
	if ($db->query($sql)) 
	{
        show_message('删除日记成功',$referer_url);
	}
	else
	{
		show_message('删除日记失败，请重新删除',$referer_url);
	}
}

elseif ($action=='add_daily')
{
	$smarty->assign('action_pri',$action_pri);
	$smarty->assign('type','act_add_daily');
	$smarty->display('add_daily.html');
}

elseif ($action=='act_add_daily')
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');
	
		$user_id=intval($_SESSION['user_id']);
		$user_name=$_SESSION['user_name'];
		
		$time=date("Y-m-d H:i:s");
		
		$content=process_text($_POST['daily_content']);

	$sql='INSERT INTO '.table('daily').
		" (`id` ,`content` ,`post_time`,`user_id` ,`user_name` )
		VALUES (NULL , '".$content."', '".$time."', '".$user_id."', '".$user_name."')";
		
	if ($db->query($sql)) 
	{
		show_message('添加日记成功','admin.php?act=add_daily');
	}
	else
	{
		show_message('添加日记失败，请重新返回添加','admin.php?act=add_daily');
	}
}

elseif ($action=='edit_daily')
{
	$daily_id=intval($_GET['id']);
	if (empty($daily_id)) 
	{
		show_message('日记id不能为空',$referer_url);
	}
	
	$sql='SELECT * FROM '.table('daily')." WHERE id='".$daily_id."'";
	if($row=$db->getrow($sql))
	{


		$smarty->assign('daily',$row);
		$smarty->assign('action_pri',$action_pri);
	}
	else 
	{
		show_message('读取日记数据失败，请返回重新修改',$referer_url);
	}
	

	$smarty->assign('type','act_edit_daily&id='.$daily_id);
	$smarty->display('add_daily.html');
}

elseif ($action=='act_edit_daily')
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');
	
	$daily_id=intval($_GET['id']);
	if (empty($daily_id)) 
	{
		show_message('日记id不能为空',$referer_url);
	}
	
	$content=process_text($_POST['daily_content']);
	
			$user_id=intval($_SESSION['user_id']);
		$user_name=$_SESSION['user_name'];
		
		$time=date("Y-m-d H:i:s");
	
	$sql='UPDATE '.table('daily').
		"  SET `content` = '".$content."',`post_time` = '".$time."',`user_id` = '".$id."',`user_name` = '".$user_name.
		"' WHERE id='".$daily_id."'";
		
	if ($db->query($sql)) 
	{
		show_message('修改日记成功','admin.php?act=edit_daily&id='.$daily_id);
	}
	else
	{
		show_message('修改日记失败，请重新返回添加','admin.php?act=edit_daily&id='.$daily_id);
	}
}


?>