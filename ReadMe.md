### 一，概述

​	ArRtspTool是anyRTC开源的一款将rtsp流转为rtc的工具，这样rtsp的流可以不需要外网服务或IP地址，即可实现网页/H5无插件观看，小程序，APP等各种方式查看视频流。

​	支持常见的Linux、Windows、树莓派、英伟达TX系列等等。

​	支持Rtsp流，支持USB摄像头，支持窗口推流等等。

​	**适用的场景：**

​	1，内网摄像头穿透到公网：使用网页，App或小程序进行观看，超低1s内延时

​	2，远程驾驶：超低延时，远程操控，流程不卡顿

​	3，无人机：超低延时，精准控制，AI识别反馈

​	4，小区门禁：实时监看，双向对讲，远程操控

### 二，编译

​		下载代码到本地：git clone https://github.com/anyRTC-UseCase/ArRtspTool.git

​		编译脚本对应的平台(已验证，其他平台或系统版本可联系我司进行确认)：

```
Makefile.linux  - Centos7.0及以上
Makefile.pi		- 树莓派4
Makefile.tx		- Nvidia TX2
```

​		以树莓派为例(以下命令均以root运行，非root可能会报权限错误)：

```
***# cd ArRtspTool
***# cp Makefile.pi Makefile
***# make && make install
```

​		启动程序，运行之前记得先配置一下相关参数

```
***# chmod +x run.sh
***# ./run.sh start ArRtspTool rtsp.conf 
```

​		停止程序

```
***# ./run.sh stop ArRtspTool
```



### 三，如何配置

```
[rtsp]
url=你的Rtsp流的Url

[nv]
dev_id=设备ID(/dev/video0)

[rtc]
app_id=rtc的AppId，
chan_id=频道ID,可设置任意值，web或App通过此ID可以观看rtsp的流
```

​	AppId的获取可以登录[anyRTC](https://console.anyrtc.io/signin)官网获取

​	**注意：** Rtsp地址和设备ID二者选其一，优先Rtsp地址，若推本地摄像头则无需配置Rtsp地址

### 四，如何观看

**在线体验**

前往[体验demo](https://demos.anyrtc.io/Demo/basicLive/index.html)

输入 AppID 和 Channel 后点击Join as audience 按钮进行观看。

**观看端集成到自己的系统中**

- 前往[下载中心](https://docs.anyrtc.io/download)下载对应的开发SDK.
- 前往[开发者文档](https://docs.anyrtc.io/)，对应平台查看集成文档

### 五，常见问题

详见[常见问题](https://docs.anyrtc.io/platforms/docs/platforms/FAQ/faq)。

**Buglist：**
 Bug001 : TX2: no element "h264parse"
 解决001：
 `sudo apt-get install gstreamer1.0-plugins-bad`

**anyRTC创业扶持计划**

- 30万免费分钟数，助力初创企业快速发展。

> [anyRTC](https://www.anyrtc.io)初创企业扶持计划，只要通过企业审核，联系客服加入[anyRTC](https://www.anyrtc.io)创业扶持计划，即可享受30万免费分钟数。获得分钟数可降低在实时音视频技术服务所产生的成本费用，零成本快速启动项目。

- 专属技术指导支持

> [anyRTC](https://www.anyrtc.io)为初创企业提供一对一专属客服，为客户提供专业、认真的服务，及时解答您的疑惑。并为客户提供专属技术指导，更快上手，轻松上线！

### 六，联系我们

联系电话：021-65650071

QQ咨询群：580477436

ArCall技术交流群：597181019

咨询邮箱：[hi@dync.cc](mailto:hi@dync.cc)

技术问题：[开发者论坛](https://bbs.anyrtc.io/)

获取更多帮助前往：[www.anyrtc.io](http://www.anyrtc.io/)
