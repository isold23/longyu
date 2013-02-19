<?php 
  define('IN_PBBLOG', true);
  require(dirname(__FILE__) . '/include/core.php');
  require(dirname(__FILE__) . '/include/json.class.php');
  //获取所有日记
  $cache_announcement=md5("all_daily");
	$sql="select * from ".table('daily')." ORDER BY post_time DESC";
	$daily_list=$db->getall($sql);
	foreach ($daily_list as $key=>$val){
		$object[$key] = array("content" => $daily_list[$key]['content'], "post_time" => $daily_list[$key]['post_time']); 
		$encoded = json_encode(array_values($object));
	}
	echo $encoded;
?>