<?php

//友情链接列表
if ($action=='web_friend_link_list')
{
	$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
	$page_size=!empty($page_size)?$page_size:'15';
	$sql='SELECT count(*) FROM '.table('friendlink').' WHERE 1';
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	$page_arr=create_page($page_count,$pg,0);

	$start=($pg-1)*$page_size;
	$sql='SELECT * FROM '.table('friendlink').' WHERE 1 '.
	" ORDER BY id ASC LIMIT ".$start.' , '.$page_size;
	$web_friend_link_list=$db->getall($sql);

	$smarty->assign('web_friend_link_list',$web_friend_link_list);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$smarty->assign('url','admin.php?act=web_friend_link_list&pg=');

	$smarty->assign('type','act_edit_web_friend_link_sort');
	$smarty->display('web_friend_link_list.html');
}

//编辑友情链接
elseif ($action=='edit_web_friend_link')
{

	$id=$_GET['id'];

	$sql='SELECT * FROM '.table('friendlink')." WHERE id= '".$id."'";
	$module=$db->getrow($sql);
	$smarty->assign('module',$module);
	$smarty->assign('type','act_edit_web_friend_link');
	$smarty->assign('setup_type',2);
	$smarty->assign('sort',$module['sort']);
	$smarty->assign('id',$id);
	$smarty->display('add_web_friend_link.html');
}

//编辑友情链接到数据库
elseif ($action=='act_edit_web_friend_link')
{
	$module_title=$_POST['module_title'];
	$module_content=$_POST['module_content'];
	$module_id=$_POST['id'];
	$sort=isset($_POST['sort'])?intval($_POST['sort']):1;


	if (empty($module_title))
	{
		show_message('请填写友情链接名称',$referer_url);
	}

	if (empty($module_content))
	{
		show_message('请填写友情链接URL',$referer_url);
	}
	$desc=htmlspecialchars($_POST['module_desc']);


	$sql='UPDATE '.table('friendlink').
	"  SET  `name` =  '$module_title',`link_url` =  '$module_content'".
	" WHERE  `id` ='".$module_id."'";

	if ($db->query($sql))
	{

		show_message('编辑友情链接成功','admin.php?act=web_friend_link_list');
	}
	else
	{
		show_message('编辑友情链接失败，请重新返回添加',$referer_url);
	}
}




//安装友情链接页面
elseif ($action=='add_web_friend_link')
{
	$smarty->assign('setup_type',1);
	$smarty->assign('type','act_add_web_friend_link');
	$smarty->assign('sort',1);
	$smarty->display('add_web_friend_link.html');
}


//安装友情链接
elseif ($action=='act_add_web_friend_link')
{
	$module_title=$_POST['module_title'];
	$module_content=$_POST['module_content'];
	$sort=isset($_POST['sort'])?intval($_POST['sort']):1;


	if (empty($module_title))
	{
		show_message('请填写友情链接名称',$referer_url);
	}

	if (empty($module_content))
	{
		show_message('请填写友情链接URL',$referer_url);
	}

	$desc=htmlspecialchars($_POST['module_desc']);

	$sql='INSERT INTO '.table('friendlink').
	" (`id` ,`name` ,`link_url` ,`rss`  )
		VALUES (NULL , '".$module_title."', '".$module_content."', '".$rss."')";
	if ($db->query($sql))
	{

		show_message('添加友情链接成功','admin.php?act=web_friend_link_list');
	}
	else
	{
		show_message('添加失败，请重新返回添加',$referer_url);
	}
}

//删除安装友情链接
elseif ($action=='del_web_friend_link')
{
	$module_id=$_GET['id'];
	$sql='DELETE FROM '.table('friendlink')." WHERE id='".$module_id."'";
	if ($db->query($sql))
	{

		show_message('删除成功',$referer_url);
	}
	else
	{
		show_message('删除失败，请重新删除',$referer_url);
	}
}


?>