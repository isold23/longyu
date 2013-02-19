<?php

function process_text($str)
{
	$str=htmlspecialchars($str);
	$str=str_replace(' ','&nbsp;',$str);
	$str=str_replace(array("\r\n", "\n"), array('<br />', '<br />'),$str);
	return $str;
}

function unprocess_text($str)
{
	$str=htmlspecialchars_decode($str);
	$str=str_replace('&nbsp;',' ',$str);
	$str=str_replace('<br />', "\r\n",$str);
	return $str;
}

function pbtime($dateline){
	return date('Y-m-d H:i:s',$dateline);
}

function isset_member($member)
{
	$sql='SELECT * FROM '.table('user')." WHERE name ='".$member."'";
	if ($GLOBALS['db']->getrow($sql)) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

function isset_group($group)
{
	$sql='SELECT * FROM '.table('user_group')." WHERE name='".$group."'";
	if ($GLOBALS['db']->getrow($sql)) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}




function pbsubstr($Str, $Length) {
global $s; 
$i = 0; 
$l = 0; 
$ll = strlen($Str); 
$s = $Str; 
$f = true;

while ($i <= $ll) { 
    if (ord($Str{$i}) < 0x80) { 
        $l++; $i++; 
    } else if (ord($Str{$i}) < 0xe0) { 
        $l++; $i += 2; 
    } else if (ord($Str{$i}) < 0xf0) { 
        $l += 2; $i += 3; 
    } else if (ord($Str{$i}) < 0xf8) {
        $l += 1; $i += 4; 
    } else if (ord($Str{$i}) < 0xfc) { 
        $l += 1; $i += 5; 
    } else if (ord($Str{$i}) < 0xfe) { 
        $l += 1; $i += 6; 
    }

    if (($l >= $Length - 1) && $f) { 
        $s = substr($Str, 0, $i); 
        $f = false; 
    }
} 
return $s;
}

/********************************** 
  * 截取字符串(UTF-8)
  *
  * @param string $str 原始字符串
  * @param $position 开始截取位置
  * @param $length 需要截取的偏移量
  * @return string 截取的字符串
  * $type=1 等于1时末尾加'...'不然不加
 *********************************/ 
 function utfSubstr($str, $position, $length,$type=1){
  $startPos = strlen($str);
  $startByte = 0;
  $endPos = strlen($str);
  $count = 0;
  for($i=0; $i<strlen($str); $i++){
   if($count>=$position && $startPos>$i){
    $startPos = $i;
    $startByte = $count;
   }
   if(($count-$startByte) >= $length) {
    $endPos = $i;
    break;
   }    
   $value = ord($str[$i]);
   if($value > 127){
    $count++;
    if($value>=192 && $value<=223) $i++;
    elseif($value>=224 && $value<=239) $i = $i + 2;
    elseif($value>=240 && $value<=247) $i = $i + 3;
    else return self::raiseError("\"$str\" Not a UTF-8 compatible string", 0, __CLASS__, __METHOD__, __FILE__, __LINE__);
   }
   $count++;

  }
  if($type==1 && ($endPos-6)>$length){
   return substr($str, $startPos, $endPos-$startPos)."..."; 
       }else{
   return substr($str, $startPos, $endPos-$startPos);     
    }
  
 }

?>