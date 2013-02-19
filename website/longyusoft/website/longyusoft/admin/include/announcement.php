<?php

//友情链接列表
if ($action=='announcement_list')
{
	$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
	$page_size=!empty($pager_size)?$pager_size:'20';
	$sql='SELECT count(*) FROM '.table('announcement').' WHERE 1';
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	$page_arr=create_page($page_count,$pg,0);

	$start=($pg-1)*$page_size;
	$sql='SELECT * FROM '.table('announcement').' WHERE 1 '.
	" ORDER BY post_time ASC LIMIT ".$start.' , '.$page_size;
	$announcement_list=$db->getall($sql);

	$smarty->assign('announcement_list',$announcement_list);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$smarty->assign('url','admin.php?act=announcement_list&pg=');
	$smarty->display('announcement_list.html');
}

//编辑友情链接
elseif ($action=='edit_announcement')
{

	$module_id=$_GET['id'];

	$sql='SELECT * FROM '.table('announcement')." WHERE id= '".$module_id."'";
	$module=$db->getrow($sql);
	$smarty->assign('module',$module);
	$smarty->assign('type','act_edit_announcement');
	$smarty->assign('setup_type',2);
	$smarty->assign('id',$id);
	$smarty->display('add_announcement.html');
}

//编辑友情链接到数据库
elseif ($action=='act_edit_announcement')
{
	$module_title=$_POST['module_title'];
	$module_content=$_POST['module_content'];
	$module_id=$_POST['id'];


	if (empty($module_title))
	{
		show_message('请填写网站公告标题',$referer_url);
	}

	if (empty($module_content))
	{
		show_message('请填写网站公告内容',$referer_url);
	}
	$desc=htmlspecialchars($_POST['module_desc']);

	$time=date("Y-m-d H:i:s");

	$sql='UPDATE '.table('announcement').
	"  SET  `title` =  '$module_title',`content` =  '$module_content',`post_time` =  '$time'".
	" WHERE  `id` ='".$module_id."'";

	if ($db->query($sql))
	{

		show_message('编辑网站公告成功','admin.php?act=announcement_list');
	}
	else
	{
		show_message('编辑网站公告失败，请重新返回添加',$referer_url);
	}
}




//安装友情链接页面
elseif ($action=='add_announcement')
{
	$smarty->assign('setup_type',1);
	$smarty->assign('type','act_add_announcement');
	$smarty->assign('sort',1);
	$smarty->display('add_announcement.html');
}


//安装友情链接
elseif ($action=='act_add_announcement')
{
	$module_title=$_POST['module_title'];
	$module_content=$_POST['module_content'];
	$sort=isset($_POST['sort'])?intval($_POST['sort']):1;


	if (empty($module_title))
	{
		show_message('请填写网站公告标题',$referer_url);
	}

	if (empty($module_content))
	{
		show_message('请填写网站公告内容',$referer_url);
	}

	$desc=htmlspecialchars($_POST['module_desc']);
	
		$time=date("Y-m-d H:i:s");

	$sql='INSERT INTO '.table('announcement').
	" (`id` ,`title` ,`content` ,`post_time`  )
		VALUES (NULL , '".$module_title."', '".$module_content."', '".$time."')";
	if ($db->query($sql))
	{

		show_message('添加网站公告成功','admin.php?act=announcement_list');
	}
	else
	{
		show_message('添加失败，请重新返回添加',$referer_url);
	}
}

//删除安装友情链接
elseif ($action=='del_announcement')
{
	$module_id=$_GET['id'];
	$sql='DELETE FROM '.table('announcement')." WHERE id='".$module_id."'";
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