#include <aliIotLink.h>
#include <ESP8266WiFi.h>

const char* ssid = "C601";
const char* password = "13855694020";

static const char ProductKey[] PROGMEM = "a1BllGqYfBO";
static const char DeviceName[] PROGMEM = "QNfNlOW1l9uTY2V0Dw2E";  
static const char DeviceSecret[] PROGMEM = "jIM4j0tphyiXhx4yVzuv2BcF1bz916Oo";

static const char postTopic[]  PROGMEM = "";   //上报消息topic
static const char setTopic[]  PROGMEM = "";    //服务器消息topic

WiFiClient espClient;   //实例化 wifi网络
PubSubClient client(espClient); //将网络传入MQTT
AliIotLink aliLink(client);  //将mqtt传入服务

//回调函数
void Callbacks(char* topic, byte* payload, unsigned int length)
{
  Serial.print(topic);
  Serial.print(":");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup()
{

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);   //配置为客户端模式
  WiFi.begin(ssid, password);  //初始化并且链接wifi
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  aliLink.subTopic("/a1agPKQ3fSf/sensor1/get");   //订阅
  //aliLink.subTopic("/a1agPKQ3fSf/sensor1/update/error");   //订阅
  aliLink.setCallback(Callbacks);
  aliLink.begin(FPSTR(DeviceName),FPSTR(ProductKey),FPSTR(DeviceSecret));  //完成初始化配置 三元素(DeviceName,ProductKey,DeviceSecret)
}
void loop()
{

  if (aliLink.state() != 0)
  {
    Serial.println(aliLink.state());
  }
  aliLink.loop();
}
