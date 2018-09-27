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




void Alink::post(String _id, JsonObject &_AlinkJson)
{
	StaticJsonBuffer<512> jsonBuffer;
	JsonObject& AlinkJson = jsonBuffer.createObject();
	
	AlinkJson["id"] = _id;
	AlinkJson["params"] = _AlinkJson;
	AlinkJson["version"] = "0.0.1";
	AlinkJson["method"] = topoc_post;
 
	AlinkJson.printTo(json_str_post);
}