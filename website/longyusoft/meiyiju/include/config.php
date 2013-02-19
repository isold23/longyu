<?php

/**
 * : isold
 * : 2011-01-28
 * www.longyunet.net 
*/ 

/*数据库信息*/ 
$dbhost   = '127.0.0.1';
//数据库主机地址
$dbname   = 'meiyiju';
//数据库名字
$dbuser   = 'root';
//用户名
$dbpw   = 'wlx8010040625';
//数据库密码
$dbprefix   = 'meiyiju_';
//表前缀
$pconnect   = '';
//是否保持连接

/*网站相关设置*/ 
$web_name   = '美宜居装饰';
$web_desc   = '美宜居装饰';	
$web_title   = '美宜居装饰';
$web_domain = 'www.meiyiju.net';
$web_url='http://www.meiyiju.net';
$hot_line='0314-2520581';
$address='承德世纪城八号楼一单元303室';
$email='isold_wang@yahoo.com.cn';
$blog_keyword   = '';
$open_comment   = '0';
$domain   = 'http://127.0.0.1:8888/meiyiju/';
$page_size   = '20';
$pager_size   = '5';

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