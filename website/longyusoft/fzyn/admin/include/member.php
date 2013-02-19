<?php


if ($action=='member_list')
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');
	$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
	$page_size=!empty($page_size)?$page_size:'15';
	$sql='SELECT count(*) FROM '.table('user');
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	$page_arr=create_page($page_count,$pg,0);

	$start=($pg-1)*$page_size;
	$sql='SELECT o.id,o.name AS uname,o.reg_time,o.last_time,u.name AS gname FROM '.table('user').
	" o LEFT JOIN ".table('user_group')." u on o.group_id=u.id".
	" ORDER BY o.id DESC  LIMIT ".$start.' , '.$page_size;
	$user_list=$db->getall($sql);
	/*foreach ($user_list as $key=>$val)
	{
		$user_list[$key]['reg_time']=pbtime($user_list[$key]['reg_time']);
		$user_list[$key]['last_time']=pbtime($user_list[$key]['last_time']);
	}*/

	$smarty->assign('user_list',$user_list);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$smarty->assign('url','admin.php?act=member_list&pg=');

	$smarty->display('member_list.html');
}

elseif($action=='reg_member')
{
	
}

elseif ($action=='del_member')
{
	$member_id=intval($_GET['id']);
	$sql='DELETE FROM '.table('user')." WHERE id='".$member_id."'";
	if ($db->query($sql))
	{
		show_message('删除会员成功',$referer_url);
	}
	else
	{
		show_message('删除会员失败，请重新删除',$referer_url);
	}
}

elseif ($action=='add_member')
{
	$sql='SELECT id,name FROM '.table('user_group');
	$group_list=$db->getall($sql);
	$smarty->assign('group_list',$group_list);

	$smarty->assign('type','act_add_member');
	$smarty->display('add_member.html');
}

elseif ($action=='act_add_member')
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');

	$user_name=$_POST['user_name'];
	if (empty($user_name))
	{
		show_message('会员名字不能为空',$referer_url);
	}
	else
	{
		if (isset_member($username))
		{
			show_message('会员名字已经存在',$referer_url);
		}
	}

	$email=$_POST['email'];
	if (empty($email))
	{
		show_message('email不能为空',$referer_url);
	}

	$password=$_POST['password'];
	if (empty($password))
	{
		show_message('密码不能为空',$referer_url);
	}

	$group_id=$_POST['group'];



	$sql='INSERT INTO '.table('user').
	" (`id` ,`name` ,`password` ,`email`,`group_id`,`reg_time`,`last_time` )
		VALUES (NULL , '".$user_name."', '".md5($password)."', '".$email."','".$group_id."','".$time."','".$time."')";

	if ($db->query($sql))
	{
		//show_message('添加会员成功','index.php');
	}
	else
	{
		//show_message('添加会员失败，请重新返回添加','index.php');
	}
}

elseif ($action=='edit_member')
{
	$member_id=intval($_GET['id']);
	if (empty($member_id))
	{
		show_message('用户id不能为空',$referer_url);
	}
	$sql='SELECT * FROM '.table('user')." WHERE id='".$member_id."'";

	if ($row=$db->getrow($sql))
	{
		$smarty->assign('member',$row);
	}
	else
	{
		show_message('读取用户数据失败，请返回重新修改',$referer_url);
	}

	$sql='SELECT id,name FROM '.table('user_group');
	$group_list=$db->getall($sql);

	$smarty->assign('group_list',$group_list);




	$smarty->assign('type','act_edit_member&id='.$member_id);
	$smarty->display('add_member.html');
}

elseif ($action=='act_edit_member')
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');

	$member_id=intval($_GET['id']);
	$user_name=$_POST['user_name'];
	if (empty($user_name))
	{
		show_message('会员名字不能为空',$referer_url);
	}
	else
	{
		if (isset_member($username))
		{
			$u_name=$db->getone('SELECT name FROM '.table('user')." WHERE id='".$user_id."'");
			if ($u_name!=$user_name)
			{
				show_message('会员名字已经存在',$referer_url);
			}
		}
	}

	$email=$_POST['email'];
	if (empty($email))
	{
		show_message('email不能为空',$referer_url);
	}

	$password=$_POST['password'];
	if (!empty($password))
	{
		$password="' , `password`='".md5($password);
	}

	$group_id=$_POST['group'];


	$sql='UPDATE '.table('user').
	"  SET `name` = '".$user_name."',`email` = '".$email."',`group_id` = '".$group_id.
	$password.
	"' WHERE id='".$member_id."'";

	if ($db->query($sql))
	{
		show_message('修改会员成功','admin.php?act=edit_member&id='.$member_id);
	}
	else
	{
		show_message('修改会员失败，请重新返回添加','admin.php?act=edit_member&id='.$member_id);
	}
}

?>