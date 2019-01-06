#include <aliIotLink.h>
#include <SPI.h>
#include <Ethernet2.h>
//W5500 链接阿里云

byte mac[] = {0x00, 0xED, 0xBA, 0xFE, 0xFE, 0xED };  //MAC地址


static const char ProductKey[] PROGMEM = "a1BllGqYfBO";
static const char DeviceName[] PROGMEM = "QNfNlOW1l9uTY2V0Dw2E";  
static const char DeviceSecret[] PROGMEM = "jIM4j0tphyiXhx4yVzuv2BcF1bz916Oo";

static const char postTopic[]  PROGMEM = "";   //上报消息topic
static const char setTopic[]  PROGMEM = "";    //服务器消息topic

EthernetClient ethClient;  //实例化以太网
PubSubClient client(ethClient); //将网络传入MQTT
AliIotLink aliLink(client);   //将mqtt传入服务


//回调函数
void Callbacks(char* topic, byte* payload, unsigned int length)
{
	//回调功能演示，将监听到的消息直接打印到串口
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
  Ethernet.begin(mac);  //初始化以太网

  
  aliLink.subTopic(FPSTR(setTopic));   //订阅服务器下行消息
  aliLink.setCallback(Callbacks);   //注册下发消息回调函数
  aliLink.begin(FPSTR(DeviceName),FPSTR(ProductKey),FPSTR(DeviceSecret));  //完成初始化配置 三元素(DeviceName,ProductKey,DeviceSecret)
}
void loop() 
{
  
  if (aliLink.state() != 0) // 显示连接错误码，实际项目不需要
  {
    Serial.println(aliLink.state());
  }
  aliLink.loop();  //循环维持心跳与消息触发，应尽可能多的执行
  
}

