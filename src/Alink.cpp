#include "aliIot.h"

void AliIot::alink_begin()
{
	String productKey_ = _ProductKey;
	String deviceName_ = _DeviceName;
	topic_post_ = "/sys/" + productKey_ + "/" + deviceName_ + "/thing/event/property/post";
	topic_post_reply_ = "/sys/" + productKey_ + "/" + deviceName_ + "/thing/event/property/post_reply";
	topic_set_ = "/sys/" + productKey_ + "/" + deviceName_ + "/thing/service/property/set";
    topic_set_reply_ = "/sys/" + productKey_ + "/" + deviceName_ + "/thing/service/property/set_reply";
}




void AliIot::serialization_post(uint16_t _id, JsonObject &_AliIotJson)
{
	json_str_post_ ="";
	StaticJsonBuffer<512> jsonBuffer;
	JsonObject& AliIotJson = jsonBuffer.createObject();
	AliIotJson["id"] = String(_id, DEC);
	AliIotJson["params"] = _AliIotJson;
	AliIotJson["version"] = "0.0.1";
	AliIotJson["method"] = topic_post_;
 
	AliIotJson.printTo(json_str_post_);
}



void AliIot::deserialization_post(String _JsonStr, uint16_t &_id, uint16_t &_code)   //上报应答解码
{
	StaticJsonBuffer<512>  jsonBuffer;
	JsonObject& JsonReply = jsonBuffer.parseObject(_JsonStr.c_str());
	
	String _ID = JsonReply["id"];    //接收字符串
	_id = atoi(_ID.c_str());  //字符转数字
	_code = JsonReply["code"];
}

void AliIot::deserialization_post(byte *_JsonStr,uint16_t _length,uint16_t &_id,uint16_t &_code)
{
	byte JsonStrBuff[_length];
	for(uint16_t a=0;a<_length;a++)
	{
		JsonStrBuff[a] = _JsonStr[a];
	}
	
	StaticJsonBuffer<512>  jsonBuffer;
	JsonObject& JsonReply = jsonBuffer.parseObject(JsonStrBuff);
	
	String _ID = JsonReply["id"];    //接收字符串
	_id = atoi(_ID.c_str());  //字符转数字
	_code = JsonReply["code"];
}

void AliIot::serialization_set(uint16_t _id,uint16_t _code)  //应答ID与编码[服务器应答包编包]
{
	json_str_set_reply_ ="";
	StaticJsonBuffer<512> jsonBuffer;
	JsonObject& AliIotJson = jsonBuffer.createObject();
	
	AliIotJson["id"] = String(_id, DEC);
	AliIotJson["code"] = _code;
	StaticJsonBuffer<10> jsonData;
	AliIotJson["data"] = jsonData.createObject();;

	AliIotJson.printTo(json_str_set_reply_);
}

//服务器下推消息解码
void AliIot::deserialization_set(String _JsonStr,uint16_t &_id,String &_AliIotJson) //服务器下推消息解码
{
	/*
	StaticJsonBuffer<512>  jsonBuffer;
	JsonObject& JsonReply = jsonBuffer.parseObject(_JsonStr.c_str());
	
	String _ID = JsonReply["id"];    //接收字符串
	_id = atoi(_ID.c_str());  //字符转数字
	const char *AliIotJsonp = JsonReply["params"];
	_AliIotJson = AliIotJsonp;
	*/
	
}

void AliIot::deserialization_set(byte *_JsonStr,uint16_t _length,uint16_t &_id, String &_AliIotJson)
{
	byte JsonStrBuff[_length];
	for(uint16_t a=0; a<_length; a++)
	{
		JsonStrBuff[a] = _JsonStr[a];
	}
	
	StaticJsonBuffer<512>  jsonBuffer;
	JsonObject& JsonReply = jsonBuffer.parseObject(JsonStrBuff);
	
	String _ID = JsonReply["id"];    //接收字符串
	_id = atoi(_ID.c_str());  //字符转数字
	_AliIotJson = JsonReply["params"].as<String>(); //负载数据字符串传出
}

