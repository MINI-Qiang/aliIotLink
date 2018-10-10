#ifndef aliIotLink_H
#define aliIotLink_H

#include <aliIot.h>

class aliIotLink : public AliIot
{
    public:
        aliIotLink(PubSubClient &Client);

        void begin(String __ServerUrl,uint16_t __port ,String __DeviceName,String __ProductKey,String __DeviceSecret); //初始化

        void setCallback(MQTT_CALLBACK_SIGNATURE);//注册回调函数

        bool connect();   //链接服务器

        void loop();  //心跳维持与重连

};

#endif