<?php

if ($action=='online_small_cat_list')
{
	$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
	$page_size=!empty($page_size)?$pager_size:'15';
	$sql='SELECT count(*) FROM '.table('online_small_cat');
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	$page_arr=create_page($page_count,$pg,0);

	$start=($pg-1)*$page_size;
	$sql='SELECT * FROM '.table('online_small_cat').
	" ORDER BY id ASC , id ASC LIMIT ".$start.' , '.$page_size;
	$cat_list=$db->getall($sql);

	$smarty->assign('cat_list',$cat_list);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$smarty->assign('url','admin.php?act=online_small_cat_list&pg=');

	$smarty->display('online_small_cat_list.html');
}


elseif ($action=='del_online_small_cat')
{
	$cat_id=intval($_GET['id']);
	$sql='SELECT count(*) FROM '.table('online_resource')." WHERE id='".$cat_id."'";
	if ($db->getone($sql)>0) {
		show_message('该分类下还有日志，请先删除该分类下的日志',$referer_url);
	}
	$sql='DELETE FROM '.table('online_small_cat')." WHERE id='".$cat_id."'";
	if ($db->query($sql))
	{
		show_message('删除分类成功',$referer_url);
	}
	else
	{
		show_message('删除失败，请重新删除',$referer_url);
	}
}

elseif ($action=='add_online_small_cat')
{
	$sql='SELECT id,name FROM '.table('online_cat')." ORDER BY id ASC ";
	$cat_list=$db->getall($sql);
	$smarty->assign('cat_list',$cat_list);
	
	$sql='SELECT id,name FROM '.table('online_small_cat');
	$small_cat_list=$db->getall($sql);

	$smarty->assign('cat_list', $cat_list);
	$smarty->assign('small_cat_list',$small_cat_list);
	$smarty->assign('type','act_add_online_small_cat');
	$smarty->assign('rewrite',$rewrite);
	$smarty->assign('url_type',1);
	$smarty->assign('u',str_replace("admin", '', dirname($url)));
	$smarty->display('add_online_small_cat.html');
}

elseif ($action=='act_add_online_small_cat')
{
	$cat_name=$_POST['cat_name'];
	if (empty($cat_name))
	{
		show_message('分类名字不能为空',$referer_url);
	}
	$parent_id=$_POST['cat'];
	$cat_desc=$_POST['cat_desc'];
	$list_sort=$_POST['list_sort'];
	$sql='INSERT INTO '.table('online_small_cat').
	"  (`id` ,`name` ,`cat_id` ,`description`) VALUES (".
	"Null, '".$cat_name."', '".$parent_id."', '".$cat_desc."')";
	if ($db->query($sql))
	{
		show_message('添加分类成功','admin.php?act=add_online_small_cat');
	}
	else
	{
		show_message('添加分类失败，请重新返回添加','admin.php?act=add_online_small_cat');
	}
}

elseif ($action=='edit_online_small_cat')
{
	$sql='SELECT id,name FROM '.table('online_cat')." ORDER BY id ASC ";
	$cat_list=$db->getall($sql);
	$smarty->assign('cat_list',$cat_list);
	
	$cat_id=intval($_GET['id']);
	if (empty($cat_id))
	{
		show_message('分类id不能为空',$referer_url);
	}
	$sql='SELECT * FROM '.table('online_small_cat')." WHERE id='".$cat_id."'";

	if ($row=$db->getrow($sql))
	{
		$sql='SELECT id,name,description FROM '.table('online_small_cat').
		" WHERE id!=".$cat_id;
		$small_cat_list=$db->getall($sql);

		$smarty->assign('cat_list', $cat_list);
		$smarty->assign('small_cat_list',$small_cat_list);
		$smarty->assign('cat_name',$row['name']);
		$smarty->assign('cat_desc',$row['description']);
		$smarty->assign('blog',$row);
	}
	else
	{
		show_message('读取分类数据失败，请返回重新修改',$referer_url);
	}

	$smarty->assign('rewrite',$rewrite);
	$smarty->assign('u',str_replace("admin", '', dirname($url)));
	$smarty->assign('type','act_edit_online_small_cat&id='.$cat_id);
	$smarty->display('add_online_small_cat.html');
}

elseif ($action=='act_edit_online_small_cat')
{
	$cat_id=intval($_GET['id']);
	if (empty($cat_id))
	{
		show_message('分类id不能为空',$referer_url);
	}
	
	$parent_id=$_POST['cat'];

	$cat_name=$_POST['cat_name'];
	if (empty($cat_name))
	{
		show_message('分类名字不能为空',$referer_url);
	}
	$cat_desc=$_POST['cat_desc'];
	$list_sort=$_POST['list_sort'];
	
	$sql='UPDATE '.table('online_small_cat').
	"  SET `name` = '".$cat_name."',`description` = '".$cat_desc."',`cat_id` = '".$parent_id."' WHERE id='".$cat_id."'";

	if ($db->query($sql))
	{
		show_message('修改分类成功','admin.php?act=edit_online_small_cat&id='.$cat_id);
	}
	else
	{
		show_message('修改分类失败，请重新返回添加','admin.php?act=edit_online_small_cat&id='.$cat_id);
	}
}

?>