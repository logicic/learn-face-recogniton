# learn-face-recognition
something about my learning face recognition 

### Face Recognition



##### 开源人脸检测模型框架：

- 安装：

  - face_recognition, openface, facenet这几个使用python，有些依赖于dlib库用作检测定位人脸，有些用他的深度残差网络来做人脸特征获取。在一些用例中有用到opencv作为辅助，不过他本身的人脸识别库没有opencv的依赖。openface, facenet这两个在下载依赖的时候，会有些函数已经被新版本的库给删掉了，face_recognition下载的时候的时候算是比较顺的。
  - Seetaface2使用c/c++语言，配合使用动态链接库来使用它的库函数，但是官方给的文档支持Win和Linux，试着使用MacOS编译，倒也能编译出来，不过修改example内容后，重新编译，出错了，大概是需要修改他提供的cmake文件，使得可以生成一个完整的编译链，会有些麻烦。

- 文档：

  - face_recognition没有规范的文档，但是用例比较多，注释也比较多
  - openface有规范的API[文档](https://openface-api.readthedocs.io/en/latest/index.html)
  - Seetaface2官方也给有[文档](https://github.com/seetafaceengine/SeetaFace2/tree/master/documents)
  - facenet官方资料查到的比较少

- 效果：

  从官方给的表面数据来看，准确率：facenet > face_recognition > openface > Seetaface2, 但是我在openface上看到，他的给的数据，有FaceNet Paper (Reference)，准确性：0.9963 ± 0.009，Model给的准确率：0.9292 ± 0.0134，那么就有理由怀疑，其他的到底有没有那么高。在face_recognition中有说明，**本项目的人脸识别是基于业内领先的C++开源库 [dlib](http://dlib.net/)中的深度学习模型，用[Labeled Faces in the Wild](http://vis-www.cs.umass.edu/lfw/)人脸数据集进行测试，有高达99.38%的准确率。但对小孩和亚洲人脸的识别准确率尚待提升。**那么也有理由怀疑，其他的库对于亚洲人脸效果到底也有没有那么高，不过Seetaface2怀疑度倒是最小。



##### 公司产品的人脸识别框架：

- 1.基本的功能都是齐全的，收费有按时收费和按调用次数收费。
- 2.效果的话，从给的数据来看，应该差不了太多。
- 3.费用方面，ArcSoft每年一次更新一次key；百度和腾讯优图有一定的免费额度；旷世face++和云从科技没找到免费额度。



##### 开源和公司间比较：

- 收费与否：公司有收费项目也有部分免费，也有计量计时的模式
- 功能：公司的功能齐全，有图像预处理，活体检测，开源的只有基本的人脸检测，人脸特征获取，人脸比对
- 文档：公司的文档肯定更齐全，可以直接使用，只要宏观地明白输入输出就行。开源的文档不一定全，可能还需要深挖才能实现某些功能。



**LFW**全名`Labeled Faces in the Wild`，是由马萨诸塞大学于2007年建立，用于评测非约束条件下的人脸识别算法性能，是人脸识别领域使用最广泛的评测集合。

| 开源库           | 效果（LFW）   |
| ---------------- | ------------- |
| Face_recognition | 99.38         |
| SeetaTech        |               |
| Openface         | 0.9292±0.0134 |
| facenet          | 0.9963±0.0009 |

| 产品            | 效果（LFW）   |
| --------------- | ------------- |
| 百度大脑        | 0.9977±0.0006 |
| 旷世Face++      | 0.9950±0.0036 |
| 腾讯优图        | 0.9980±0.0023 |
| 云从科技        | 0.9950±0.0022 |
| ARcSoft（虹软） |               |



#### 数据集dataset：

[Labeled Faces in the Wild](http://vis-www.cs.umass.edu/lfw/)

 [VGGFace2 dataset](https://www.robots.ox.ac.uk/~vgg/data/vgg_face2/)

 [FaceScrub](http://vintage.winklerbros.net/facescrub.html) 

 [CASIA-WebFace](http://arxiv.org/abs/1411.7923)



#### 网络模型:

VGG	resnet深度残差网络	



#### dlib

dlib：https://www.cnblogs.com/supersayajin/p/8489435.html

残差网络：https://zhuanlan.zhihu.com/p/72679537。    https://www.bbsmax.com/A/8Bz8nXQo5x/

模型获取：http://dlib.net/files/

最好使用GPU



#### face_recognition

Github：https://github.com/ageitgey/face_recognition

语言：Python

网络模型：使用dlib的网络模型

可以使用gpu加速，cuda加速



#### openFace

#### 基于faceNet方法

文档：http://cmusatyalab.github.io/openface/

Github：https://github.com/cmusatyalab/openface

models：http://cmusatyalab.github.io/openface/models-and-accuracies/

环境：Python2   torch  Opencv2.4  dlib18.16

使用docker测试：http://cmusatyalab.github.io/openface/setup/

模型准确性：http://cmusatyalab.github.io/openface/models-and-accuracies/

网络模型：DNN网络模型

使用的训练集： [FaceScrub](http://vintage.winklerbros.net/facescrub.html) 和 [CASIA-WebFace](http://arxiv.org/abs/1411.7923).

得到四个不同参数的模型：

- [nn4.v1](https://storage.cmusatyalab.org/openface-models/nn4.v1.t7)
- [nn4.v2](https://storage.cmusatyalab.org/openface-models/nn4.v2.t7)
- [nn4.small1.v1](https://storage.cmusatyalab.org/openface-models/nn4.small1.v1.t7)
- [nn4.small2.v1](https://storage.cmusatyalab.org/openface-models/nn4.small2.v1.t7)

可以开gpu加速和cuda加速

缺点：所需的依赖版本太老了，好多新版本的库都已经删除了现使用的函数了。





#### FaceNet

GitHub：https://github.com/davidsandberg/facenet

语言：Python

框架：tensorflow，dlib

训练集：Casia-WebFace和VGGFace2

网络模型：Inception - resNet

| Model name                                                   | LFW accuracy | Training dataset | Architecture                                                 |
| ------------------------------------------------------------ | ------------ | ---------------- | ------------------------------------------------------------ |
| [20180408-102900](https://drive.google.com/open?id=1R77HmFADxe87GmoLwzfgMu_HY0IhcyBz) | 0.9905       | CASIA-WebFace    | [Inception ResNet v1](https://github.com/davidsandberg/facenet/blob/master/src/models/inception_resnet_v1.py) |
| [20180402-114759](https://drive.google.com/open?id=1EXPBSXwTaqrSC0OhUdXNmKSh9qJUQ55-) | 0.9965       | VGGFace2         | [Inception ResNet v1](https://github.com/davidsandberg/facenet/blob/master/src/models/inception_resnet_v1.py) |

可以开gpu加速和cuda加速

缺点：所需的依赖版本太老了，好多新版本的库都已经删除了现使用的函数了。



#### SeetaTech（中科视拓）

- Github：https://github.com/seetafaceengine/SeetaFace2

语言：c/c++

网络模型：深度残差网络模型ResNet50

训练集：3300万张

测试使用的是FDDB数据集，人脸检测的准确率：

| 模块                          | 方法概述     | 基础技术指标                                                 | 典型平台速度                                            |
| ----------------------------- | ------------ | ------------------------------------------------------------ | ------------------------------------------------------- |
| **人脸检测**                  | Cascaded CNN | FDDB 上召回率达到92%（100个误检情况下）。                    | 40 最小人脸 I7: 70FPS(1920x1080) RK3399: 25FPS(640x480) |
| **面部关建点定位(81点和5点)** | FEC-CNN      | 平均定位误差（根据两眼中心距离归一化） 300-W Challenge Set 上达到 0.069。 | I7: 450FPS 和 500FPS RK3399: 110FPS 和 220FPS           |
| **人脸特征提取与比对**        | ResNet50     | 识别：通用1：N+1场景下，错误接受率1%时， 1000人底库，首选识别率超过98%， 5000人底库，首选识别率超过95%。 | I7: 8FPS RK3399: 2.5FPS                                 |

<table>
    <tr>
        <th rowspan="2">版本</th>
        <th colspan="2">人脸检测</th>
        <th colspan="2">关键点定位</th>
        <th colspan="2">人脸识别</th>
        <th rowspan="2">第三方依赖</th>
    </tr>
    <tr>
        <td>速度[1]</td>
        <td>单精度[2]</td>
        <td>速度</td>
        <td>功能</td>
        <td>训练数据规模</td>
        <td>应用</td>
    </tr>
    <tr>
        <th>1.0</th>
        <td>16FPS</td>
        <td>85%</td>
        <td>200FPS</td>
        <td>5点</td>
        <td>140万张</td>
        <td>实验室</td>
        <td>无</td>
    </tr>
    <tr>
        <th>2.0</th>
        <td>77FPS</td>
        <td>92%</td>
        <td>500FPS</td>
        <td>5/81点</td>
        <td>3300万张</td>
        <td>商业环境</td>
        <td>无</td>
    </tr>
    <tr>
        <th>备注</th>
        <td colspan="7">
            [1] 640x480输入、检测40x40人脸、I7-6700。<br>
            [2] 人脸检测的精度指100个误捡FDDB数据集的召回率。
        </td>
    </tr>
</table>



#### ARcSoft

https://ai.arcsoft.com.cn/manual/docs#/41

使用的是CPU

- 1.支持的语言及平台：

虹软视觉开放平台根据不同操作平台提供不同的SDK。目前 SDK（内置活体检测） x86，x64平台（c++/Java语言）、Linux x64平台（c++/Java语言）、iOS平台（Objective-C语言）与Android arm32平台（Java语言）； 人证核验SDK 可下载 Windows x86，x64平台（c++语言）与Android arm32平台（Java语言）。

- 2.有收费和免费的：

  - 免费：

    - 个人有100个终端数量，企业有5000个终端数量
    - 获取方法：平台注册，配置
    - 使用限制：Windows和Linux平台所有的SDK以及Android平台的活体检测有一年期限，自下载之日起，一年内需重新申请下载更新引擎，更新后即可继续免费使用。
    - 更新方式：登录视觉开放平台重新申请下载引擎，将原应用工程中的引擎相关包文件，代码中所使用的APPID以及各引擎Key均替换成最新的即可。

  - 收费：

    - 购买的是APP 人脸识别SDK授权数
    - ![arcsoft](https://ai.arcsoft.com.cn/uploadFiles/1/sdk/9aac256f-3edd-4d62-b8a1-e629ee0510a9.png)

    



#### 百度大脑

- 有手机刷脸登陆的方案：https://ai.baidu.com/ai-doc/FACE/7k37c1k3a

- 有离线sdk，还有在线访问API的

- 看了很多，给的指标的都是活体的性能指标：

- 付费

  - 离线sdk，采集模块免费，识别对比模块是收费的。

    - | SDK                                                          | 免费额度                                                     |
      | ------------------------------------------------------------ | ------------------------------------------------------------ |
      | [离线采集 SDK](https://ai.baidu.com/docs#/Face-Collect-SDK/top) | 离线采集 SDK 是免费产品，您可以[免费申请](https://console.bce.baidu.com/ai/#/ai/face/client/index)，无需付费 |
      | [离线识别 SDK](https://ai.baidu.com/docs#/Face-Offline-SDK/top) | 每个账号下默认分配 **5个** 试用版序列号，有效期为**三个月**，供前期测试。 如需正式使用，支持 [购买授权](https://console.bce.baidu.com/ai/#/ai/face/offline/index) |

  - 访问云API

    - 免费额度

    - | 接口                                                      | 免费额度                                                     |
      | --------------------------------------------------------- | ------------------------------------------------------------ |
      | [人脸检测](https://ai.baidu.com/docs#/Face-Detect-V3/top) | 调用量免费，以 [QPS](https://baike.baidu.com/item/QPS/4818554?fr=aladdin) 维度来进行资源的赠送或购买。 个人账户默认赠送 **2QPS**；企业认证账户默认赠送 **10QPS**。 如需更多 QPS，支持 [付费购买](https://ai.baidu.com/docs#/Face-Pricing/top) |
      | [人脸对比](https://ai.baidu.com/docs#/Face-Match-V3/top)  | 调用量免费，以 [QPS](https://baike.baidu.com/item/QPS/4818554?fr=aladdin) 维度来进行资源的赠送或购买。 个人账户默认赠送 **2QPS**；企业认证账户默认赠送 **10QPS**。 如需更多 QPS，支持 [付费购买](https://ai.baidu.com/docs#/Face-Pricing/top) |
      | [人脸搜索](https://ai.baidu.com/docs#/Face-Search-V3/top) | 调用量免费，以 [QPS](https://baike.baidu.com/item/QPS/4818554?fr=aladdin) 维度来进行资源的赠送或购买。 个人账户默认赠送 **2QPS**；企业认证账户默认赠送 **10QPS**。 如需更多 QPS，支持 [付费购买](https://ai.baidu.com/docs#/Face-Pricing/top) |
      | [人脸库管理](https://ai.baidu.com/docs#/Face-Set-V3/top)  | 包含人脸注册、人脸更新、人脸删除等子接口，每个接口并发相同 调用量免费，以 [QPS](https://baike.baidu.com/item/QPS/4818554?fr=aladdin) 维度来进行资源的赠送或购买。 个人账户默认赠送 **2QPS**；企业认证账户默认赠送 **10QPS**。 如需更多 QPS，支持 [付费购买](https://ai.baidu.com/docs#/Face-Pricing/top) |

    **免费额度说明：**

    如果账号完成企业认证`基础服务API`并发支持永久赠送 10QPS，折算成实际业务调用次数，相当于：

    - 每天：最高免费享用 **10QPS \*24h\* 3600s = 864000次** 有效调用
    - 每年：最高免费享用 **864000次/天 \* 365天 = 315360000次** 有效调用。

    

    购买费用

    - | 购买 QPS 数量 | 按月购买     | 按天购买    |
      | ------------- | ------------ | ----------- |
      | 0<QPS<=10     | 300元/月/QPS | 30元/天/QPS |
      | 10<QPS<=50    | 250元/月/QPS | 25元/天/QPS |
      | 50<QPS<=100   | 200元/月/QPS | 20元/天/QPS |
      | 100<QPS       | 150元/月/QPS | 15元/天/QPS |

      > 说明：
      >
      > 1. 同一个百度云账号下多个应用共享各接口的并发支持。
      > 2. 阶梯价格梯度按照单次购买的数量计算，不同订单不累计。
      > 3. 每个接口单独计算QPS，若您需要人脸注册和人脸比对接口各15个QPS，则您需要分别购买5个QPS的人脸注册和人脸比接口（企业认证用户免费赠送10QPS）。
      > 4. 每个接口最多只可购买200个QPS，如需更多QPS，请 [提交工单](https://ticket.bce.baidu.com/#/ticket/create~productId=95) 与我们联系。

      **调用计费示例**

      - 如果您需要50个QPS，除免费赠送的10QPS外（需要企业认证），您还需购买40个QPS。则计费方式为：`300*10+250*30=10500` 元/月
      - 如果您需要购买1个月+5天的1个QPS，可以按照包月+按天的搭配模式购买，即：`300*1+30*5=450` 元

  - 活体检测使用另外的的计费

    - 活体验证 API ： [在线活体检测](https://ai.baidu.com/docs#/Face-Liveness-V3/top) 、[H5视频活体检测](https://ai.baidu.com/docs#/Face-H5Liveness-V3/top) 与 [H5语音验证码](https://ai.baidu.com/docs#/Face-H5Liveness-V3/top)

      产品价格如下表所示：

      | 接口           | 产品价格                                                     | 计费错误码                 |
      | -------------- | ------------------------------------------------------------ | -------------------------- |
      | 在线活体检测   | 调用量免费，以 [QPS](https://baike.baidu.com/item/QPS/4818554?fr=aladdin) 维度来进行资源的赠送或购买。 个人账户默认赠送 **2QPS**；企业认证账户默认赠送 **10QPS**。 如需更多 QPS，**产品价格与基础服务 API 一致** | 无                         |
      | H5视频活体检测 | **0.2 元/次**，每天50次免费调用，免费额度用尽后开始计费      | 计费错误码：216434、216500 |
      | H5语音验证码   | **0.01 元/次**，每天50次免费调用，免费额度用尽后开始计费     | 无                         |

      > 说明：
      > 1.“调用量”包含成功调用与少部分需计费的失败调用，其中需要计费的失败调用请参考上述表格最后一列，[错误码详情](https://ai.baidu.com/docs#/Face-ErrorCode-V3/top)
      > 2.`H5视频活体检测 API`与`H5语音验证码 API`接口并发支持默认 2QPS ，完成百度云企业认证后，并发支持将扩充至 10QPS。如需更多QPS，可以通过[提交工单](https://ticket.bce.baidu.com/#/ticket/create~productId=95)与我们联系



#### 旷世Face++

- 开放形式：

  - 1.API

    通过 API 直接调用 Face++ 的各项能力，适合联网产品。

  - 2.SDK

    移动端应用通过嵌入SDK获得开放能力，适合离线场景（如实时美颜），目前支持 Android / iOS。

- [收费](https://www.faceplusplus.com.cn/v2/pricing/#face.api)

  - 包时计费：

    | 人脸识别         | 面部特征分析               | 人脸稠密关键点   | 其他                        |                  |                             |                                                              |
    | ---------------- | -------------------------- | ---------------- | --------------------------- | ---------------- | --------------------------- | ------------------------------------------------------------ |
    | 100元 / QPS / 天 | 1,000元 / QPS / 个月(30天) | 500元 / QPS / 天 | 10,500元 / QPS / 个月(30天) | 500元 / QPS / 天 | 10,500元 / QPS / 个月(30天) | [更多](https://www.faceplusplus.com.cn/v2/pricing-details/#api_1) |

  - 按量计费：

    | 人脸检测     | 人脸搜索    | 人脸比对    | 人脸稠密关键点 | 人脸集合API组 | 面部特征分析 | 皮肤分析   | 3D人脸重建 | 高阶版-皮肤分析 | 其他                                                         |
    | ------------ | ----------- | ----------- | -------------- | ------------- | ------------ | ---------- | ---------- | --------------- | ------------------------------------------------------------ |
    | 0.001元 / 次 | 0.01元 / 次 | 0.01元 / 次 | 0.03元 / 次    | 0.0005元 / 次 | 0.1元 / 次   | 0.1元 / 次 | 2元 / 次   | 0.3元 / 次      | [更多](https://www.faceplusplus.com.cn/v2/pricing-details/#api_1) |

- [功能演示](https://www.faceplusplus.com.cn/)：

  人脸检测：https://www.faceplusplus.com.cn/face-detection/

  人脸对比：https://www.faceplusplus.com.cn/face-comparing/

  人脸搜索：https://www.faceplusplus.com.cn/face-searching/

- [how to use](https://console.faceplusplus.com.cn/documents/5671791)





#### 云从

[指南](https://ai.cloudwalk.cn/wiki/新手指南/接入指南)

[文档](https://ai.cloudwalk.cn/cloudwalk/#/face/search)

费用：

![yuncong](https://cloudwalk-doc.s3.cn-north-1.amazonaws.com.cn/6e4b1e60-9af2-11e8-b0d6-8904a06f19be.png)



#### 腾讯优图

https://open.youtu.qq.com/#/open/experience/living

- 提供包括人脸检测与分析、五官定位、人脸搜索、人脸比对、人脸验证、人员查重、活体检测等多种功能。

- 腾讯云的已编写好的开发工具集（SDK）来调用人脸识别服务 API。SDK 已支持多种语言，包括 Python、Java、PHP、Go、NodeJS、.Net 等。可以通过 [SDK 中心](https://cloud.tencent.com/document/sdk) 获取。这样就很方便的集成在我们的程序中了。

- Go封装好的访问云端API的库：https://github.com/Tencent-YouTu/Go_sdk

- [计费](https://cloud.tencent.com/document/product/867/17640)：

  - 在线API调用

    #### 免费额度

    针对在线 API 调用方式，腾讯云提供预付费和后付费两种计费模式，无论您选择何种计费模式，您每月每种服务均有10000次的免费调用额度，以免费资源包的形式发放到您的腾讯云账号中，优先扣除。

    - 您可以在 [控制台-资源包管理](https://console.cloud.tencent.com/aiface/source) 中查看免费资源包的消耗情况。
    - 免费资源包消耗完后，如果您已购买付费资源包，则将转入预付费资源包结算，如果您未购买预付费资源包或者预付费资源包已耗尽，将直接转入后付费结算。

    #### 预付费

    预付费当前不支持退款和剩余次数冻结。如需购买，请单击 [购买资源包](https://buy.cloud.tencent.com/iai_face)。

    | 资源包规格       | 100万次 | 1000万次 | 5000万次 | 1亿次    |
    | :--------------- | :------ | :------- | :------- | :------- |
    | 人脸检测与分析   | 450元   | 4100元   | 17500元  | 25000元  |
    | 五官定位         | 1900元  | 18200元  | 82500元  | 135000元 |
    | 人脸比对         | 3100元  | 30400元  | 142500元 | 255000元 |
    | 人脸验证         | 3100元  | 30400元  | 142500元 | 255000元 |
    | 人脸搜索         | 3100元  | 30400元  | 142500元 | 255000元 |
    | 人员库管理       | 3100元  | 30400元  | 142500元 | 255000元 |
    | 人脸静态活体检测 | 1800元  | 17400元  | 75000元  | 110000元 |



#### 两套方案：

- dlib----go----读取模型，参考例子：

1.https://studygolang.com/articles/20172

2.https://hackernoon.com/face-recognition-with-go-676a555b8a7e

3.https://godoc.org/github.com/Kagami/go-face

4.https://github.com/Kagami/go-face/blob/master/classify.cc

- opencv---dnn库----gocv----读取模型，参考例子：

1.https://github.com/tczhangzhi/face-recognition

2.https://zhuanlan.zhihu.com/p/54845295

3.https://www.jianshu.com/p/c87e3e88e8dc



#### 计算两条数据间的距离

- 利用欧式距离计算相似度：

1.np.linalg.norm：https://blog.csdn.net/qq_36387683/article/details/87636019?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase

2.dlib：dlib::squared_euclidean_distance()

3.golang：gonum.Norm



- 利用余弦距离计算相似度：

https://blog.csdn.net/akadiao/article/details/79767113

- 他们两的区别：https://blog.csdn.net/weixin_39393430/article/details/89786020





**Deep Neural Networks (dnn module)**

https://docs.opencv.org/master/d2/d58/tutorial_table_of_content_dnn.html



##### Deep Learning in OpenCV

https://github.com/opencv/opencv/wiki/Deep-Learning-in-OpenCV



##### model类型：

https://docs.opencv.org/3.4/d6/d0f/group__dnn.html#ga3b34fe7a29494a6a4295c169a7d32422



#### 人脸检测方案：

https://github.com/Smartuil/OpenCV-Practical-Exercise



1.人脸检测，opencv-haar，opencv-dnn，dlib-hog，dlib-dnn

2.特征提取，dlib-dnn+res模型，opencv-dnn+模型

3.匹配和识别，分类比对，欧式距离，余弦距离



DNN：

1.Net解析：https://blog.csdn.net/u011028771/article/details/85533517?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase

2.BlobFromImage函数解析：https://blog.csdn.net/u011341856/article/details/100041050

3.使用：

- face detection —— FMTCNN

- face calibration —— Affine Transform

- face feature extraction —— SphereFace

- face classification —— Cosine Similarity

https://github.com/tczhangzhi/face-recognition

4.opencv DNN模块之人脸识别基于Torch openface：

https://blog.csdn.net/z961968549/article/details/104270723

5.https://github.com/Smartuil/OpenCV-Practical-Exercise

| [1.Gender & Age Classification](https://www.learnopencv.com/age-gender-classification-using-opencv-deep-learning-c-python/) | [基于OpenCV深度学习进行性别和年龄分类](https://zhuanlan.zhihu.com/p/111721652) |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| [2.Face Detection](https://www.learnopencv.com/face-detection-opencv-dlib-and-deep-learning-c-python/) | [人脸识别的对比 – OpenCV, Dlib and Deep Learning](https://zhuanlan.zhihu.com/p/111925661) |
| [3.InvisibilityCloak](https://www.learnopencv.com/invisibility-cloak-using-color-detection-and-segmentation-with-opencv/) | [基于OpenCV的颜色检测和分割的隐形斗篷](https://zhuanlan.zhihu.com/p/112219627) |
| [4.ColorSpaces](https://www.learnopencv.com/color-spaces-in-opencv-cpp-python/) | [OpenCV中的颜色空间](https://zhuanlan.zhihu.com/p/112790325) |
| [5.TextDetection](https://www.learnopencv.com/deep-learning-based-text-detection-using-opencv-c-python/) | [基于OpenCV的深度学习文本检测](https://zhuanlan.zhihu.com/p/112909119) |
| [6.VideoStabilization](https://www.learnopencv.com/video-stabilization-using-point-feature-matching-in-opencv/) | [OpenCV中使用点特征匹配的视频稳定方法](https://zhuanlan.zhihu.com/p/113144000) |
| [7.ObjectDetection](https://www.learnopencv.com/deep-learning-based-object-detection-using-yolov3-with-opencv-python-c/) | [基于深度学习的目标检测](https://zhuanlan.zhihu.com/p/113825562) |
| [8.CenterofBlob](https://www.learnopencv.com/find-center-of-blob-centroid-using-opencv-cpp-python/) | [使用OpenCV寻找平面图形的质心](https://zhuanlan.zhihu.com/p/115813693) |
| [9.HuMoments](https://www.learnopencv.com/shape-matching-using-hu-moments-c-python/) | [使用Hu矩进行形状匹配](https://zhuanlan.zhihu.com/p/117344473) |

