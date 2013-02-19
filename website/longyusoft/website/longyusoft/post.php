<?php

define('IN_PBBLOG', true);

require(dirname(__FILE__) . '/include/core.php');
require(dirname(__FILE__) . '/include/json.class.php');

$id=!empty($_GET['id'])?intval($_GET['id']):'1';

$act=!empty($_GET['act'])?trim($_GET['act']):'default';

if ($act=='comments_list')
{
	$json   = new JSON;
	$res=array('type'=>'comments_list','content'=>'');
	$sql='SELECT * FROM '.table('blog_comment')." WHERE blog_id ='".$id."' order by post_time DESC ";
	if ($comments=$db->getall($sql))
	{
		$res['content']=get_comments($comments);
	}
	else
	{
		$res['content']='该日志暂无评论';
	}

	die($json->encode($res));
}

elseif ($act=='resource_comments_list')
{
	$json   = new JSON;
	$res=array('type'=>'resource_comments_list','content'=>'');
	$sql='SELECT * FROM '.table('resource_comment')." WHERE resource_id ='".$id."' order by post_time DESC ";
	if ($comments=$db->getall($sql))
	{
		$res['content']=get_comments($comments);
	}
	else
	{
		$res['content']='该资源暂无评论';
	}

	die($json->encode($res));
}

elseif ($act=='post_comment')
{
	$json   = new JSON;
	$res=array('type'=>'comments_list','content'=>'','error'=>'no');

	$user_name=$_POST['name'];
	if (empty($user_name))
	{
		$res['error']='用户名字不能为空';
		die($json->encode($res));
	}
	else
	{
		if ($_SESSION['user_id']>0)
		{
			$u_name=$db->getone('SELECT name FROM '.table('user')." WHERE id='".$_SESSION['user_id']."'");
			if ($u_name!=$user_name)
			{
				$res['error']='您的名字与您注册的名字不一致请返回重新填写';
				die($json->encode($res));
			}
		}
		else
		{
			if ($db->getone('SELECT name FROM '.table('user')." WHERE name='".$user_name."'"))
			{
				$res['error']='您的名字已经被注册了，请返回重新填写';
				die($json->encode($res));
			}
		}
	}

	$home=$_POST['url'];
	$replay_id=intval($_GET['comment_id']);
	$email=$_POST['email'];

	$content=$_POST['content'];
	if (empty($content))
	{
		$res['error']='评论内容不能为空';
		die($json->encode($res));
	}
	else
	{
		$content=process_text($content);
	}
	
	if ($replay_id>0) 
	{
		$sql='SELECT * FROM '.table('blog_comment')." WHERE id='".$replay_id."'";
		$replay_comment=$db->getrow($sql);
		$replay_comment['content']=htmlspecialchars_decode($replay_comment['content']);
		$replay_time=date('Y-m-d H:i:s',$replay_comment['post_time']);
		$content="<ol> <li> <div class=\"comment_data\">引用 $replay_comment[user_name] 发表于 $replay_time 的评论</div>$replay_comment[content]</li></ol>".$content;
	}
	
	$content=htmlspecialchars($content);
	
	$time=date("Y-m-d H:i:s");

	$sql="INSERT INTO ".table('blog_comment')." (`id` ,`blog_id` ,`user_id`,`user_name`,`content` ,`post_time` ,`ip` ,`status` )".
	"VALUES (NULL , '$id', '$user_id', '$user_name', '$content', '$time', '$ip', '".$comment_safe."') ";
	if ($db->query($sql)===false)
	{
		$res['error']='添加失败，请重试';
	}


	/* 更新评论次数 */
	$db->query('UPDATE ' . table('blog') . " SET comment_count = comment_count + 1 WHERE id = '$id'");

	$sql='SELECT * FROM '.table('blog_comment')." WHERE blog_id='".$id."'  order by post_time ASC ";
	if ($comments=$db->getall($sql))
	{
		$res['content']=get_comments($comments);
	}
	else
	{
		$res['content']='该日志暂无评论';
	}

	die($json->encode($res));
}

elseif ($act=='post_resource_comment')
{
	$json   = new JSON;
	$res=array('type'=>'resource_comments_list','content'=>'','error'=>'no');

	$user_name=$_POST['name'];
	if (empty($user_name))
	{
		$res['error']='用户名字不能为空';
		die($json->encode($res));
	}
	else
	{
		if ($_SESSION['user_id']>0)
		{
			$u_name=$db->getone('SELECT name FROM '.table('user')." WHERE id='".$_SESSION['user_id']."'");
			if ($u_name!=$user_name)
			{
				$res['error']='您的名字与您注册的名字不一致请返回重新填写';
				die($json->encode($res));
			}
		}
		else
		{
			if ($db->getone('SELECT name FROM '.table('user')." WHERE name='".$user_name."'"))
			{
				$res['error']='您的名字已经被注册了，请返回重新填写';
				die($json->encode($res));
			}
		}
	}

	//$home=$_POST['url'];
	
	$replay_id=intval($_GET['comment_id']);
	$email=$_POST['email'];

	$content=$_POST['content'];
	if (empty($content))
	{
		$res['error']='评论内容不能为空';
		die($json->encode($res));
	}
	else
	{
		$content=process_text($content);
	}
	
	if ($replay_id>0) 
	{
		$sql='SELECT * FROM '.table('resource_comment')." WHERE id='".$replay_id."'";
		$replay_comment=$db->getrow($sql);
		$replay_comment['content']=htmlspecialchars_decode($replay_comment['content']);
		$replay_time=date('Y-m-d H:i:s',$replay_comment['post_time']);
		$content="<ol> <li> <div class=\"comment_data\">引用 $replay_comment[user_name] 发表于 $replay_time 的评论</div>$replay_comment[content]</li></ol>".$content;
	}
	
	$content=htmlspecialchars($content);
	
	$time=date("Y-m-d H:i:s");

	$sql="INSERT INTO ".table('resource_comment')." (`id` ,`resource_id` ,`user_id`,`user_name`,`content` ,`post_time` ,`ip` ,`status` )".
	"VALUES (NULL , '$id', '$user_id', '$user_name', '$content', '$time', '$ip', '".$comment_safe."') ";
	if ($db->query($sql)===false)
	{
		$res['error']='添加失败，请重试';
	}


	/* 更新评论次数 */
	//$db->query('UPDATE ' . table('resource') . " SET comment_count = comment_count + 1 WHERE id = '$id'");

	$sql='SELECT * FROM '.table('resource_comment')." WHERE resource_id='".$id."'  order by post_time ASC ";
	if ($comments=$db->getall($sql))
	{
		$res['content']=get_comments($comments);
	}
	else
	{
		$res['content']='该日志暂无评论';
	}

	die($json->encode($res));
}

elseif ($act=='check_name')
{
	$json = new JSON;
	$result=array('content'=>'','error'=>0);
	$member=$_POST['name'];
	if (isset_member($member))
	{
		$result=array('content'=>'用户名已经存在','error'=>1);
		die($json->encode($result));
	}
}

function get_comments($comments)
{
	foreach ($comments as $key=>$val)
	{
		$new_key=$key+1;
		$comment[$new_key]=$comments[$key];
		if ($key%2==0) 
		{
			$comment[$new_key]['odd']=1;
		}
		if (($val['user_id']==$_SESSION['user_id']))
		{
			$comment[$new_key]['edit']=true;
		}
		$comment[$new_key]['content']=unprocess_text($comment[$new_key]['content']);

		//评论是否还在审核中
		if ($val['status']==1)
		{
			$comment[$new_key]['content']='该评论正在审核中';
		}
		$comment[$new_key]['add_time']=pbtime($comment[$new_key]['post_time']);
		
		
	}
	$caching_setting = $GLOBALS['smarty']->caching;
	$GLOBALS['smarty']->caching = false;
	$GLOBALS['smarty']->assign('comments_list',        $comment);
	$GLOBALS['smarty']->assign('group_id',        $GLOBALS['group_id']);
	$res = $GLOBALS['smarty']->fetch('comments.html');
	$GLOBALS['smarty']->caching = $caching_setting;
	return $res;
}

function repaly_comments($id)
{
	$sql='SELECT * FROM '.table('blog_comment')." WHERE parent_id='".$id."'  order by post_time ASC ";
	if ($re_comments=$GLOBALS['db']->getall($sql))
	{
		return $re_comments;
	}
}

function repaly_resource_comments($id)
{
	$sql='SELECT * FROM '.table('resource_comment')." WHERE parent_id='".$id."'  order by post_time ASC ";
	if ($re_comments=$GLOBALS['db']->getall($sql))
	{
		return $re_comments;
	}
}
?>