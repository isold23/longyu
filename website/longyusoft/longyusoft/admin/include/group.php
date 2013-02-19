<?php

//会员分组列表
if ($action=='group_list') 
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');
	
	//页数处理
	$pg=isset($_GET['pg'])>0?intval($_GET['pg']):1;
	$page_size=!empty($page_size)?$page_size:'15';
	$sql='SELECT count(*) FROM '.table('user_group');
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	$page_arr=create_page($page_count,$pg,0);
	
	//获取分组数据
	$start=($pg-1)*$page_size;
	$sql='SELECT id,name FROM '.table('user_group').
			" ORDER BY id ASC  LIMIT ".$start.' , '.$page_size;
	$group_list=$db->getall($sql);
	
	$smarty->assign('group_list',$group_list);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$smarty->assign('url','admin.php?act=group_list&pg=');
	
	$smarty->display('group_list.html');
}


elseif ($action=='del_group')
{
	$group_id=intval($_GET['id']);
	
	if ($group_id==1||$group_id==2||$group_id==3) {
		show_message('系统默认分组不允许删除',$referer_url);
	}
	
	$sql='SELECT count(*) FROM '.table('user_group')." WHERE id='".$group_id."'";
	if ($db->getone($sql)>0) {
		show_message('该分类下还有日志，请先删除该分类下的日志',$referer_url);
	}
	
	$sql='DELETE FROM '.table('user_group')." WHERE id='".$group_id."'";
	if ($db->query($sql)) 
	{
        show_message('删除会员分组成功',$referer_url);
	}
	else
	{
		show_message('删除会员分组失败，请重新删除',$referer_url);
	}
}

elseif ($action=='add_group')
{
	require_once(PBBLOG_ROOT.'/admin/include/action_pri.php');
	
	$smarty->assign('action_pri',$action_pri);
	$smarty->assign('type','act_add_group');
	$smarty->display('add_group.html');
}

elseif ($action=='act_add_group')
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');

	$group_name=trim($_POST['group_name']);
	if (empty($group_name)) 
	{
		show_message('会员分组名字不能为空',$referer_url);
	}
	else
	{
		if (isset_group($group_name)) 
		{
			show_message('会员分组名字已经存在',$referer_url);
		}
	}
	
	//如果传递过来的表单为空，那么将权限设置为全部，也就是为all，否则按照传递过来的权限用逗号隔开
	if (empty($_POST['action_pri'])||$_POST['checkall']=='checkbox') 
	{
		$act_pri='all';
	}
	else 
	{
		$act_pri='pbblog';
		foreach ($_POST['action_pri'] as $val)
		{
			$act_pri.=','.$val;
		}
	}
	
	$sql='INSERT INTO '.table('user_group').
		" (`id` ,`name` ,`rights` )
		VALUES (NULL , '".$group_name."', '".$act_pri."')";
		
	if ($db->query($sql)) 
	{
		show_message('添加会员分组成功','admin.php?act=add_group');
	}
	else
	{
		show_message('添加会员分组失败，请重新返回添加','admin.php?act=add_group');
	}
}

elseif ($action=='edit_group')
{
	$group_id=intval($_GET['id']);
	if (empty($group_id)) 
	{
		show_message('分组id不能为空',$referer_url);
	}
	
	$sql='SELECT * FROM '.table('user_group')." WHERE id='".$group_id."'";
	if ($row=$db->getrow($sql)) 
	{
		//开始标记权限数组，标记对应的权限十分已经选择，如果已经选择，那么将其select设置为1
		require(PBBLOG_ROOT.'/admin/include/action_pri.php');
		$group_pri=explode(',',$row['admin_privilege']);
		foreach ($action_pri as $k=>$val)
		{
			foreach ($val['value'] as $key=>$value)
			{
				$act_type_arr=explode(',',$value['act_type']);
				foreach ($act_type_arr as $act_type_arr_val)
				{
					if (in_array($act_type_arr_val,$group_pri)||$group_pri[0]=='all') 
					{
						$action_pri[$k]['value'][$key]['select']=1;
						break;
					}
				}
			}
		}

		$smarty->assign('group',$row);
		$smarty->assign('action_pri',$action_pri);
	}
	else 
	{
		show_message('读取用户组数据失败，请返回重新修改',$referer_url);
	}
	

	$smarty->assign('type','act_edit_group&id='.$group_id);
	$smarty->display('add_group.html');
}

elseif ($action=='act_edit_group')
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');
	
	$group_id=intval($_GET['id']);
	if (empty($group_id)) 
	{
		show_message('分组id不能为空',$referer_url);
	}

	$group_name=trim($_POST['group_name']);
	if (empty($group_name)) 
	{
		show_message('会员分组名字不能为空',$referer_url);
	}
	else
	{
		if (isset_group($group_name)) 
		{
			if ($db->getone('SELECT name FROM '.table('user_group')." WHERE id='".$group_id."'")!=$group_name) {
				show_message('会员分组名字已经存在',$referer_url);
			}
		}
	}
	
	//如果传递过来的表单为空，那么将权限设置为全部，也就是为all，否则按照传递过来的权限用逗号隔开
	if (empty($_POST['action_pri'])||$_POST['checkall']=='checkbox') 
	{
		$act_pri='all';
	}
	else 
	{
		$act_pri='pbblog';
		foreach ($_POST['action_pri'] as $val)
		{
			$act_pri.=','.$val;
		}
	}
	
	$sql='UPDATE '.table('user_group').
		"  SET `name` = '".$group_name."',`rights` = '".$act_pri.
		"' WHERE id='".$group_id."'";
		
	if ($db->query($sql)) 
	{
		show_message('修改会员分组成功','admin.php?act=edit_group&id='.$group_id);
	}
	else
	{
		show_message('修改会员分组失败，请重新返回添加','admin.php?act=edit_group&id='.$group_id);
	}
}


?>