#include <aliIotLink.h>

AliIotLink::AliIotLink()
{
	
}

void AliIotLink::begin()
{
  randomSeed(analogRead(A0));
  delayMicroseconds(random(0,10000));
}


void AliIotLink::begin(String __ServerUrl,uint16_t __port,String __Id,String __DeviceName,String __ProductKey,String __DeviceSecret)
{
	_ServerUrl = __ServerUrl;
	_port = __port;
	_Id = __Id;
	_DeviceName = __DeviceName;
	_ProductKey = __ProductKey;
	_DeviceSecret = __DeviceSecret;
	randomSeed(analogRead(A0));
    delayMicroseconds(random(0,10000));
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
	 String _URL = _ProductKey + "." + _ServerUrl;
	 return _URL;
 }
 
 //合成访问用户名
 String AliIotLink::readUser()
 {
	 String _Username  = _DeviceName + "&" + _ProductKey ;
	 return _Username;
 }
 
 
 //合成访问密码
 String AliIotLink::readPasswd()
 {
	 String _Passwd =  "clientId" + _Id + "deviceName" + _DeviceName +"productKey"+_ProductKey + "timestamp" + Times;
	 String _hash = "";
	 
	 Sha1.initHmac(_DeviceSecret.c_str(),32);  //传入密钥
	 Sha1.print(_Passwd);   //传入内容
	 uint8_t *ByteHash = Sha1.resultHmac() ;
	 
	 for(int i =0;i<20;i++)
	 {
		_hash = _hash + "0123456789ABCDEF"[ByteHash[i]>>4];
		_hash = _hash + "0123456789ABCDEF"[ByteHash[i]&0xf];
	 } 
	 return _hash;  //返回HASH密文
 }