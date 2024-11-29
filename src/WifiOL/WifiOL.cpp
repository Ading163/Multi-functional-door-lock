#include <Arduino.h>
#include <WiFi.h>
#include "WifiOL.h"
#include "Config/Config.h"
#include <U8g2lib.h>

int WifiOL::redLED;
int WifiOL::greenLED;
// 初始化WiFi连接
void WifiOL::init(int redLEDPin, int greenLEDPin)
{
    redLED = redLEDPin;
    greenLED = greenLEDPin;
    pinMode(redLED, OUTPUT);   // 设置红色LED引脚为输出
    pinMode(greenLED, OUTPUT); // 设置绿色LED引脚为输出
 
    // 连接到WiFi网络
    connect();
}

// 连接WiFi网络
bool WifiOL::connect()
{
    // LED闪烁逻辑
    // 连接过程中 绿灯闪烁-表示正在尝试连接，红灯熄灭
    // 连接成功后 绿灯常亮-表示连接成功，红灯熄灭
    // 连接失败后 红灯常亮-表示连接失败，绿灯熄灭
    Serial.print("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // 使用配置中的SSID和密码连接WiFi
    int attempts = 0;                     // 定义链接尝试次数
    digitalWrite(redLED, LOW);            // 熄灭红色LED

    while (WiFi.status() != WL_CONNECTED && attempts < 10)
    {
        digitalWrite(greenLED, HIGH); // 点亮绿色LED
        delay(500);
        digitalWrite(greenLED, LOW); // 熄灭绿色LED
        delay(500);
        Serial.print(".");
        attempts++;
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        digitalWrite(greenLED, HIGH); // 连接成功，绿色LED常亮
        Serial.println("Connected!");
        return true; // 连接成功
    }
    else
    {
        digitalWrite(redLED, HIGH); // 连接失败，红色LED常亮
        Serial.println("Failed to connect to WiFi.");
        switch (WiFi.status())
        {
        case WL_NO_SSID_AVAIL:
            Serial.println("Error: SSID not available.");
            break;
        case WL_CONNECT_FAILED:
            Serial.println("Error: Connection failed.");
            break;
        case WL_CONNECTION_LOST:
            Serial.println("Error: Connection lost.");
            break;
        case WL_DISCONNECTED:
            Serial.println("Error: Disconnected.");
            break;
        default:
            Serial.println("Error: Unknown error.");
            break;
        }
        return false; // 连接失败
    }
}
