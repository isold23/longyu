<?php
define('IN_PBBLOG', true);

require(dirname(__FILE__) . '/include/core.php');
require(dirname(__FILE__) . '/include/json.class.php');
require_once(PBBLOG_ROOT.'/include/base.function.php');

$msg_id=!empty($_GET['msg_id'])?intval($_GET['msg_id']):'1';
$act=!empty($_GET['act'])?trim($_GET['act']):'default';

if ($act=='post_message'){
	$json   = new JSON;
	$res=array('type'=>'msg_list','content'=>'','error'=>'no');

	$user_name=$_POST['name'];
	if (empty($user_name)){
			if ($_SESSION['user_id']>0){
				$user_name=$db->getone('SELECT name FROM '.table('user')." WHERE id='".$_SESSION['user_id']."'");
			}else{
				$res['error']='name not null';
				die($json->encode($res));
			}
	}else{
		if ($_SESSION['user_id']>0){
			$u_name=$db->getone('SELECT name FROM '.table('user')." WHERE id='".$_SESSION['user_id']."'");
			if ($u_name!=$user_name)
			{
				$res['error']='name not same';
				die($json->encode($res));
			}
		}else{
			if ($db->getone('SELECT name FROM '.table('user')." WHERE name='".$user_name."'"))
			{
				$res['error']='name exit';
				die($json->encode($res));
			}
		}
	}

	$home=$_POST['url'];
	$email=$_POST['email'];
	
	$content1=$_POST['content'];
	if (empty($content1))
	{
		$res['error']='content null';
		die($json->encode($res));
	}else{
		$l_content=process_text($content1);
	}
	
	$time=date("Y-m-d H:i:s");
	
	if($msg_id != 1){
		$u_content=$db->getone('SELECT content FROM '.table('message')." WHERE id='".$msg_id."'");
		$content=$u_content."</br>回复：".htmlspecialchars($l_content);
		$sql='UPDATE '.table('message')."  SET `content` = '".$content."' WHERE id='".$msg_id."'";
		if ($db->query($sql)===false)
		{
			$res['error']='update failed';
			die($json->encode($res));
		}else{
			$res['content']=$content;
			$res['error']='添加成功';
			die($json->encode($res));
		}
	}else{
		$content=htmlspecialchars($l_content);
		$sql="INSERT INTO ".table('message')." (`id` ,`user_id`,`user_name`,`content` ,`post_time` )".
		"VALUES (NULL , '$user_id', '$user_name', '$content', '$time') ";
		if ($db->query($sql)===false)
		{
			$res['error']='insert failed';
		}else{
			$res['error']='添加成功';
		}
	}
	die($json->encode($res));
}

?>