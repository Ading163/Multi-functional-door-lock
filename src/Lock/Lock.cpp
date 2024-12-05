#include <Arduino.h>
#include "Lock.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <U8g2lib.h>

#include "Morse/Morse.h"
#include "Fingerprint/Fingerprint.h"
#include "Remote/Remote.h"
#include "Display/Display.h"
#include "Feedback/Feedback.h"
#include "Cloud/Cloud.h"
#include "WifiOL/WifiOL.h"

// 音符频率定义
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523

// 旋律音符
int melody[] = {
    NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
    NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4,
    NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
    NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
    NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
    NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4};

// 每个音符的持续时间（单位：ms）
int noteDurations[] = {
    500, 500, 500, 500, 500, 500, 1000,
    500, 500, 500, 500, 500, 500, 1000,
    500, 500, 500, 500, 500, 500, 1000,
    500, 500, 500, 500, 500, 500, 1000,
    500, 500, 500, 500, 500, 500, 1000,
    500, 500, 500, 500, 500, 500, 1000};

// 定义锁 LED 引脚
// Define lock LED pin
int Lock::lockLed;
// 定义按钮引脚
// Define button pin
int Lock::button;

// 定义锁的初始状态，默认为上锁
// Define initial lock state, true means locked
bool Lock::isLocked = true;

/**
 * Initialize lock module
 * 初始化锁控模块
 * @param lockLedPin Lock LED pin
 * @param buttonPin Button pin
 */
void Lock::init(int lockLedPin, int buttonPin)
{
    lockLed = lockLedPin;                         // Initialize lock LED pin // 初始化锁 LED 引脚
    button = buttonPin;                           // Initialize button pin // 初始化按钮引脚
    pinMode(lockLed, OUTPUT);                     // Set lock LED pin as output mode // 设置锁 LED 引脚为输出模式
    pinMode(button, INPUT_PULLUP);                // Set button pin as input mode with pull-up resistor // 设置按钮引脚为输入模式，并启用上拉电阻
    digitalWrite(lockLed, isLocked ? HIGH : LOW); // Light up or turn off lock LED based on lock state // 根据锁的状态点亮或熄灭锁 LED
    Serial.println("Lock Initialized");           // Output initialization complete message // 输出初始化完成消息
}


/**
 * Toggle lock state
 * 切换锁的状态
 */
void Lock::toggleLock()
{
    isLocked = !isLocked;                             // Toggle lock state // 切换锁的状态
    Serial.println(isLocked ? "Locked" : "Unlocked"); // Output lock state information // 输出锁状态信息
    digitalWrite(lockLed, isLocked ? HIGH : LOW);     // Update lock LED based on new lock state // 根据新的锁状态更新锁 LED
}

/**
 * Handle button press event
 * 处理按钮按下事件
 */
void Lock::handleButton()
{
    static unsigned long lastPressTime = 0; // Record last button press time // 记录上次按钮按下的时间
    unsigned long currentTime = millis();   // Get current time // 获取当前时间

    if (digitalRead(button) == LOW)
    { // Detect if button is pressed // 检测按钮是否被按下
        if (currentTime - lastPressTime > 1000)
        {                                                          // Check if press interval is over 1 second // 检查按下间隔是否超过 1 秒
            Serial.println("Button pressed, toggling lock state"); // Output button press information // 输出按钮按下信息
            toggleLock();                                          // Toggle lock state  // 切换锁的状态
            lastPressTime = currentTime;                           // Update last press time // 更新上次按下时间
        }
        else
        {
            Serial.println("Button pressed too frequently, ignoring"); // Output frequent click information // 输出点击过于频繁信息
        }
        while (digitalRead(button) == LOW)
        {              // Wait for button release // 等待按钮松开
            delay(10); // Simple debounce // 简单去抖动
        }
    }
}

/**
 * Morse code unlock
 * 摩斯密码解锁
 */
void Lock::morseCodeUnlock()
{
    Morse::checkCode(); // Check Morse code input // 检查摩斯密码输入
}

/**
 * Fingerprint unlock
 * 指纹解锁
 */
void Lock::fingerprintUnlock()
{
}

/**
 * Remote control unlock
 * 远程控制解锁
 */
void Lock::remoteControlUnlock()
{
    // Placeholder for remote control unlock logic // 远程控制解锁逻辑占位符
}

/**
 * Return lock state
 * 返回锁的状态
 */
bool Lock::isLockActive()
{
    return isLocked; // Return current lock state // 返回当前锁状态
}
