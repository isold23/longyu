<?php

define('IN_PBBLOG', true);
define('PBBLOG_ROOT', str_replace('include','',str_replace("\\", '/', dirname(__FILE__))));

//对安装目录尝试自动设置权限
@chmod(PBBLOG_ROOT.'/include/config.php',0777);
@chmod(PBBLOG_ROOT.'/admin/compiled/',0777);
@chmod(PBBLOG_ROOT.'/include/cache/',0777);
@chmod(PBBLOG_ROOT.'/include/compiled/',0777);
@chmod(PBBLOG_ROOT.'/include/upload',0777);

error_reporting(E_ALL & ~E_NOTICE);
require(PBBLOG_ROOT . '/include/config.php');
require(PBBLOG_ROOT.'/include/main.function.php');							//主要的函数文件
require(PBBLOG_ROOT.'/include/base.function.php');							//一些基本的函数文件
require(PBBLOG_ROOT.'/include/mysql.class.php');							//数据库类文件
require(PBBLOG_ROOT.'/include/Smarty/libs/Smarty.class.php');				//smarty模板

if (PHP_VERSION>5.1)
{
	if (empty($timezone))
	{
		$timezone='Etc/GMT-8';
	}
	date_default_timezone_set($timezone);
}

// 对传入的变量过滤
if (!get_magic_quotes_gpc())
{
	$_GET  	  = empty($_GET)?'':input_filter($_GET);
	$_POST    = empty($_POST)?'':input_filter($_POST);
	$_COOKIE  = empty($_COOKIE)?'':input_filter($_COOKIE);
}

//初始化模板
$smarty=new Smarty();
$smarty->template_dir=PBBLOG_ROOT.'/themes/'.$template_name;
$smarty->compile_dir=PBBLOG_ROOT.'/include/compiled';
$smarty->cache_dir      = PBBLOG_ROOT . 'include/cache';


$setup=!empty($_POST['setup'])?$_POST['setup']:'check';

if ($install_lock&&$setup!='finish')
{
	header('location: index.php');
}

if ($setup=='check')
{


	//检查安装环境

	$smarty->assign('php_version',PHP_VERSION);
	$smarty->assign('SERVER_SOFTWARE',$_SERVER['SERVER_SOFTWARE']);

	//检查目录权限
	if (!check_write(PBBLOG_ROOT.'/include/config.php',2))
	{
		$file[]='/home/config.php文件不可写，安装将无法继续进行';
		$set=1;
	}

	if (!check_write(PBBLOG_ROOT.'/admin/compiled/'))
	{
		$file[]='/home/admin/compiled/目录不可写，程序将无法正常运行';
		$set=1;
	}

	if (!check_write(PBBLOG_ROOT.'/include/compiled/'))
	{
		$file[]='/home/compiled/目录不可写，程序将无法正常运行';
		$set=1;
	}

	if (!check_write(PBBLOG_ROOT.'/include/cache/'))
	{
		$file[]='/home/cache/目录不可写，程序将无法正常运行';
		$set=1;
	}

	if (!check_write(PBBLOG_ROOT.'/include/upload'))
	{
		$file[]='/home/upload/目录不可写，此目录放置上传的文件，建议将其设置可写';
	}
	if (!check_write(PBBLOG_ROOT.'/include/backup/'))
	{
		$file[]='/home/backup/目录不可写，此目录用于备份数据库，建议将其设置可写';
	}

	if (!check_write(PBBLOG_ROOT.'/themes/',1,2))
	{
		$file[]='/themes/目录及其所有子目录没有写权限，建议将其设置可写';
	}

	$smarty->assign('id',1);
	$smarty->assign('set',$set);
	$smarty->assign('file_list',$file);

	$smarty->display('install.html');
}

elseif ($setup=='config')
{
	$smarty->assign('id',2);
	$smarty->display('install.html');
}

elseif ($setup=='finish')
{
	$error=array();
	if (empty($_POST['host']))
	{
		$error[]='请填写数据库地址';
	}
	if (empty($_POST['dbname']))
	{
		$error[]='请填写数据库';
	}
	if (empty($_POST['dbuser']))
	{
		$error[]='请填写数据库用户名';
	}
	if (empty($_POST['admin_user']))
	{
		$error[]='请填写管理员账号';
	}
	if (empty($_POST['admin_pass']))
	{
		$error[]='请填写管理员密码';
	}
	if (empty($_POST['webname']))
	{
		$error[]='请填写博客名字';
	}

	if ($error)
	{
		$smarty->assign('error',$error);
		$smarty->assign('id',3);
		$smarty->display('install.html');
		exit;
	}

	$dbhost=$_POST['host'];
	$dbuser=$_POST['dbuser'];
	$dbpw=$_POST['dbpass'];
	$dbname=$_POST['dbname'];
	$db1=new cls_mysql();
	if ($db1->connect($dbhost,$dbuser,$dbpw,$dbname,$charset,$pconnect))
	{
		$error[]='数据库连接错误';
	}

	if (empty($_POST['dbprefix']))
	{
		$dbprefix='longyu_';
	}
	else
	{
		$dbprefix=$_POST['dbprefix'];
	}

	$admin_user=$_POST['admin_user'];
	$admin_pass=$_POST['admin_pass'];
	$blogname=$_POST['blogname'];
	$blogdesc=$_POST['blogdesc'];
	$blog_keyword=$_POST['blogkeyword'];

	$domain=dirname(url()).'/';

	//写入配置文件
	$blog_config="<?php

/**
 * $Author: isold
 * $Date: 2011-01-28
 * www.longyunet.net 
*/ \n\n/*数据库信息*/ \n";
	$blog_config.='$dbhost   = \''.$dbhost."';\n//数据库主机地址\n";
	$blog_config.='$dbname   = \''.$dbname."';\n//数据库名字\n";
	$blog_config.='$dbuser   = \''.$dbuser."';\n//用户名\n";
	$blog_config.='$dbpw   = \''.$dbpw."';\n//数据库密码\n";
	$blog_config.='$dbprefix   = \''.$dbprefix."';\n//表前缀\n";
	$blog_config.='$pconnect   = \''.$pconnect."';\n//是否保持连接\n";

	$blog_config.="\n/*网站相关设置*/ \n";
	$blog_config.='$web_name   = \''.$webname."';\n";
	$blog_config.='$web_desc   = \''.$webdesc."';\n";
	$blog_config.='$web_title   = \''.$webname."';\n";
	$blog_config.='$blog_keyword   = \''.$blog_keyword."';\n";
	$blog_config.='$open_comment   = \''.$open_comment."';\n";
	$blog_config.='$domain   = \''.$domain."';\n";
	$blog_config.='$page_size   = \''.$page_size."';\n";
	$blog_config.='$pager_size   = \''.$pager_size."';\n";

	$blog_config.="\n/*会话、cookie设置*/ \n";
	$blog_config.='$cookie_path   = \''.$cookie_path."';\n";
	$blog_config.='$cookie_domain   = \''.$cookie_domain."';\n";
	$blog_config.='$session   = \''.$session."';\n";

	$blog_config.="\n/*网站编码，暂时只支持utf8*/ \n";
	$blog_config.='$charset   = \''.$charset."';\n";

	$blog_config.="\n/*安全哈希密码*/ \n";
	$blog_config.='$hash_secret   = \''.$hash_secret."';\n//此处与全站的md5相关\n";
	$blog_config.="\$check_ip=true;  \n//是否对后台登陆ip进行检测，默认为开启\n";

	$blog_config.="\n/*模板设置，以后要将模板设置扩展到后台*/ \n";
	$blog_config.='$template_name   = \''.$template_name."';\n//默认为default\n";

	$blog_config.="\$install_lock=true;  \n//网站是否已经安装\n";

	$blog_config.="\n?>";

	//将博客配置保存到文件中
	$fp=@fopen(PBBLOG_ROOT.'/include/config.php',"w") or die('can not open file');
	flock($fp,LOCK_EX);
	fwrite($fp,$blog_config);
	fclose($fp);

	//导入数据库

	$tables = array(
	$dbprefix.'blog',
	$dbprefix.'category',
	$dbprefix.'comment',
	$dbprefix.'link',
	$dbprefix.'modules',
	$dbprefix.'user',
	$dbprefix.'user_group'
	);
		
	//清空已经安装了数据库
	foreach ($tables as $val)
	{
		$db1->query('DROP TABLE IF EXISTS '.$val);
	}
	
	//创建数据库
	/*$database="CREATE DATABASE $dbname DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;";
	$db1->query($database);
	
	$dbadmin="grant select,insert,update,delete on $dbname.* to $dbname@$dbhost identified by $dbpw;";
	$db1->query($dbadmin);*/
	

	$albums_table=$dbprefix.'albums';
	$albums_sql="CREATE TABLE ".$albums_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`name` varchar(50) NOT NULL,
	`create_time` datetime NOT NULL,
	`description` varchar(200) NOT NULL,
	`photo_count` int(11) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($albums_sql);
	
	
	$announce_table=$dbprefix.'announce';
	$announce_sql="CREATE TABLE ".$announce_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`announce` longtext NOT NULL,
	`post_time` datetime NOT NULL,
	`show` tinyint(3) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($announce_sql);
	
	
	$announcement_table=$dbprefix.'announcement';
	$announcement_sql="CREATE TABLE ".$announcement_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`title` varchar(100) NOT NULL,
	`content` longtext NOT NULL,
	`post_time` datetime NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($announcement_sql);
	
	$blog_table=$dbprefix.'blog';
	$blog_sql="CREATE TABLE ".$blog_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`cat_id` int(11) NOT NULL,
	`title` varchar(255) NOT NULL,
	`author` varchar(25) NOT NULL,
	`trackback_url` varchar(255) NOT NULL,
	`content` longtext NOT NULL,
	`mode` tinyint(3) NOT NULL,
	`locked` tinyint(3) NOT NULL,
	`selected` tinyint(3) NOT NULL,
	`post_time` datetime NOT NULL,
	`ip` varchar(15) NOT NULL,
	`comment_count` int(11) NOT NULL,
	`view_count` int(11) NOT NULL,
	`trackback_count` int(11) NOT NULL,
	`user_id` int(11) NOT NULL,
	`description` varchar(100) NOT NULL,
	`last_time` datetime NOT NULL,
	`password` varchar(20) NOT NULL,
	`view_group` int(11) NOT NULL,
	`open_type` int(11) NOT NULL,
	`url_type` int(11) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($blog_sql);
	
	
	$blog_category_table=$dbprefix.'blog_category';
	$blog_category_sql="CREATE TABLE ".$blog_category_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`name` varchar(50) NOT NULL,
	`cat_order` int(11) NOT NULL,
	`blog_count` int(11) NOT NULL,
	`hidden` tinyint(3) NOT NULL,
	`locked` tinyint(3) NOT NULL,
	`parent_id` int(11) NOT NULL,
	`description` varchar(100) NOT NULL,
	`url_type` int(11) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($blog_category_sql);
	
	$blog_comment_table=$dbprefix.'blog_comment';
	$blog_comment_sql="CREATE TABLE ".$blog_comment_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`blog_id` int(11) NOT NULL,
	`content` longtext NOT NULL,
	`edit_mark` varchar(50) NOT NULL,
	`hidden` tinyint(3) NOT NULL,
	`post_time` datetime NOT NULL,
	`ip` varchar(15) NOT NULL,
	`user_id` int(11) NOT NULL,
	`status` int(11) NOT NULL,
	`user_name` varchar(25) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($blog_comment_sql);
	
	$blog_link_table=$dbprefix.'blog_link';
	$blog_link_sql="CREATE TABLE ".$blog_link_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`name` varchar(50) NOT NULL,
	`lin_url` varchar(255) NOT NULL,
	`rss` varchar(255) NOT NULL,
	`lnk_sort` int(11) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($blog_link_sql);
	
	$config_table=$dbprefix.'config';
	$config_sql="CREATE TABLE ".$config_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`last_login_time` datetime NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($config_sql);
	
	$daily_table=$dbprefix.'daily';
	$daily_sql="CREATE TABLE ".$daily_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`content` longtext NOT NULL,
	`post_time` datetime NOT NULL,
	`comments_count` int(11) NOT NULL,
	`user_id` int(11) NOT NULL,
	`user_name` varchar(50) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($daily_sql);
	
	$daily_comment_table=$dbprefix.'daily_comment';
	$daily_comment_sql="CREATE TABLE ".$daily_comment_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`content` longtext NOT NULL,
	`post_time` datetime NOT NULL,
	`daily_id` int(11) NOT NULL,
	`user_id` int(11) NOT NULL,
	`user_name` varchar(50) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($daily_comment_sql);
	
	$friendlink_table=$dbprefix.'friendlink';
	$friendlink_sql="CREATE TABLE ".$friendlink_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`name` varchar(255) NOT NULL,
	`link_url` varchar(255) NOT NULL,
	`rss` varchar(255) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($friendlink_sql);
	
	$guestbook_table=$dbprefix.'guestbook';
	$guestbook_sql="CREATE TABLE ".$guestbook_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`name` varchar(50) NOT NULL,
	`email` varchar(50) NOT NULL,
	`content` longtext NOT NULL,
	`edit_mark` varchar(50) NOT NULL,
	`post_time` datetime NOT NULL,
	`replay_name` varchar(50) NOT NULL,
	`replay` longtext NOT NULL,
	`replay_time` datetime NOT NULL,
	`hidden` tinyint(3) NOT NULL,
	`ip` varchar(15) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($guestbook_sql);
	
	$message_table=$dbprefix.'message';
	$message_sql="CREATE TABLE ".$message_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`content` longtext NOT NULL,
	`post_time` datetime NOT NULL,
	`user_id` int(11) NOT NULL,
	`user_name` varchar(50) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($message_sql);
	
	$photo_table=$dbprefix.'photo';
	$photo_sql="CREATE TABLE ".$photo_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`cat_id` int(11) NOT NULL,
	`name` varchar(255) NOT NULL,
	`remark` longtext NOT NULL,
	`post_time` datetime NOT NULL,
	`path` varchar(255) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($photo_sql);
	
	
	$resource_table=$dbprefix.'resource';
	$resource_sql="CREATE TABLE ".$resource_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`cat_id` int(11) NOT NULL,
	`name` varchar(255) NOT NULL,
	`author` varchar(50) NOT NULL,
	`path` varchar(255) NOT NULL,
	`upload_time` datetime NOT NULL,
	`image_path` varchar(255) NOT NULL,
	`remark` longtext NOT NULL,
	`view_time` int(11) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($resource_sql);
	
	$resource_category_table=$dbprefix.'resource_category';
	$resource_category_sql="CREATE TABLE ".$resource_category_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`name` varchar(50) NOT NULL,
	`resource_count` int(11) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($resource_category_sql);
	
	
	$resource_comment_table=$dbprefix.'resource_comment';
	$resource_comment_sql="CREATE TABLE ".$resource_comment_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`resource_id` int(11) NOT NULL,
	`content` longtext NOT NULL,
	`edit_mark` varchar(50) NOT NULL,
	`hidden` tinyint(3) NOT NULL,
	`post_time` datetime NOT NULL,
	`ip` varchar(15) NOT NULL,
	`user_id` int(11) NOT NULL,
	`status` int(11) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($resource_comment_sql);
	
	$settings_table=$dbprefix.'settings';
	$settings_sql="CREATE TABLE ".$settings_table." (
	`blog_id` 	int(11) NOT NULL,
	`blog_title` 	varchar(50) NOT NULL,
	`blog_description` 	longtext NOT NULL,
	`base_url` 	varchar(50) NOT NULL,
	`logo_image` 	varchar(50) NOT NULL,
	`blog_web_master` 	varchar(20) NOT NULL,
	`blog_web_master_email` 	varchar(30) NOT NULL,
`blog_language` 	varchar(8) 	NOT NULL,
	`blog_rss_language` 	varchar(4) NOT NULL,
	`default_view_mode`	tinyint(3) 	NOT NULL,
	`article_perpage_normal` 	smallint(6) NOT NULL,
	`article_perpage_list` 	smallint(6) NOT NULL,
	`list_entry_perpage` 	smallint(6) NOT NULL,
	`comment_perpage` 	smallint(6) NOT NULL,
	`comment_time_order` 	tinyint(3) NOT NULL,
	`show_trackback_with_comment` 	tinyint(3) NOT NULL,
	`show_trackback_position` 	tinyint(3) NOT NULL,
	`recent_article_list` 	smallint(6) NOT NULL,
	`recent_comment_list` 	smallint(6) NOT NULL,
	`enable_dynamic_calendar` 	tinyint(3) 	NOT NULL,
	`content_auto_split_chars` 	smallint(6) NOT NULL,
	`enable_register` 	tinyint(3) 		NOT NULL,
	`enable_security_code` 	tinyint(3) NOT NULL,
	`enable_trackback_in` 	tinyint(3) 	NOT NULL,
	`enable_trackback_out` 	tinyint(3) NOT NULL,
	`enable_comment` 	tinyint(3) 		NOT NULL,
	`enable_guest_book` 	tinyint(3) 	NOT NULL,
	`entry_perpage_guest_book` 	smallint(6) NOT NULL,
	`blog_skin` 	varchar(20) NOT NULL,
	`min_post_duration` 	smallint(6) 		NOT NULL,	
	`enable_visitor_record` 	tinyint(3) 	NOT NULL,
	`max_visitor_record` 	int(11) 		NOT NULL,
	`enable_upload` 	tinyint(3) 	NOT NULL,
	`upload_size` 	int(11) 		NOT NULL,
	`upload_path` 	varchar(50) NOT NULL,
	`upload_types` 	varchar(50)NOT NULL,
	`recent_resource_list` 	smallint(6) NOT NULL,
	 PRIMARY KEY (`blog_id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($settings_sql);
	
	$trackback_table=$dbprefix.'trackback';
	$trackback_sql="CREATE TABLE ".$trackback_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`blog_id` int(11) NOT NULL,
	`url` varchar(100) NOT NULL,
	`title` varchar(100) NOT NULL,
	`blog` varchar(100) NOT NULL,
	`excerpt` longtext NOT NULL,
	`time` datetime NOT NULL,
	`ip` varchar(15) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($trackback_sql);
	
	$user_table=$dbprefix.'user';
	$user_sql="CREATE TABLE ".$user_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`last_ip` varchar(15) NOT NULL,
	`name` varchar(50) NOT NULL,
	`password` varchar(50) NOT NULL,
	`group_id` int(11) NOT NULL,
	`gender` tinyint(3) NOT NULL,
	`email` varchar(50) NOT NULL,
	`reg_time` datetime NOT NULL,
	`hide_email` tinyint(3) NOT NULL,
	`homepage` varchar(255) NOT NULL,
	`blog_count` int(11) NOT NULL,
	`comment_count` int(11) NOT NULL,
	`last_time` datetime NOT NULL,
	`reg_ip` varchar(15) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($user_sql);
	
	$group_table=$dbprefix.'group';
	$group_sql="CREATE TABLE ".$group_table." (
	`id` int(11) NOT NULL AUTO_INCREMENT,
	`name` varchar(50) NOT NULL,
	`rights` varchar(50) NOT NULL,
	 PRIMARY KEY (`id`)
	) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($group_sql);

	/*$blog_table=$dbprefix.'blog';
	$blog_sql="CREATE TABLE $blog_table (
  `id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` mediumint(8) NOT NULL,
  `cat_id` smallint(4) NOT NULL,
  `title` varchar(120) NOT NULL,
  `description` text NOT NULL,
  `content` mediumtext NOT NULL,
  `add_time` int(10) unsigned NOT NULL DEFAULT '0',
  `edit_time` int(10) NOT NULL,
  `comments` mediumint(8) NOT NULL,
  `views` mediumint(8) NOT NULL,
  `password` varchar(20) NOT NULL,
  `view_group` varchar(255) NOT NULL,
  `open_type` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `url_type` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($blog_sql);

	$time=time();
	$blog_data="INSERT INTO $blog_table (`blog_id`,`user_id`,`cat_id`,`title`,`description`,`content`,`add_time`,`edit_time`,`comments`,`views`,`password`,`view_group`,`open_type`,`url_type` ) VALUES ( '1','1','1','Simple-Log简介','&lt;p&gt;<br />	&lt;strong&gt;简单易用：&lt;/strong&gt;<br />	这是一个简便易用的功能强大的系统，在后台没有复杂的菜单，使用起来方便快捷&lt;/p&gt;<br />&lt;p&gt;<br />	&lt;strong&gt;飞一般的访问速度：&lt;/strong&gt;<br />	采用双重数据缓存，前台访问飞一般的速度&lt;/p&gt;<br />&lt;p&gt;<br />	&lt;strong&gt;网站修改随心所欲：&lt;/strong&gt;<br />	可以在后台一键更换模板，也可以在后台自定义整个网站，可以随心所欲的在后台修改模板，修改边栏，修改导航，网站页面修改一切随心所欲&lt;/p&gt;<br />&lt;p&gt;<br />	&lt;strong&gt;模板设计简单：&lt;/strong&gt;<br />	模板中没有php代码，无论是转模板还是重新设计模板都是非常简单快捷，几个小时即可完成模板转换&lt;/p&gt;<br />&lt;p&gt;<br />	&lt;strong&gt;多人联合撰写：&lt;/strong&gt;<br />	后台轻松完成多人联合撰写&lt;/p&gt;<br />&lt;p&gt;<br />	&lt;strong&gt;完善的后台权限机制：&lt;/strong&gt;<br />	可以设置不同的会员组后台操作权限，再多的人访问后台联合撰写也没烦恼&lt;/p&gt;<br />&lt;p&gt;<br />	&lt;strong&gt;完善的数据备份、恢复：&lt;/strong&gt;<br />	后台支持博客数据的备份和恢复&lt;/p&gt;<br />&lt;p&gt;<br />	&lt;strong&gt;优秀的可扩展性：&lt;/strong&gt;<br />	系统采用PHP+MySQL构建，模板采用Smarty模板引擎，使模板设计变得简单。&lt;br/&gt;<br />	系统采用jQuery框架，使js扩展变得更加便捷。&lt;br/&gt;<br />	对系统边栏插件化，模板文件在后台可以直接修改，使网站修改更加简单&lt;/p&gt;<br />','&lt;p&gt;\r\n	&lt;strong&gt;简单易用：&lt;/strong&gt;&lt;/p&gt;\r\n&lt;p&gt;\r\n	这是一个简便易用的功能强大的系统，在后台没有复杂的菜单，使用起来方便快捷&lt;/p&gt;\r\n&lt;p&gt;\r\n	&amp;nbsp;&lt;/p&gt;\r\n&lt;p&gt;\r\n	&lt;strong&gt;飞一般的访问速度：&lt;/strong&gt;&lt;/p&gt;\r\n&lt;p&gt;\r\n	采用双重数据缓存，前台访问飞一般的速度&lt;/p&gt;\r\n&lt;p&gt;\r\n	&amp;nbsp;&lt;/p&gt;\r\n&lt;p&gt;\r\n	&lt;strong&gt;网站修改随心所欲：&lt;/strong&gt;&lt;/p&gt;\r\n&lt;p&gt;\r\n	可以在后台一键更换模板，也可以在后台自定义整个网站，可以随心所欲的在后台修改模板，修改边栏，修改导航，网站页面修改一切随心所欲&lt;/p&gt;\r\n&lt;p&gt;\r\n	&amp;nbsp;&lt;/p&gt;\r\n&lt;p&gt;\r\n	&lt;strong&gt;模板设计简单：&lt;/strong&gt;&lt;/p&gt;\r\n&lt;p&gt;\r\n	模板中没有php代码，无论是转模板还是重新设计模板都是非常简单快捷，几个小时即可完成模板转换&lt;/p&gt;\r\n&lt;p&gt;\r\n	&amp;nbsp;&lt;/p&gt;\r\n&lt;p&gt;\r\n	&lt;strong&gt;多人联合撰写：&lt;/strong&gt;&lt;/p&gt;\r\n&lt;p&gt;\r\n	后台轻松完成多人联合撰写&lt;/p&gt;\r\n&lt;p&gt;\r\n	&amp;nbsp;&lt;/p&gt;\r\n&lt;p&gt;\r\n	&lt;strong&gt;完善的后台权限机制：&lt;/strong&gt;&lt;/p&gt;\r\n&lt;p&gt;\r\n	可以设置不同的会员组后台操作权限，再多的人访问后台联合撰写也没烦恼&lt;/p&gt;\r\n&lt;p&gt;\r\n	&amp;nbsp;&lt;/p&gt;\r\n&lt;p&gt;\r\n	&lt;strong&gt;完善的数据备份、恢复：&lt;/strong&gt;&lt;/p&gt;\r\n&lt;p&gt;\r\n	后台支持博客数据的备份和恢复&lt;/p&gt;\r\n&lt;p&gt;\r\n	&amp;nbsp;&lt;/p&gt;\r\n&lt;p&gt;\r\n	&lt;strong&gt;优秀的可扩展性&lt;/strong&gt;&lt;/p&gt;\r\n&lt;p&gt;\r\n	系统采用PHP+MySQL构建，模板采用Smarty模板引擎，使模板设计变得简单。&lt;/p&gt;\r\n&lt;p&gt;\r\n	系统采用jQuery框架，使js扩展变得更加便捷。&lt;/p&gt;\r\n&lt;p&gt;\r\n	对系统边栏插件化，模板文件在后台可以直接修改，使网站修改更加简单&lt;/p&gt;\r\n','".$time."','0','0','0','','all','0','1');
";
	$db1->query($blog_data);

	$category=$dbprefix.'category';
	$sql="CREATE TABLE $category (
  `cat_id` smallint(4) NOT NULL AUTO_INCREMENT,
  `cat_name` varchar(120) NOT NULL,
  `cat_desc` varchar(255) NOT NULL DEFAULT '',
  `parent_id` smallint(4) unsigned NOT NULL DEFAULT '0',
  `listorder` smallint(4) unsigned NOT NULL DEFAULT '0',
  `url_type` varchar(100) NOT NULL,
  PRIMARY KEY (`cat_id`),
  KEY `parent_id` (`parent_id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($sql);

	$date="INSERT INTO $category (`cat_id`,`cat_name`,`cat_desc`,`parent_id`,`listorder`,`url_type` ) VALUES ( '1','记录','记录生活中的点点滴滴','0','0','1');
";
	$db1->query($date);

	$comment=$dbprefix.'comment';
	$sql="CREATE TABLE $comment (
  `comment_id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `blog_id` mediumint(8) NOT NULL,
  `user_id` mediumint(8) NOT NULL,
  `user_name` varchar(60) NOT NULL DEFAULT '',
  `content` text NOT NULL,
  `email` varchar(50) NOT NULL,
  `home` varchar(50) NOT NULL,
  `add_time` int(10) unsigned NOT NULL DEFAULT '0',
  `ip` varchar(15) NOT NULL,
  `status` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`comment_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;";
	$db1->query($sql);

	$link=$dbprefix.'link';
	$sql="CREATE TABLE IF NOT EXISTS $link (
  `link_id` mediumint(8) NOT NULL AUTO_INCREMENT,
  `title` varchar(100) NOT NULL,
  `desc` varchar(255) NOT NULL,
  `url` varchar(100) NOT NULL,
  `sort` mediumint(8) NOT NULL,
  PRIMARY KEY (`link_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2;";
	$db1->query($sql);

	$date="INSERT INTO $link (`link_id`, `title`, `desc`, `url`, `sort`) VALUES
(1, 'Simple-Log', 'Simple-Log官方网站', 'http://www.simple-log.com', 1);";
	$db1->query($date);



	$modules=$dbprefix.'modules';
	$sql="CREATE TABLE $modules (
  `id` mediumint(5) NOT NULL AUTO_INCREMENT,
  `module_id` varchar(30) NOT NULL,
  `title` varchar(100) NOT NULL,
  `desc` varchar(255) NOT NULL,
  `content` varchar(5000) NOT NULL,
  `sort` mediumint(5) NOT NULL,
  `type` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";
	$db1->query($sql);
	$data="INSERT INTO $modules (`id`,`module_id`,`title`,`desc`,`content`,`sort`,`type` ) VALUES ( '1','','首页','网站首页','index.php','1','2'),('2','sysnav','系统导航','系统导航','{insert name=\'member_info\'}','1','1');";
	$db1->query($data);



	$user=$dbprefix.'user';
	$sql="CREATE TABLE $user (
  `user_id` mediumint(8) unsigned NOT NULL AUTO_INCREMENT,
  `user_name` varchar(60) NOT NULL DEFAULT '',
  `password` varchar(32) NOT NULL DEFAULT '',
  `email` varchar(60) NOT NULL,
  `group_id` smallint(4) NOT NULL,
  `reg_time` int(10) unsigned NOT NULL DEFAULT '0',
  `last_time` int(10) NOT NULL,
  `reg_ip` varchar(15) NOT NULL,
  `last_ip` varchar(15) NOT NULL DEFAULT '',
  `visit_count` smallint(5) unsigned NOT NULL DEFAULT '0',
  `msn` varchar(60) NOT NULL,
  `qq` varchar(20) NOT NULL,
  `home` varchar(50) NOT NULL,
  PRIMARY KEY (`user_id`),
  UNIQUE KEY `user_name` (`user_name`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;";
	$db1->query($sql);
	$data="INSERT INTO $user (`user_id`,`user_name`,`password`,`email`,`group_id`,`reg_time`,`last_time`,`reg_ip`,`last_ip`,`visit_count`,`msn`,`qq`,`home` ) VALUES ( '1','".$admin_user."','".md5($admin_pass)."','p@simple-log.com','1','".$time."','".$time."','','','0','','','');
";
	$db1->query($data);

	$user_group=$dbprefix.'user_group';
	$sql="CREATE TABLE $user_group (
  `group_id` smallint(4) unsigned NOT NULL AUTO_INCREMENT,
  `group_name` varchar(60) NOT NULL,
  `admin_privilege` varchar(255) NOT NULL,
  PRIMARY KEY (`group_id`)
) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;
";
	$db1->query($sql);
	$data="INSERT INTO $user_group (`group_id`,`group_name`,`admin_privilege` ) VALUES ( '1','管理员','all'),('2','注册会员',''),('3','游客','');
";
	$db1->query($data);
*/

	$smarty->assign('admin_user',$admin_user);
	$smarty->assign('admin_pass',$admin_pass);
	$smarty->assign('id',3);
	$smarty->assign('success',1);
	$smarty->display('install.html');

}

function check_write($path,$path_type=1,$check_type=1) {

	if ($path_type==1)
	{
		if (is_dir($path))
		{
			if ($check_type==1)
			{
				$testfile = $path.'/test.tmp';
			}
			else
			{
				check_write($path);
				$testfile = $path.'default'.'/test.tmp';
			}

			@chmod($testfile,0777);
			$fp = @fopen($testfile,'ab');
			@unlink($testfile);
			if ($fp===false)
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	elseif ($path_type==2)
	{
		@chmod($path,0777);
		$fp = @fopen($path,'ab');
		if ($fp===false)
		{
			return false;
		}
	}

	return true;

}

?>