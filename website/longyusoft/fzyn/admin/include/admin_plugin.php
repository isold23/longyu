<?php

$id=intval($_GET['id']);
//先获取所有插件列表
$sql='SELECT * FROM '.table('plugin').' WHERE';
$plugin_list=$db->getall($sql);
foreach ($plugin_list as $val)
{
	if ($id==$val['plugin_id']) 
	{
		require(PBBLOG_ROOT.'/home/plugins/'.$val['plugin_name'].'/admin.php');
		exit;
	}
}
?>