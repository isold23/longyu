/*
Copyright (c) 2003-2010, CKSource - Frederico Knabben. All rights reserved.
For licensing, see LICENSE.html or http://ckeditor.com/license
*/

CKEDITOR.editorConfig = function( config )
{
	config.extraPlugins = 'myCode';
	config.scayt_autoStartup = false;
	config.skin = 'v2';
	config.width = '900px'; // 宽度
	config.height = '500px'; // 高度
	config.filebrowserImageUploadUrl = 'admin.php?act=upload&type=img';
	config.filebrowserFlashUploadUrl = 'admin.php?act=upload&type=flash';
	config.filebrowserUploadUrl = 'admin.php?act=upload&type=file';
};
