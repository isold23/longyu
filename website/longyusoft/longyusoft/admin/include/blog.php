<?php

if($action=='blog_search')
{
	$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
	$page_size=!empty($pager_size)?$pager_size:'20';
	$sql='SELECT count(*) FROM '.table('blog');
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	$page_arr=create_page($page_count,$pg,0);

	$start=($pg-1)*$page_size;
	$sql='SELECT id,title,post_time,view_count FROM '.table('blog').
	" WHERE title like '%".$search_text."%' ORDER BY post_time DESC LIMIT ".$start.' , '.$page_size;
	$blog_list=$db->getall($sql);
	foreach ($blog_list as $key=>$val)
	{
		$blog_list[$key]['add_time']=pbtime($val['add_time']);
		$blog_list[$key]['description']=unprocess_text($val['log_title']);
	}

	$smarty->assign('blog_list',$blog_list);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$smarty->assign('url','admin.php?act=blog_search&pg=');
	$smarty->display('blog_list.html');
}else if ($action=='blog_list')
{
	$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
	$page_size=!empty($pager_size)?$pager_size:'20';
	$sql='SELECT count(*) FROM '.table('blog');
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	$page_arr=create_page($page_count,$pg,0);

	$start=($pg-1)*$page_size;
	$sql='SELECT id,title,post_time,view_count,key_word FROM '.table('blog').
	" ORDER BY post_time DESC LIMIT ".$start.' , '.$page_size;
	$blog_list=$db->getall($sql);
	foreach ($blog_list as $key=>$val)
	{
		$blog_list[$key]['add_time']=pbtime($val['add_time']);
		$blog_list[$key]['description']=unprocess_text($val['log_title']);
	}

	$smarty->assign('blog_list',$blog_list);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$smarty->assign('url','admin.php?act=blog_list&pg=');
	$smarty->display('blog_list.html');
}elseif($action=='del_blog'){
	$blog_id=intval($_GET['id']);
	$sql='DELETE FROM '.table('blog')." WHERE id='".$blog_id."'";
	if ($db->query($sql)){
		show_message('删除博客成功',$referer_url);
	}else{
		show_message('删除博客失败，请重新删除',$referer_url);
	}
}elseif($action=='add_blog'){
	$sql='SELECT id,name FROM '.table('blog_category')." ORDER BY id ASC ";
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


	$smarty->assign('type','act_add_blog');
	$smarty->assign('rewrite',$rewrite);
	$smarty->assign('url_type',1);
	$smarty->assign('u',str_replace("admin", '', dirname($url)));
	$smarty->display('add_blog.html');
}elseif ($action=='act_add_blog'){
	require_once(PBBLOG_ROOT.'/include/base.function.php');
	$user_id=intval($_SESSION['user_id']);
	$url_type=intval($_POST['url_type']);
	$blog_title=$_POST['title'];
	if (empty($blog_title)){
		show_message('博客标题不能为空',$referer_url);
	}
	$cat_id=intval($_POST['cat']);
	if (empty($cat_id)){
		show_message('请选择分类',$referer_url);
	}

	$desc=process_text($_POST['description']);
	$tag=process_text($_POST['tag']);
	$content=htmlspecialchars($_POST['editor']);
	$open_type=$_POST['blog_comment'];
	$key_word=process_text($_POST['key_word']);

	//对自定义url处理
	if ($url_type==2)
	{
		$url_type=$_POST['url'];

		//对自定义url唯一性检查
		if (!empty($url_type))
		{
			if($db->getone('SELECT url_type FROM '.table('blog')." WHERE url_type='".$url_type."'"))
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

	$sql='INSERT INTO '.table('blog').
	" (`id` ,`user_id` ,`cat_id` ,`title` ,`description` ,`tag` ,`key_word` ,`content` ,`post_time` ,`last_time` ,`comment_count` ,`view_count` ,`password`,`view_group`,`open_type`,`url_type` )
		VALUES (NULL , '".$user_id."', '".$cat_id."', '".$blog_title."', '".
	$desc."', '".$tag."','".$key_word."', '".$content."', '".$time."', '0', '0', '0', '".$password."', '".$group."','".$open_type."','".$url_type."')";
	if ($db->query($sql))
	{
		//开始ping
/*		$u=str_replace("admin", '', dirname($url));
		require(PBBLOG_ROOT.'home/plugins/ping/ping.php');
		if ($rewrite) 
		{
			if ($url_type==1)
			{
				$blogurl='blog/'.$db->insert_id().'.html';
			}
			else 
			{
				$blogurl=$url_type;
			}
		}
		else 
		{
			$blogurl='blog/'.$db->insert_id().'.html';
		}
		ping($u,$u.$blogurl);
		*/
		
		show_message('添加日志成功','admin.php?act=add_blog');
	}
	else
	{
		show_message('添加日志失败，请重新返回添加','admin.php?act=add_blog');
	}
}

elseif ($action=='edit_blog')
{
	$blog_id=intval($_GET['id']);
	if (empty($blog_id))
	{
		show_message('日志id不能为空',$referer_url);
	}
	$sql='SELECT * FROM '.table('blog')." WHERE id='".$blog_id."'";

	if ($row=$db->getrow($sql))
	{
		$row['description']=unprocess_text($row['description']);
		$smarty->assign('blog',$row);
	}
	else
	{
		show_message('读取日志数据失败，请返回重新修改',$referer_url);
	}

	$sql='SELECT id,name,hidden  FROM '.table('blog_category ').' ORDER BY id ASC';
	$cat_list=$db->getall($sql);

	//获取子分类，暂时只支持二级分类
	/*foreach ($cat_list as $key=>$val)
	{
		$sql='SELECT id,name,hidden FROM '.table('blog_category ').' ORDER BY id ASC ';
		$cat_list[$key]['children']=$db->getall($sql);
	}*/

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
	$smarty->assign('type','act_edit_blog&id='.$blog_id);
	$smarty->display('add_blog.html');
}elseif ($action=='act_edit_blog')
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');

	$blog_id=intval($_GET['id']);

	if (empty($blog_id))
	{
		show_message('日志id不能为空',$referer_url);
	}

	$blog_title=$_POST['title'];
	if (empty($blog_title))
	{
		show_message('博客标题不能为空',$referer_url);
	}
	$cat_id=$_POST['cat'];
	if (empty($blog_title))
	{
		show_message('请选择分类',$referer_url);
	}

	$desc=process_text($_POST['description']);
	$tag=process_text($_POST['tag']);
	$key_word=process_text($_POST['key_word']);
	$content=htmlspecialchars($_POST['editor']);
	$open_type=$_POST['blog_comment'];				//1表示关闭评论

	//对自定义url处理
	$url_type=intval($_POST['url_type']);
	if ($url_type==2)
	{
		$url_type=$_POST['url'];
		
		//对自定义url唯一性检查
		if (!empty($url_type))
		{
			if($db->getone('SELECT url_type FROM '.table('blog')." WHERE url_type='".$url_type."' AND blog_id!='".$blog_id."'"))
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
	$sql='UPDATE '.table('blog').
	"  SET `title` = '".$blog_title."',`description` = '".$desc."',`tag` = '".$tag."',`key_word` = '".$key_word."',`content` = '".$content.
	"' , `post_time`='".$time."', `cat_id`='".$cat_id."' , `password`='".$password."' , `open_type`='".$open_type."' , `view_group`='".$group."' , `url_type`='".$url_type.
	"' WHERE id='".$blog_id."'";

	if ($db->query($sql))
	{
		show_message('修改日志成功','admin.php?act=edit_blog&id='.$blog_id);
	}
	else
	{
		show_message('修改日志失败，请重新返回添加','admin.php?act=edit_blog&id='.$blog_id);
	}
}

?>