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

include(PBBLOG_ROOT.'/include/config.php');								//配置文件
include(PBBLOG_ROOT.'/include/main.function.php');							//主要的函数文件
include(PBBLOG_ROOT.'/include/base.function.php');							//一些基本的函数文件
include(PBBLOG_ROOT.'/include/mysql.class.php');							//数据库类文件
include(PBBLOG_ROOT.'/include/Smarty/libs/Smarty.class.php');				//smarty模板

//如果系统没有安装，跳转到安装页面
if (!$install_lock)
{
	header("location: install.php");
}


//$lan=$_GET['lan'];
$lan='cn';

$template_name = 'default';
if($lan=='en')
{
	include(PBBLOG_ROOT.'/include/lang/english.php');
} else {
	include(PBBLOG_ROOT.'/include/lang/chinese_simplified.php');
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
//$smarty->assign('_template_dir',$smarty->template_dir);
$smarty->assign('user_id',$_SESSION['user_id']);
$smarty->assign('user_name',$_SESSION['user_name']);
$smarty->assign('web_name', $web_name);
$smarty->assign('web_domain', $web_domain);
$smarty->assign('web_url', $web_url);
$smarty->assign('hot_line', $hot_line);
$smarty->assign('address', $address);
$smarty->assign('address_short', $address_short);
$smarty->assign('email', $email);
$smarty->assign('lang', $lan);
$smarty->assign('email_key', $email_key);
$smarty->assign('telephone', $telephone);
$smarty->assign('menu_home', $menu_home);
$smarty->assign('menu_about_us', $menu_about_us);
$smarty->assign('menu_message', $menu_message);
$smarty->assign('menu_contact_us', $menu_contact_us);
$smarty->assign('menu_travel_blog', $menu_travel_blog);
$smarty->assign('popular_destinations', $popular_destinations);
$smarty->assign('menu_destinations', $menu_destinations);
$smarty->assign('menu_tours', $menu_tours);
$smarty->assign('menu_advice', $menu_advice);
$smarty->assign('hot_line_key', $hot_line_key);
$smarty->assign('zipcode_key', $zipcode_key);
$smarty->assign('zipcode', $zipcode);

$smarty->assign('help', $help);
$smarty->assign('close', $close);
$smarty->assign('welcome', $welcome);
$smarty->assign('login', $login);
$smarty->assign('logout', $logout);
$smarty->assign('user_info', $user_info);
$smarty->assign('tours_necessary', $tours_necessary);
$smarty->assign('register', $register);
$smarty->assign('bookmark', $bookmark);
$smarty->assign('user_name_key', $user_name_key);
$smarty->assign('user_password_key', $user_password_key);
$smarty->assign('confirm_password_key', $confirm_password_key);
$smarty->assign('user_website_key', $user_website_key);
$smarty->assign('recommended_tours', $recommended_tours);
$smarty->assign('friend_link', $friend_link);
$smarty->assign('share', $share);
$smarty->assign('detail', $detail);
$smarty->assign('china', $china);
$smarty->assign('kenya', $kenya);
$smarty->assign('office_tel', $office_tel);
$smarty->assign('fax', $fax);
$smarty->assign('address_key', $address_key);
$smarty->assign('first_page', $first_page);
$smarty->assign('last_page', $last_page);
$smarty->assign('previous_page', $previous_page);
$smarty->assign('next_page', $next_page);
$smarty->assign('post', $post);
$smarty->assign('post_message', $post_message);
$smarty->assign('post_time', $post_time);
$smarty->assign('author', $author);
$smarty->assign('name', $name);

$smarty->assign('no_comment', $no_comment);
$smarty->assign('comments', $comments);
$smarty->assign('references', $references);
$smarty->assign('view_times', $view_times);
$smarty->assign('post_comment', $post_comment);
$smarty->assign('load', $load);
$smarty->assign('loading', $loading);
$smarty->assign('about_us', $about_us);
$smarty->assign('foot_content', $foot_content);
$smarty->assign('top_destinations', $top_destinations);
$smarty->assign('top_tours', $top_tours);
$smarty->assign('travel_blog', $travel_blog);
$smarty->assign('travel_advice', $travel_advice);

$smarty->assign('summary', $summary);


$smarty->assign('price', $price);
$smarty->assign('send_email', $send_email);
$smarty->assign('send', $send);
$smarty->assign('subject', $subject);
$smarty->assign('content', $content);
$smarty->assign('travel', $travel);
$smarty->assign('traffic', $traffic);
$smarty->assign('stay', $stay);
$smarty->assign('telephone_consultation', $telephone_consultation);
assign_page_info();


?>