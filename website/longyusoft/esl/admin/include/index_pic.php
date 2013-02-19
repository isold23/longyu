<?php

//友情链接列表
if ($action=='index_pic_list')
{
	$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
	$page_size=!empty($page_size)?$page_size:'15';
	$sql='SELECT count(*) FROM '.table('index_pic').' WHERE 1';
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	$page_arr=create_page($page_count,$pg,0);

	$start=($pg-1)*$page_size;
	$sql='SELECT * FROM '.table('index_pic').' WHERE 1 '.
	" ORDER BY id ASC LIMIT ".$start.' , '.$page_size;
	$index_pic_list=$db->getall($sql);

	$smarty->assign('index_pic_list',$index_pic_list);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$smarty->assign('url','admin.php?act=index_pic_list&pg=');

	$smarty->display('index_pic_list.html');
}

//编辑友情链接
elseif ($action=='edit_index_pic')
{
$image_path=$_GET['image_path'];
	$id=$_GET['id'];

	$sql='SELECT * FROM '.table('index_pic')." WHERE id= '".$id."'";
	$module=$db->getrow($sql);
	$smarty->assign('module',$module);
	$smarty->assign('type','act_edit_index_pic');
	$smarty->assign('setup_type',2);
	$smarty->assign('id',$id);
		if($image_path)
	{
	$smarty->assign('image_path',$image_path);
}
else
{
	$smarty->assign('image_path',$module['image_path']);
}
	$smarty->display('add_index_pic.html');
}

//编辑友情链接到数据库
elseif ($action=='act_edit_index_pic')
{
	$id=$_POST['module_id'];
	$image_path=$_POST['image_path'];
	$desc=($_POST['module_desc']);
	$title=($_POST['module_title']);


	$sql='UPDATE '.table('index_pic').
	"  SET  `description` =  '$desc',`title` =  '$title',`image_path` =  '$image_path'".
	" WHERE  `id` ='".$id."'";

	if ($db->query($sql))
	{

		show_message('编辑首页图片成功','admin.php?act=index_pic_list');
	}
	else
	{
		show_message('编辑首页图片失败，请重新返回添加',$referer_url);
	}
}




//安装友情链接页面
elseif ($action=='add_index_pic')
{
	$image_path=$_GET['image_path'];
	$smarty->assign('setup_type',1);
	$smarty->assign('type','act_add_index_pic');
	$smarty->assign('sort',1);
	$smarty->assign('image_path',$image_path);
	$smarty->display('add_index_pic.html');
}


//安装友情链接
elseif ($action=='act_add_index_pic')
{
	$image_path=$_POST['image_path'];
	$desc=($_POST['module_desc']);
	$title=($_POST['module_title']);

	$sql='INSERT INTO '.table('index_pic').
	" (`id` ,`image_path` ,`description` ,`title`   )
		VALUES (NULL , '".$image_path."', '".$desc."', '".$title."')";
	if ($db->query($sql))
	{

		show_message('添加首页图片接成功','admin.php?act=index_pic_list');
	}
	else
	{
		show_message('添加失败，请重新返回添加',$referer_url);
	}
}

//删除安装友情链接
elseif ($action=='del_index_pic')
{
	$module_id=$_GET['id'];
	$sql='DELETE FROM '.table('index_pic')." WHERE id='".$module_id."'";
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