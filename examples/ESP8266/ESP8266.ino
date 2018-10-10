#include <aliIot.h>
#include <ESP8266WiFi.h>

const char* ssid = "OCROBOT";
const char* password = "jiekgongfang";


WiFiClient espClient;   //实例化 wifi网络
PubSubClient client(espClient); //将网络传入MQTT
AliIot aliLink(client);  //将mqtt传入服务

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

  if (aliLink.state() != 0)
  {
    Serial.println(aliLink.state());
  }
  aliLink.loop();
  //delay(1000);
}

