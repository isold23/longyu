<?php

/**
 * : isold
 * : 2011-01-28
 * www.longyusoft.com 
*/ 

/*数据库信息*/ 
$dbhost   = '127.0.0.1';
//数据库主机地址
$dbname   = 'esl';
//数据库名字
$dbuser   = 'root';
//用户名
$dbpw   = 'wlx8010040625';
//数据库密码
$dbprefix   = 'erdemannsafari_';
//表前缀
$pconnect   = '';
//是否保持连接

/*网站相关设置*/ 
$web_name   = '爱德曼旅游';
$web_desc   = '爱德曼旅游';	
$web_title   = '爱德曼旅游';
$web_domain = 'www.erdemannsafari.com';
$web_url='http://www.erdemannsafari.com';
$hot_line='(+86)13911101326';
$address='承德世纪城八号楼一单元303室';
$email='seefar.kenya@gmail.com';
$blog_keyword   = '';
$open_comment   = '0';
$domain   = 'http://www.erdemannsafari.com/';
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