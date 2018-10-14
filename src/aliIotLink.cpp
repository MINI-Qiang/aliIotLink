#include "aliIot.h"


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
	subTopic(topic_set_);   //下发消息
	subTopic(topic_post_reply_);  //上报应答
	_client->setServer(_URL.c_str(),_port);  //写入服务器名称与端口号
	//_client->setServer("106.15.100.2",_port);
	
    alink_begin(); //productKey,deviceName
	
}



//上行消息自动应答
void AliIot::autoAnswer(char* __topic, byte* __payload, unsigned int __length)
{
 if (strcmp(__topic,topic_post_reply_.c_str()) == 0)
	{
		uint16_t ID, CODE;
		deserialization_post(__payload, __length, ID, CODE);  //POST解码
		serialization_set(ID, 200); //编码确认消息
		publish(topic_set_reply_.c_str(),json_str_set_reply_.c_str()); //消息topic,json内容编码
		//Serial.println("POST");
	}
}