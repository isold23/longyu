<?php
if ($action=='resource_list')
{
	$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
	$page_size=!empty($pager_size)?$pager_size:'20';
	$sql='SELECT count(*) FROM '.table('resource');
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	$page_arr=create_page($page_count,$pg,0);

	$start=($pg-1)*$page_size;
	$sql='SELECT id,name,upload_time,view_time,blog_id FROM '.table('resource').
	" ORDER BY upload_time DESC LIMIT ".$start.' , '.$page_size;
	$resource_list=$db->getall($sql);
	foreach ($resource_list as $key=>$val)
	{
		$resource_list[$key]['add_time']=pbtime($val['add_time']);
		$resource_list[$key]['description']=unprocess_text($val['log_name']);
	}

	$smarty->assign('resource_list',$resource_list);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$smarty->assign('url','admin.php?act=resource_list&pg=');
	$smarty->display('resource_list.html');
}elseif($action=='del_resource'){
	$resource_id=intval($_GET['id']);
	$sql='DELETE FROM '.table('resource')." WHERE id='".$resource_id."'";
	if ($db->query($sql)){
		show_message('删除博客成功',$referer_url);
	}else{
		show_message('删除博客失败，请重新删除',$referer_url);
	}
}elseif($action=='add_resource'){
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
	$smarty->assign('u',str_replace("admin", '', dirname($url)));
	$smarty->display('add_resource.html');
	
	
}elseif ($action=='act_add_resource'){
	require_once(PBBLOG_ROOT.'/include/base.function.php');

	$user_id=intval($_SESSION['user_id']);
	$url_type=intval($_POST['url_type']);
	$resource_name=$_POST['title'];
	if (empty($resource_name)){
		show_message('博客标题不能为空',$referer_url);
	}
	$cat_id=intval($_POST['cat']);
	if (empty($cat_id)){
		show_message('请选择分类',$referer_url);
	}

	$path=process_text($_POST['path']);
	$image_pat=process_text($_POST['image_path']);
	$remark=htmlspecialchars($_POST['remark']);
	$open_type=$_POST['resource_comment'];				//1表示关闭评论
	$blog_id=$_POST['blog_id'];

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
	$author="isold";

	$sql='INSERT INTO '.table('resource').
	" (`id`  ,`cat_id` ,`name` ,`path` ,`image_path` ,`remark` ,`blog_id` ,`upload_time` ,`author` )
		VALUES (NULL ,  '".$cat_id."', '".$resource_name."', '".
	$path."', '".$image_path."', '".$remark."', '".$blog_id."','".$time."', '".$author."')";
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
		
		show_message('添加日志成功','admin.php?act=add_resource');
	}
	else
	{
		show_message('添加日志失败，请重新返回添加','admin.php?act=add_resource');
	}
}

elseif ($action=='edit_resource')
{
	$resource_id=intval($_GET['id']);
	if (empty($resource_id))
	{
		show_message('日志id不能为空',$referer_url);
	}
	$sql='SELECT * FROM '.table('resource')." WHERE id='".$resource_id."'";

	if ($row=$db->getrow($sql))
	{
		$row['remark']=unprocess_text($row['remark']);
		$smarty->assign('resource',$row);
	}
	else
	{
		show_message('读取日志数据失败，请返回重新修改',$referer_url);
	}

	$sql='SELECT id,name  FROM '.table('resource_category ').' ORDER BY id ASC';
	$cat_list=$db->getall($sql);

	$smarty->assign('cat_list',$cat_list);

	//读取用户组数据
	$sql='SELECT id,name FROM '.table('user_group');
	$group_list=$db->getall($sql);
	if ($row['view_group']!='all') {
		$view_group=explode(' ',$row['view_group']);
		foreach ($group_list as $key=>$val)
		{
			//读出并标记已选择的用户组
			if (in_array($val['group_id'],$view_group))
			{
				$group_list[$key]['flag']=1;
			}
		}
	}
	$smarty->assign('group_list',$group_list);

	$smarty->assign('rewrite',$rewrite);
	$smarty->assign('url_type',$row['url_type']);
	$smarty->assign('u',str_replace("admin", '', dirname($url)));
	$smarty->assign('type','act_edit_resource&id='.$resource_id);
	$smarty->display('add_resource.html');
	
	
}elseif ($action=='act_edit_resource')
{

	require_once(PBBLOG_ROOT.'/include/base.function.php');

	$resource_id=intval($_GET['id']);

	if (empty($resource_id))
	{
		show_message('日志id不能为空',$referer_url);
	}


	$resource_name=$_POST['title'];

	if (empty($resource_name))
	{
		show_message('博客标题不能为空',$referer_url);
	}
	
	$cat_id=$_POST['cat'];
	if (empty($resource_name))
	{
		show_message('请选择分类',$referer_url);
	}

	$path=process_text($_POST['path']);
	$image_path=process_text($_POST['image_path']);
	$remark=htmlspecialchars($_POST['remark']);
	$blog_id=$_POST['blog_id'];
	$author='isold';

	$time=date("Y-m-d H:i:s");
	$sql='UPDATE '.table('resource').
	"  SET `name` = '".$resource_name."',`image_path` = '".$image_path."',`path` = '".$path."',`remark` = '".$remark.
	"' , `upload_time`='".$time."',`blog_id`='".$blog_id."',`author`='".$author."', `cat_id`='".$cat_id.
	"' WHERE id='".$resource_id."'";

	if ($db->query($sql))
	{
		show_message('修改资源成功','admin.php?act=edit_resource&id='.$resource_id);
	}
	else
	{
		show_message('修改资源失败，请重新返回添加','admin.php?act=edit_resource&id='.$resource_id);
	}
}

?>