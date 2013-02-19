<?php 
define('IN_PBBLOG', true);
require(dirname(__FILE__) . '/include/core.php');

$action=$_GET['act'];
if($action=='search')
{
	$search_text=$_POST['search_text'];
	$sql='SELECT id,title,content FROM '.table('online_resource')." where cat_id=2 and title like '%".$search_text."%'";
	$fun_info=$db->getrow($sql);
	$fun_info['content']=htmlspecialchars_decode($fun_info['content']);
	$smarty->assign('fun_info',$fun_info);
	$smarty->display('linux_command.html');
}else if($action=='list'){
	$sql='SELECT id,name FROM '.table('online_small_cat')." where cat_id=2";
	$cat_list=$db->getall($sql);

	foreach ($cat_list as $key=>$val)
	{
		$sql='SELECT * FROM '.table('online_resource').
		" WHERE child_cat=".$val['id']." ORDER BY id ASC ";
		$cat_list[$key]['children'] = $db->getall($sql);
	}
	assign_page_info("Linux命令");
	$smarty->assign('cat_list',$cat_list);
	$smarty->display('linux_command_list.html');

}else if($action=='detail'){
 	$id=$_GET['id'];
	$sql='SELECT id,title,content FROM '.table('online_resource')." where cat_id=2 and id=".$id;
	$fun_info=$db->getrow($sql);
	$fun_info['content']=htmlspecialchars_decode($fun_info['content']);
	$smarty->assign('fun_info',$fun_info);
	assign_page_info($fun_info['title']);
	$smarty->display('linux_command.html');
}
	

?>


