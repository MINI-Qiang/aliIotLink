#ifndef aliIotLink_H
#define aliIotLink_H

#include <Arduino.h>
//#include "Adafruit_MQTT.h"
//#include "mod/mqtt/Adafruit_MQTT_Client.h"
#include <modules/Sha/sha1.h>

//随机数发生器（时间种子），产生适合ID的 时间戳



class AliIotLink
{
	public:
		AliIotLink();
		void begin();
		void begin(String __ServerUrl,uint16_t __port ,String __Id,String __DeviceName,String __ProductKey,String __DeviceSecret);
		void writeUrl(String __ServerUrl);    // 设置登录网址
		void writePort(uint16_t __port);   //服务器端口
		void writeID(String __Id);    //设备ID
		void writeDeviceName(String __DeviceName);  // 设置设备名称
		void writeProductKey(String __ProductKey);
		void writeDeviceSecret(String __DeviceSecret);
		
		
		
		//登录用四元数
		
		void  generateClientId();  //获取登录的设备ID
		String readClientId();  //获取登录的设备ID
		String readUrl();  
		String readUser();
		String readPasswd();
		
		
		
		
	private:
		//私有函数
	
		//私有变量
		String _ServerUrl = "iot-as-mqtt.cn-shanghai.aliyuncs.com";
		String _Id;
		String _ClientIdSuffix = "|securemode=3,signmethod=hmacsha1,timestamp=";
		String _ClientId;
		uint16_t _port = 1883;
		uint16_t Times;
		  //三元素
		String _DeviceName;	
		String _ProductKey;
		String _DeviceSecret;
};




#endif