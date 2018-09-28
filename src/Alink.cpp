#include "Alink.h"

void Alink::begin(String _productKey,String _deviceName)
{
	productKey = _productKey;
	deviceName = _deviceName;
	topoc_post = "/sys/" + productKey + "/" + deviceName + "/thing/event/property/post";
	topoc_post_reply = "/sys/" + productKey + "/" + deviceName + "/thing/event/property/post_reply";
	topoc_set = "/sys/" + productKey + "/" + deviceName + "/thing/service/property/set";
    topoc_set_reply = "/sys/" + productKey + "/" + deviceName + "/thing/service/property/set_reply";
}




void Alink::post(uint16_t _id, JsonObject &_AlinkJson)
{
	json_str_post ="";
	StaticJsonBuffer<512> jsonBuffer;
	JsonObject& AlinkJson = jsonBuffer.createObject();
	AlinkJson["id"] = String(_id, DEC);
	AlinkJson["params"] = _AlinkJson;
	AlinkJson["version"] = "0.0.1";
	AlinkJson["method"] = topoc_post;
 
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

void Alink::set_reply(uint16_t _id,uint16_t _code)  //应答ID与编码[服务器应答包编包]
{
	topoc_set_reply ="";
	StaticJsonBuffer<512> jsonBuffer;
	JsonObject& AlinkJson = jsonBuffer.createObject();
	
	AlinkJson["id"] = String(_id, DEC);
	AlinkJson["code"] = _code;
	StaticJsonBuffer<10> jsonData;
	AlinkJson["data"] = jsonData.createObject();;

	AlinkJson.printTo(topoc_set_reply);
}
void Alink::set(String JsonStr,uint16_t &_id,JsonObject &_AlinkJson) //服务器下推消息解码
{
	
}




