#ifndef aliIot_H
#define aliIot_H

#include <Arduino.h>

#include "Alink.h"
#include <modules/mqtt/PubSubClient.h>
#include <modules/Sha/sha1.h>

#define MQTT_Topic_Quantity  4  // 订阅TOPIC 数量


class AliIot
{
	public:
		AliIot(PubSubClient& client);
		void begin();
		void begin(String __ServerUrl,uint16_t __port ,String __Id,String __DeviceName,String __ProductKey,String __DeviceSecret);
		void writeUrl(String __ServerUrl);    // 设置登录网址
		void writePort(uint16_t __port);   //服务器端口
		void writeID(String __Id);    //设备ID
		void writeDeviceName(String __DeviceName);  // 设置设备名称
		void writeProductKey(String __ProductKey);
		void writeDeviceSecret(String __DeviceSecret);
		
		void  generateClientId();  //获取登录的设备ID

		bool connect();   //链接服务器
		void subTopic(String topic);    //配置订阅topic
		void publish(const char* topic, const char * payload);  //推送消息
		void setCallback(MQTT_CALLBACK_SIGNATURE);//注册回调函数
		void reconnect();
		void loop();  //心跳维持与重连
	    int state();   //错误消息返回
		//AliIOTlink部分
		void init(String __DeviceName,String __ProductKey,String __DeviceSecret);
		void autoAnswer(char* __topic, byte* __payload, unsigned int __length);   //上行反馈自动应答

	protected:
		//私有函数
		void subscribe(const char* topic);  //监听Topic
		String readClientId();  //获取登录的设备ID
		String readUrl();  
		String readUser();
		String readPasswd();
	
		//私有对象
		PubSubClient *_client;    //mqtt接口
		//私有变量
		String TopicName[MQTT_Topic_Quantity];
		String _ServerUrl = "iot-as-mqtt.cn-shanghai.aliyuncs.com";
		String _Id;
		String _ClientIdSuffix = "|securemode=3,signmethod=hmacsha1,timestamp=";
		
		uint16_t _port = 1883;
		uint16_t Times;
		uint8_t TopicNum =0;   //topic计数器
		//
		String _URL;
		String _ClientId;
		String _Username;
		String _PasswdHash;
		//三元素
		String _DeviceName;	
		String _ProductKey;
		String _DeviceSecret;
	private:
};
#endif