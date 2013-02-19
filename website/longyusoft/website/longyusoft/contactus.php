<?php 
  define('IN_PBBLOG', true);
	require(dirname(__FILE__) . '/include/core.php');
	
	$action=$_GET['act'];
	
	if($action == 'send_email')
	{
		$to = "isold.wang@qq.com";
$subject = "Test mail";
$message = "Hello! This is a simple email message.";
$from = "isold.wang@qq.com";
$headers = "From: $from";
mail($to,$subject,$message,$headers);
echo "Mail Sent.";

	}
  	$smarty->display('contactus.html');
 ?>
  