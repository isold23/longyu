<?php
  define('IN_PBBLOG', true);
	require(dirname(__FILE__) . '/include/core.php');
  
	require_once(PBBLOG_ROOT.'/include/base.function.php');

$act=!empty($_GET['act'])?trim($_GET['act']):'default';

if ($act=='default'||$act=='profile') 
{
	if ($_SESSION['user_id']<1) 
	{
		header('location: user.php?act=login');
	}
	$member_id=$_SESSION['user_id'];
	
	$sql='SELECT * FROM '.table('user')." WHERE id='".$member_id."'";
	
	if ($row=$db->getrow($sql)) 
	{
		$notice=$title='个人资料维护';
		assign_page_info($title);
		$smarty->assign('user',$row);
		$smarty->assign('notice',$notice);
	}
	else 
	{
		show_message('读取用户数据失败，将返回首页','index.php');
	}
	
	$smarty->display('user.html');
}

elseif ($act=='edit_profile')
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');
	
	$member_id=$_SESSION['user_id'];
	$user_name=$_POST['name'];
	if (empty($user_name)) 
	{
		show_message('会员名字不能为空',$referer_url);
	}
	else
	{
		if (isset_member($user_name)) 
		{
			$u_name=$db->getone('SELECT name FROM '.table('user')." WHERE id='".$user_id."'");
			if ($u_name!=$user_name) 
			{
				show_message('会员名字已经存在',$referer_url);
			}
		}
	}
	
	$email=$_POST['email'];
	if (empty($email)) 
	{
		show_message('email不能为空',$referer_url);
	}
	
	$password=$_POST['password'];
	if (!empty($password)) 
	{
		$password="' , `password`='".md5($password);
	}
	
	$home=$_POST['home'];
	
	
	$sql='UPDATE '.table('user').
		"  SET `homepage` = '".$home."',`email` = '".$email.
		$password.
		"' WHERE id='".$member_id."'";
		
	if ($db->query($sql)) 
	{
		show_message('修改个人资料成功','user.php?act=profile');
	}
	else
	{
		show_message('修改个人资料失败，请重新返回修改','user.php?act=profile');
	}
}

elseif ($act=='reg')
{
	if ($_SESSION['user_id']>0) 
	{
		header('location: user.php');
	}
	else 
	{
		$title='注册新用户';
		
		$smarty->assign('notice','注册新用户');
		$smarty->display('reg.html');
	}
}

elseif ($act=='act_reg')
{
	require_once(PBBLOG_ROOT.'/include/base.function.php');
	
	$user_name=$_POST['user_name'];
	if (empty($user_name)) 
	{
		show_message('会员名字不能为空',$referer_url);
	}
	else
	{
		if (isset_member($user_name)) 
		{
			show_message('会员名字已经存在',$referer_url);
		}
	}
	
	$password=$_POST['password'];
	if (empty($password)) 
	{
		show_message('密码不能为空',$referer_url);
	}
	$re_password=$_POST['re_password'];
	if ($password!=$re_password) 
	{
		show_message('两次密码不相同',$referer_url);
	}
	
	$email=$_POST['email'];
	if (empty($email)) 
	{
		show_message('email不能为空',$referer_url);
	}
	
	$homepage=$_POST['homepage'];
	
	
	$group_id=2;

	$time=date("Y-m-d H:i:s");
	
	$sql='INSERT INTO '.table('user').
		" (`id` ,`name` ,`password` ,`email`,`homepage`,`group_id`,`reg_time`,`reg_ip`,`last_time` )
		VALUES (NULL , '".$user_name."', '".md5($password)."', '".$email."','".$homepage."','".$group_id."','".$time."','".$ip."', '".$time."')";
		
	if ($db->query($sql)) 
	{
		$_SESSION['user_id']=$db->insert_id();
		$_SESSION['group_id']=2;
		$_SESSION['user_name']=$user_name;
		$_SESSION['last_time']=$time;
		$_SESSION['last_ip']=$row['ip'];
		show_message('注册成功','user.php?act=profile');
		//注册到会话中
	}
	else
	{
		show_message('注册失败，请重新返回注册','user.php?act=reg');
	}
}

elseif ($act=='login')
{
	if ($_SESSION['user_id']>0) 
	{
		header('location: user.php');
	}
	else 
	{
		//开始防止其他非该页面登录
		$safe_url=substr(md5($url.$time.$hash_secret),14,28);
		$_SESSION['login_time']=$time;
		$smarty->assign('safe_url',$safe_url);
		
		$title='用户登陆';
		
		$smarty->assign('notice','用户登陆');
		$smarty->display('login.html');
	}
}

elseif ($act=='act_login')
{
	$user_name=$_POST['name'];
	$password=$_POST['password'];
	
	$safe_url=$_POST['safe_url'];
	$check_safe_url=substr(md5($referer_url.$_SESSION['login_time'].$hash_secret),14,28);
/*	if ($safe_url!=$check_safe_url) {
		show_message('来源错误，请在正确页面输入登录数据','user.php?act=login');
		$_SESSION['user_login_faild']++;
	}*/
	
	$sql='SELECT id,last_time,reg_ip,group_id FROM '.table('user')." WHERE name='".
		$user_name."' AND password ='".md5($password)."'";

	if ($row=$db->getrow($sql)) 
	{
		$time=date("Y-m-d H:i:s");
		$_SESSION['user_id']=$row['id'];
		$_SESSION['user_name']=$user_name;
		$_SESSION['last_time']=$row['last_time'];
		$_SESSION['last_ip']=$row['ip'];
		$_SESSION['group_id']=$row['group_id'];
		$db->query('UPDATE '.table('user').
		          " SET last_time ='" . $time . "', reg_ip='" . $ip . "'".
                  " WHERE id='".$row['user_id']."'");
		
        show_message('登录成功','user.php?act=profile');
	}
	else
	{
		show_message('登录失败，请重新登录','user.php?act=login');
	}
}

elseif ($act=='logout')
{
	$_SESSION=array();
	session_destroy();
	header('location: index.php');
}

/*对用户的操作的ajax处理部分*/

//检查用户是否已经被注册
elseif ($act=='check_name')
{
	require(dirname(__FILE__) . '/include/json.class.php');
	$json   = new JSON;

	$user_name=$_POST['name'];

	$res=array('error'=>-1);
	$sql='SELECT * FROM '.table('user')." WHERE name='".$user_name."'";
	if ($db->getall($sql)) 
	{
		$res['error']=1;
	}
	die($json->encode($res));
}

//检查E-MAIL,包括是否已经注册和email校验
elseif ($act=='check_email')
{

	require(dirname(__FILE__) . '/include/json.class.php');
	$json   = new JSON;

	$email=$_POST['email'];
	$res=array('error'=>-1);

	//开始校验email的正确性
	$p="^[-a-zA-Z0-9_\.]+\@([0-9A-Za-z][0-9A-Za-z-]+\.)+[A-Za-z]{2,5}$";
	if(!eregi($p,$email))
	{
		$res['error']=2;
		die($json->encode($res));
	}

	//判断email是否已经被注册
	$sql='SELECT * FROM '.table('user')." WHERE email='".$email."'";
	if ($db->getall($sql)) 
	{
		$res['error']=1;
	}
	die($json->encode($res));
}

?>