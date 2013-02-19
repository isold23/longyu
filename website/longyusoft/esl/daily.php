<?php 

define('IN_PBBLOG', true);
require(dirname(__FILE__) . '/include/core.php');

	$pg=isset($_GET['pg'])?intval($_GET['pg']):1;

	$page_size=!empty($page_size)?$page_size:'15';

	$sql='SELECT count(*) FROM '. table('daily');
	$page_count=intval(($db->getone($sql)-1)/$page_size)+1;

	$page_arr=create_page($page_count,$pg,0);

	$page_url='daily.php';

	$start=($pg-1)*$page_size;

	$cache_id = md5("daily_list".$pg);
	
	$sql = "select * from ".table('daily')." ORDER BY post_time DESC LIMIT ".$start.' , '.$page_size;

	$daily_list=$db->getall($sql);
	$smarty->assign('daily_list',$daily_list);
	
	$smarty->assign('page_url',$page_url);
	$smarty->assign('page_arr',$page_arr);
	$smarty->assign('page_count',$page_count);
	$smarty->assign('pg',$pg);
	$pre=$pg-1; 
	if($pre <= 0)
	{
		$pre = 1;
	}
	$smarty->assign('pre',$pre);
	$next=$pg+1;
	if($next >= $page_count)
	{
		$next = $page_count;
	}
	$smarty->assign('next',$next);	


$smarty->display('daily.html', $cache_id);

 ?>
  