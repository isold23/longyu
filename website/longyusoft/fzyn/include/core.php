<?php

/*核心公共文件*/

if (!defined('IN_PBBLOG')) {
	die('Access Denied');
}

error_reporting(E_ALL & ~E_NOTICE);

//获得系统运行开始时间
$mtime= explode(' ',microtime());
$start_time=$mtime[1]+$mtime[0];

define('PBBLOG_ROOT', str_replace('include','',str_replace("\\", '/', dirname(__FILE__))));

//定义博客系统的根路径

require(PBBLOG_ROOT.'/include/config.php');								//配置文件
require(PBBLOG_ROOT.'/include/main.function.php');							//主要的函数文件
require(PBBLOG_ROOT.'/include/base.function.php');							//一些基本的函数文件
require(PBBLOG_ROOT.'/include/mysql.class.php');							//数据库类文件
require(PBBLOG_ROOT.'/include/Smarty/libs/Smarty.class.php');				//smarty模板

//如果系统没有安装，跳转到安装页面
if (!$install_lock)
{
	header("location: install.php");
}

//5.1以上的PHP版本设置时区，将默认时区设置成为东8区，也就是北京时间
if (PHP_VERSION>5.1)
{
	if (empty($timezone))
	{
		$timezone='Etc/GMT-8';
	}
	date_default_timezone_set($timezone);
}
$time=time();
$date=date('Y-m-d H:i:s',$time);


// 对传入的变量过滤
if (!get_magic_quotes_gpc())
{
	$_GET  	  = empty($_GET)?'':input_filter($_GET);
	$_POST    = empty($_POST)?'':input_filter($_POST);
	$_COOKIE  = empty($_COOKIE)?'':input_filter($_COOKIE);
}


//开始获得客户端的参数
$ip=ip();
$referer_url=referer_url();
$url=url();

//初始化数据库
$db=new cls_mysql();
$db->connect($dbhost,$dbuser,$dbpw,$dbname,$charset,$pconnect);
unset($dbhost,$dbuser,$dbname,$charset,$pconnect);

//初始化模板
$smarty=new Smarty();

if (defined('IN_PBADMIN'))
{
	$smarty->template_dir=PBBLOG_ROOT.'admin/templates';
	$smarty->compile_dir=PBBLOG_ROOT.'admin/compiled';
	$smarty->caching = false;
}
elseif (!defined('IN_PBADMIN'))
{
	$smarty->template_dir=PBBLOG_ROOT.'/themes/'.$template_name;
	$smarty->compile_dir=PBBLOG_ROOT.'/include/compiled';
	//开启缓存
	if ($caching)
	{
		$smarty->caching = true;
		$smarty->cache_lifetime = '24*3600';
	}
	$smarty->cache_dir      = PBBLOG_ROOT.'/cache';
	
}

$smarty->left_delimiter = "<{";
$smarty->right_delimiter= "}>";


//获得会话信息，并初始化会员信息
session_start();
if (empty($_SESSION['user_id']))
{
	//游客登陆设置
	$_SESSION['user_id']=-1;
	$_SESSION['user_name']='';
	$_SESSION['group_id']=-1;
}
else
{
	$user_id=$_SESSION['user_id'];
	$user_name=$_SESSION['user_name'];
	$group_id=$_SESSION['group_id'];
}
$smarty->assign('_template_dir',$smarty->template_dir);
$smarty->assign('user_id',$_SESSION['user_id']);
$smarty->assign('user_name',$_SESSION['user_name']);

assign_page_info();

?>