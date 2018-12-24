#include "aliIotLink.h"
SHA256 sha256;

AliIotLink::AliIotLink(PubSubClient& client)
{
	_client = &client;	
}
void AliIotLink::begin()
{
  //randomSeed(analogRead(A0));   //获取IO随机值【非安全的伪随机】作为种子
  delayMicroseconds(random(0,10000));   //延迟随机时间
  
  generateClientId();
  readUrl();
  readUser();
  readPasswd();
  _client->setServer(_URL.c_str(),_port); //写入服务器名称与端口号
  
}


void AliIotLink::begin(String __DeviceName,String __ProductKey,String __DeviceSecret)
{
	_Id = __DeviceName;
	_DeviceName = __DeviceName;
	_ProductKey = __ProductKey;
	_DeviceSecret = __DeviceSecret;
	//randomSeed(analogRead(A0));
    delayMicroseconds(random(0,10000));
	generateClientId();
	readUrl();
	readUser();
	readPasswd();
	_client->setServer(_URL.c_str(),_port);  //写入服务器名称与端口号
}

void AliIotLink::writeUrl(String __ServerUrl)    // 设置登录网址
{
	_ServerUrl = __ServerUrl;
}
//服务器端口设置
void AliIotLink::writePort(uint16_t __port)
{
	_port = __port;
}
//硬件设备名称
void AliIotLink::writeID(String __Id)
{
	_Id = __Id;
}
// 设置设备硬件标签名称【阿里云提供】
void AliIotLink::writeDeviceName(String __DeviceName)  
{
	_DeviceName = __DeviceName;
}
//【阿里云提供】
void AliIotLink::writeProductKey(String __ProductKey)
{
	_ProductKey = __ProductKey;
}
//【阿里云提供】
void AliIotLink::writeDeviceSecret(String __DeviceSecret)
{
	_DeviceSecret = __DeviceSecret;
}

void AliIotLink::generateClientId()
{
	//ID+参数+随机数+结尾符号
	randomSeed(micros());
	Times  =random(0, 65535);
	_ClientId = _Id + _ClientIdSuffix + Times +"|";
}

//获取合成好的登录用的ClientId
String AliIotLink::readClientId()
{
	return _ClientId;
}


//合成访问网址
 String AliIotLink::readUrl()
 {
	 _URL = _ProductKey + "." + _ServerUrl;
	 return _URL;
 }
 
 //合成访问用户名
 String AliIotLink::readUser()
 {
	 _Username = _DeviceName + "&" + _ProductKey ;
	 return _Username;
 }
 
 
 //合成访问密码
 String AliIotLink::readPasswd()
 {
	 String _Passwd =  "clientId" + _Id + "deviceName" + _DeviceName +"productKey"+_ProductKey + "timestamp" + Times;
	 _PasswdHash = "";
	 
	 byte hashData[64];
	 
	 HMAC(_DeviceSecret.c_str(), 32, _Passwd.c_str(), _Passwd.length(), hashData);

	 for (int i = 0; i < 32; i++)  //hash 固定长度
	 {
		_PasswdHash = _PasswdHash + "0123456789ABCDEF"[hashData[i] >> 4];
	 	_PasswdHash = _PasswdHash + "0123456789ABCDEF"[hashData[i] & 0xf];
	 }

	 //return _PasswdHash;  //返回HASH密文
 }
 
 
 
 //===================mqtt部分=====================
 
 bool AliIotLink::connect()
 {


	 return _client->connect(_ClientId.c_str(),_Username.c_str(),_PasswdHash.c_str());   //像服务器传递 ClientId，用户名，密码

	 
 }
 
 //重连
 void AliIotLink::reconnect()
 {

   while(!_client->connected()) //检查网络网络是否不正常，断开的网络会锁定重试
   {

	  if (connect())   //重连并判断是否成功
	  {

		  //成功
		  for(byte a = 0;a<TopicNum;a++)
		  {
			  subscribe(TopicName[a].c_str());
		  }
		  
		  //填写上线订阅，应该是个String数组传入循环订阅处理
	  } 
	else 
		{
			//链接失败

		   delay(5000);   //暂停5秒钟重试
		}
  }
 }
 
 
 //循环检测
 void AliIotLink::loop()
 {
   if (!_client->connected()) 
   {
    reconnect();
   }
	_client->loop();
}
 
 
int AliIotLink::state()    //错误消息返回
{
	return _client->state();
}



//回调函数
void AliIotLink::setCallback(MQTT_CALLBACK_SIGNATURE)
{
	_client->setCallback(callback);
	//SerialUSB.println(callback);
}
//监听Topic
void AliIotLink::subscribe(const char* topic)
{
	_client->subscribe(topic);
}
//推送消息
void AliIotLink::publish(const char* topic, const char* payload)
{
	_client->publish(topic,payload);
}


//登记topic
void AliIotLink::subTopic(String topic)
{
	TopicName[TopicNum] = topic;
	TopicNum++;
	if(TopicNum > MQTT_Topic_Quantity)
	{
		TopicNum = MQTT_Topic_Quantity;
	}
}

void AliIotLink::HMAC( char const *key, byte KeySize,  char const *data, byte dataSize, byte *hashData)
{
  uint8_t result[32];
  sha256.resetHMAC(key, KeySize);  //传入KEY,和key长度
  sha256.update(data, dataSize);// 传输 hash明文
  sha256.finalizeHMAC(key, KeySize, result, sizeof(result)); // 计算
  for (byte a = 0; a < sizeof(result); a++) //传出签名
  {
    *(hashData + a) = result[a];
  }
}