#include <Arduino.h>
#include "Display.h"

// 初始化显示模块
void Display::init() {
    Serial.println("Display Module Initialized");
    // 这里可以添加更多初始化代码
}

// 显示信息
void Display::showMessage(const char* message) {
    // 模拟显示信息
    // 实际实现中需要根据具体需求编写代码
    Serial.print("Display: ");
    Serial.println(message);
}
