#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <U8g2lib.h>

#include "Morse/Morse.h"
#include "Fingerprint/Fingerprint.h"
#include "Remote/Remote.h"
#include "Lock/Lock.h"
#include "Display/Display.h"
#include "Feedback/Feedback.h"
#include "Cloud/Cloud.h"
#include "WifiOL/WifiOL.h"
#include "Ultrasonic/Ultrasonic.h"

// Define LED pins  定义LED引脚
int redLED = 14;         // Red LED for indicating WiFi not connected 红色LED用于指示WiFi未连接
int greenLED = 12;       // Green LED for indicating WiFi connected 绿色LED用于指示WiFi已连接
int lockLed = 13;        // Lock LED pin - currently using LED as substitute for lock 锁LED连接的引脚-目前没有锁 所以用led等代替
int buttonPin = 27;      // Button piN  按钮连接的引脚
int morseButtonPin = 33; // Morse code button pi // 摩斯密码按钮引脚
int trigPin = 15;       // Trigger pin for ultrasonic sensor 定义超声波传感器的触发引脚
int echoPin = 2;        // Echo pin for ultrasonic sensor 定义超声波传感器的回声引脚

// Initialize all components
// 初始化所有组件
void initializeComponents()
{
  Display::init();
  // Initialize display module
  // 初始化显示模块
  Fingerprint::init();
  // Initialize fingerprint module
  // 初始化指纹识别模块
  Feedback::init();
  // Initialize feedback module
  // 初始化反馈模块】
  Lock::init(lockLed, buttonPin);
  // Initialize lock module
  // 初始化锁控模块
  Morse::init(morseButtonPin);
  // Initialize Morse code input module
  // 初始化摩尔斯电码输入模块
  Remote::init();
  // Initialize remote control module
  // 初始化远程控制模块
  WifiOL::init(redLED, greenLED);
  // Initialize WiFi module
  // 初始化WiFi模块
  Cloud::init();
  // 初始化超声波模块
  Ultrasonic::init(trigPin, echoPin);
}

// Setup function
// 启动函数
void setup()
{
  // Start serial communication at 115200 baud
  // 启动串口通信，波特率为115200
  Serial.begin(115200);

  // 初始化显示模块
  Display::init();
  Serial.print("正在启动");
  Display::showMessage("System startup...");
  delay(1000);
  // Initialize all modules
  // 初始化所有模块
  initializeComponents();
  // Show initialization complete message
  // 显示初始化完成消息
  Display::showInitializationComplete();
  delay(2000);
}

// Main loop function
// 主循环函数
void loop()
{
  // Handle button press events
  // 处理按钮按下事件
  Lock::handleButton();
  // 显示当前门锁状态和超声波测距结果 true表示上锁 false表示解锁
  Display::showDistance(Lock::isLockActive() ? true : false, Ultrasonic::getDistance());
  if (Lock::isLockActive())
  {

    // Check Morse code unlock conditionmm
    // 检查摩斯密码解锁条件
    Lock::morseCodeUnlock();

    //  Check remote control unlock condition
    //  检查远程控制解锁条件
    // Lock::remoteControlUnlock();
  }

  delay(100);
}