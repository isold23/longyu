<?php

if (!defined('IN_PBADMIN'))
{
	die('Access Denied');
}

function check_privilege($action)
{
	if (!empty($_SESSION['group_id'])&&$_SESSION['group_id']!=-1)
	{
		$admin_privilege=$GLOBALS['db']->getone('SELECT rights FROM '.table('user_group').
		" WHERE id='".$_SESSION['group_id']."'");
		$admin_privilege=explode(',',$admin_privilege);

		if ((!in_array($action,$admin_privilege))&&$admin_privilege[0]!='99999')
		{
			$link_url=!empty($GLOBALS['referer_url'])?$GLOBALS['referer_url']:'./';
			show_message('您没有权限访问该页面',$GLOBALS['referer_url']);
		}

	}
	elseif ($_SESSION['group_id']==-1)
	{
		show_message('请先登录','admin.php?act=pre_login');
	}
}

function group_name($group_id)
{
	return $GLOBALS['db']->getone('SELECT name FROM '.table('user_group').
	" WHERE id='".$_SESSION['group_id']."'");
}

function admin_here($type)
{
	if ($type=='add_nav')
	{
		$admin_here= ' | 添加网站导航元素 | <a href="admin.php?act=nav_list">网站导航列表</a>';
		$admin_title='添加网站导航元素';
	}
	elseif ($type=='nav_list')
	{
		$admin_here= ' | 网站导航列表 | <a href="admin.php?act=add_nav">添加网站导航元素</a> ';
		$admin_title='网站导航列表';
	}
	elseif ($type=='edit_nav')
	{
		$admin_here= ' | 编辑网站导航 | <a href="admin.php?act=nav_list">网站导航列表</a> ';
		$admin_title='编辑网站导航';
	}

	elseif ($type=='add_blog')
	{
		$admin_here= '添加日志 ';
		$admin_title='添加日志';
	}

	elseif ($type=='blog_list')
	{
		$admin_here= ' 日志列表';
		$admin_title='日志列表';
	}

	elseif ($type=='edit_blog')
	{
		$admin_here= ' 编辑日志';
		$admin_title='编辑日志';
	}

	elseif ($type=='add_cat')
	{
		$admin_here= '添加分类';
		$admin_title='添加分类';
	}


	elseif ($type=='edit_cat')
	{
		$admin_here= '编辑分类';
		$admin_title='编辑分类';
	}


	elseif ($type=='cat_list')
	{
		$admin_here= '分类列表  |  <a href="admin.php?act=add_cat">添加分类</a>';
		$admin_title='分类列表';
	}

	elseif ($type=='comment_list')
	{
		$admin_here= '评论列表';
		$admin_title='评论列表';
	}


	elseif ($type=='edit_comment')
	{
		$admin_here= '编辑评论';
		$admin_title='编辑评论';
	}
	
		elseif ($type=='add_resource')
	{
		$admin_here= '添加资源 ';
		$admin_title='添加资源';
	}

	elseif ($type=='resource_list')
	{
		$admin_here= ' 资源列表';
		$admin_title='资源列表';
	}

	elseif ($type=='edit_resource')
	{
		$admin_here= ' 编辑资源';
		$admin_title='编辑资源';
	}

	elseif ($type=='add_resource_cat')
	{
		$admin_here= '添加分类';
		$admin_title='添加分类';
	}


	elseif ($type=='edit_resource_cat')
	{
		$admin_here= '编辑分类';
		$admin_title='编辑分类';
	}


	elseif ($type=='resource_cat_list')
	{
		$admin_here= '分类列表  |  <a href="admin.php?act=add_resource_cat">添加分类</a>';
		$admin_title='分类列表';
	}

	elseif ($type=='member_list')
	{
		$admin_here= '会员列表';
		$admin_title='会员列表';
	}

	elseif ($type=='edit_member')
	{
		$admin_here= '编辑会员';
		$admin_title='编辑会员';
	}

	elseif ($type=='add_member')
	{
		$admin_here= '添加会员';
		$admin_title='添加会员';
	}

	elseif ($type=='group_list')
	{
		$admin_here= '会员组列表';
		$admin_title='会员组列表';
	}

	elseif ($type=='edit_group')
	{
		$admin_here= '编辑会员组';
		$admin_title='编辑会员组';
	}

	elseif ($type=='add_group')
	{
		$admin_here= '添加会员组';
		$admin_title='添加会员组';
	}
	
		elseif ($type=='daily_list')
	{
		$admin_here= '日记列表';
		$admin_title='日记列表';
	}

	elseif ($type=='edit_daily')
	{
		$admin_here= '编辑日记';
		$admin_title='编辑日记';
	}

	elseif ($type=='add_daily')
	{
		$admin_here= '添加日记';
		$admin_title='添加日记';
	}
	
			elseif ($type=='message_list')
	{
		$admin_here= '留言列表';
		$admin_title='留言列表';
	}

	elseif ($type=='edit_message')
	{
		$admin_here= '编辑留言';
		$admin_title='编辑留言';
	}

	elseif ($type=='setting')
	{
		$admin_here= '网站设置';
		$admin_title='网站设置';
	}

	elseif ($type=='templates_list')
	{
		$admin_here= '模板选择';
		$admin_title='模板选择';
	}

	elseif ($type=='sidebar_list')
	{
		$admin_here= '边栏插件列表';
		$admin_title='边栏插件列表';
	}

	elseif ($type=='setup_sidebar')
	{
		$admin_here= '可安装边栏插件列表';
		$admin_title='可安装边栏插件列表';
	}

	elseif ($type=='sidebar_setup_list')
	{
		$admin_here= '未安装边栏插件列表';
		$admin_title='未安装边栏插件列表';
	}

	elseif ($type=='edit_sidebar')
	{
		$admin_here= '编辑边栏';
		$admin_title='编辑边栏';
	}

	elseif ($type=='add_sidebar')
	{
		$admin_here= '自定义边栏';
		$admin_title='自定义边栏';
	}

	elseif ($type=='edit_group')
	{
		$admin_here= '编辑会员组';
		$admin_title='编辑会员组';
	}

	elseif ($type=='add_group')
	{
		$admin_here= '添加会员组';
		$admin_title='添加会员组';
	}

	elseif ($type=='databak')
	{
		$admin_here= '数据备份';
		$admin_title='数据备份';
	}

	elseif ($type=='re_data')
	{
		$admin_here= '数据恢复';
		$admin_title='数据恢复';
	}

	elseif ($type=='set_footer')
	{
		$admin_here= '自定义网站页面';
		$admin_title='自定义网站页面';
	}

	elseif ($type=='add_friend_link')
	{
		$admin_here= ' | 添加友情链接 | <a href="admin.php?act=friend_link_list">友情链接列表</a>';
		$admin_title='添加友情链接';
	}
	elseif ($type=='friend_link_list')
	{
		$admin_here= ' | 友情链接列表 | <a href="admin.php?act=add_friend_link">添加友情链接</a> ';
		$admin_title='友情链接列表';
	}
	elseif ($type=='edit_friend_link')
	{
		$admin_here= ' | 编辑友情链接 | <a href="admin.php?act=friend_link_list">友情链接列表</a> ';
		$admin_title='编辑友情链接';
	}
	
		elseif ($type=='add_index_pic')
	{
		$admin_here= ' | 添加首页图片 | <a href="admin.php?act=index_pic_list">首页图片列表</a>';
		$admin_title='添加首页图片';
	}
	elseif ($type=='index_pic_list')
	{
		$admin_here= ' | 首页图片列表 | <a href="admin.php?act=add_index_pic">添加首页图片</a> ';
		$admin_title='首页图片列表';
	}
	elseif ($type=='edit_index_pic')
	{
		$admin_here= ' | 编辑首页图片 | <a href="admin.php?act=index_pic_list">首页图片列表</a> ';
		$admin_title='编辑首页图片';
	}
	
	elseif ($type=='add_web_friend_link')
	{
		$admin_here= ' | 添加友情链接 | <a href="admin.php?act=web_friend_link_list">友情链接列表</a>';
		$admin_title='添加友情链接';
	}
	elseif ($type=='web_friend_link_list')
	{
		$admin_here= ' | 友情链接列表 | <a href="admin.php?act=add_web_friend_link">添加友情链接</a> ';
		$admin_title='友情链接列表';
	}
	elseif ($type=='edit_web_friend_link')
	{
		$admin_here= ' | 编辑友情链接 | <a href="admin.php?act=web_friend_link_list">友情链接列表</a> ';
		$admin_title='编辑友情链接';
	}
	
	elseif ($type=='add_announcement')
	{
		$admin_here= ' | 添加网站公告 | <a href="admin.php?act=announcement_list">网站公告列表</a>';
		$admin_title='添加网站公告';
	}
	elseif ($type=='announcement_list')
	{
		$admin_here= ' | 网站公告列表 | <a href="admin.php?act=add_announcement">添加网站公告</a> ';
		$admin_title='网站公告列表';
	}
	elseif ($type=='edit_announcement')
	{
		$admin_here= ' | 编辑网站公告 | <a href="admin.php?act=announcement_list">网站公告列表</a> ';
		$admin_title='编辑网站公告';
	}

	elseif ($type=='index')
	{
		$admin_here= '首页';
		$admin_title='首页';
	}



	$admin_here='<a href="admin.php?act=index">管理中心</a>  -  '.$admin_here;
	$title=$admin_title.'-龙宇网管理中心';
	$GLOBALS['smarty']->assign('admin_here',$admin_here);
	$GLOBALS['smarty']->assign('admin_title',$title);
}

?>