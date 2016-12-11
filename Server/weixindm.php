<?php

define("TOKEN", "hellomwq");

$wechatObj = new wechatTest();
if(isset($_GET["echostr"]))
{
$wechatObj->valid();
}
else
{
$wechatObj->responseMsg();
}

class wechatTest
{
    public function valid()
    {
        $echoStr = $_GET["echostr"];
        if($this->checkSignature()){
            echo $echoStr;
            exit;
        }
    }

    private function checkSignature()
    {
        $signature = $_GET["signature"];
        $timestamp = $_GET["timestamp"];
        $nonce = $_GET["nonce"];

        $token = TOKEN;
        $tmpArr = array($token, $timestamp, $nonce);
        sort($tmpArr,SORT_STRING);
        $tmpStr = implode( $tmpArr );
        $tmpStr = sha1( $tmpStr );

        if( $tmpStr == $signature ){
            return true;
        }else{
            return false;
        }
    }

    public function responseMsg()
    {
        //$postReq=file_get_contents("php://input");
		$postReq=$GLOBALS["HTTP_RAW_POST_DATA"];

        if (!empty($postReq)){
            $postObj = simplexml_load_string($postReq,'SimpleXMLElement',LIBXML_NOCDATA);
            
			$toUsername=$postObj->ToUserName;
			$fromUsername=$postObj->FromUserName;
			$createTime=$postObj->CreateTime;
			$msgType=$postObj->MsgType;
			$content=$postObj->Content;
			$msgId=$postObj->MsgId;
			//status 1-saved by not used; 2-saved and used
			$status=1;

			$pdo=new PDO("mysql:host=localhost;dbname=ost","mwqdanmu","danmu666");
			$res=$pdo->exec("insert into danmu values('".$toUsername."','".$fromUsername."',".$createTime.",'".$msgType."','".$content."',".$msgId.",$status,now(),now())");
			//$test=$pdo->exec("insert into danmu values('".$toUsername."','hello',12345678905,'text','hello world',1646544332424234555,5,now(),now())");	    
			
			$MSG_TYPE = trim($postObj->MsgType);
            switch ($MSG_TYPE)
            {
                case "text":
                    $resultStr = $this->receiveText($postObj);
                    break;
					
                default:
                    $resultStr = "unknow msg type: ".$MSG_TYPE;
                    break;
            }
            echo $resultStr;
        }
	else
	{
            echo "wa";
            exit;
        }
    }

    private function receiveText($object)
    {
        $contentStr = "The informaton you send is text,and content is ".$object->Content." ".$object->ToUserName." ".$object->FromUserName." ".$object->CreateTime." ".$object->MsgType." ".$object->Content." ".$object->MsgId;
		$textRes = "<xml>
		<ToUserName><![CDATA[%s]]></ToUserName>
		<FromUserName><![CDATA[%s]]></FromUserName>
		<CreateTime>%s</CreateTime>
		<MsgType><![CDATA[text]]></MsgType>
		<Content><![CDATA[%s]]></Content>
		</xml>";
		$resultStr = sprintf($textRes, $object->FromUserName, $object->ToUserName, time(), $contentStr);
        return $resultStr;
    }
}
?>
