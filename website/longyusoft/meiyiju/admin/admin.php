<?php
define('IN_PBBLOG',true);
define('IN_PBADMIN',true);

define('ROOT', str_replace('admin','',str_replace("\\", '/', dirname(__FILE__))));

require_once(ROOT.'/include/core.php');
require_once(ROOT.'/include/admin.function.php');

$safe_act=array(
'pre_login','login','logout','index','get_version',
'cat_list','del_cat','add_cat','act_add_cat','edit_cat','act_edit_cat','upload_file','upload_file_index',
'blog_list','del_blog','add_blog','act_add_blog','edit_blog','act_edit_blog','upload',
'resource_cat_list','del_resource_cat','add_resource_cat','act_add_resource_cat','edit_resource_cat','act_edit_resource_cat',
'resource_list','del_resource','add_resource','act_add_resource','edit_resource','act_edit_resource',
'comment_list','del_comment','add_comment','act_add_comment','edit_comment','act_edit_comment',
'member_list','del_member','add_member','act_add_member','edit_member','act_edit_member',
'group_list','del_group','add_group','act_add_group','edit_group','act_edit_group',
'daily_list','del_daily','add_daily','act_add_daily','edit_daily','act_edit_daily',
'message_list','del_message','edit_message','act_edit_message',
'sidebar_setup_list','del_sidebar','sidebar_list','add_sidebar','act_setup_sidebar','act_edit_sort','setup_sidebar','edit_sidebar','act_edit_sidebar',
'set_footer','act_set_page','get_page_data','ajax_post_page_data',
'nav_list','add_nav','act_add_nav','edit_nav','act_edit_nav','act_edit_nav_sort','del_nav',
'setting','act_setting','templates_list','select_template','clear_cache','databak','act_backup','re_data','act_re_data',
'friend_link_list','act_edit_friend_link_sort','edit_friend_link','act_edit_friend_link','add_friend_link','act_add_friend_link','del_friend_link',
'index_pic_list','edit_index_pic','act_edit_index_pic','add_index_pic','act_add_index_pic','del_index_pic',
'web_friend_link_list','act_edit_web_friend_link_sort','edit_web_friend_link','act_edit_web_friend_link','add_web_friend_link','act_add_web_friend_link','del_web_friend_link',
'announcement_list','edit_announcement','act_edit_announcement','add_announcement','act_add_announcement','del_announcement',
'admin_plugin'
);
$action=$_GET['act'];
if (!in_array($action,$safe_act))
{
	$action='index';
}

//对页面
admin_here($action);

//检查用户权
if ($action!='pre_login'&&$action!='login'&&$action!='logout'&&$action!='clear_cache'&&$action!='get_version')
{
	check_privilege($action);
}

if ($action=='pre_login'||$action=='login'||$action=='logout')
{
	require(ROOT.'/admin/include/login.php');
}

elseif ($action=='index'||$action=='get_version')
{
	require(ROOT.'/admin/include/index.php');
}

elseif ($action=='add_blog'||$action=='act_add_blog'||$action=='blog_list'||$action=='edit_blog'||$action=='act_edit_blog'||$action=='del_blog')
{
	require(ROOT.'/admin/include/blog.php');
}

elseif ($action=='add_cat'||$action=='act_add_cat'||$action=='cat_list'||$action=='edit_cat'||$action=='act_edit_cat'||$action=='del_cat')
{
	require(ROOT.'/admin/include/cat.php');
}

elseif ($action=='add_resource_cat'||$action=='act_add_resource_cat'||$action=='resource_cat_list'||$action=='edit_resource_cat'||$action=='act_edit_resource_cat'||$action=='del_resource_cat')
{
	require(ROOT.'/admin/include/resource_cat.php');
}

elseif ($action=='add_resource'||$action=='act_add_resource'||$action=='resource_list'||$action=='edit_resource'||$action=='act_edit_resource'||$action=='del_resource')
{
	require(ROOT.'/admin/include/resource.php');
}

elseif ($action=='reg_member'||$action=='add_member'||$action=='act_add_member'||$action=='member_list'||$action=='edit_member'||$action=='act_edit_member'||$action=='del_member')
{
	require(ROOT.'/admin/include/member.php');
}

elseif ($action=='add_group'||$action=='act_add_group'||$action=='group_list'||$action=='edit_group'||$action=='act_edit_group'||$action=='del_group')
{
	require(ROOT.'/admin/include/group.php');
}

elseif ($action=='add_daily'||$action=='act_add_daily'||$action=='daily_list'||$action=='edit_daily'||$action=='act_edit_daily'||$action=='del_daily')
{
	require(ROOT.'/admin/include/daily.php');
}

elseif ($action=='message_list'||$action=='edit_message'||$action=='act_edit_message'||$action=='del_message')
{
	require(ROOT.'/admin/include/message.php');
}

elseif ($action=='setting'||$action=='act_setting')
{
	require(ROOT.'/admin/include/setting.php');
}

elseif ($action=='templates_list'||$action=='select_template')
{
	require(ROOT.'/admin/include/template.php');
}

elseif ($action=='add_comment'||$action=='act_add_comment'||$action=='comment_list'||$action=='edit_comment'||$action=='act_edit_comment'||$action=='del_comment')
{
	require(ROOT.'/admin/include/comment.php');
}

//边栏模块
elseif ($action=='sidebar_setup_list'||$action=='edit_sidebar'||$action=='act_edit_sidebar'||$action=='sidebar_list'||$action=='del_sidebar'||$action=='act_edit_sort'||$action=='del_sidebar'||$action=='setup_sidebar'||$action=='act_setup_sidebar'||$action=='add_sidebar')
{
	require(ROOT.'/admin/include/sidebar_module.php');
}

//导航模块
elseif ($action=='nav_list'||$action=='add_nav'||$action=='act_add_nav'||$action=='edit_nav'||$action=='act_edit_nav'||$action=='act_edit_nav_sort'||$action=='del_nav')
{
	require(ROOT.'/admin/include/nav_module.php');
}

//修改页面
elseif ($action=='set_footer'||$action=='act_set_page'||$action=='get_page_data'||$action=='ajax_post_page_data')
{
	require(ROOT.'/admin/include/set_page.php');
}

//数据备份
elseif ($action=='databak'||$action=='act_backup'||$action=='re_data'||$action=='act_re_data')
{
	require(ROOT.'/admin/include/database.php');
}

//友情链接
elseif ($action=='friend_link_list'||$action=='act_edit_friend_link_sort'||$action=='edit_friend_link'||$action=='act_edit_friend_link'||$action=='add_friend_link'||$action=='act_add_friend_link'||$action=='del_friend_link')
{
	require(ROOT.'/admin/include/friendlink.php');
}

//首页图片
elseif ($action=='index_pic_list'||$action=='edit_index_pic'||$action=='act_edit_index_pic'||$action=='add_index_pic'||$action=='act_add_index_pic'||$action=='del_index_pic')
{
	require(ROOT.'/admin/include/index_pic.php');
}

//网站友情链接
elseif ($action=='web_friend_link_list'||$action=='edit_web_friend_link'||$action=='act_edit_web_friend_link'||$action=='add_web_friend_link'||$action=='act_add_web_friend_link'||$action=='del_web_friend_link')
{
	require(ROOT.'/admin/include/webfriendlink.php');
}

//网站友情链接
elseif ($action=='announcement_list'||$action=='edit_announcement'||$action=='act_edit_announcement'||$action=='add_announcement'||$action=='act_add_announcement'||$action=='del_announcement')
{
	require(ROOT.'/admin/include/announcement.php');
}

//调用后台插
elseif ($action=='admin_plugin')
{
	require(ROOT.'/admin/include/admin_plugin.php');
}

elseif ($action=='clear_cache'){
	$smarty->cache_dir      = PBBLOG_ROOT . 'include/cache';
	$smarty->compile_dir=PBBLOG_ROOT.'/include/compiled';
	$smarty->clear_all_cache();
	$smarty->clear_compiled_tpl();
	show_message('清除缓存成功','admin.php?act=index');
	}

	elseif ($action=='upload')
	{
	require(ROOT.'/include/upload.class.php');
	$file=new cls_upload();

	$file_name=$file->upload($_FILES['upload'],$_GET['type']);

	$file_url='';
	if ($file->error()=='')
	{
	$u=str_replace("admin", '', dirname($url));
	$file_url=$u.$file_name;
	}

	$str='<script type="text/javascript">'.
	'window.parent.CKEDITOR.tools.callFunction('.$_GET['CKEditorFuncNum'].
	', \''.$file_url.'\', \''.$file->error().'\');</script>';
	exit($str);
}

elseif($action='upload_file')
{
if ((($_FILES["browsefile"]["type"] == "image/gif")
|| ($_FILES["browsefile"]["type"] == "image/jpeg")
|| ($_FILES["browsefile"]["type"] == "image/jpg")
|| ($_FILES["browsefile"]["type"] == "image/png")
|| ($_FILES["browsefile"]["type"] == "image/pjpeg"))
&& ($_FILES["browsefile"]["size"] < 2000000000000))
  {
  if ($_FILES["browsefile"]["error"] > 0)
    {
    	$smarty->assign('upload_file_name',$_FILES["browsefile"]["name"]);
    	show_message('文件有错误',$referer_url);
    }
  else
    {
    if (file_exists(ROOT."/upload/" . $_FILES["browsefile"]["name"]))
      {
      $smarty->assign('upload_file_name',$_FILES["browsefile"]["name"]);
      show_message($_FILES["browsefile"]["name"].'文件已经存在',$referer_url);
      }
    else
      {
      move_uploaded_file($_FILES["browsefile"]["tmp_name"],
      ROOT."/upload/" . $_FILES["browsefile"]["name"]);
      $smarty->assign('upload_file_name',$_FILES["browsefile"]["name"]);
      $smarty->assign('upload_return_value',"上传文件成功");
      show_message($_FILES["browsefile"]["name"].'文件上传成功',$referer_url."&image_path=".$_FILES["browsefile"]["name"]);
    }
    }
  }
else
  {
  	$smarty->assign('upload_file_name',$_FILES["browsefile"]["name"]);
  	$smarty->assign('upload_return_value',"上传文件失败");
  	show_message($_FILES["browsefile"]["name"].'上传文件失败',$referer_url);
  }
}



?>