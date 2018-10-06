#include "Alink.h"

void Alink::begin(String _productKey,String _deviceName)
{
	productKey = _productKey;
	deviceName = _deviceName;
	topic_post = "/sys/" + productKey + "/" + deviceName + "/thing/event/property/post";
	topic_post_reply = "/sys/" + productKey + "/" + deviceName + "/thing/event/property/post_reply";
	topic_set = "/sys/" + productKey + "/" + deviceName + "/thing/service/property/set";
    topic_set_reply = "/sys/" + productKey + "/" + deviceName + "/thing/service/property/set_reply";
}




void Alink::post(uint16_t _id, JsonObject &_AlinkJson)
{
	json_str_post ="";
	StaticJsonBuffer<512> jsonBuffer;
	JsonObject& AlinkJson = jsonBuffer.createObject();
	AlinkJson["id"] = String(_id, DEC);
	AlinkJson["params"] = _AlinkJson;
	AlinkJson["version"] = "0.0.1";
	AlinkJson["method"] = topic_post;
 
	AlinkJson.printTo(json_str_post);
}



void Alink::post_reply(String _JsonStr, uint16_t &_id, uint16_t &_code)   //上报应答解码
{
	StaticJsonBuffer<512>  jsonBuffer;
	JsonObject& JsonReply = jsonBuffer.parseObject(_JsonStr.c_str());
	
	String _ID = JsonReply["id"];    //接收字符串
	_id = atoi(_ID.c_str());  //字符转数字
	_code = JsonReply["code"];
}

void Alink::post_reply(byte *_JsonStr,uint16_t _length,uint16_t &_id,uint16_t &_code)
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

void Alink::set_reply(uint16_t _id,uint16_t _code)  //应答ID与编码[服务器应答包编包]
{
	json_str_set_reply ="";
	StaticJsonBuffer<512> jsonBuffer;
	JsonObject& AlinkJson = jsonBuffer.createObject();
	
	AlinkJson["id"] = String(_id, DEC);
	AlinkJson["code"] = _code;
	StaticJsonBuffer<10> jsonData;
	AlinkJson["data"] = jsonData.createObject();;

	AlinkJson.printTo(json_str_set_reply);
}

//服务器下推消息解码
void Alink::set(String _JsonStr,uint16_t &_id,String &_AlinkJson) //服务器下推消息解码
{
	/*
	StaticJsonBuffer<512>  jsonBuffer;
	JsonObject& JsonReply = jsonBuffer.parseObject(_JsonStr.c_str());
	
	String _ID = JsonReply["id"];    //接收字符串
	_id = atoi(_ID.c_str());  //字符转数字
	const char *AlinkJsonp = JsonReply["params"];
	_AlinkJson = AlinkJsonp;
	*/
	
}

void Alink::set(byte *_JsonStr,uint16_t _length,uint16_t &_id,String &_AlinkJson)
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

	
	_AlinkJson = JsonReply["params"].as<String>();
	//Serial.println(AlinkJson);
	//_AlinkJson = AlinkJsonpas
}

