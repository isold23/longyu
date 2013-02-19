<?php

/**
 * : isold
 * : 2011-01-28
 * www.longyunet.net 
*/ 

/*数据库信息*/ 
$dbhost   = 'localhost';
//数据库主机地址
$dbname   = 'sql_longyunet';
//数据库名字
$dbuser   = 'root';
//用户名
$dbpw   = 'wlx8010040625';
//数据库密码
$dbprefix   = 'longyu_';
//表前缀
$pconnect   = '';
//是否保持连接

/*网站相关设置*/ 
$web_name   = '龙宇网';
$web_desc   = '软件开发';
$web_title   = '龙宇网';
$blog_keyword   = '';
$open_comment   = '0';
$domain   = 'http://localhost/longyusoft/';
$page_size   = '8';
$pager_size   = '30';

/*会话、cookie设置*/ 
$cookie_path   = '/';
$cookie_domain   = '';
$session   = '1440';

/*网站编码，暂时只支持utf8*/ 
$charset   = 'utf8';

/*安全哈希密码*/ 
$hash_secret   = 'please put your secret';
//此处与全站的md5相关
$check_ip=true;  
//是否对后台登陆ip进行检测，默认为开启

/*模板设置，以后要将模板设置扩展到后台*/ 
$template_name   = 'default';
//默认为default
$install_lock=true;  
//网站是否已经安装

?>