#ifndef DISPLAY_H
#define DISPLAY_H

// 显示模块头文件
class Display {
public:
    static void init();  // 初始化显示模块
    static void showMessage(const char* message);  // 显示信息
};

#endif // DISPLAY_H
