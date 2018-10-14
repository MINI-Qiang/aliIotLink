#ifndef ALink_H
#define ALink_H
#include "Arduino.h"
#include <modules/ArduinoJson.h>

//   /sys/{productKey}/{deviceName}/thing/event/property/post        消息上报与应答（属性上报与应答）
//   /sys/{productKey}/{deviceName}/thing/event/property/post_reply  服务器应答上报

//   /sys/{productKey}/{deviceName}/thing/service/property/set       服务器下发消息（属性下推与应答）
//   /sys/{productKey}/{deviceName}/thing/service/property/set_reply   设备应答

/*暂不实现*/
/*
TOPIC：/sys/{productKey}/{deviceName}/thing/event/{tsl.event.identifier}/post  事件上报与应答
REPLY TOPIC：/sys/{productKey}/{deviceName}/thing/event/{tsl.event.identifier}/post_reply

TOPIC：/sys/{productKey}/{deviceName}/thing/service/{tsl.service.identifier}  服务下推
REPLY TOPIC：/sys/{productKey}/{deviceName}/thing/service/{tsl.service.identifier}_reply
*/	

void begin(String _productKey,String _deviceName);  //传入2元素
//void version(String _version);

void serialization_post(uint16_t _id,JsonObject &_AlinkJson);    //编码Alink 上行消息
void deserialization_post(String _JsonStr,uint16_t &_id,uint16_t &_code);   //上报应答解码
void deserialization_post(byte *_JsonStr,uint16_t _length,uint16_t &_id,uint16_t &_code);   //上报应答解码


//编码Alink 应答消息
void serialization_set(uint16_t _id,uint16_t _code);  //应答ID与编码
void deserialization_set(String _JsonStr,uint16_t &_id, String &_AlinkJson); //服务器下推消息解码
void deserialization_set(byte *_JsonStr,uint16_t _length,uint16_t &_id, String &_AlinkJson);

String json_str_post_;
String json_str_set_reply_;
String topic_post_;
String topic_post_reply_;
String topic_set_;
String topic_set_reply_;

String productKey_;
String deviceName_;

#endif