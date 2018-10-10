#include "aliIot.h"
Alink alink;

//初始化网络
void AliIot::init(String __DeviceName,String __ProductKey,String __DeviceSecret)
{
	_Id = __DeviceName;
	_DeviceName = __DeviceName;
	_ProductKey = __ProductKey;
	_DeviceSecret = __DeviceSecret;
	generateClientId();
	readUrl();
	readUser();
	readPasswd();
	_client->setServer(_URL.c_str(),_port);  //写入服务器名称与端口号
    alink.begin(_ProductKey,_DeviceName); //productKey,deviceName
	subTopic(alink.topic_set_);   //下发消息
	subTopic(alink.topic_post_reply_);  //上报应答
}

