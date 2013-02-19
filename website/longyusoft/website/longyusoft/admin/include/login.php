<?php

if ($action=='pre_login') 
{

	//开始防止其他非该页面登录
	$safe_url=substr(md5($url.$time.$hash_secret),14,28);
	$_SESSION['admin_login_time']=$time;
	$smarty->assign('safe_url',$safe_url);
	$smarty->assign('ip',$ip);
	$smarty->assign('date',$date);
	$smarty->display('login.html');
}

elseif ($action=='login')
{
	$user_name=$_POST['username'];
	$password=$_POST['password'];
	
	/*$safe_url=$_POST['safe_url'];
	$check_safe_url=substr(md5($referer_url.$_SESSION['admin_login_time'].$hash_secret),14,28);
	if ($safe_url!=$check_safe_url) {
		show_message('来源错误，请在正确页面输入登录数据','admin.php?act=pre_login');
		$_SESSION['admin_login_faild']++;
	}*/
	
	$sql='SELECT id,last_time,reg_ip,group_id FROM '.table('user')." WHERE name='".
		$user_name."' AND password='".md5($password)."'";

	if ($row=$db->getrow($sql)) 
	{
		//开始根据登陆ip进行检测
/*		if ($check_ip) 
		{
			require(PBBLOG_ROOT.'/include/ip.function.php');
			if(!check_ip($row['last_ip'],$ip))
			{
				show_message('此次登陆ip不在上次登录ip的区域内','admin.php?act=pre_login');
			}
		}*/
	
		$_SESSION['user_id']=$row['id'];
		$_SESSION['user_name']=$user_name;
		$_SESSION['last_time']=$row['last_time'];
		$_SESSION['last_ip']=$row['ip'];
		$_SESSION['group_id']=$row['group_id'];
		$db->query('UPDATE '.table('user').
		          " SET last_time='" . time() . "', last_ip='" . $ip . "'".
                  " WHERE id='".$row['user_id']."'");
		
        show_message('登录成功','./admin.php?act=index');
	}
	else
	{
		show_message('登录失败，请重新登录','admin.php?act=pre_login');
	}
}

elseif ($action=='logout')
{
	$_SESSION=array();
	session_destroy();
	header('location: ../index.php');
}

?>