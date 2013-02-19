<?php

if (!defined('IN_PBBLOG'))
{
	die('Access Denied');
}

//过滤函数
function input_filter($input)
{
	return is_array($input) ? array_map('input_filter', $input) : addslashes($input);
}

//将过滤的数据转换为正常数据
function input_filter_decode($input)
{
	return is_array($input) ? array_map('input_filter_decode', $input) : stripslashes($input);
}


//来源页面
function referer_url()
{
	return isset($_SERVER['HTTP_REFERER']) ? $_SERVER['HTTP_REFERER'] : '';
}


//当前访问页面地址
function url()
{
	$scheme=$_SERVER['SERVER_PORT'] == '443' ? 'https://' : 'http://';

	if (isset($_SERVER['HTTP_X_FORWARDED_HOST']))
	{
		$host = $_SERVER['HTTP_X_FORWARDED_HOST'];
	}
	elseif (isset($_SERVER['HTTP_HOST']))
	{
		$host = $_SERVER['HTTP_HOST'];
	}

	if (isset($_SERVER['REQUEST_URI']))
	{
		$relate_url=$_SERVER['REQUEST_URI'];
	}
	else
	{
		$php_self = isset($_SERVER['PHP_SELF']) ? $_SERVER['PHP_SELF'] : $_SERVER['SCRIPT_NAME'];
		if (isset($_SERVER['QUERY_STRING']))
		{
			$relate_url=$php_self.'?'.$_SERVER['QUERY_STRING'];
		}
		else
		{
			$relate_url=$php_self.(isset($_SERVER['PATH_INFO']) ? $_SERVER['PATH_INFO'] : '');
		}
		echo $relate_url;
	}
	return $scheme.$host.$relate_url;
}


//当前域名
function domain()
{
	$scheme=$_SERVER['SERVER_PORT'] == '443' ? 'https://' : 'http://';

	if (isset($_SERVER['HTTP_X_FORWARDED_HOST']))
	{
		$host = $_SERVER['HTTP_X_FORWARDED_HOST'];
	}
	elseif (isset($_SERVER['HTTP_HOST']))
	{
		$host = $_SERVER['HTTP_HOST'];
	}
	return $scheme.$host;
}

//获取IP地址，用户通过高匿名代理服务器或者欺骗性代理服务器时是无法获取到真实ip的，因此ip获取只能作为参考,这个函数是互联网的一个通俗写法
function ip()
{
	if(getenv('HTTP_CLIENT_IP') && strcasecmp(getenv('HTTP_CLIENT_IP'), 'unknown'))
	{
		$ip = getenv('HTTP_CLIENT_IP');
	}
	elseif(getenv('HTTP_X_FORWARDED_FOR') && strcasecmp(getenv('HTTP_X_FORWARDED_FOR'), 'unknown'))
	{
		$ip = getenv('HTTP_X_FORWARDED_FOR');
	}
	elseif(getenv('REMOTE_ADDR') && strcasecmp(getenv('REMOTE_ADDR'), 'unknown'))
	{
		$ip = getenv('REMOTE_ADDR');
	}
	elseif(isset($_SERVER['REMOTE_ADDR']) && $_SERVER['REMOTE_ADDR'] && strcasecmp($_SERVER['REMOTE_ADDR'], 'unknown'))
	{
		$ip = $_SERVER['REMOTE_ADDR'];
	}
	else
	{
		$ip = '0.0.0.0';
	}
	return $ip;
}


//加上表前缀，获得真实的表名字
function table($tablename)
{
	return $GLOBALS['dbprefix'].$tablename;
}

//输出消息格式
function show_message($msg,$link_url)
{
	$GLOBALS['smarty']->assign('msg',$msg);
	$GLOBALS['smarty']->assign('new_url',$link_url);
	$GLOBALS['smarty']->display('notice.html');
	exit;
}

//重建url
function build_url($base,$id=1,$type=1)
{
	if ($GLOBALS['rewrite']==1)
	{
		//对默认重写方式构建url重写
		if ($type==1||empty($type))
		{
			if ($base=='blog')
			{
				$url='blog/'.$id.'.html';
			}
			elseif ($base=='cat')
			{
				$url='category/'.$id.'.html';
			}
			elseif ($base=='archive')
			{
				$url='archive/'.$id.'/';
			}
		}
		else
		{
			if ($base=='blog')
			{
				$url='blog/'.$type;
			}
			elseif ($base=='cat')
			{
				$url='category/'.$type;
			}
		}

		//对分页重构url
		if ($base=='index_page')
		{
			$url='index/'.$id.'/';
		}
		elseif ($base=='archives_list')
		{
			$url='archives/'.$type.'/'.$id.'/';
		}
		elseif ($base=='cat_list')
		{
			$url='category/'.$type.'/'.$id.'/';
		}
	}
	else
	{
		if ($base=='blog')
		{
			$url='blog.php?id='.$id;
		}
		elseif ($base=='cat')
		{
			$url='list.php?act=cat_list&id='.$id;
		}
		elseif ($base=='archive')
		{
			$url='list.php?act=archives_list&date='.$id;
		}
		elseif ($base=='index_page')
		{
			$url='index.php?pg='.$id;
		}
		elseif ($base=='archives_list')
		{
			$url='list.php?act=archives_list&date='.$type.'&pg='.$id;
		}
		elseif ($base=='cat_list')
		{
			$url='list.php?act=cat_list&id='.$type.'&pg='.$id;
		}
	}
	return $GLOBALS['domain'].$url;
}


//页数函数，创建页数所有的参数
function create_page($page_count,$pg,$type=0)
{
	$pager_size=!empty($GLOBALS['pager_size'])?$GLOBALS['pager_size']:'5';


	if ($pg>$page_count)
	{
		show_message('错误页数',$GLOBALS['referer_url']);
	}
	$page_arr=array();

	if ($type==1)
	{
		$i=0;
		$page_arr[$i]['name']='首页';
		$page_arr[$i]['value']='1';
		$i++;
		if ($pg>1)
		{
			$page_arr[$i]['name']='上一页';
			$page_arr[$i]['value']=$pg-1;
			$i++;
		}
		if ($pg<$page_count)
		{
			$page_arr[$i]['name']='下一页';
			$page_arr[$i]['value']=$pg+1;
			$i++;
		}
		$page_arr[$i]['name']='尾页';
		$page_arr[$i]['value']=$page_count;
	}
	else
	{
		$i=0;
		if ($pg-$pager_size<1)
		{
			for ($j=1;$j<=$pg;$j++)
			{
				$page_arr[$i]['name']=$j;
				$page_arr[$i]['value']=$j;
				$i++;
			}
		}
		else
		{
			for ($j=$pg-$pager_size;$j<=$pg;$j++)
			{
				$page_arr[$i]['name']=$j;
				$page_arr[$i]['value']=$j;
				$i++;
			}
		}

		if ($pg+$pager_size<$page_count)
		{
			for ($j=$pg+1;$j<=$pg+$pager_size;$j++)
			{
				$page_arr[$i]['name']=$j;
				$page_arr[$i]['value']=$j;
				$i++;
			}
		}
		else
		{
			for ($j=$pg+1;$j<$page_count+1;$j++)
			{
				$page_arr[$i]['name']=$j;
				$page_arr[$i]['value']=$j;
				$i++;
			}
		}

	}

	return $page_arr;
}

function create_page_url($page_arr,$base,$type)
{
	//对页面url重构
	foreach ($page_arr as $key=>$val)
	{
		$page_arr[$key]['url']=build_url($base,$val['value'],$type);
	}
	return $page_arr;
}

//对页面进行模板初始化，包括页面标题，博客名称，博客描述等
function assign_page_info($title='')
{
	/*对首页初始化*/
	if (empty($title))
	{
		$page_title=$GLOBALS['web_title'];
	}

	//首页默认为空，其他情况下页面标题为$title的值
	elseif ($title!='')
	{
		$page_title=$title.'-';
	}


	$page_title.= $GLOBALS['blog_name'].'-非洲艺术品，非洲工艺品、非洲乌木雕，非洲木雕，非洲石雕，非洲面具等';
	$GLOBALS['smarty']->assign('page_title',$page_title);
	$GLOBALS['smarty']->assign('notice',$GLOBALS['notice']);
	$GLOBALS['smarty']->assign('open_comment',$GLOBALS['open_comment']);

	$GLOBALS['smarty']->assign('blog_name',$GLOBALS['blog_name']);
	$GLOBALS['smarty']->assign('blog_desc',$GLOBALS['blog_desc']);
	$GLOBALS['smarty']->assign('blog_keyword',$GLOBALS['blog_keyword']);

	$GLOBALS['smarty']->assign('domain',$GLOBALS['domain']);

	$GLOBALS['smarty']->assign('templates_dir','themes/'.$GLOBALS['template_name'].'/');

	$GLOBALS['smarty']->assign('feed_url',dirname($GLOBALS['url']).'/feed.php');
}

//对页面进行边栏初始化，包括页面分类，归档等
function assign_sidebar_info()
{
	//获得网站导航数据
	$sql='SELECT * FROM '.table('modules').' WHERE type=2 '.
	" ORDER BY sort ASC  ";
	$nav_list=$GLOBALS['db']->getall($sql);
	foreach ($nav_list as $key=>$val)
	{
		if (strpos(substr(strrchr($_SERVER['REQUEST_URI'],'/'),1),$val['content'])===0)
		{
			$nav_list[$key]['current']=1;
		}
		
		//重写导航url
		if ($GLOBALS['rewrite']) 
		{
			if (substr($val['content'],0,4)!='http') 
			{
				$nav_list[$key]['content']=$GLOBALS['domain'].$val['content'];
			}
		}
	}

	//获得友情链接
	$sql='SELECT * FROM '.table('link').
	" ORDER BY sort ASC  ";
	$link_list=$GLOBALS['db']->getall($sql);

	//获得分类数据
	$sql='SELECT cat_id,cat_name,cat_desc,listorder,url_type FROM '.table('category').
	" WHERE parent_id=0 ORDER BY listorder ASC , cat_id ASC ";
	$cat_list=$GLOBALS['db']->getall($sql);

	//获取子分类，暂时只支持二级分类
	foreach ($cat_list as $key=>$val)
	{
		$sql='SELECT cat_id,cat_name,cat_desc,listorder,url_type FROM '.table('category').
		" WHERE parent_id=".$val['cat_id']." ORDER BY listorder ASC , cat_id ASC ";
		$cat_list[$key]['url']=build_url('cat',$val['cat_id'],$val['url_type']);
		$cat_list[$key]['children']=$GLOBALS['db']->getall($sql);
		if ($cat_list[$key]['children'])
		{
			foreach ($cat_list[$key]['children'] as $children_key=>$children_val)
			{
				$cat_list[$key]['children'][$children_key]['url']=build_url('cat',$children_val['cat_id'],$children_val['url_type']);
			}
		}
	}

	//获得归档数据
	$sql = 'SELECT add_time FROM '.table('blog').' ORDER BY add_time DESC';
	$archives=$GLOBALS['db']->getall($sql);
	foreach ($archives as $key => $val)
	{
		$archive[]=date("Y/m",$val['add_time']);
		//将日志中的时间转换成为档案时间的形式，也就是年月的形式
	}

	$archive=!empty($archive)?array_count_values($archive):array();

	foreach ($archive as $key=>$val)
	{
		$year=substr($key,0,4);
		$month=substr($key,5,6);
		$archive_list[$key]['data']=$year.'年'.$month.'月['.$val.']';
		$archive_list[$key]['url']=build_url('archive',$key,1);
	}

	$GLOBALS['smarty']->assign('link_list',$link_list);
	$GLOBALS['smarty']->assign('nav_list',$nav_list);
	$GLOBALS['smarty']->assign('feed_url',dirname($GLOBALS['url']).'/feed.php');
	$GLOBALS['smarty']->assign('cat',$cat_list);
	$GLOBALS['smarty']->assign('archives',$archive_list);


}


//调用会员信息
function insert_member_info()
{
	$need_cache = $GLOBALS['smarty']->caching;
	$GLOBALS['smarty']->caching = false;
	$domain=$GLOBALS['domain'];

	if ($_SESSION['user_id'] > 0)
	{
		$user=user_info();

		//如果是管理员登陆，出现后台管理地址
		if ($user['group_id']==1) {
			$admin_url='<li><a href="'.$domain.'admin/">后台管理</a></li>';
		}

		$output='<ul><li><a href="'.$domain.'">首页</a></li><li><a>欢迎您,'.$user['user_name'].'</a></li><li><a>您所在用户组:'.
		$user['group_name'].'</a></li><li><a href="'.$domain.'user.php?act=profile">个人资料</a></li>'.$admin_url.
		'<li><a href="'.$domain.'user.php?act=logout">退出</a></li></ul>';

	}
	else
	{
		$output='<ul><li><a href="'.$domain.'">首页</a></li>'.
		'<li><a href="'.$domain.'user.php?act=reg">注册</a></li>'.
		'<li><a href="'.$domain.'user.php?act=login">登陆</a></li></ul>';
	}

	$GLOBALS['smarty']->caching = $need_cache;

	return $output;
}

//用户信息函数
function user_info()
{
	$sql='SELECT o.id,o.name,o.email,o.homepage,o.reg_time,o.last_time,u.name AS gname,u.id AS gid FROM '.table('user').
	" o LEFT JOIN ".table('user_group')." u on o.group_id=u.id".
	" WHERE o.id='".$_SESSION['user_id']."'";
	return $GLOBALS['db']->getrow($sql);
}


//插入评论者的名字
function insert_comments_name()
{
	if ($_SESSION['user_id']>0)
	{
		$user=user_info();
		$content='<p>名字：'.$user['name'].'<br /><input type="hidden" name="name" id="name" value='.$user['name'].' /></p>'.
		'<input type="hidden" name="url" id="url" value="'.$user['home'].'" />'.
		'<input type="hidden" name="email" id="email" value="'.$user['email'].'" />';
	}
	else
	{
		$content='<p>名字：<br /><input type="text" name="name" id="name" /></p>';
		$content.='<p>个人主页地址：<br />'.'<input type="text" name="url" id="url"  /></p>';
		$content.='<p>E-mail：<br />'.'<input type="text" name="email" id="email" /></p>';
	}
	return $content;
}

//打印函数
function print_k($a){
	echo '<pre>';
	print_r($a);
	echo '</pre>';
	exit;
}

//blog内容摘要
function blog_summary($str){
	if(strlen($str) > 500)
	{
		$str1 = strip_tags($str);
		$str2 = substr($str1, 0, 800);
		return $str2."...";
	}
	else
	{
		return $str;
	}
}




?>