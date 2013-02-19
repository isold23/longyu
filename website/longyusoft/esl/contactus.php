<?php 
  	
  	define('IN_PBBLOG', true);
	require(dirname(__FILE__) . '/include/core.php');
	require(dirname(__FILE__) . '/include/smtp.php'); 
	$act=!empty($_GET['act'])?trim($_GET['act']):'default';
	if ($act=='send_email') {
		$email=$_POST['email'];
		$subject=$_POST['subject'];
		$message_content=$_POST['message_content'];

$smtpserver = "smtp.gmail.com";//SMTP服务器 
$smtpserverport = 465;//SMTP服务器端口 
$smtpusermail = "isold.wang@gmail.com";//SMTP服务器的用户邮箱 
$smtpemailto = "isold.wang@qq.com";//发送给谁 
$smtpuser = "isold.wang@gmail.com";//SMTP服务器的用户帐号 
$smtppass = "wlx80100450625";//SMTP服务器的用户密码 
$mailsubject = "中文";//邮件主题 
$mailbody = "<h1>中文</h1>测试下能淤泥新年感";//邮件内容 
$mailtype = "HTML";//邮件格式（HTML/TXT）,TXT为文本邮件 

$smtp = new smtp($smtpserver,$smtpserverport,true,$smtpuser,$smtppass);//这里面的一个true是表示使用身份验证,否则不使用身份验证. 
$smtp->debug = TRUE;//是否显示发送的调试信息 
$smtp->sendmail($smtpemailto, $smtpusermail, $mailsubject, $mailbody, $mailtype); 
	}
  	$smarty->display('contactus.html');
 ?>
  