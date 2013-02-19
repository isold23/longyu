<?php

if ($action=='resource_cat_list')
{
	$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
	$page_size=!empty($page_size)?$page_size:'15';
	$sql='SELECT count(*) FROM '.table('resource_category');
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	$page_arr=create_page($page_count,$pg,0);

	$start=($pg-1)*$page_size;
	$sql='SELECT * FROM '.table('resource_category').
	" ORDER BY id ASC LIMIT ".$start.' , '.$page_size;
	$resource_cat_list=$db->getall($sql);

	//获取子分类，暂时只支持二级分类
	/*foreach ($resource_cat_list as $key=>$val)
	{
		$sql='SELECT cat_id,cat_name,cat_desc,listorder FROM '.table('category').
		" WHERE parent_id=".$val['cat_id']." ORDER BY listorder ASC , cat_id ASC LIMIT ".$start.' , '.$page_size;
		$cat_list[$key]['children']=$db->getall($sql);
	}*/

	$smarty->assign('resource_cat_list',$resource_cat_list);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$smarty->assign('url','admin.php?act=resource_cat_list&pg=');

	$smarty->display('resource_cat_list.html');
}


elseif ($action=='del_resource_cat')
{
	$resource_cat_id=intval($_GET['id']);
	$sql='SELECT count(*) FROM '.table('resource')." WHERE cat_id='".$resource_cat_id."'";
	if ($db->getone($sql)>0) {
		show_message('该分类下还有资源，请先删除该分类下的资源',$referer_url);
	}
	$sql='DELETE FROM '.table('resource_category')." WHERE id='".$resource_cat_id."'";
	if ($db->query($sql))
	{
		show_message('删除分类成功',$referer_url);
	}
	else
	{
		show_message('删除失败，请重新删除',$referer_url);
	}
}

elseif ($action=='add_resource_cat')
{
	$sql='SELECT id,name,resource_count FROM '.table('resource_category');
	$resource_cat_list=$db->getall($sql);

	$smarty->assign('resource_cat_list',$resource_cat_list);
	$smarty->assign('type','act_add_resource_cat');
	$smarty->assign('rewrite',$rewrite);
	$smarty->assign('url_type',1);
	$smarty->assign('u',str_replace("admin", '', dirname($url)));
	$smarty->display('add_resource_cat.html');
}

elseif ($action=='act_add_resource_cat')
{
	$resource_cat_name=$_POST['cat_name'];
	if (empty($resource_cat_name))
	{
		show_message('分类名字不能为空',$referer_url);
	}
	$resource_cat_desc=$_POST['cat_desc'];
	$resource_cat_order=$_POST['cat_order'];
		if (empty($resource_cat_order))
	{
		show_message('分类序列ID不能为空',$referer_url);
	}

	$sql='INSERT INTO '.table('resource_category').
	"  (`id` ,`name` ,`list_order` ) VALUES (".
	"Null, '".$resource_cat_name."','".$resource_cat_order."')";
	if ($db->query($sql))
	{
		show_message('添加分类成功','admin.php?act=add_resource_cat');
	}
	else
	{
		show_message('添加分类失败，请重新返回添加','admin.php?act=add_resource_cat');
	}
}

elseif ($action=='edit_resource_cat')
{
	$resource_cat_id=intval($_GET['id']);
	if (empty($resource_cat_id))
	{
		show_message('分类id不能为空',$referer_url);
	}
	$sql='SELECT * FROM '.table('resource_category')." WHERE id='".$resource_cat_id."'";

	if ($row=$db->getrow($sql))
	{
		$sql='SELECT id,name,list_order,resource_count FROM '.table('resource_category').
		" WHERE id !=".$resource_cat_id;
		$resource_cat_list=$db->getall($sql);

		$smarty->assign('resource_cat_list',$resource_cat_list);
		$smarty->assign('cat_name',$row['name']);
		$smarty->assign('cat_order',$row['list_order']);
	}
	else
	{
		show_message('读取分类数据失败，请返回重新修改',$referer_url);
	}

	$smarty->assign('rewrite',$rewrite);
	$smarty->assign('url_type',$row['url_type']);
	$smarty->assign('u',str_replace("admin", '', dirname($url)));
	$smarty->assign('type','act_edit_resource_cat&id='.$resource_cat_id);
	$smarty->display('add_resource_cat.html');
}

elseif ($action=='act_edit_resource_cat')
{
	$resource_cat_id=intval($_GET['id']);
	$parent_id=intval($_POST['parent_id']);
	if (empty($resource_cat_id))
	{
		show_message('分类id不能为空',$referer_url);
	}

	$resource_cat_name=$_POST['cat_name'];
	if (empty($resource_cat_name))
	{
		show_message('分类名字不能为空',$referer_url);
	}
	$resource_cat_desc=$_POST['cat_desc'];
	$resource_cat_order=$_POST['cat_order'];
		
	//对自定义url处理
	$url_type=intval($_POST['url_type']);
	if ($url_type==2)
	{
		$url_type=$_POST['url'];
	}

	$sql='UPDATE '.table('resource_category').
	"  SET `name` = '".$resource_cat_name."',`list_order` = '".$resource_cat_order.
	"' WHERE id='".$resource_cat_id."'";

	if ($db->query($sql))
	{
		show_message('修改分类成功','admin.php?act=edit_resource_cat&id='.$resource_cat_id);
	}
	else
	{
		show_message('修改分类失败，请重新返回添加','admin.php?act=edit_resource_cat&id='.$resource_cat_id);
	}
}

?>