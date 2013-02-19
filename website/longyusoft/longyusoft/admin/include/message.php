<?php

//留言列表
if ($action=='message_list') 
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');
	
	//页数处理
	$pg=isset($_GET['pg'])>0?intval($_GET['pg']):1;
	$page_size=!empty($pager_size)?$pager_size:'15';
	$sql='SELECT count(*) FROM '.table('message');
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	$page_arr=create_page($page_count,$pg,0);
	
	//获取留言数据
	$start=($pg-1)*$page_size;
	$sql='SELECT * FROM '.table('message').
			" ORDER BY id ASC  LIMIT ".$start.' , '.$page_size;
	$message_list=$db->getall($sql);
	
	$smarty->assign('message_list',$message_list);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$smarty->assign('url','admin.php?act=message_list&pg=');
	
	$smarty->display('message_list.html');
}


elseif ($action=='del_message')
{
	$message_id=intval($_GET['id']);
	
	$sql='DELETE FROM '.table('message')." WHERE id='".$message_id."'";
	if ($db->query($sql)) 
	{
        show_message('删除留言成功',$referer_url);
	}
	else
	{
		show_message('删除日记失败，请重新删除',$referer_url);
	}
}

elseif ($action=='edit_message')
{
	$message_id=intval($_GET['id']);
	if (empty($message_id)) 
	{
		show_message('留言id不能为空',$referer_url);
	}
	
	$sql='SELECT * FROM '.table('message')." WHERE id='".$message_id."'";
	if($row=$db->getrow($sql))
	{
		$smarty->assign('message',$row);
		$smarty->assign('action_pri',$action_pri);
	}
	else 
	{
		show_message('读取留言数据失败，请返回重新修改',$referer_url);
	}
	

	$smarty->assign('type','act_edit_message&id='.$message_id);
	$smarty->display('add_message.html');
}

elseif ($action=='act_edit_message')
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');
	
	$message_id=intval($_GET['id']);
	if (empty($message_id)) 
	{
		show_message('留言id不能为空',$referer_url);
	}
	
	$content=process_text($_POST['message_content']);
	
			$user_id=intval($_SESSION['user_id']);
		$user_name=$_SESSION['user_name'];
		
		$time=date("Y-m-d H:i:s");
	
	$sql='UPDATE '.table('message').
		"  SET `content` = '".$content."',`post_time` = '".$time."',`user_id` = '".$id."',`user_name` = '".$user_name.
		"' WHERE id='".$message_id."'";
		
	if ($db->query($sql)) 
	{
		show_message('修改留言成功','admin.php?act=edit_message&id='.$message_id);
	}
	else
	{
		show_message('修改留言失败，请重新返回添加','admin.php?act=edit_message&id='.$message_id);
	}
}


?>