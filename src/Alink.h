#ifndef ALink_H
#define ALink_H

#include <modules/ArduinoJson.h>

//   /sys/{productKey}/{deviceName}/thing/event/property/post 消息上报与应答（属性上报与应答）
//   /sys/{productKey}/{deviceName}/thing/event/property/post_reply  服务器应答上报

//   /sys/{productKey}/{deviceName}/thing/service/property/set   服务器下发消息（属性下推与应答）
//   /sys/{productKey}/{deviceName}/thing/service/property/set_reply   设备应答

/*暂不实现*/
/*

TOPIC：/sys/{productKey}/{deviceName}/thing/event/{tsl.event.identifier}/post  事件上报与应答
REPLY TOPIC：/sys/{productKey}/{deviceName}/thing/event/{tsl.event.identifier}/post_reply


TOPIC：/sys/{productKey}/{deviceName}/thing/service/{tsl.service.identifier}  服务下推
REPLY TOPIC：/sys/{productKey}/{deviceName}/thing/service/{tsl.service.identifier}_reply
*/	
	
	

class Alink
{
	public:
		
		void begin(String _productKey,String _deviceName);  //传入2元素
		//void version(String _version);
		//编码Alink 上行消息
		void post(String _id,JsonObject &_AlinkJson);
		
		//编码Alink 应答消息
		void set_reply(JsonObject &_AlinkJson);
	
		String json_str_post;
		String topoc_post;
		String topoc_post_reply;
		String topoc_set;
		String topoc_set_reply;
	private:
		String productKey;
		String deviceName;
};


//解码路由

//解码应答消息

//解码下行消息


#endif