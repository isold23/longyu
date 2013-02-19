	<?php 
	
	  define('IN_PBBLOG', true);
		require(dirname(__FILE__) . '/include/core.php');
		require(dirname(__FILE__) . '/include/json.class.php');
	  
		require_once(PBBLOG_ROOT.'/include/base.function.php');
	
	$act=!empty($_GET['act'])?trim($_GET['act']):'default';
	
	if ($act=='default'||$act=='message_list') 
	{
	
		$pg=isset($_GET['pg'])?intval($_GET['pg']):1;
	
		$page_size=!empty($page_size)?$page_size:'15';
	
		$sql='SELECT count(*) FROM '. table('message');
		$page_count=intval(($db->getone($sql)-1)/$page_size)+1;
	
		$page_arr=create_page($page_count,$pg,0);
	
		$page_url='message.php';
	
		$start=($pg-1)*$page_size;
	
		$cache_id = md5("message_list".$pg);
		
		$sql = "select * from ".table('message')." ORDER BY post_time DESC LIMIT ".$start.' , '.$page_size;
	
		$message_list=$db->getall($sql);
		$smarty->assign('message_list',$message_list);
		
		$smarty->assign('page_url',$page_url);
		$smarty->assign('page_arr',$page_arr);
		$smarty->assign('page_count',$page_count);
		$smarty->assign('pg',$pg);
		$pre=$pg-1; 
		if($pre <= 0)
		{
			$pre = 1;
		}
		$smarty->assign('pre',$pre);
		$next=$pg+1;
		if($next >= $page_count)
		{
			$next = $page_count;
		}
		$smarty->assign('next',$next);	
	
	
	$smarty->display('message.html', $cache_id);
	
	}
	
	elseif($act=='post_message')
	{
		$json   = new JSON;
		$res=array('type'=>'message_list','message_content'=>'','error'=>'no');
		$user_name=$_POST['name'];
		if (empty($user_name))
		{
			if ($_SESSION['user_id']>0)
			{
				$user_name=$db->getone('SELECT name FROM '.table('user')." WHERE id='".$_SESSION['user_id']."'");
			}
			else
			{
				show_message('用户名字不能为空','message.php?act=message_list');
			}
		}
		else
		{
			if ($_SESSION['user_id']>0)
			{
				$u_name=$db->getone('SELECT name FROM '.table('user')." WHERE id='".$_SESSION['user_id']."'");
				if ($u_name!=$user_name)
				{
					$res['error']='您的名字与您注册的名字不一致请返回重新填写';
					show_message('您的名字与您注册的名字不一致请返回重新填写','message.php?act=message_list');
				}
			}
			else
			{
				if ($db->getone('SELECT name FROM '.table('user')." WHERE name='".$user_name."'"))
				{
					$res['error']='您的名字已经被注册了，请返回重新填写';
					show_message('您的名字已经被注册了，请返回重新填写','message.php?act=message_list');
				}
			}
			
		}
	
		$content=$_POST['message_content'];
		if (empty($content))
		{
			$res['error']='留言内容不能为空';
			
			show_message('留言内容不能为空','message.php?act=message_list');
		}
		else
		{
			$content=process_text($content);
		}
		
		$content=htmlspecialchars($content);
		
		$time=date("Y-m-d H:i:s");
	
		$sql="INSERT INTO ".table('message')." (`id` ,`user_id`,`user_name`,`content` ,`post_time` )".
		"VALUES (NULL , '$user_id', '$user_name', '$content', '$time') ";
		if ($db->query($sql)===false)
		{
			show_message('添加失败','message.php?act=message_list');
			
		}
		else
		{
		 show_message('添加成功','message.php?act=message_list');
		}
	}
	?>