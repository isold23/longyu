<?php

define('IN_PBBLOG', true);
require(dirname(__FILE__) . '/include/core.php');

$sql='SELECT b.id,b.title,b.description,b.post_time,b.view_count,b.comment_count,b.password,b.view_group,u.name AS user_name,c.name AS cat_name,c.id AS cat_id FROM '.
table('blog').' AS  b LEFT JOIN '.table('user').' AS u on b.user_id=u.id'.
'  LEFT JOIN '.table('blog_category').' AS c on b.cat_id=c.id'.
" ORDER BY b.post_time DESC LIMIT 0 , 20 ";
$blog_list=$db->getall($sql);
foreach ($blog_list as $key=>$val)
{
	$blog_list[$key]['description']=($val['description']);
}

$u=dirname($url);
$logo=$u.'/themes/'.$template_name."/logo.jpg";
$xml="<?xml version=\"1.0\" encoding=\"UTF-8\"?>  \n";
$xml.="<rss version=\"2.0\"> \n";
$xml.="<channel> \n";
$xml.="<title>{$web_name}</title>  \n";
$xml.="<link>{$u}/index.php</link> \n";
$xml.="<description>{$web_desc}</description> \n";
$xml.="<generator>龙宇网</generator> \n";
$xml.="<pubDate>{$date}</pubDate> \n";
$xml.="<image> \n";
$xml.="<url>{$logo}</url> \n";
$xml.="<title>{$web_name}</title> \n";
$xml.="<link>{$u}/index.php</link> \n";
$xml.="</image> \n";

foreach ($blog_list as $val)
{
	$xml.="<item> \n";
	$xml.="<title>{$val['title']}</title> \n";
	$xml.="<author>{$val['user_name']}</author> \n";
	$xml.="<link>{$u}/detail.php?id={$val['id']}</link> \n";
	$xml.="<description><![CDATA[{$val['description']}]]></description> \n";
	$xml.="<category><![CDATA[{$val['cat_name']}]]></category> \n";
	$xml.="<pubDate>{$val['post_time']}</pubDate> \n";
	$xml.="<guid>{$u}/blog.php?cat={$val['cat_id']}</guid> \n";
	$xml.="</item> \n";
}
$xml.="</channel> \n";
$xml.="</rss> \n";

echo $xml;
?>