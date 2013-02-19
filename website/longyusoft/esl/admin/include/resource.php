<?php


if ($action=='resource_list')
{
	$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
	$page_size=!empty($page_size)?$page_size:'15';
	$sql='SELECT count(*) FROM '.table('resource');
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	$page_arr=create_page($page_count,$pg,0);

	$start=($pg-1)*$page_size;
	$sql='SELECT * FROM '.table('resource').
	" ORDER BY upload_time DESC LIMIT ".$start.' , '.$page_size;
	$resource_list=$db->getall($sql);
	foreach ($resource_list as $key=>$val)
	{
		$resource_list[$key]['add_time']=pbtime($val['add_time']);
		$resource_list[$key]['description']=unprocess_text($val['log_title']);
	}

	$smarty->assign('resource_list',$resource_list);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$smarty->assign('url','admin.php?act=resource_list&pg=');
	$smarty->display('resource_list.html');
}


elseif ($action=='del_resource')
{
	$resource_id=intval($_GET['id']);
	$cat_id=intval($db->getone('SELECT cat_id FROM '.table('resource')." WHERE id='".$resource_id."'"));
	$db->query('UPDATE ' . table('resource_category') . " SET resource_count = resource_count - 1 WHERE id = '$cat_id'");
	$sql='DELETE FROM '.table('resource')." WHERE id='".$resource_id."'";
	if ($db->query($sql))
	{
		show_message('删除资源成功',$referer_url);
	}
	else
	{
		show_message('删除资源失败，请重新删除',$referer_url);
	}
}

elseif ($action=='add_resource')
{
	$image_path=$_GET['image_path'];
	
	$sql='SELECT id,name FROM '.table('resource_category')." ORDER BY id ASC ";
	$cat_list=$db->getall($sql);

	//获取子分类，暂时只支持二级分类
	/*foreach ($cat_list as $key=>$val)
	{
		$sql='SELECT cat_id,cat_name,cat_desc,listorder FROM '.table('category').
		" WHERE parent_id=".$val['cat_id']." ORDER BY listorder ASC , cat_id ASC ";
		$cat_list[$key]['children']=$db->getall($sql);
	}*/

	$smarty->assign('cat_list',$cat_list);

	//读取用户组数据
	$sql='SELECT id,name FROM '.table('user_group');
	$group_list=$db->getall($sql);
	$smarty->assign('group_list',$group_list);


	$smarty->assign('type','act_add_resource');
	$smarty->assign('rewrite',$rewrite);
	$smarty->assign('url_type',1);
	$smarty->assign('image_path',$image_path);
	$smarty->assign('u',str_replace("admin", '', dirname($url)));
	$smarty->display('add_resource.html');
}

elseif ($action=='act_add_resource')
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');

	$user_id=intval($_SESSION['user_id']);
	$url_type=intval($_POST['url_type']);
	$resource_title=$_POST['title'];
	$resource_number=$_POST['number'];
	$resource_spec=$_POST['spec'];
	$resource_origin=$_POST['origin'];
	$resource_material=$_POST['material'];
	$resource_weight=$_POST['weight'];
	$resource_price=$_POST['price'];
	$resource_image_path=$_POST['image_path'];
	$travel_price=htmlspecialchars($_POST['travel_price']);
	$travel_feature=($_POST['travel_feature']);
	$trave_note=($_POST['trave_note']);
	
	if (empty($resource_title))
	{
		show_message('资源标题不能为空',$referer_url);
	}
	$cat_id=intval($_POST['cat']);
	if (empty($resource_title))
	{
		show_message('请选择分类',$referer_url);
	}

	$desc=process_text($_POST['description']);
	//$content=htmlspecialchars($_POST['editor']);
	$resource_remark=htmlspecialchars($_POST['remark']);
	$open_type=$_POST['resource_comment'];				//1表示关闭评论

	//对自定义url处理
	if ($url_type==2)
	{
		$url_type=$_POST['url'];

		//对自定义url唯一性检查
		if (!empty($url_type))
		{
			if($db->getone('SELECT url_type FROM '.table('resource')." WHERE url_type='".$url_type."'"))
			{
				show_message('您定义的URL已经存在于其他日志中，请返回重新定义',$referer_url);
			}
		}
	}

	$password=trim($_POST['password']);

	//将选取的用户组连接起来
	if (!empty($_POST['group'])) {
		foreach ($_POST['group'] as $val){
			$group.=$val.' ';
		}
	}
	else {
		$group='all';
	}
	
	$time=date("Y-m-d H:i:s");

	$sql='INSERT INTO '.table('resource').
	" (`id` ,`user_id` ,`cat_id` ,`name` ,`number` ,`spec` ,`upload_time` ,`origin` ,`material` ,`weight` ,`price` ,`image_path`,`remark`,`travel_price`,`travel_feature`,`trave_note` )
		VALUES (NULL , '".$user_id."', '".$cat_id."', '".$resource_title."', '".
	$resource_number."', '".$resource_spec."', '".$time."', '".$resource_origin."', '".$resource_material."','".$resource_weight."', '".$resource_material."', '".$resource_image_path."', '".$resource_remark."', '".$travel_price."', '".$travel_feature."', '".$trave_note."')";
	if ($db->query($sql))
	{
		//开始ping
/*		$u=str_replace("admin", '', dirname($url));
		require(PBresource_ROOT.'home/plugins/ping/ping.php');
		if ($rewrite) 
		{
			if ($url_type==1)
			{
				$resourceurl='resource/'.$db->insert_id().'.html';
			}
			else 
			{
				$resourceurl=$url_type;
			}
		}
		else 
		{
			$resourceurl='resource/'.$db->insert_id().'.html';
		}
		ping($u,$u.$resourceurl);
		*/
		
		$db->query('UPDATE ' . table('resource_category') . " SET resource_count = resource_count + 1 WHERE id = '$cat_id'");

		show_message('添加资源成功','admin.php?act=add_resource');
	}
	else
	{
		show_message('添加资源失败，请重新返回添加','admin.php?act=add_resource');
	}
}

elseif ($action=='edit_resource')
{
	$image_path=$_GET['image_path'];
	$resource_id=intval($_GET['id']);
	if (empty($resource_id))
	{
		show_message('日志id不能为空',$referer_url);
	}
	$sql='SELECT * FROM '.table('resource')." WHERE id='".$resource_id."'";

	if ($row=$db->getrow($sql))
	{
		$smarty->assign('resource',$row);
	}
	else
	{
		show_message('读取资源数据失败，请返回重新修改',$referer_url);
	}

	$sql='SELECT id,name  FROM '.table('resource_category ').' ORDER BY id ASC';
	$cat_list=$db->getall($sql);

	//获取子分类，暂时只支持二级分类
	/*foreach ($cat_list as $key=>$val)
	{
		$sql='SELECT id,name FROM '.table('resource_category ').' ORDER BY id ASC ';
		$cat_list[$key]['children']=$db->getall($sql);
	}*/

	$smarty->assign('cat_list',$cat_list);

	$smarty->assign('rewrite',$rewrite);
	$smarty->assign('url_type',$row['url_type']);
	if($image_path)
	{
	$smarty->assign('image_path',$image_path);
}
else
{
	$smarty->assign('image_path',$row['image_path']);
}
	$smarty->assign('u',str_replace("admin", '', dirname($url)));
	$smarty->assign('type','act_edit_resource&id='.$resource_id.'&cat_id='.$row['cat_id']);
	$smarty->display('add_resource.html');
}

elseif ($action=='act_edit_resource')
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');

	$resource_id=intval($_GET['id']);
	$resource_cat_id=intval($_GET['cat_id']);

	if (empty($resource_id))
	{
		show_message('资源id不能为空',$referer_url);
	}

	$resource_title=$_POST['title'];
	$resource_number=$_POST['number'];
	$resource_spec=$_POST['spec'];
	$resource_origin=$_POST['origin'];
	$resource_material=$_POST['material'];
	$resource_weight=$_POST['weight'];
	$resource_price=$_POST['price'];

	$resource_image_path=($_POST['image_path']);
	if (empty($resource_title))
	{
		show_message('资源标题不能为空',$referer_url);
	}
	$cat_id=$_POST['cat'];
	if (empty($resource_title))
	{
		show_message('请选择分类',$referer_url);
	}

	$desc=process_text($_POST['description']);
	
	$travel_price=htmlspecialchars($_POST['travel_price']);
	$travel_feature=($_POST['travel_feature']);
	$trave_note=($_POST['trave_note']);
	
	$resource_remark=htmlspecialchars($_POST['remark']);

	//对自定义url处理
	$url_type=intval($_POST['url_type']);
	if ($url_type==2)
	{
		$url_type=$_POST['url'];
		
		//对自定义url唯一性检查
		if (!empty($url_type))
		{
			if($db->getone('SELECT url_type FROM '.table('resource')." WHERE url_type='".$url_type."' AND resource_id!='".$resource_id."'"))
			{
				show_message('您定义的URL已经存在于其他资源中，请返回重新定义',$referer_url);
			}
		}
	}

	$password=trim($_POST['password']);

	$time=date("Y-m-d H:i:s");
	$sql='UPDATE '.table('resource').
	"  SET `name` = '".$resource_title."',`number` = '".$resource_number."',`spec` = '".$resource_spec.
	"' ,`remark`='".$resource_remark."',`image_path`='".$resource_image_path."',`travel_price`='".$travel_price."',`travel_feature`='".$travel_feature."',`trave_note`='".$trave_note."', `upload_time`='".$time."', `cat_id`='".$cat_id."' ,`origin`='".$resource_origin."' , `material`='".$resource_material."' , `weight`='".$resource_weight."' , `price`='".$resource_price.
	"' WHERE id='".$resource_id."'";

	if ($db->query($sql))
	{
		$db->query('UPDATE ' . table('resource_category') . " SET resource_count = resource_count - 1 WHERE id = '$resource_cat_id'");
		$db->query('UPDATE ' . table('resource_category') . " SET resource_count = resource_count + 1 WHERE id = '$cat_id'");
		show_message('修改资源成功','admin.php?act=edit_resource&id='.$resource_id);
	}
	else
	{
		show_message('修改资源失败，请重新返回添加','admin.php?act=edit_resource&id='.$resource_id);
	}
}

?>