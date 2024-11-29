#ifndef CLOUD_H
#define CLOUD_H

// 云通信模块头文件
class Cloud {
public:
    static void init();  // 初始化云通信模块
    static void sendData(const char* data);  // 发送数据到云端
};

#endif // CLOUD_H
