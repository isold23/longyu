<?php
  define('IN_PBBLOG', true);
  require(dirname(__FILE__) . '/include/core.php');
	require_once(PBBLOG_ROOT.'/include/base.function.php');
	
	$user_id=intval($_SESSION['user_id']);
	$user_name=$_SESSION['user_name'];
	$time=date("Y-m-d H:i:s");
	$content=process_text($_POST['daily_content']);

	$sql='INSERT INTO '.table('daily').
		" (`id` ,`content` ,`post_time`,`user_id` ,`user_name` )
		VALUES (NULL , '".$content."', '".$time."', '".$user_id."', '".$user_name."')";
		
	if ($db->query($sql)) 
	{
		show_message('添加日记成功','admin.php?act=add_daily');
	}
	else
	{
		show_message('添加日记失败，请重新返回添加','admin.php?act=add_daily');
	}
	
?>