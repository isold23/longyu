<?php
/*+++
|
| Author :陈毓端
| 使用方法
|   $shtml = new Shtml($Url,$FileBag,$FolderName,$fileid)
|   $Url：       页面 URL 地址
|   $FileBag：   文件夹标记   1 为：指定文件夹
|         2 为：默认文件夹(时间(年月日))
|        $FolderRoot html文件存放路径
|   $FolderName 指定文件夹的名称 $FileBag为2时 可以写为空("");
|   $fileid      静态页面名称(后缀 默认为 .html)
|
|$fileid=2;
|$shtml = new Shtml("http://www.qq.com",1,"","cc",$fileid);
|
/*++*/
class Shtml
{
    var $message1="Error    1: You write class Shtml is Wrong !   The second parameter is 1 or 2 in   this class!.";
    var $message2="Error    2: The file write    Error.";
    function __construct ($Url,$FileBag,$FolderRoot,$FolderName,$fileid)
    {
        $this->Url   = $Url;
        $this->FileBag   = $FileBag;
        $this->FileRoot = $FolderRoot;
        $this->FileName = $FolderName;
        $this->fileid    = $fileid;
        Shtml::useFolder ();
    }
    /*************获取数据*******************/
    public function loadcontent ($Folder)
    {
        ob_start();
        require_once $this->Url;
        Shtml::writehtml ($Folder,ob_get_contents());
        ob_clean();
    }
    /********** 指定文件夹*****************/
    public function useFolder ()
    {
        if($this->FileBag==1)
        {
            $Folder=$this->FileName;
        }
        else if($this->FileBag==2)
        {
            $Folder=date('Ymd',time());
        }
        else
        {
            exit($this->message1);
        }
        if(!is_dir($this->FileRoot.$Folder)){ mkdir($this->FileRoot.$Folder,0700);}
        Shtml::loadcontent ($Folder);
    }
    /********** 生成静态页面*****************/
    public function writehtml ($Folder,$cache_value)
    {
        $file   = fopen($this->FileRoot.$Folder.'/'.$this->fileid.'.html','w+');
        fwrite($file,$cache_value);
        fclose($file);
    }
}
?>
  