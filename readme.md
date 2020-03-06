## 阿里云物联网平台的 arduino连接工具包
* 目前实现了订阅消息与平台推送消息的回调
* 只能发布QoS 0消息,可以订阅QoS 0或QoS 1
* 目前已支持 arduino UNO  ,MEGA2560 （基于W5100,W5500），esp8266，esp8285，esp32 (wifi)
* 基于[Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32) ，可扩展支持STM32系列处理器 F0~F4等
