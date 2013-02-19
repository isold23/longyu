<?php

/**
 * : pengwenfei p@simple-log.com
 * : 2010-02-16
 * www.simple-log.com 
*/ 

/*数据库信息*/ 
$dbhost   = '60.28.249.42';
//数据库主机地址
$dbname   = 'sq_fzyn';
//数据库名字
$dbuser   = 'sq_fzyn';
//用户名
$dbpw   = '123456';
//数据库密码
$dbprefix   = 'fzyn_';
//表前缀
$pconnect   = '';
//是否保持连接

/*博客相关设置*/ 
$website_name	= '野牛非洲艺术馆';
$website_url	= 'http://www.fzyn.net';
$blog_name	= '野牛非洲艺术馆';
$blog_desc	= '野牛非洲艺术馆';
$blog_keyword	= '非洲艺术 非洲木雕  石雕 非洲画 ';
$domain	= 'http://www.fzyn.net/';
$open_comment	= '0';
$comment_safe	= '0';
$rewrite	= '0';
$caching	= '0';
$page_size	= '8';
$pager_size	= '20';
$button	= '提交';

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
//博客是否已经安装

?>
