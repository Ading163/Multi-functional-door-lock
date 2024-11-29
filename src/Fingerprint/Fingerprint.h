#ifndef FINGERPRINT_H
#define FINGERPRINT_H

// 指纹识别头文件
class Fingerprint {
public:
    static void init();  // 初始化指纹识别
    static bool authenticate();  // 验证指纹输入
};

#endif // FINGERPRINT_H
