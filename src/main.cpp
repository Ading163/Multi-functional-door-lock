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

// Define LED pins  定义LED引脚
int redLED = 14;         // Red LED for indicating WiFi not connected 红色LED用于指示WiFi未连接
int greenLED = 12;       // Green LED for indicating WiFi connected 绿色LED用于指示WiFi已连接
int lockLed = 13;        // Lock LED pin - currently using LED as substitute for lock 锁LED连接的引脚-目前没有锁 所以用led等代替
int buttonPin = 27;      // Button piN  按钮连接的引脚
int morseButtonPin = 33; // Morse code button pi // 摩斯密码按钮引脚
uint64_t fullChipId;     // 存储完整的 64 位 MAC 地址
uint32_t shortChipId;    // 存储低 24 位短 ID
// 使用 U8g2 库初始化 OLED 显示屏，I2C 地址为 0x3C
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
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
  // Initialize cloud communication module
  // 初始化云通信模块
}

// Setup function
// 启动函数
void setup()
{
  // Start serial communication at 115200 baud
  // 启动串口通信，波特率为115200
  Serial.begin(115200);
  // 获取完整的 64 位 eFuse MAC 地址
  fullChipId = ESP.getEfuseMac();

  // 提取低 24 位（短 ID）
  shortChipId = (uint32_t)(fullChipId & 0xFFFFFF);
  // 初始化 OLED 屏幕
  u8g2.begin();
  u8g2.enableUTF8Print(); // 启用 UTF-8 支持
  // 显示启动提示并加载进度条
  u8g2.setFont(u8g2_font_ncenB08_tr); // 设置更大的字体
                                      // 连接到 Wi-Fi 网络
  Serial.print("正在启动");
  for (int i = 0; i <= 10; i++)
  {
    u8g2.clearBuffer(); // 清除显示缓冲区
    u8g2.setCursor(10, 20);
    u8g2.print("System startup");

    // 绘制一个小图标，例如一个小太阳表示启动
    u8g2.drawCircle(110, 10, 5, U8G2_DRAW_ALL);

    // 绘制进度条边框
    u8g2.drawFrame(10, 30, 108, 10);

    // 绘制进度条
    u8g2.drawBox(10, 30, i * 10, 10);

    u8g2.sendBuffer(); // 将缓冲区内容发送到显示器
    delay(300);        // 延迟以创建动画效果
  }

  // Initialize all modules
  // 初始化所有模块
  initializeComponents();

  // 显示初始化完成信息
  u8g2.clearBuffer();
  u8g2.setCursor(10, 20);
  u8g2.print("Start Done!");

  // // 设置较小的字体以显示 MAC 地址和 UUID
  u8g2.setFont(u8g2_font_6x10_tf);

  u8g2.setCursor(10, 35);
  u8g2.print("ID:");
  u8g2.printf("%06X", shortChipId); // 使用 printf 格式化输出 shortChipId

  // 将光标移动到下一行显示完整的 MAC 地址
  u8g2.setCursor(10, 45);
  u8g2.print("MAC:");
  u8g2.printf("%08X%08X", (uint32_t)(fullChipId >> 32), (uint32_t)fullChipId); // 使用 printf 格式化输出 fullChipId(fullChipId >> 32), (uint32_t)fullChipId);

  // 添加一个小图标，例如一个勾表示完成
  u8g2.drawDisc(110, 10, 5, U8G2_DRAW_ALL);

  u8g2.sendBuffer();
  delay(2000); // 显示2秒钟
}

// Main loop function
// 主循环函数
void loop()
{

  // Handle button press events
  // 处理按钮按下事件
  Lock::handleButton();

  if (Lock::isLockActive())
  {
    // Check Morse code unlock condition
    // 检查摩斯密码解锁条件
    Lock::morseCodeUnlock();
    //  Check fingerprint unlock condition
    //  检查指纹解锁条件
    // Lock::fingerprintUnlock();

    //  Check remote control unlock condition
    //  检查远程控制解锁条件
    // Lock::remoteControlUnlock();
  }

  // Add small delay to avoid excessive processing
  // 添加小延迟，避免过度处理
  delay(100);
}