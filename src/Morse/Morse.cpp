// Morse code decoding and input processing
// 莫尔斯电码解码与输入处理
#include <Arduino.h>
#include "Morse.h"
#include "Lock/Lock.h"

// Morse code
// 摩斯密码

String morseCode = "";                  // Store current input Morse code // 存储当前输入的摩斯密码
String correctCode = "·-···";           // Preset correct Morse code // 预设正确的摩斯密码
unsigned long pressStartTime = 0;       // Morse code button press start time // 摩斯密码按钮按下开始时间
unsigned long releaseStartTime = 0;     // Morse code button release time // 摩斯密码按钮松开时间
int Morse::morseButton;                 // Define lock LED pin // 定义锁 LED 引脚
bool isButtonPressed = false;           // Button pressed state // 按钮按下状态
const unsigned long debounceDelay = 50; // Debounce delay (milliseconds) // 去抖动延迟（毫秒）

void MorseSetup()
{
    // Setup and initialize Morse code input // 设置和初始化莫尔斯电码输入
    Serial.println("Morse Setup Complete");
}

// Initialize Morse code input
// 初始化摩尔斯电码输入
void Morse::init(int morseButtonPin)
{
    morseButton = morseButtonPin;
    pinMode(morseButton, INPUT_PULLUP);
    Serial.println("Morse Input Initialized");
}

// Check if the input Morse code is correct
// 检查输入的摩尔斯电码是否正确
void Morse::checkCode()
{
    // Simulate checking Morse code input
    // 模拟检查摩尔斯电码输入
    // Serial.println("Checking Morse Code");
    // return true;  // Assume input is correct

    static unsigned long lastDebounceTime = 0; // Last detection time
    // 上次检测时间

    // Read current button state
    // 读取按钮当前状态
    int buttonState = digitalRead(morseButton);

    // Detect button press and debounce
    // 检测按钮按下并消除抖动
    if (buttonState == LOW && !isButtonPressed && (millis() - lastDebounceTime > debounceDelay))
    {
        isButtonPressed = true; // Mark button as pressed
        // 标记按钮已按下
        pressStartTime = millis(); // Record press time
        // 记录按下的时间
        releaseStartTime = 0; // Clear release time
        // 清除松开时间
        lastDebounceTime = millis(); // Update debounce time
        // 更新去抖动时间
    }

    // Detect button release and debounce
    // 检测按钮松开并消除抖动
    if (buttonState == HIGH && isButtonPressed && (millis() - lastDebounceTime > debounceDelay))
    {
        isButtonPressed = false; // Mark button as released
        // 标记按钮已松开
        unsigned long pressDuration = millis() - pressStartTime; // Calculate press duration
        // 计算按下持续时间

        // Determine dot or dash based on press duration
        // 根据按下时长判断是点还是划
        if (pressDuration <= 300)
        {
            morseCode += "·"; // Short press is dot
            // 短按为点
            Serial.println("Input spot: ·");
  
        }
        else
        {
            morseCode += "-"; // Long press is dash
            // 长按为划
            Serial.println("Input Draw: -");
    
        }

        releaseStartTime = millis(); // Record release time
        // 记录松开的时间
        lastDebounceTime = millis(); // Update debounce time
        // 更新去抖动时间
    }

    // Check if input is complete (release over 2 seconds)
    // 检测输入是否完成（松开超过2秒）
    if (releaseStartTime > 0 && (millis() - releaseStartTime > 2000))
    {
        if (morseCode == correctCode)
        {
            Serial.println("Morse code is correct, unlock!");
            Serial.println("Morse code unlocked successfully"); // Output unlock success information
            // 输出解锁成功信息
            Lock::toggleLock();
            morseCode = ""; // Reset input Morse code
            // 重置输入的摩斯密码
            releaseStartTime = 0; // Reset release time
            // 重置松开时间
        }
        else
        {
            Serial.println("Morse code is incorrect, keep locked!");
            morseCode = "";       // Reset input Morse code // 重置输入的摩斯密码
            releaseStartTime = 0; // Reset release time // 重置松开时间
        }
    }
}
