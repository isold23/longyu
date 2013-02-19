-- phpMyAdmin SQL Dump
-- version 3.3.8
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Jul 18, 2011 at 04:12 AM
-- Server version: 5.1.52
-- PHP Version: 5.3.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


--
-- Database: `meiyiju`
--

-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_albums`
--

CREATE TABLE IF NOT EXISTS `meiyiju_albums` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `create_time` datetime NOT NULL,
  `description` varchar(200) NOT NULL,
  `photo_count` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `meiyiju_albums`
--


-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_announce`
--

CREATE TABLE IF NOT EXISTS `meiyiju_announce` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `announce` longtext NOT NULL,
  `post_time` datetime NOT NULL,
  `show` tinyint(3) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `meiyiju_announce`
--


-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_announcement`
--

CREATE TABLE IF NOT EXISTS `meiyiju_announcement` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `title` varchar(100) NOT NULL,
  `content` longtext NOT NULL,
  `post_time` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

--
-- Dumping data for table `meiyiju_announcement`
--

INSERT INTO `meiyiju_announcement` (`id`, `title`, `content`, `post_time`) VALUES
(2, '美宜居装饰8月8日盛大开业！', '美宜居装饰8月8日盛大开业！', '2011-07-16 17:19:39'),
(3, '庆祝开业 四重大礼回报客户', '庆祝开业 四重大礼回报客户', '2011-07-17 12:31:15');

-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_blog`
--

CREATE TABLE IF NOT EXISTS `meiyiju_blog` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `cat_id` int(11) NOT NULL,
  `title` varchar(255) NOT NULL,
  `author` varchar(25) NOT NULL,
  `trackback_url` varchar(255) NOT NULL,
  `content` longtext NOT NULL,
  `mode` tinyint(3) NOT NULL,
  `locked` tinyint(3) NOT NULL,
  `selected` tinyint(3) NOT NULL,
  `post_time` datetime NOT NULL,
  `ip` varchar(15) NOT NULL,
  `comment_count` int(11) NOT NULL,
  `view_count` int(11) NOT NULL,
  `trackback_count` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `description` varchar(100) NOT NULL,
  `last_time` datetime NOT NULL,
  `password` varchar(20) NOT NULL,
  `view_group` int(11) NOT NULL,
  `open_type` int(11) NOT NULL,
  `url_type` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=10 ;

--
-- Dumping data for table `meiyiju_blog`
--

INSERT INTO `meiyiju_blog` (`id`, `cat_id`, `title`, `author`, `trackback_url`, `content`, `mode`, `locked`, `selected`, `post_time`, `ip`, `comment_count`, `view_count`, `trackback_count`, `user_id`, `description`, `last_time`, `password`, `view_group`, `open_type`, `url_type`) VALUES
(2, 2, '2010年家居装修瓷砖流行亮点', '', '', '<p>在<a href="http://www.zx1234.com/" target="_blank">家居</a><a href="http://www.zx1234.com/" target="_blank">装修</a>中，<a href="http://www.zx1234.com/cz/" target="_blank">瓷砖</a>一直是持久不衰，随着人们对装修风格要求的不断提高瓷砖的运用也在发生着变化。</p><p>\r\n	<br>\r\n	<strong>打破传统，<a href="http://www.zx1234.com/cz/" target="_blank">地砖</a>也能上墙</strong></p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	传统意义上，用于装修的内墙砖与地砖在材质、花色、规格上都有着一定的差别。然而在当下的装修中，地砖上墙已经不再是新鲜事，因为这样能衬得居室比较大气。据业内人士介绍，地砖上墙需要经过工艺的改造，多了墙面的防水性能，而保留地砖的纹理和大气的规格，也有业主喜用仿皮的瓷砖上墙，像<a href="http://www.zx1234.com/cz/makeboluo/" target="_blank">马可波罗</a>、<a href="http://www.zx1234.com/wy/dongpengjieju/" target="_blank">东鹏</a><a href="http://www.zx1234.com/cz/" target="_blank">陶瓷</a>这些<a href="http://www.zx1234.com/shida/index.html" target="_blank">品牌</a>都已研发出可配各种居家风格的瓷砖。<br>\r\n	<br>\r\n	<strong>功能型瓷砖走进书房卧室</strong></p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	由于木材给人感觉温馨、踩上去脚感舒适，以及相对瓷砖硬度偏低等共性，让业主在卧室地面的选择上，更多地倾向于<a href="http://www.zx1234.com/db/" target="_blank">地板</a>。然而随着中央<a href="http://www.zx1234.com/jiadian/" target="_blank">空调</a>，<a href="http://www.zx1234.com/cainuang/" target="_blank">地暖</a>系统的普及，室内开始进入恒温阶段，同时更多的仿古砖、个性砖开始走向市场，如仿木砖、仿<a href="http://www.zx1234.com/bizhi/" target="_blank">壁纸</a>砖、仿布砖等，仿木砖简直和地板外观一样，仿壁纸砖惟妙惟肖酷似壁纸，而它们却更易于打理，颜色和风格也有更多的选择。于是一部分业主在卧室选择瓷砖进行<a href="http://www.zx1234.com/" target="_blank">装饰</a>。</p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	消费者选择瓷砖来铺贴卧室的原因有很多。第一，<a href="http://www.zx1234.com/cainuang/" target="_blank">地热</a>会促进不良<a href="http://www.zx1234.com/db/" target="_blank">木地板</a>的<a href="http://www.zx1234.com/" target="_blank">甲醛</a>释放，对人体健康不利，而瓷砖并不受此影响;第二，瓷砖所营造的艺术氛围和舒适感觉可以缓解一天工作后的压力，让人陶醉在安逸的艺术海洋中;最后，让消费者顾虑的，<a href="http://www.zx1234.com/cz/czfitment/" target="_blank">瓷砖铺贴</a>卧室不够温馨，也已被推陈出新的各种瓷砖而打消了。随着制作工艺水平的提高，以及暖融融的羊毛地垫，使得瓷砖的脚感离“冰凉”的传统感觉越来越远。<br>\r\n	<br>\r\n	<strong>新款大砖古典现代两相宜</strong></p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	最初同样是因为清洁卫生的考虑，不少业主选择在客餐厅也铺贴瓷砖&nbsp;。而在现代家居中，瓷砖的运用已超越了其传统的保护作用，更多地着重于装饰功效。在材质选择上，仿古砖、皮纹砖和波光砖行走在潮流和复古之间;设计风格上，古典的清新淡雅和现代的明艳欢快都发挥得淋漓尽致。</p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	相对于地板，瓷砖有了更多的风格搭配，因此很多业主选择瓷砖来铺贴--&gt;客厅地面。在颜色选择上，偏好柔和的色调，像米黄色、咖啡色、浅红色、胡桃木色都是运用较多的色彩，因为柔和的色彩能给人一种安全感，而这也是大多数业主从营造温馨家居氛围的角度所考虑。而在规格上，1.2×1.2米的大砖更受业主的欢迎，特别是一些别墅业主。<br>\r\n	<br>\r\n	<strong><a href="http://www.zx1234.com/cj/" target="_blank">厨卫</a></strong><strong>瓷砖点缀浪漫与时尚</strong></p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	厨卫间是最早使用瓷砖的场所。过去人们铺贴瓷砖，主要从清洁卫生角度考虑，于是瓷砖尤其是墙砖，几乎是清一色的白色或光面砖，质感变化少。而随着瓷砖制作工艺的逐步提高，瓷砖表面质感有了丰富的变化，装饰效果会使<a href="http://www.zx1234.com/cj/" target="_blank">厨房</a>和卫生间呈现出不同质感的风格，因此在厨卫装修中，瓷砖的选择受到了业主更多的重视。</p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	如今，各式各样的瓷砖开始进入厨卫间，厨房和卫生间成为了整体<a href="http://www.zx1234.com/" target="_blank">家装</a>的组成部分，而不再只是独立的空间。小巧玲珑、色彩斑斓的马赛克砖，点缀在<a href="http://www.zx1234.com/wy/" target="_blank">卫浴</a>小空间，不仅显得主人很潮流，还能够营造出浪漫的氛围;而在厨房点缀几块花色瓷砖，美轮美奂的效果更是立马呈现。</p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	瓷砖企业只要抓住好这些流行的趋势，成功地运用在产品中，必定会收到很大的市场效应。</p>', 0, 0, 0, '2011-07-17 11:53:22', '', 5, 6, 0, 2, '在家居装修中，瓷砖一直是持久不衰，随着人们对装修风格要求的不断提高瓷砖的运用也在发生着变化。', '0000-00-00 00:00:00', '', 0, 0, 1),
(3, 2, '2010年仿古砖十大品牌排行榜', '', '', '<p>\r\n	&nbsp;</p>\r\n<p align="left">\r\n	1、金意陶-KITO &nbsp; &nbsp; &nbsp;(仿古砖十大品牌,著名品牌,佛山金意陶陶瓷有限公司)</p>\r\n<p align="left">\r\n	2、马可波罗-E石代&nbsp; &nbsp; (中国名牌,十大仿古砖品牌,广东唯美陶瓷有限公司)&nbsp;</p>\r\n<p align="left">\r\n	3、帝舵-圣马力亚&nbsp; &nbsp; (仿古砖十大品牌,一线牌子,佛山市辉达陶瓷有限公司)&nbsp;</p>\r\n<p align="left">\r\n	4、新中源/新中瓷&nbsp; &nbsp; (中国驰名商标,广东新中源(新里万/陶仙坊),佛山新中瓷NCC)&nbsp;</p>\r\n<p align="left">\r\n	5、能强&nbsp; &nbsp; (十大仿古砖品牌,广东省名牌产品,广东能强陶瓷有限公司)&nbsp;</p>\r\n<p align="left">\r\n	6、欧典/欧古&nbsp; &nbsp; (十大仿古砖品牌,佛山市彩蝶陶瓷科技有限公司)&nbsp;</p>\r\n<p align="left">\r\n	7、路易摩登&nbsp; &nbsp; (仿古砖十大品牌,广东百强民营企业,广东新明珠陶瓷公司)&nbsp;</p>\r\n<p align="left">\r\n	8、圣陶坊&nbsp; &nbsp; (十大仿古砖品牌,一线牌子,佛山圣陶坊陶瓷有限公司)&nbsp;</p>\r\n<p align="left">\r\n	9、RGC荣高&nbsp; &nbsp; (仿古砖十大品牌,绿色环保产品,佛山市顺德区荣高陶瓷有限公司)&nbsp;</p>\r\n<p align="left">\r\n	10、大唐合盛&nbsp; &nbsp; (十大仿古砖品牌,最具成长性仿古砖品牌,佛山市大唐合盛陶瓷有限公司)</p>\r\n', 0, 0, 0, '2011-07-17 11:44:57', '', 0, 2, 0, 2, '2010年仿古砖十大品牌排行榜', '0000-00-00 00:00:00', '', 0, 0, 1),
(4, 2, '墙面&木器伤不起 如何监督油漆抢先知', '', '', '<p class="MsoNormal" style="text-indent:21.0pt"><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-theme-font:minor-fareast;\r\nmso-fareast-theme-font:minor-fareast;mso-hansi-theme-font:minor-fareast;\r\ncolor:black;mso-themecolor:text1">乳胶漆是目前最常见的墙面<span lang="EN-US"><a href="http://www.zx1234.com/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">装饰</span></span></a></span>材料，在具体施工中可以进行涂刷、辊涂或喷涂。如果工人在施工时不认真或敷衍了事，常会出现微小的色差。尤其是颜色较深的乳胶漆更会出现这种问题。墙面专家提醒：乳胶漆在使用之前需要加入一定的清水，调配好的乳胶漆要一次用完。同一颜色的涂料也最好一次涂刷完毕。如果施工完毕后墙面需要修补，就要将整个墙面重新涂刷一遍。</span><span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p class="MsoNormal" style="text-indent:21.0pt"><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-theme-font:\r\nminor-fareast;mso-fareast-theme-font:minor-fareast;mso-hansi-theme-font:minor-fareast;\r\ncolor:black;mso-themecolor:text1"><o:p>&nbsp;</o:p></span></span></p>\r\n\r\n<p class="MsoNormal" style="text-indent:21.0pt"><span style="mso-bidi-font-size:\r\n10.5pt;font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-theme-font:minor-fareast;color:black;mso-themecolor:\r\ntext1">刷木器漆的时间最好等房间铺完<span lang="EN-US"><a href="http://www.zx1234.com/cz/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;\r\ntext-decoration:none;text-underline:none"><span lang="EN-US">地砖</span></span></a></span>或<span lang="EN-US"><a href="http://www.zx1234.com/db/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;\r\ntext-underline:none"><span lang="EN-US">木</span></span></a><a href="http://www.zx1234.com/db/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">地板</span></span></a></span>再刷。如果一定要刷的话，最好也要将房间打扫干净。没铺地砖或木地板的房间，房间里的粉尘很多，这时刷木器漆的话，粉尘容易附着在刷过木器漆的木制品表面，摸上去有刺刺的感觉，这种情况虽然可用较高标号的砂纸打磨后再刷一遍解决，但是最后刷出来摸上去的手感与整体效果就会打点折扣。房间铺完地砖后再刷，那时空气里的粉尘含量比之铺前少很多，基本不会出现刷过一遍木器漆后粉尘附着在木制品表面的情况。<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p class="MsoNormal" style="text-indent:21.0pt"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-theme-font:minor-fareast;\r\nmso-fareast-theme-font:minor-fareast;mso-hansi-theme-font:minor-fareast;\r\ncolor:black;mso-themecolor:text1"><o:p>&nbsp;</o:p></span></p>\r\n\r\n<p class="MsoNormal" style="text-indent:21.0pt"><span class="Apple-style-span" style="font-family: 宋体; ">漆</span><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-theme-font:minor-fareast;\r\nmso-fareast-theme-font:minor-fareast;mso-hansi-theme-font:minor-fareast;\r\ncolor:black;mso-themecolor:text1">师傅是等墙面干透再批完腻子的，腻子层干透后刷漆。刷完漆之后如果没什么原因就要装<span lang="EN-US"><a href="http://www.zx1234.com/dj/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;\r\ntext-underline:none"><span lang="EN-US">灯具</span></span></a></span>和各种<span lang="EN-US"><a href="http://www.zx1234.com/jiadian/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;\r\ntext-underline:none"><span lang="EN-US">电器</span></span></a></span>开关了。请同学们提醒装灯具与电器开关的师傅注意一下，装之前将手冼干净，这样装的时候就不会弄污墙面了。也就省了一道补漆的工序了。当然，弄污了墙面，<span lang="EN-US"><a href="http://www.zx1234.com/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">装修</span></span></a></span>队肯定是要让油漆师傅再来补漆的，也就是将弄污的墙面弄干净（如果是油漆公司的话，他们也会让师傅来补漆的，如果注意一下很多油漆师傅在刷完墙面后都会剩一部分漆，这剩余的一部分漆是用来补漆用的）。只是注意一下，不要让装灯具的师傅弄污了墙面，就可以让让油漆师傅少跑一趟（至少也要半天）。一般来说，在刷<span lang="EN-US"><a href="http://www.zx1234.com/yq/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;\r\ntext-underline:none"><span lang="EN-US">墙面漆</span></span></a></span>之前都会将木器漆刷完，这样做是避免木器漆在干的过程中会对刷过墙面漆的墙面有影响。当然，在实际操作过程中，也可以将地砖铺完之后（铺地砖之前已将墙面的腻子批好）再刷木器漆，等木器漆干透之后再刷墙面漆，只是这样做，当然会影响工期。如果怕影响工期的话，又要将空气中粉尘的影响降到最小，那就要勤快点多多打扫一下房间里的卫生了。<span lang="EN-US"><o:p></o:p></span></span></p>', 0, 0, 0, '2011-07-17 11:58:31', '', 0, 4, 0, 2, '墙面&amp;木器伤不起&nbsp;如何监督油漆抢先知', '0000-00-00 00:00:00', '', 0, 0, 1),
(5, 5, '涂料装修业花样多 商家大赚黑心钱', '', '', '<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">涂料行业的竞争角逐越来越激烈，市场上和<span lang="EN-US"><a href="http://www.zx1234.com/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;\r\ntext-decoration:none;text-underline:none"><span lang="EN-US">装修</span></span></a></span>中那些不为人知的内幕你又知道多少呢？在<span lang="EN-US">3.15</span>临近之际，小编为您揭开那些不为人知的黑幕。<span lang="EN-US"><o:p></o:p></span></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"=""><br></span></p>\r\n\r\n<p style="line-height:17.25pt"><b><span style="font-size:10.5pt;mso-ascii-font-family:\r\n宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;\r\nmso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:text1"="">玩材料<span lang="EN-US">“</span>文章<span lang="EN-US">”</span></span></b><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;\r\nmso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:\r\n宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:" times="" new="" roman";="" color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">人们往往在装修后才知道装修过程是怎么回事，<span lang="EN-US"><a href="http://www.zx1234.com/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;\r\ntext-decoration:none;text-underline:none"><span lang="EN-US">家装</span></span></a></span>的专业性也绝不是一般人几天时间就可以了解的，所以家装在工程上的<span lang="EN-US">“</span>猫腻<span lang="EN-US">”</span>往往较多。<span lang="EN-US"><o:p></o:p></span></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"=""><br></span></p>\r\n\r\n<p style="line-height:17.25pt"><b><span style="font-size:10.5pt;mso-ascii-font-family:\r\n宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;\r\nmso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:text1"="">手法一：以次充好</span></b><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:\r\nminor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;\r\nmso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:\r\n" times="" new="" roman";color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">业内人士易琦说：刚装修完工的新居，如果发现<span lang="EN-US"><a href="http://www.zx1234.com/db/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;\r\ntext-decoration:none;text-underline:none"><span lang="EN-US">地板</span></span></a></span>起翘，拱起，施工方往往会推辞是地板质量问题，而地板经销商却推脱是施工方铺设不当造成的。<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">对策：新居装修多半都是业主自己买主材，施工方施工以半包方式进行，这给日后双方责任区分不清埋下了隐患。特别是有<span lang="EN-US">“</span>三分材料，七分铺设<span lang="EN-US">”</span>之说的地板，对施工的要求非常高，发生的投诉也非常多，同一<span lang="EN-US"><a href="http://www.zx1234.com/shida/index.html" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">品牌</span></span></a></span>的砖，等级、色彩、规格是不一样的。因此，在选择地板时，地板提供者和安装者最好是一个主体，这样出了问题，责任人只有一个，避免扯皮现象的发生。签订合同时，所用材料的品牌、等级、规格及数量都要明确，不管用什么材料，货到现场业主一定要认真验收。<span lang="EN-US"><o:p></o:p></span></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"=""><br></span></p>\r\n\r\n<p style="line-height:17.25pt"><b><span style="font-size:10.5pt;mso-ascii-font-family:\r\n宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;\r\nmso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:text1"="">手法二：多买材料</span></b><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:\r\nminor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;\r\nmso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:\r\n" times="" new="" roman";color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">一次新居装修要多少材料，这对施工方或业主来说只是一个大概的数字。为此，不管是施工方或是业主在购回材料装修完后，很多施工方往往在拿回去退货的过程中，挣多买的材料钱，同时又可以多拿工钱，赚的是真实数量与虚报数量的差价。<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">对策：叫施工方提供购买材料时的单据，在耗损允许的情况之内与所用实际的材料进行核算。<span lang="EN-US"><o:p></o:p></span></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"=""><br></span></p>\r\n\r\n<p style="line-height:17.25pt"><b><span style="font-size:10.5pt;mso-ascii-font-family:\r\n宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;\r\nmso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:text1"="">偷工减料</span></b><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:\r\nminor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;\r\nmso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:\r\n" times="" new="" roman";color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">家装投诉主要是水、电改<span lang="EN-US">(</span>安<span lang="EN-US">)</span>装等隐蔽工程。本来只用两根导线管就可接几个<span lang="EN-US"><a href="http://www.zx1234.com/dj/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;\r\ntext-underline:none"><span lang="EN-US">插座</span></span></a></span>，而施工队却用<span lang="EN-US">6</span>根或<span lang="EN-US">8</span>根导线连接几个插座，工程量一下子提高了两三倍；本来是<span lang="EN-US">9</span>股线的电线被施工队换成只有四五股线的电线，表面上根本看不出破绽<span lang="EN-US">……<o:p></o:p></span></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"=""><span lang="EN-US"><br></span></span></p>\r\n\r\n<p style="line-height:17.25pt"><b><span style="font-size:10.5pt;mso-ascii-font-family:\r\n宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;\r\nmso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:text1"="">手法一：挪用材料</span></b><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:\r\nminor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;\r\nmso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:\r\n" times="" new="" roman";color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">易琦说，他曾经碰到这样一件事，业主请来一个<span lang="EN-US">“</span>马路游击队<span lang="EN-US">”</span>给新房装修。在装修过程中，业主想把墙壁上的插座挪个位置，但现场施工人员说挪位要等施工监理过来才行，不许该业主挪位。对此，该业主觉得事有蹊跷，便坚决要挪，没想到原本用于隐蔽工程的铜线，只是露出的一小部分，墙体内埋的全都是铝线<span lang="EN-US">(</span>国家法规不允许<span lang="EN-US">)</span>，该业主随后将房间内的几处内线全抽出来，都是类似情况。<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p class="MsoNormal" style="text-indent:21.0pt"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-theme-font:minor-fareast;\r\nmso-fareast-theme-font:minor-fareast;mso-hansi-theme-font:minor-fareast;\r\ncolor:black;mso-themecolor:text1"><o:p>&nbsp;</o:p></span></p>\r\n\r\n\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">对策：业主最好是明白自己的房间该用多少材料，施工方要有记录，业主也要做到心中有数。<span lang="EN-US"><o:p></o:p></span></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"=""><br></span></p>\r\n\r\n<p style="line-height:17.25pt"><b><span style="font-size:10.5pt;mso-ascii-font-family:\r\n宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;\r\nmso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:text1"="">手法二：以次充好</span></b><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:\r\nminor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;\r\nmso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:\r\n" times="" new="" roman";color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">一名市民装修房子遇到了尴尬情况：本来墙壁应刷<span lang="EN-US">6</span>桶面漆，结果施工人员仅刷了<span lang="EN-US">3</span>桶面漆；本来是用一种<span lang="EN-US"><a href="http://www.zx1234.com/shida/index.html" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">名牌</span></span></a></span>面漆，可施工队却用名牌涂料桶装劣等涂料，以此大赚黑心钱，业主却很少知道。<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">对策：业主与施工方一定要签订装修合同，要明确双方的违约责任，或请律师、饰装协会或公证员进行监督或公证。在购买<span lang="EN-US"><a href="http://www.zx1234.com/yq/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">油漆</span></span></a></span>、涂料等数量较大的<span lang="EN-US"><a href="http://www.zx1234.com/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">装饰</span></span></a></span>材料时，不要一次性买完，最好分批购买，同时对使用完的桶及其他包装要留下，以备核算数量。<span lang="EN-US"><o:p></o:p></span></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"=""><br></span></p>\r\n\r\n<p style="line-height:17.25pt"><b><span style="font-size:10.5pt;mso-ascii-font-family:\r\n宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;\r\nmso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:text1"="">少做多量</span></b><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:\r\nminor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;\r\nmso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:\r\n" times="" new="" roman";color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">装修时，很大一部分价格的计算都是以测量的方式计算，比如墙体的面积、水电的长度等，装修公司往往为了能够多赚利润，采取少做多量的方式榨取，<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">业内人士王祥彬告诉记者，在装修过程中，有一个必不可少的程序，那就是水电的安装，许多施工队不仅在水电材料上做文章，还在测量算价时大做文章，其中材料方面，那是明显以次充好，一般的水电材料分有数个等级，报<span lang="EN-US">A</span>管的价格，却拿<span lang="EN-US">B</span>管材料，于是造成水电设备不是线径的规格减少就是电线没有地线或者多路同组电线，将<span lang="EN-US">B</span>管充<span lang="EN-US">A</span>管用。<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">而算价时，大部分施工队是按位计算，前期与业主谈单价时会承诺业主多少钱一位，然后会大概的估价业主套房需多少位，但在实际施工中，施工队却<span lang="EN-US">“</span>善意<span lang="EN-US">”</span>提醒某些重要位置需要增加，即使有所谓验收，但是因随意性较大，没有统一的验收规范，也没有详细的水电路走向图，于是就多量出了水电线，导致业主会多出许多意想不到的<span lang="EN-US">????X?</span>钱。<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">对策：任何测量业主都要到场，不仅仅要认真测量，还要细心地做好记录，一旦被多测算出了面积或者长度，那都是钱。<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">总之在面临这些陷阱时，业主应与施工方有明确的责任关系，责任承担人应尽量找规模较大，操作专业正规的家装公司，不要省表面的钱邀请<span lang="EN-US">“</span>马路游击队<span lang="EN-US">”</span>施工，在验收时业主一定要在现场，对所有要验收的项目仔细检查，对所有材料的使用铺设都要询问清楚，做到心中有数，明白消费，才能做到对自己消费权益的正当的维护。<span lang="EN-US"><o:p></o:p></span></span></p>', 0, 0, 0, '2011-07-18 01:35:46', '', 0, 4, 0, 2, '涂料行业的竞争角逐越来越激烈，市场上和装修中那些不为人知的内幕你又知道多少呢？在3.15临近之际，小编为您揭开那些不为人知的黑幕。', '0000-00-00 00:00:00', '', 0, 0, 1),
(6, 4, '地板胶地板垫竟是健康杀手', '', '', '<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:\r\ntext1">人们在挑选<span lang="EN-US"><a href="http://www.zx1234.com/db/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;\r\ntext-underline:none"><span lang="EN-US">木</span></span></a><a href="http://www.zx1234.com/db/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">地板</span></span></a></span>时，往往将注意力集中在地板的耐磨度、<span lang="EN-US"><a href="http://www.zx1234.com/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">甲醛</span></span></a></span>释放量、花色款式等地板质量问题上，而对于踢脚板、地板胶、地板垫等配件的环保问题却往往不太重视。国家建筑材料测试中心的专家说：<span lang="EN-US">“</span>木地板的配件和辅料选择不好，也有可能暗藏杀机。<span lang="EN-US">”<o:p></o:p></span></span></p>\r\n\r\n<p style="line-height:17.25pt"><b><span style="font-size:10.5pt;mso-ascii-font-family:\r\n宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;\r\nmso-bidi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">环保杀手一：地板胶</span></b><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:\r\nminor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;\r\nmso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:\r\n&quot;Times New Roman&quot;;color:black;mso-themecolor:text1"><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:\r\ntext1">一般人认为，只有木制地板本身才会释放出甲醛，但在实际安装过程中，会使用大量的地板胶，地板胶的作用是在地板块连接处形成胶膜，有效锁住地板中游离的甲醛。<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:\r\ntext1">地板胶本身是否环保，成为选用地板胶的主要衡量指标。优质地板胶价格昂贵，很多小作坊式的商家往往选用便宜的普通胶，甚至是价格更加低廉的劣质胶，在<span lang="EN-US">“<a href="http://www.zx1234.com/shida/index.html" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;\r\ntext-underline:none"><span lang="EN-US">品牌</span></span></a></span>专用<span lang="EN-US">”</span>和<span lang="EN-US">“</span>全包价<span lang="EN-US">”</span>的幌子下顺理成章地进入消费者家庭，带来环保隐患。<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p style="line-height:17.25pt"><b><span style="font-size:10.5pt;mso-ascii-font-family:\r\n宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;\r\nmso-bidi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">环保杀手二：踢脚板</span></b><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:\r\nminor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;\r\nmso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:\r\n&quot;Times New Roman&quot;;color:black;mso-themecolor:text1"><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:\r\ntext1">此外，踢脚板也是暗藏的环保<span lang="EN-US">“</span>杀手<span lang="EN-US">”</span>之一。因为大多数木制踢脚板在生产过程中同样选用甲醛系胶粘剂进行胶合、贴面或上漆。而且，踢脚板的表面无法做到像地板表面一样致密，在正常使用过程中，基材中的游离甲醛很容易肆无忌惮地释放出来，对室内空气环境造成污染。<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p style="line-height:17.25pt"><b><span style="font-size:10.5pt;mso-ascii-font-family:\r\n宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;\r\nmso-bidi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">环保杀手三：地板垫</span></b><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:\r\nminor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;\r\nmso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:\r\n&quot;Times New Roman&quot;;color:black;mso-themecolor:text1"><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:\r\ntext1">强化木地板在安装过程中，会在地面和地板之间铺设地板垫。在这个狭小的、被人遗忘的空间里，很容易孳生各类细菌，往往成为家庭环保的死角，所以，选用具有防腐功能的地板垫，是保证地板全面环保的重要一环。<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:\r\ntext1">专家说：<span lang="EN-US">“</span>地板胶、踢脚板、地板垫等这些强化复合木地板的配料、辅料，通过与地板搭售的方式蒙混过关牟取利益，已经成为一些地板商的惯用伎俩，而这也正成为百姓家庭的环保隐患。消费者在购买时不要只注重木地板的品质而忽略了这些辅料的质量与环保，对于这些地板<span lang="EN-US">‘</span>配角<span lang="EN-US">’</span>也要选择符合国家环保标准的产品。<span lang="EN-US">”<o:p></o:p></span></span></p>', 0, 0, 0, '2011-07-17 12:08:16', '', 0, 1, 0, 2, '人们在挑选木地板时，往往将注意力集中在地板的耐磨度、甲醛释放量、花色款式等地板质量问题上，而对于踢脚板、地板胶、地板垫等配件的环保问题却往往不太重视。国家建筑材料测试中心的专家说：“木地板的配件和辅料', '0000-00-00 00:00:00', '', 0, 0, 1);
INSERT INTO `meiyiju_blog` (`id`, `cat_id`, `title`, `author`, `trackback_url`, `content`, `mode`, `locked`, `selected`, `post_time`, `ip`, `comment_count`, `view_count`, `trackback_count`, `user_id`, `description`, `last_time`, `password`, `view_group`, `open_type`, `url_type`) VALUES
(7, 7, '个性化整体衣柜或将走红家居市场', '', '', '<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">十年前，当整体衣柜作为外来概念被引入到中国时，很多人并不看好它。但是，随着消费者收入及消费习惯的变化，整体衣柜越来越被重视。消费市场的扩大，也引来了除专门衣柜<span lang="EN-US"><a href="http://www.zx1234.com/shida/index.html" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;\r\ntext-underline:none"><span lang="EN-US">品牌</span></span></a></span>外的其他<span lang="EN-US"><a href="http://www.zx1234.com/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">家居</span></span></a></span>品牌加入，<span lang="EN-US"><a href="http://www.zx1234.com/jj/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">家具</span></span></a></span>、<span lang="EN-US"><a href="http://www.zx1234.com/cj/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">橱柜</span></span></a></span>、<span lang="EN-US"><a href="http://www.zx1234.com/db/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">地板</span></span></a></span>等品牌在巩固原有产品的同时，也将衣柜这一产品纳入生产线。<span lang="EN-US"><o:p></o:p></span></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"=""><br></span></p>\r\n\r\n<p style="line-height:17.25pt"><b><span style="font-size:10.5pt;mso-ascii-font-family:\r\n宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;\r\nmso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:text1"="">市场大吸引品牌跨界加入</span></b><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:\r\nminor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;\r\nmso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:\r\n" times="" new="" roman";color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;\r\nmso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:\r\n宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:" times="" new="" roman";="" color:black;mso-themecolor:text1"="">4</span><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">月份，<span lang="EN-US">“</span>定制衣柜<span lang="EN-US">”</span>品牌索菲亚衣柜的生产商宁基股份在中小板正式挂牌上市交易，成为<span lang="EN-US">A</span>股首家定制家具公司，引得不少家居品牌企业纷纷关注整体衣柜这一行业。今日，<span lang="EN-US"><a href="http://www.zx1234.com/db/Nature/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">大自然</span></span></a></span>地板于港股上市，也计划募资进军橱柜、衣柜行业。<span lang="EN-US"><o:p></o:p></span></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"=""><br></span></p>\r\n\r\n<p style="line-height:17.25pt"><b><span style="font-size:10.5pt;mso-ascii-font-family:\r\n宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;\r\nmso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:text1"="">个性化促<span lang="EN-US">“</span>整体衣柜<span lang="EN-US">”</span>发展</span></b><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;\r\nmso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:\r\n宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:" times="" new="" roman";="" color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">业内人士表示，整体衣柜流行的主要原因在于房地产新户型层出不穷和<span lang="EN-US"><a href="http://www.zx1234.com/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">装修</span></span></a></span>风格日趋多样化的潮流。另外，中小户型的业主多是<span lang="EN-US">80</span>后、<span lang="EN-US">90</span>后的年轻人，这个年龄层的消费者定制衣柜不仅仅看重衣柜的实用性，更注重独特个性和品位。全国工商联衣柜专委会的数据也显示，在未来<span lang="EN-US">4</span>、<span lang="EN-US">5</span>年中，我国整体衣柜市场还将有<span lang="EN-US">2000</span>万套以上市场容量，平均每年<span lang="EN-US">500</span>多万套，粗略估算产值大约有<span lang="EN-US">4000</span>亿元。如此庞大的市场容量，也难怪<span lang="EN-US">“</span>整体衣柜<span lang="EN-US">”</span>被家居业界人士称为行业内<span lang="EN-US">“</span>最后一块蛋糕<span lang="EN-US">”</span>。<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">在众多家居企业挺进整体衣柜的进程中，由于橱柜、衣柜在生产工艺上有很多共同点，运营模式方面也以定制为主，因此企业很容易转产。而且，整体衣柜市场知名的品牌还不多，但橱柜、家居企业已经有许多的大型知名品牌，这些有效而健全的销售渠道可以迅速打开全国市场。<span lang="EN-US"><o:p></o:p></span></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"=""><br></span></p>\r\n\r\n<p style="line-height:17.25pt"><b><span style="font-size:10.5pt;mso-ascii-font-family:\r\n宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;\r\nmso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:text1"="">聚焦整体衣柜市场</span></b><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:\r\nminor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;\r\nmso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:\r\n" times="" new="" roman";color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">据某整体衣柜品牌的刘姓销售经理透露，刚进入北京市场的时候，家居卖场不知该把<span lang="EN-US">“</span>整体衣柜<span lang="EN-US">”</span>归入家具类还是建材类，只好分散在卖场中<span lang="EN-US"><a href="http://www.zx1234.com/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">装饰</span></span></a></span>材料区或<span lang="EN-US"><a href="http://www.zx1234.com/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">家装</span></span></a></span>公司区域之间的零散区域。现在北京大型的家居卖场里，整体衣柜逐渐有了自己独立的区域。<span lang="EN-US"><o:p></o:p></span></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">小编看到，在红星美凯龙的<span lang="EN-US">“</span>移门衣柜区<span lang="EN-US">”</span>或居然之家的<span lang="EN-US">“</span>衣帽间<span lang="EN-US">”</span>区域，以整体衣柜为主打的品牌占到卖场一个楼层的<span lang="EN-US">1/4</span>左右，远超过<span lang="EN-US"><a href="http://www.zx1234.com/bizhi/" target="_blank"><span lang="EN-US" style="color:black;mso-themecolor:text1;text-decoration:none;text-underline:\r\nnone"><span lang="EN-US">壁纸</span></span></a></span>、吊顶等非主材的装饰材料。不少整体衣柜品牌也获得了一定的知名度。去年索菲亚衣柜签约舒淇，配合《非诚勿扰<span lang="EN-US">2</span>》全国热映成功营销，成为家居品牌推广的成功案例之一。最早提出<span lang="EN-US">“</span>整体衣柜<span lang="EN-US">”</span>概念的好莱客衣柜，瞄准高端整体衣柜市场空白，推出的<span lang="EN-US">“</span>欧陆精品<span lang="EN-US">”</span>也创下单套销售<span lang="EN-US">26</span>万元的记录。<span lang="EN-US"><o:p></o:p></span></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"=""><br></span></p>\r\n\r\n<p style="line-height:17.25pt"><b><span style="font-size:10.5pt;mso-ascii-font-family:\r\n宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;\r\nmso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:text1"=""></span>业内说法</b><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:\r\nminor-fareast;mso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;\r\nmso-hansi-font-family:宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:\r\n" times="" new="" roman";color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-font-family:\r\n宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:宋体;mso-hansi-theme-font:\r\nminor-fareast;mso-bidi-font-family:" times="" new="" roman";color:black;mso-themecolor:="" text1"="">定制衣柜产品兼具标准化生产和个性化设计的优点，其细分市场蕴含着高增长的潜力。未来城市化进程快加之住房刚性需求替代投资性需求，定制衣柜相比传统衣柜有标准化、规模化生产的优点，相比成品衣柜有空间利用率高、设计个性化、功能多样化的优点，我认为衣柜行业整体增速不低于<span lang="EN-US">10%</span>。<span lang="EN-US"><o:p></o:p></span></span></p>', 0, 0, 0, '2011-07-17 12:20:13', '', 0, 4, 0, 2, '十年前，当整体衣柜作为外来概念被引入到中国时，很多人并不看好它。但是，随着消费者收入及消费习惯的变化，整体衣柜越来越被重视。消费市场的扩大，也引来了除专门衣柜品牌外的其他家居品牌加入，家具、橱柜、地板', '0000-00-00 00:00:00', '', 0, 0, 1),
(8, 8, '二手房翻新实用技巧全攻略', '', '', '<p style="text-indent:21.0pt;line-height:17.25pt"><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;\r\nmso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:\r\n宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:" times="" new="" roman";="" color:black;mso-themecolor:text1"=""><o:p>&nbsp;</o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span class="apple-style-span"><span style="font-size:10.5pt;mso-ascii-font-family:" times="" new="" roman";mso-hansi-font-family:="" "times="" roman";mso-bidi-font-family:"times="" roman";color:black;="" mso-themecolor:text1"="">没有钻戒也不度蜜月，不拍婚纱照也不办酒席，这就是</span></span><span class="apple-style-span"><span lang="EN-US" style="font-size:10.5pt;font-family:\r\n" times="" new="" roman","serif";color:black;mso-themecolor:text1"="">“</span></span><span class="apple-style-span"><span style="font-size:10.5pt;mso-ascii-font-family:\r\n" times="" new="" roman";mso-hansi-font-family:"times="" roman";mso-bidi-font-family:="" "times="" roman";color:black;mso-themecolor:text1"="">裸婚</span></span><span class="apple-style-span"><span lang="EN-US" style="font-size:10.5pt;font-family:\r\n" times="" new="" roman","serif";color:black;mso-themecolor:text1"="">”</span></span><span class="apple-style-span"><span style="font-size:10.5pt;mso-ascii-font-family:\r\n" times="" new="" roman";mso-hansi-font-family:"times="" roman";mso-bidi-font-family:="" "times="" roman";color:black;mso-themecolor:text1"="">族的写照。仪式之类都是浮云，过日子精打细算才是真理。裸婚男女通常择性价高的二手房而居。房子虽老，巧妙布置一番作为婚房也不赖。</span></span><span class="apple-style-span"><span lang="EN-US" style="font-size:10.5pt;font-family:\r\n" times="" new="" roman","serif";color:black;mso-themecolor:text1"=""><o:p></o:p></span></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span class="apple-style-span"><span style="font-size:10.5pt;mso-ascii-font-family:\r\n" times="" new="" roman";mso-hansi-font-family:"times="" roman";mso-bidi-font-family:="" "times="" roman";color:black;mso-themecolor:text1"=""><br></span></span></p>\r\n\r\n<p style="line-height:17.25pt"><strong><span style="font-size:10.5pt;\r\nfont-family:宋体;mso-ascii-font-family:" times="" new="" roman";mso-hansi-font-family:="" "times="" roman";color:black;mso-themecolor:text1"="">小户型采光不佳显亮功能的</span></strong><strong><span lang="EN-US" style="font-size:10.5pt;color:black;mso-themecolor:text1"><a href="http://www.zx1234.com/yq/" target="_blank"><span lang="EN-US" style="font-family:宋体;mso-ascii-font-family:" times="" new="" roman";mso-hansi-font-family:="" "times="" roman";color:black;mso-themecolor:text1;text-decoration:none;="" text-underline:none"=""><span lang="EN-US">墙面漆</span></span></a></span></strong><strong><span style="font-size:10.5pt;font-family:宋体;mso-ascii-font-family:" times="" new="" roman";="" mso-hansi-font-family:"times="" roman";color:black;mso-themecolor:text1"="">提升亮度</span></strong><span lang="EN-US" style="font-size:10.5pt;font-family:" times="" new="" roman","serif";="" color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:" times="" new="" roman";mso-hansi-font-family:"times="" roman";="" mso-bidi-font-family:"times="" roman";color:black;mso-themecolor:text1"="">高居不下的房价令许多人无奈之下选择小户型，然而这种户型的采光问题是业主的心头针。因此，新婚业主可以选择使用具有显亮功能的墙面漆从视觉上提升宽敞度和明亮度，形成视觉上的开阔。</span><span lang="EN-US" style="font-size:10.5pt;font-family:" times="" new="" roman","serif";="" color:black;mso-themecolor:text1"=""><o:p></o:p></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:" times="" new="" roman";mso-hansi-font-family:"times="" roman";="" mso-bidi-font-family:"times="" roman";color:black;mso-themecolor:text1"=""><br></span></p>\r\n\r\n<p style="line-height:17.25pt"><strong><span style="font-size:10.5pt;\r\nfont-family:宋体;mso-ascii-font-family:" times="" new="" roman";mso-hansi-font-family:="" "times="" roman";color:black;mso-themecolor:text1"="">老龄旧房翻新</span></strong><strong><span style="font-size:10.5pt;color:black;mso-themecolor:text1"> </span></strong><strong><span style="font-size:10.5pt;font-family:宋体;mso-ascii-font-family:" times="" new="" roman";="" mso-hansi-font-family:"times="" roman";color:black;mso-themecolor:text1"="">增白功能的墙面漆</span></strong><span lang="EN-US" style="font-size:10.5pt;font-family:" times="" new="" roman","serif";="" color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:" times="" new="" roman";mso-hansi-font-family:"times="" roman";="" mso-bidi-font-family:"times="" roman";color:black;mso-themecolor:text1"="">老房子经年累月，墙面泛黄陈旧。新婚业主要</span><span lang="EN-US" style="font-size:10.5pt;font-family:" times="" new="" roman","serif";="" color:black;mso-themecolor:text1"=""><a href="http://www.zx1234.com/" target="_blank"><span lang="EN-US" style="font-family:宋体;mso-ascii-font-family:\r\n" times="" new="" roman";mso-hansi-font-family:"times="" roman";color:black;="" mso-themecolor:text1;text-decoration:none;text-underline:none"=""><span lang="EN-US">装饰</span></span></a></span><span style="font-size:10.5pt;mso-ascii-font-family:\r\n" times="" new="" roman";mso-hansi-font-family:"times="" roman";mso-bidi-font-family:="" "times="" roman";color:black;mso-themecolor:text1"="">漂亮温馨的婚房，可以选择有增白功能的墙面漆，让旧墙面焕然一新，同时也能起到预防墙面老化的作用。</span><span lang="EN-US" style="font-size:10.5pt;font-family:" times="" new="" roman","serif";="" color:black;mso-themecolor:text1"=""><o:p></o:p></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;mso-ascii-font-family:\r\n" times="" new="" roman";mso-hansi-font-family:"times="" roman";mso-bidi-font-family:="" "times="" roman";color:black;mso-themecolor:text1"=""><br></span></p>\r\n\r\n<p style="line-height:17.25pt"><strong><span style="font-size:10.5pt;\r\nfont-family:宋体;mso-ascii-font-family:" times="" new="" roman";mso-hansi-font-family:="" "times="" roman";color:black;mso-themecolor:text1"="">即刷即住的业主</span></strong><strong><span style="font-size:10.5pt;color:black;mso-themecolor:text1"> </span></strong><strong><span style="font-size:10.5pt;font-family:宋体;mso-ascii-font-family:" times="" new="" roman";="" mso-hansi-font-family:"times="" roman";color:black;mso-themecolor:text1"="">防潮净味漆速度翻新</span></strong><span lang="EN-US" style="font-size:10.5pt;font-family:" times="" new="" roman","serif";="" color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:" times="" new="" roman";mso-hansi-font-family:"times="" roman";="" mso-bidi-font-family:"times="" roman";color:black;mso-themecolor:text1"="">也许婚期将近，但新房</span><span lang="EN-US" style="font-size:10.5pt;font-family:" times="" new="" roman","serif";="" color:black;mso-themecolor:text1"=""><a href="http://www.zx1234.com/" target="_blank"><span lang="EN-US" style="font-family:宋体;mso-ascii-font-family:\r\n" times="" new="" roman";mso-hansi-font-family:"times="" roman";color:black;="" mso-themecolor:text1;text-decoration:none;text-underline:none"=""><span lang="EN-US">装修</span></span></a></span><span style="font-size:10.5pt;mso-ascii-font-family:\r\n" times="" new="" roman";mso-hansi-font-family:"times="" roman";mso-bidi-font-family:="" "times="" roman";color:black;mso-themecolor:text1"="">的进度落后，很多新婚业主希望能够加快二手房的翻新速度。防潮净味墙面漆的潮气、水分可以很快散去</span><span style="font-size:10.5pt;font-family:" times="" new="" roman","serif";color:black;="" mso-themecolor:text1"=""> </span><span style="font-size:10.5pt;mso-ascii-font-family:\r\n" times="" new="" roman";mso-hansi-font-family:"times="" roman";mso-bidi-font-family:="" "times="" roman";color:black;mso-themecolor:text1"="">，预防霉菌的滋生，而且净味效果好，没有异味，适合业主即刷即住。</span><span lang="EN-US" style="font-size:10.5pt;font-family:" times="" new="" roman","serif";="" color:black;mso-themecolor:text1"=""><o:p></o:p></span></p><p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;mso-ascii-font-family:\r\n" times="" new="" roman";mso-hansi-font-family:"times="" roman";mso-bidi-font-family:="" "times="" roman";color:black;mso-themecolor:text1"=""><br></span></p>\r\n\r\n<p style="line-height:17.25pt"><strong><span style="font-size:10.5pt;\r\nfont-family:宋体;mso-ascii-font-family:" times="" new="" roman";mso-hansi-font-family:="" "times="" roman";color:black;mso-themecolor:text1"="">奉子成婚翻新重环保</span></strong><strong><span style="font-size:10.5pt;color:black;mso-themecolor:text1"> </span></strong><strong><span style="font-size:10.5pt;font-family:宋体;mso-ascii-font-family:" times="" new="" roman";="" mso-hansi-font-family:"times="" roman";color:black;mso-themecolor:text1"="">净味环保涂料防污染</span></strong><span lang="EN-US" style="font-size:10.5pt;font-family:" times="" new="" roman","serif";="" color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span style="font-size:10.5pt;\r\nmso-ascii-font-family:" times="" new="" roman";mso-hansi-font-family:"times="" roman";="" mso-bidi-font-family:"times="" roman";color:black;mso-themecolor:text1"="">裸婚男女如果奉子成婚的话，旧房翻修需选择净味环保的涂料，减少装修带来的污染，确保宝宝安全成长。而且，业主想要提前布置宝宝房的话，可选用色彩柔和丰富的净味环保涂料，促进幼儿视觉神经发育。</span><span lang="EN-US" style="font-size:10.5pt;font-family:" times="" new="" roman","serif";="" color:black;mso-themecolor:text1"=""><o:p></o:p></span></p>\r\n\r\n<p style="text-indent:21.0pt;line-height:17.25pt"><span lang="EN-US" style="font-size:10.5pt;mso-ascii-font-family:宋体;mso-ascii-theme-font:minor-fareast;\r\nmso-fareast-font-family:宋体;mso-fareast-theme-font:minor-fareast;mso-hansi-font-family:\r\n宋体;mso-hansi-theme-font:minor-fareast;mso-bidi-font-family:" times="" new="" roman";="" color:black;mso-themecolor:text1"=""><o:p>&nbsp;</o:p></span></p>\r\n\r\n\r\n\r\n<p class="MsoNormal"><span lang="EN-US" style="font-family:宋体;mso-ascii-theme-font:\r\nminor-fareast;mso-fareast-theme-font:minor-fareast;mso-hansi-theme-font:minor-fareast;\r\ncolor:black;mso-themecolor:text1"><o:p>&nbsp;</o:p></span></p>', 0, 0, 0, '2011-07-18 01:34:51', '', 0, 2, 0, 2, '没有钻戒也不度蜜月，不拍婚纱照也不办酒席，这就是“裸婚”族的写照。仪式之类都是浮云，过日子精打细算才是真理。裸婚男女通常择性价高的二手房而居。房子虽老，巧妙布置一番作为婚房也不赖。', '0000-00-00 00:00:00', '', 0, 0, 1),
(9, 7, '装修旺季催生分户供暖时代', '', '', '<p class="MsoNormal" style="text-indent:21.0pt"><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-font-family:&quot;Times New Roman&quot;;\r\nmso-hansi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">进入九月中旬，天气渐渐转凉，很多消费者也选择在这时进行房屋</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1"><a href="http://www.zx1234.com/" target="_blank"><span lang="EN-US" style="font-family:宋体;mso-ascii-font-family:\r\n&quot;Times New Roman&quot;;mso-hansi-font-family:&quot;Times New Roman&quot;;color:black;\r\nmso-themecolor:text1;text-decoration:none;text-underline:none"><span lang="EN-US">装修</span></span></a></span></span><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-font-family:&quot;Times New Roman&quot;;\r\nmso-hansi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">，家在沈阳的陈先生早早就开始考虑装修中的供暖问题陈先生所在东北地区一直实行的是集中供暖，但是他却发现这种取暖方式有很多不合理之处，</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1">“</span></span><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-font-family:&quot;Times New Roman&quot;;\r\nmso-hansi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">去年冬天，我们小区有些居民不交供暖费，有段时间</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1"><a href="http://www.zx1234.com/cainuang/" target="_blank"><span lang="EN-US" style="font-family:宋体;mso-ascii-font-family:\r\n&quot;Times New Roman&quot;;mso-hansi-font-family:&quot;Times New Roman&quot;;color:black;\r\nmso-themecolor:text1;text-decoration:none;text-underline:none"><span lang="EN-US">暖气</span></span></a></span></span><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-font-family:&quot;Times New Roman&quot;;\r\nmso-hansi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">不是停了就是温度太低。我们家里有老人、有小孩，没有供暖怎么过日子？</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1">”</span></span><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-font-family:&quot;Times New Roman&quot;;\r\nmso-hansi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">今年，陈先生一家正打算重新装修房屋，陈先生告诉我们，他打算自己安装</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1"><a href="http://www.zx1234.com/cainuang/" target="_blank"><span lang="EN-US" style="font-family:宋体;mso-ascii-font-family:\r\n&quot;Times New Roman&quot;;mso-hansi-font-family:&quot;Times New Roman&quot;;color:black;\r\nmso-themecolor:text1;text-decoration:none;text-underline:none"><span lang="EN-US">采暖</span></span></a></span></span><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-font-family:&quot;Times New Roman&quot;;\r\nmso-hansi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">设备，不再参与小区的集中供暖。</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1"><o:p></o:p></span></span></p>\r\n\r\n<p class="MsoNormal" style="text-indent:21.0pt"><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;color:black;mso-themecolor:text1"><o:p>&nbsp;</o:p></span></span></p>\r\n\r\n<p class="MsoNormal" style="text-indent:21.0pt"><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-font-family:&quot;Times New Roman&quot;;\r\nmso-hansi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">如今，像陈先生这样的消费者已不是少数，随着生活水平的提高，他们更加注重生活质量，而冬季供暖关乎百姓民生，供暖质量的提升也需要多样化的解决方案，分户供暖时代初露端倪，</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1">“</span></span><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-font-family:&quot;Times New Roman&quot;;\r\nmso-hansi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">自己家里的温度可以随意调节，而且每一个卧室，每一个客厅，每一个房间的温度都可以调。</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1">”</span></span><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-font-family:&quot;Times New Roman&quot;;\r\nmso-hansi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">这是大多数消费者所期待的供暖方式。</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1"><o:p></o:p></span></span></p>\r\n\r\n<p class="MsoNormal" style="text-indent:21.0pt"><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;color:black;mso-themecolor:text1"><o:p>&nbsp;</o:p></span></span></p>\r\n\r\n<p class="MsoNormal" style="text-indent:21.0pt"><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-font-family:&quot;Times New Roman&quot;;\r\nmso-hansi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">要实现供暖的自给自足是一项十分庞大的工程，尤其是对于没有经验的普通消费者，安装整个供暖系统并非易事。消费者需要的是一套专业的供暖解决方案，一套从设计到安装完美贴心的优质服务。而在这两方面能打开中国消费者心扉的非德国威能莫属，在欧洲，威能有着不可动摇的地位，市场份额占</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1">27%</span></span><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;\r\nmso-ascii-font-family:&quot;Times New Roman&quot;;mso-hansi-font-family:&quot;Times New Roman&quot;;\r\ncolor:black;mso-themecolor:text1">，而在全球，其市场份额占到</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1">22%</span></span><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;\r\nmso-ascii-font-family:&quot;Times New Roman&quot;;mso-hansi-font-family:&quot;Times New Roman&quot;;\r\ncolor:black;mso-themecolor:text1">，在中国，每年</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1">40%</span></span><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;\r\nmso-ascii-font-family:&quot;Times New Roman&quot;;mso-hansi-font-family:&quot;Times New Roman&quot;;\r\ncolor:black;mso-themecolor:text1">的增长表现了其强大的市场需求。</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1"><o:p></o:p></span></span></p>\r\n\r\n<p class="MsoNormal" style="text-indent:21.0pt"><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;color:black;mso-themecolor:text1"><o:p>&nbsp;</o:p></span></span></p>\r\n\r\n<p class="MsoNormal" style="text-indent:21.0pt"><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-font-family:&quot;Times New Roman&quot;;\r\nmso-hansi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">一层秋雨一层凉，冬季供暖设施日益成为消费者装修考虑的主要项目，分户供暖时代悄然来临，越来越多的消费者都在期望更加人性化，更高性价比，更低能耗量的取暖方式，而实现消费者需求的关键就在于提供专业性的供暖解决方案，而并非简单的</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1">“</span></span><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-font-family:&quot;Times New Roman&quot;;\r\nmso-hansi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">吃大锅饭</span></span><span class="apple-style-span"><span lang="EN-US" style="mso-bidi-font-size:10.5pt;\r\ncolor:black;mso-themecolor:text1">”</span></span><span class="apple-style-span"><span style="mso-bidi-font-size:10.5pt;font-family:宋体;mso-ascii-font-family:&quot;Times New Roman&quot;;\r\nmso-hansi-font-family:&quot;Times New Roman&quot;;color:black;mso-themecolor:text1">。</span></span><span lang="EN-US" style="font-family:宋体;mso-ascii-theme-font:minor-fareast;mso-fareast-theme-font:\r\nminor-fareast;mso-hansi-theme-font:minor-fareast;color:black;mso-themecolor:\r\ntext1"><o:p></o:p></span></p>', 0, 0, 0, '2011-07-17 12:24:27', '', 1, 10, 0, 2, '进入九月中旬，天气渐渐转凉，很多消费者也选择在这时进行房屋装修，家在沈阳的陈先生早早就开始考虑装修中的供暖问题陈先生所在东北地区一直实行的是集中供暖，但是他却发现这种取暖方式有很多不合理之处，“去年冬', '0000-00-00 00:00:00', '', 0, 0, 1);

-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_blog_category`
--

CREATE TABLE IF NOT EXISTS `meiyiju_blog_category` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `cat_order` int(11) NOT NULL,
  `blog_count` int(11) NOT NULL,
  `hidden` tinyint(3) NOT NULL,
  `locked` tinyint(3) NOT NULL,
  `parent_id` int(11) NOT NULL,
  `description` varchar(100) NOT NULL,
  `url_type` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=10 ;

--
-- Dumping data for table `meiyiju_blog_category`
--

INSERT INTO `meiyiju_blog_category` (`id`, `name`, `cat_order`, `blog_count`, `hidden`, `locked`, `parent_id`, `description`, `url_type`) VALUES
(2, '装修瓷砖', 0, 2, 0, 0, 0, '0', 1),
(3, '油漆知识', 0, 2, 0, 0, 0, '', 1),
(4, '地板知识', 0, 1, 0, 0, 0, '', 1),
(5, '家具知识', 0, 1, 0, 0, 0, '', 1),
(6, '厨具知识', 0, 0, 0, 0, 0, '', 1),
(7, '采暖设备', 0, 1, 0, 0, 0, '', 1),
(8, '家电知识', 0, 0, 0, 0, 0, '', 1),
(9, '装修指南', 0, 1, 0, 0, 0, '', 1);

-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_blog_comment`
--

CREATE TABLE IF NOT EXISTS `meiyiju_blog_comment` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `blog_id` int(11) NOT NULL,
  `content` longtext NOT NULL,
  `edit_mark` varchar(50) NOT NULL,
  `hidden` tinyint(3) NOT NULL,
  `post_time` datetime NOT NULL,
  `ip` varchar(15) NOT NULL,
  `user_id` int(11) NOT NULL,
  `status` int(11) NOT NULL,
  `user_name` varchar(25) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=8 ;

--
-- Dumping data for table `meiyiju_blog_comment`
--

INSERT INTO `meiyiju_blog_comment` (`id`, `blog_id`, `content`, `edit_mark`, `hidden`, `post_time`, `ip`, `user_id`, `status`, `user_name`) VALUES
(2, 2, 'seefsddf', '', 0, '2011-07-16 21:15:47', '127.0.0.1', 2, 0, 'meiyiju'),
(3, 2, 'dfsfsd', '', 0, '2011-07-16 21:15:50', '127.0.0.1', 2, 0, 'meiyiju'),
(4, 2, 'sdfsfsfsf', '', 0, '2011-07-16 21:15:55', '127.0.0.1', 2, 0, 'meiyiju'),
(5, 2, '&lt;ol&gt; &lt;li&gt; &lt;div class=&quot;comment_data&quot;&gt;引用 meiyiju 发表于 1970-01-01 08:33:31 的评论&lt;/div&gt;seefsddf&lt;/li&gt;&lt;/ol&gt;dffdsfsd', '', 0, '2011-07-16 21:15:57', '127.0.0.1', 2, 0, 'meiyiju'),
(6, 2, '&lt;ol&gt; &lt;li&gt; &lt;div class=&quot;comment_data&quot;&gt;引用 meiyiju 发表于 1970-01-01 08:33:31 的评论&lt;/div&gt;sdfsfsfsf&lt;/li&gt;&lt;/ol&gt;sfsdfdsfs', '', 0, '2011-07-16 21:16:02', '127.0.0.1', 2, 0, 'meiyiju'),
(7, 9, '学习', '', 0, '2011-07-17 16:29:04', '127.0.0.1', 3, 0, 'liwei');

-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_blog_link`
--

CREATE TABLE IF NOT EXISTS `meiyiju_blog_link` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `link_url` varchar(255) NOT NULL,
  `rss` varchar(255) NOT NULL,
  `lnk_sort` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `meiyiju_blog_link`
--


-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_config`
--

CREATE TABLE IF NOT EXISTS `meiyiju_config` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `last_login_time` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `meiyiju_config`
--


-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_daily`
--

CREATE TABLE IF NOT EXISTS `meiyiju_daily` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `content` longtext NOT NULL,
  `post_time` datetime NOT NULL,
  `comments_count` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `user_name` varchar(50) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `meiyiju_daily`
--


-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_daily_comment`
--

CREATE TABLE IF NOT EXISTS `meiyiju_daily_comment` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `content` longtext NOT NULL,
  `post_time` datetime NOT NULL,
  `daily_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `user_name` varchar(50) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `meiyiju_daily_comment`
--


-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_friendlink`
--

CREATE TABLE IF NOT EXISTS `meiyiju_friendlink` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `link_url` varchar(255) NOT NULL,
  `rss` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=9 ;

--
-- Dumping data for table `meiyiju_friendlink`
--

INSERT INTO `meiyiju_friendlink` (`id`, `name`, `link_url`, `rss`) VALUES
(2, '龙宇网', 'www.longyusoft.com', ''),
(3, '新浪乐居', 'http://www.sina.com.cn', ''),
(4, '搜狐焦点', 'http://bd.focus.cn/', ''),
(5, '搜房', 'http://www.soufun.com', ''),
(6, '中国房地产网', 'www.zghouse.net/', ''),
(7, '搜狐家居', 'http://home.sohu.com/', ''),
(8, '深圳装饰网', 'http://www.szzs.com.cn/', '');

-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_guestbook`
--

CREATE TABLE IF NOT EXISTS `meiyiju_guestbook` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `email` varchar(50) NOT NULL,
  `content` longtext NOT NULL,
  `edit_mark` varchar(50) NOT NULL,
  `post_time` datetime NOT NULL,
  `replay_name` varchar(50) NOT NULL,
  `replay` longtext NOT NULL,
  `replay_time` datetime NOT NULL,
  `hidden` tinyint(3) NOT NULL,
  `ip` varchar(15) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `meiyiju_guestbook`
--


-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_message`
--

CREATE TABLE IF NOT EXISTS `meiyiju_message` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `content` longtext NOT NULL,
  `post_time` datetime NOT NULL,
  `user_id` int(11) NOT NULL,
  `user_name` varchar(50) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=9 ;

--
-- Dumping data for table `meiyiju_message`
--

INSERT INTO `meiyiju_message` (`id`, `content`, `post_time`, `user_id`, `user_name`) VALUES
(2, '昨天你们设计师来给我量房了 我把他给我的名片搞丢了 想问下方案什么时候能做好 我要急着装 十月份要在结婚的 麻烦帮忙联系下', '2011-07-17 16:24:43', 0, 'meiyiju'),
(3, '我家在桥东&nbsp;你们能来装修吗&nbsp;120平方的&nbsp;简单的装下&nbsp;大概多少钱啊', '2011-07-17 16:08:29', 0, 'meiyiju'),
(4, '我在滨湖有套房子，请问你们能够给我看看吗？你们在滨湖这可有工地？', '2011-07-17 16:09:08', 0, 'meiyiju'),
(5, '找你们公司装也是朋友介绍的之前他就说他姐姐家的房装得很好 说是龙然装饰公司装的 那时我就让他帮我留意了 从刚开始的接触就感觉到服务的热情 比了几家 从服务和价格来说总体龙然装饰公司最好的 快要结束了至少没让我发现有毛病的地方 希望再竭再历', '2011-07-17 16:10:13', 0, 'meiyiju'),
(6, '我在家天下&nbsp;房子才拿不久&nbsp;准备装修&nbsp;请问夏天装修好吗&nbsp;有没有什么影响啊&nbsp;98平的要多少银子能打发&nbsp;因为快结婚了&nbsp;也没太多的米了&nbsp;看你们的评价很不错&nbsp;我想你们家应该做得很好&nbsp;希望能够合作', '2011-07-17 16:21:13', 0, 'meiyiju'),
(7, '我是上城国际的业主&nbsp;现在我家快要装修好&nbsp;施工和管理方面都很到位&nbsp;我很满意&nbsp;希望后期你们的工作更加细致点&nbsp;我会介绍朋友们来参观的&nbsp;可以介绍他们去你们公司&nbsp;合作愉快', '2011-07-17 16:21:42', 0, 'meiyiju'),
(8, '你好看到你家公司留言的人很多，所以也来咨询下，我家合同已经签了，我什么时候去买材料合适呢？', '2011-07-17 16:22:08', 0, 'meiyiju');

-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_photo`
--

CREATE TABLE IF NOT EXISTS `meiyiju_photo` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `cat_id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `remark` longtext NOT NULL,
  `post_time` datetime NOT NULL,
  `path` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `meiyiju_photo`
--


-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_resource`
--

CREATE TABLE IF NOT EXISTS `meiyiju_resource` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `cat_id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `author` varchar(50) NOT NULL,
  `path` varchar(255) NOT NULL,
  `upload_time` datetime NOT NULL,
  `image_path` varchar(255) NOT NULL,
  `remark` longtext NOT NULL,
  `view_time` int(11) NOT NULL,
  `number` varchar(20) NOT NULL,
  `spec` varchar(50) NOT NULL,
  `origin` varchar(20) NOT NULL,
  `material` varchar(50) NOT NULL,
  `weight` varchar(20) NOT NULL,
  `price` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `user_name` varchar(20) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=9 ;

--
-- Dumping data for table `meiyiju_resource`
--

INSERT INTO `meiyiju_resource` (`id`, `cat_id`, `name`, `author`, `path`, `upload_time`, `image_path`, `remark`, `view_time`, `number`, `spec`, `origin`, `material`, `weight`, `price`, `user_id`, `user_name`) VALUES
(2, 4, '二居室-现代简约', '', '', '2011-07-17 20:08:54', '22.png', '<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131090423240609.png" style="width: 500px; height: 351px; " /></p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131090406155527.png" style="width: 500px; height: 348px; " /></p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131090403536740.png" style="width: 500px; height: 338px; " /></p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131090404713012.png" style="width: 500px; height: 259px; " /></p>', 3, '21', '123', '31', '3131', '3131', 3131, 2, ''),
(3, 6, '田园风格-四室两厅两卫', '', '', '2011-07-18 00:52:06', '33.png', '<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131092145238668.png" style="width: 375px; height: 360px; " /></p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131092146725449.png" style="width: 375px; height: 150px; " /></p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131092151614731.png" style="width: 375px; height: 208px; " /></p>\r\n', 0, '33', '333', '333', '333', '33', 333, 2, ''),
(4, 5, '中式风格-三室两厅两卫', '', '', '2011-07-18 00:57:40', '42.png', '<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131092183628191.png" style="width: 400px; height: 405px; " /></p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131092185358929.png" style="width: 400px; height: 193px; " /></p>\r\n', 1, '33', '3333', '313', '33', '33', 33, 2, ''),
(5, 2, '古典风格-四室两厅两卫', '', '', '2011-07-18 01:01:37', '52.png', '<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131092207110151.png" style="width: 474px; height: 363px; " /></p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131092209050547.png" style="width: 475px; height: 362px; " /></p>\r\n', 0, '42', '42', '42', '42', '24', 42, 2, ''),
(6, 9, '地中海风情-别墅花园', '', '', '2011-07-18 01:06:59', '61.png', '<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131092239414386.png" style="width: 438px; height: 390px; " /></p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131092241423017.png" style="width: 439px; height: 369px; " /></p>\r\n', 1, '23', '23', '123', '123', '132', 123, 2, ''),
(7, 5, '现代风格-三室一厅一卫', '', '', '2011-07-18 01:11:35', '71.png', '<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131092266244574.png" style="width: 300px; height: 153px; " /></p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131092267854666.png" style="width: 300px; height: 280px; " /></p>\r\n', 3, '4', '234', '234', '234', '234', 234, 2, ''),
(8, 2, '简约风格-两室两厅一卫', '', '', '2011-07-18 01:18:46', '81.png', '<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131092309847612.png" style="width: 495px; height: 215px; " /></p>\r\n<p>\r\n	&nbsp;</p>\r\n<p>\r\n	<img alt="" src="http://127.0.0.1:8888/meiyiju/home/upload/2011-07/131092311726626.png" style="width: 500px; height: 262px; " /></p>\r\n<p>\r\n	&nbsp;</p>', 1, '23', '2342', '31', '234', '3131', 234, 2, '');

-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_resource_category`
--

CREATE TABLE IF NOT EXISTS `meiyiju_resource_category` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(50) NOT NULL,
  `resource_count` int(11) NOT NULL,
  `list_order` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=10 ;

--
-- Dumping data for table `meiyiju_resource_category`
--

INSERT INTO `meiyiju_resource_category` (`id`, `name`, `resource_count`, `list_order`) VALUES
(2, '零居', 2, 1),
(3, '一居', 0, 2),
(4, '二居', 1, 3),
(5, '三居', 2, 4),
(6, '四居', 1, 5),
(7, '复式', 0, 6),
(8, '跃层', 0, 7),
(9, '别墅', 1, 8);

-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_resource_comment`
--

CREATE TABLE IF NOT EXISTS `meiyiju_resource_comment` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `resource_id` int(11) NOT NULL,
  `content` longtext NOT NULL,
  `edit_mark` varchar(50) NOT NULL,
  `hidden` tinyint(3) NOT NULL,
  `post_time` datetime NOT NULL,
  `ip` varchar(15) NOT NULL,
  `user_id` int(11) NOT NULL,
  `status` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `meiyiju_resource_comment`
--


-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_settings`
--

CREATE TABLE IF NOT EXISTS `meiyiju_settings` (
  `blog_id` int(11) NOT NULL,
  `blog_title` varchar(50) NOT NULL,
  `blog_description` longtext NOT NULL,
  `base_url` varchar(50) NOT NULL,
  `logo_image` varchar(50) NOT NULL,
  `blog_web_master` varchar(20) NOT NULL,
  `blog_web_master_email` varchar(30) NOT NULL,
  `blog_language` varchar(8) NOT NULL,
  `blog_rss_language` varchar(4) NOT NULL,
  `default_view_mode` tinyint(3) NOT NULL,
  `article_perpage_normal` smallint(6) NOT NULL,
  `article_perpage_list` smallint(6) NOT NULL,
  `list_entry_perpage` smallint(6) NOT NULL,
  `comment_perpage` smallint(6) NOT NULL,
  `comment_time_order` tinyint(3) NOT NULL,
  `show_trackback_with_comment` tinyint(3) NOT NULL,
  `show_trackback_position` tinyint(3) NOT NULL,
  `recent_article_list` smallint(6) NOT NULL,
  `recent_comment_list` smallint(6) NOT NULL,
  `enable_dynamic_calendar` tinyint(3) NOT NULL,
  `content_auto_split_chars` smallint(6) NOT NULL,
  `enable_register` tinyint(3) NOT NULL,
  `enable_security_code` tinyint(3) NOT NULL,
  `enable_trackback_in` tinyint(3) NOT NULL,
  `enable_trackback_out` tinyint(3) NOT NULL,
  `enable_comment` tinyint(3) NOT NULL,
  `enable_guest_book` tinyint(3) NOT NULL,
  `entry_perpage_guest_book` smallint(6) NOT NULL,
  `blog_skin` varchar(20) NOT NULL,
  `min_post_duration` smallint(6) NOT NULL,
  `enable_visitor_record` tinyint(3) NOT NULL,
  `max_visitor_record` int(11) NOT NULL,
  `enable_upload` tinyint(3) NOT NULL,
  `upload_size` int(11) NOT NULL,
  `upload_path` varchar(50) NOT NULL,
  `upload_types` varchar(50) NOT NULL,
  `recent_resource_list` smallint(6) NOT NULL,
  PRIMARY KEY (`blog_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;

--
-- Dumping data for table `meiyiju_settings`
--


-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_trackback`
--

CREATE TABLE IF NOT EXISTS `meiyiju_trackback` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `blog_id` int(11) NOT NULL,
  `url` varchar(100) NOT NULL,
  `title` varchar(100) NOT NULL,
  `blog` varchar(100) NOT NULL,
  `excerpt` longtext NOT NULL,
  `time` datetime NOT NULL,
  `ip` varchar(15) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `meiyiju_trackback`
--


-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_user`
--

CREATE TABLE IF NOT EXISTS `meiyiju_user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `last_ip` varchar(15) NOT NULL,
  `name` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  `group_id` int(11) NOT NULL,
  `gender` tinyint(3) NOT NULL,
  `email` varchar(50) NOT NULL,
  `reg_time` datetime NOT NULL,
  `hide_email` tinyint(3) NOT NULL,
  `homepage` varchar(255) NOT NULL,
  `blog_count` int(11) NOT NULL,
  `comment_count` int(11) NOT NULL,
  `last_time` datetime NOT NULL,
  `reg_ip` varchar(15) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=9 ;

--
-- Dumping data for table `meiyiju_user`
--

INSERT INTO `meiyiju_user` (`id`, `last_ip`, `name`, `password`, `group_id`, `gender`, `email`, `reg_time`, `hide_email`, `homepage`, `blog_count`, `comment_count`, `last_time`, `reg_ip`) VALUES
(2, '', 'meiyiju', '8a9551e50ba800caaed06666f8def267', 1, 0, 'isold_wang@yahoo.com.cn', '2011-07-16 15:03:52', 0, 'www.longyusoft.com', 0, 0, '2011-07-16 15:03:52', '127.0.0.1'),
(3, '', 'liwei', '97e8ee2f4ad8a1a455f668b6a059d32a', 2, 0, 'liwei', '2011-07-17 16:28:35', 0, 'liwei', 0, 0, '2011-07-17 16:28:35', '127.0.0.1'),
(4, '', '宏达', '698d51a19d8a121ce581499d7b701668', 2, 0, '111', '2011-07-17 16:49:04', 0, '111', 0, 0, '2011-07-17 16:49:04', '127.0.0.1'),
(5, '', '沙发', 'c20ad4d76fe97759aa27a0c99bff6710', 2, 0, '12', '2011-07-17 17:07:16', 0, '12', 0, 0, '2011-07-17 17:07:16', '127.0.0.1'),
(6, '', '微软', '289dff07669d7a23de0ef88d2f7129e7', 1, 0, '234', '2011-07-17 17:07:39', 0, '234', 0, 0, '2011-07-17 17:07:39', '127.0.0.1'),
(7, '', '说', 'eccbc87e4b5ce2fe28308fd9f2a7baf3', 2, 0, '3', '2011-07-17 17:08:00', 0, '3', 0, 0, '2011-07-17 17:08:00', '127.0.0.1'),
(8, '', '华谊', '6c8349cc7260ae62e3b1396831a8398f', 2, 0, '45', '2011-07-17 17:08:25', 0, '45', 0, 0, '2011-07-17 17:08:25', '127.0.0.1');

-- --------------------------------------------------------

--
-- Table structure for table `meiyiju_user_group`
--

CREATE TABLE IF NOT EXISTS `meiyiju_user_group` (
  `id` int(11) NOT NULL,
  `name` varchar(20) NOT NULL,
  `rights` varchar(20) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `meiyiju_user_group`
--

INSERT INTO `meiyiju_user_group` (`id`, `name`, `rights`) VALUES
(1, 'Admin', '99999'),
(1, 'Admin', '99999');
