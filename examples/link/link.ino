#include <aliIotLink.h>
#include <SPI.h>
#include <Ethernet2.h>
EthernetClient ethClient;
PubSubClient client(ethClient);
AliIotLink aliLink(client);
byte mac[] = {0x00, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

void Callbacks(char* topic, byte* payload, unsigned int length)
{
  Serial.print(topic);
  Serial.print(":");
  for (int i=0;i<length;i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() 
{
  delay(5000);
  Serial.begin(115200);
  Ethernet.begin(mac);
  aliLink.writeID("ArduinoIOT");   //设备名称
  aliLink.writeDeviceName("ArduinoIOT");  //元素1  DeviceName
  aliLink.writeProductKey("a1SRXXXXX5L");  //元素2  ProductKey
  aliLink.writeDeviceSecret("TQw1KMA7NXXXXXrw7CWVaQybt2gvqQEd"); //元素3  DeviceSecret
  aliLink.subTopic("/a1SRXXXXX5L/ArduinoIOT/get");   //订阅
  aliLink.subTopic("/a1SRXXXXX5L/ArduinoIOT/update/error");   //订阅
  aliLink.setCallback(Callbacks);
  aliLink.begin();  //完成初始化配置
}
void loop() 
{
  
  if(aliLink.state() != 0)
  {
    Serial.println(aliLink.state());
   }
  aliLink.loop();
  //delay(1000);
}

