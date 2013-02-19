<?php

if ($action=='setting')
{

	include_once(PBBLOG_ROOT.'include/config.php');

	$smarty->assign('blog_name',$blog_name);
	$smarty->assign('blog_desc',$blog_desc);
	$smarty->assign('blog_keyword',$blog_keyword);
	$smarty->assign('page_size',$page_size);
	$smarty->assign('pager_size',$pager_size);
	$smarty->assign('open_comment',$open_comment);
	$smarty->assign('comment_safe',$comment_safe);
	$smarty->assign('caching',$caching);
	$smarty->assign('notice',$notice);
	
	if (empty($domain)) 
	{
		$domain=str_replace("admin", '', dirname($url));
	}
	
	$smarty->assign('domain',$domain);
	$smarty->assign('rewrite',$rewrite);
	$smarty->assign('pager_size',$pager_size);

	$smarty->assign('type','act_setting');
	$smarty->display('setting.html');
}

elseif ($action=='act_setting')
{
	include(PBBLOG_ROOT.'include/config.php');
	$blog_config="<?php

/**
 * $Author: pengwenfei p@simple-log.com
 * $Date: 2010-02-16
 * www.simple-log.com 
*/ \n\n/*数据库信息*/ \n";
	$blog_config.='$dbhost   = \''.$dbhost."';\n//数据库主机地址\n";
	$blog_config.='$dbname   = \''.$dbname."';\n//数据库名字\n";
	$blog_config.='$dbuser   = \''.$dbuser."';\n//用户名\n";
	$blog_config.='$dbpw   = \''.$dbpw."';\n//数据库密码\n";
	$blog_config.='$dbprefix   = \''.$dbprefix."';\n//表前缀\n";
	$blog_config.='$pconnect   = \''.$pconnect."';\n//是否保持连接\n";

	$blog_config.="\n/*博客相关设置*/ \n";
	//如果在页面没有填写数据，提示错误，具体的细节需要完善，比如判断哪个没有
	if (empty($_POST))
	{
		show_message('请填写数据',$referer_url);
	}
	else
	{
		//循环得到传递过来的数据并为写入配置文件做准备
		foreach ($_POST as $key => $val)
		{
			$blog_config.='$'.$key."	= '".$val."';\n";
		}
	}

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
	$blog_config.="\$install_lock=true;  \n//博客是否已经安装\n";

	$blog_config.="\n?>";

	//将博客配置保存到文件中
	$fp=@fopen(PBBLOG_ROOT.'include/config.php',"w") or die('can not open file');
	flock($fp,LOCK_EX);
	fwrite($fp,$blog_config);
	fclose($fp);
	show_message('网站设置成功','admin.php?act=setting');

}
?>