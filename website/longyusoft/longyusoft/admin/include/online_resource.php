<?php


if ($action=='online_resource_list')
{
	$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
	$page_size=!empty($pager_size)?$pager_size:'20';
	$sql='SELECT count(*) FROM '.table('online_resource');
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	$page_arr=create_page($page_count,$pg,0);

	$start=($pg-1)*$page_size;
	$sql='SELECT id,title,post_time FROM '.table('online_resource').
	" ORDER BY post_time DESC LIMIT ".$start.' , '.$page_size;
	$list=$db->getall($sql);

	$smarty->assign('online_resource_list',$list);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$smarty->assign('url','admin.php?act=online_resource_list&pg=');
	$smarty->display('online_resource_list.html');
	
}elseif($action=='del_online_resource'){
	$id=intval($_GET['id']);
	$sql='DELETE FROM '.table('online_resource')." WHERE id='".$id."'";
	if ($db->query($sql)){
		show_message('删除在线资源成功',$referer_url);
	}else{
		show_message('删除在线资源失败，请重新删除',$referer_url);
	}
}elseif($action=='add_online_resource'){
	
	$sql='SELECT id,name FROM '.table('online_cat')." ORDER BY id ASC ";
	$cat_list=$db->getall($sql);
	
	
	
	
	//获取子分类，暂时只支持二级分类
	foreach ($cat_list as $key=>$val)
	{
		$sql='SELECT * FROM '.table('online_small_cat').
		" WHERE cat_id=".$val['id']." ORDER BY id ASC ";
		$row = $db->getall($sql);
		$size = sizeof($row);
		for($i=0; $i<$size; $i++)
		{
			$cat_list[$key]['children'][$i]["name"] = $row[$i]["name"];
			$cat_list[$key]['children'][$i]["id"] = $row[$i]["id"];
			$cat_list[$key]['children'][$i]["cat_id"] = $row[$i]["cat_id"];
		}
	}
	
	$smarty->assign('cat_list',$cat_list);
	$smarty->assign('json_cat_list',json_encode($cat_list));
	
	//读取用户组数据
	$sql='SELECT id,name FROM '.table('user_group');
	$group_list=$db->getall($sql);
	$smarty->assign('group_list',$group_list);

	$smarty->assign('time_now', time());
	$smarty->assign('type','act_add_online_resource');
	$smarty->assign('rewrite',$rewrite);
	$smarty->assign('url_type',1);
	$smarty->assign('u',str_replace("admin", '', dirname($url)));
	$smarty->display('add_online_resource.html');
}

elseif ($action=='act_add_online_resource'){
	require_once(PBBLOG_ROOT.'/include/base.function.php');
	$user_id=intval($_SESSION['user_id']);
	$url_type=intval($_POST['url_type']);
	$title=$_POST['title'];
	if (empty($title)){
		show_message('在线资源标题不能为空',$referer_url);
	}
	$cat_id=intval($_POST['first_cat']);
	if (empty($cat_id)){
		show_message('请选择分类',$referer_url);
	}
	
	$child_id=intval($_POST['second_cat']);
	
	$content=htmlspecialchars($_POST['editor']);
	$time=date("Y-m-d H:i:s");

	$sql='INSERT INTO '.table('online_resource').
	" (`id` ,`cat_id` ,`title` ,`content` ,`post_time`, `child_cat`)
		VALUES (NULL , '".$cat_id."', '".$title."', '".$content."', '".$time."', '".$child_id."')";
	if ($db->query($sql))
	{
		show_message('添加在线资源成功','admin.php?act=add_online_resource');
	}
	else
	{
		show_message('添加在线资源失败，请重新返回添加','admin.php?act=add_online_resource');
	}
}

elseif ($action=='edit_online_resource')
{
	$id=intval($_GET['id']);
	if (empty($id))
	{
		show_message('在线资源id不能为空',$referer_url);
	}
	$sql='SELECT * FROM '.table('online_resource')." WHERE id='".$id."'";

	if ($row=$db->getrow($sql))
	{
		$row['description']=unprocess_text($row['description']);
		$smarty->assign('blog',$row);
	}
	else
	{
		show_message('读取在线资源数据失败，请返回重新修改',$referer_url);
	}

	$sql='SELECT id,name  FROM '.table('online_cat').' ORDER BY id ASC';
	$cat_list=$db->getall($sql);
	
	//获取子分类，暂时只支持二级分类
	foreach ($cat_list as $key=>$val)
	{
		$sql='SELECT * FROM '.table('online_small_cat').
		" WHERE cat_id=".$val['id']." ORDER BY id ASC ";
		$row = $db->getall($sql);
		$size = sizeof($row);
		for($i=0; $i<$size; $i++)
		{
			$cat_list[$key]['children'][$i]["name"] = $row[$i]["name"];
			$cat_list[$key]['children'][$i]["id"] = $row[$i]["id"];
			$cat_list[$key]['children'][$i]["cat_id"] = $row[$i]["cat_id"];
		}
	}

	$smarty->assign('cat_list',$cat_list);
	
	$smarty->assign('json_cat_list',json_encode($cat_list));
		
	$smarty->assign('rewrite',$rewrite);
	$smarty->assign('url_type',$row['url_type']);
	$smarty->assign('u',str_replace("admin", '', dirname($url)));
	$smarty->assign('type','act_edit_online_resource&id='.$id);
	$smarty->display('add_online_resource.html');
	
}elseif ($action=='act_edit_online_resource')
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');

	$id=intval($_GET['id']);

	if (empty($id))
	{
		show_message('在线资源id不能为空',$referer_url);
	}

	$blog_title=$_POST['title'];
	if (empty($blog_title))
	{
		show_message('在线资源标题不能为空',$referer_url);
	}
	$cat_id=$_POST['first_cat'];
	if (empty($blog_title))
	{
		show_message('请选择分类',$referer_url);
	}
	
	$child_id=$_POST['second_cat'];

	$content=htmlspecialchars($_POST['editor']);

	$time=date("Y-m-d H:i:s");
	$sql='UPDATE '.table('online_resource').
	"  SET `title` = '".$blog_title."',`content` = '".$content.
	"' , `post_time`='".$time."', `child_cat`='".$child_id."', `cat_id`='".$cat_id.
	"' WHERE id='".$id."'";

	if ($db->query($sql))
	{
		show_message('修改在线资源成功','admin.php?act=edit_online_resource&id='.$id);
	}
	else
	{
		show_message('修改在线资源失败，请重新返回添加','admin.php?act=edit_online_resource&id='.$blog_id);
	}
}

?>