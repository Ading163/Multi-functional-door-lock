#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>

// 显示模块头文件
class Display
{
public:
    static void init();                            // 初始化显示模块
    static void showInitializationComplete();       // 显示初始化完成
    static void showDistance(bool isLocked, float distance);     // 显示距离
    static void showMessage(const char *message); // 显示信息
};

#endif // DISPLAY_H
