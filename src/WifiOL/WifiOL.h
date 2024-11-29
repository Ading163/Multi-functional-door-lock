#ifndef WIFIOL_H
#define WIFIOL_H

// WiFi connection header file
// WiFi连接头文件

// WiFiOL class definition
class WifiOL {
public:
    // Initialize WiFi connection
    // 初始化WiFi连接
    static void init(int redLEDPin, int greenLEDPin);  

    // Connect to WiFi network
    // 连接WiFi网络
    static bool connect();  

private:
    // Red LED pin
    // 红色LED引脚
    static int redLED;  
  
    // Green LED pin
    // 绿色LED引脚
    static int greenLED;  
 
};

#endif // WIFIOL_H
// 结束WiFiOL_H
