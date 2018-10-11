#include "aliIot.h"

AliIot::AliIot(PubSubClient& client)
{
	_client = &client;	
}
void AliIot::begin()
{
  //randomSeed(analogRead(A0));   //获取IO随机值【非安全的伪随机】作为种子
  delayMicroseconds(random(0,10000));   //延迟随机时间
  
  generateClientId();
  readUrl();
  readUser();
  readPasswd();
  _client->setServer(_URL.c_str(),_port); //写入服务器名称与端口号
  
}


void AliIot::begin(String __ServerUrl,uint16_t __port,String __Id,String __DeviceName,String __ProductKey,String __DeviceSecret)
{
	_ServerUrl = __ServerUrl;
	_port = __port;
	_Id = __Id;
	_DeviceName = __DeviceName;
	_ProductKey = __ProductKey;
	_DeviceSecret = __DeviceSecret;
	//randomSeed(analogRead(A0));
	generateClientId();
	readUrl();
	readUser();
	readPasswd();
	_client->setServer(_URL.c_str(),_port);  //写入服务器名称与端口号
}



void AliIot::writeUrl(String __ServerUrl)    // 设置登录网址
{
	_ServerUrl = __ServerUrl;
}
//服务器端口设置
void AliIot::writePort(uint16_t __port)
{
	_port = __port;
}
//硬件设备名称
void AliIot::writeID(String __Id)
{
	_Id = __Id;
}
// 设置设备硬件标签名称【阿里云提供】
void AliIot::writeDeviceName(String __DeviceName)  
{
	_DeviceName = __DeviceName;
}
//【阿里云提供】
void AliIot::writeProductKey(String __ProductKey)
{
	_ProductKey = __ProductKey;
}
//【阿里云提供】
void AliIot::writeDeviceSecret(String __DeviceSecret)
{
	_DeviceSecret = __DeviceSecret;
}

void AliIot::generateClientId()
{
	//ID+参数+随机数+结尾符号
	randomSeed(micros());
	Times  =random(0, 65535);
	_ClientId = _Id + _ClientIdSuffix + Times +"|";
}

//获取合成好的登录用的ClientId
String AliIot::readClientId()
{
	return _ClientId;
}


//合成访问网址
 String AliIot::readUrl()
 {
	 _URL = _ProductKey + "." + _ServerUrl;
	 return _URL;
 }
 
 //合成访问用户名
 String AliIot::readUser()
 {
	 _Username = _DeviceName + "&" + _ProductKey ;
	 return _Username;
 }
 
 
 //合成访问密码
 String AliIot::readPasswd()
 {
	 String _Passwd =  "clientId" + _Id + "deviceName" + _DeviceName +"productKey"+_ProductKey + "timestamp" + Times;
	 _PasswdHash = "";
	 
	 Sha1.initHmac((const uint8_t*)_DeviceSecret.c_str(),32);  //传入密钥
	 Sha1.print(_Passwd);   //传入内容
	 uint8_t *ByteHash = Sha1.resultHmac() ;
	 
	 for(int i =0;i<20;i++)
	 {
		_PasswdHash = _PasswdHash + "0123456789ABCDEF"[ByteHash[i]>>4];
		_PasswdHash = _PasswdHash + "0123456789ABCDEF"[ByteHash[i]&0xf];
	 } 
	 return _PasswdHash;  //返回HASH密文
 }
 
 
 
 //===================mqtt部分=====================
 
 bool AliIot::connect()
 {
	return _client->connect(_ClientId.c_str(),_Username.c_str(),_PasswdHash.c_str());   //像服务器传递 ClientId，用户名，密码
 }
 
 //重连
 void AliIot::reconnect()
 {
  byte Num=0;   //失败计数器
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
			Num++;
			 if(Num >3)  //大于3次则跳出死循环
		   {
			   break;
		   }
		   delay(5000);   //暂停5秒钟重试
		  
		}
  }
 }
 
 
 //循环检测
 void AliIot::loop()
 {
   if (!_client->connected()) 
   {
    reconnect();
   }
	_client->loop();
}
 
 
int AliIot::state()    //错误消息返回
{
	return _client->state();
}



//回调函数
void AliIot::setCallback(MQTT_CALLBACK_SIGNATURE)
{
	_client->setCallback(callback);
	//SerialUSB.println(callback);
}
//监听Topic
void AliIot::subscribe(const char* topic)
{
	_client->subscribe(topic);
}
//推送消息
void AliIot::publish(const char* topic, const char* payload)
{
	_client->publish(topic,payload);
}


//登记topic
void AliIot::subTopic(String topic)
{
	TopicName[TopicNum] = topic;
	TopicNum++;
	if(TopicNum > MQTT_Topic_Quantity)
	{
		TopicNum = MQTT_Topic_Quantity;
	}
}