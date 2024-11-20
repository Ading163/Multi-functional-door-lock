#include <WiFi.h> // 引入WiFi库
#include <Config/Config.h>

void WifiSetup() {
    Serial.println("Initializing WiFi...");
    
    // WiFi网络信息从配置文件获取
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
    
    // 等待WiFi连接
    int retryCount = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print("Connecting to WiFi");
        for (int i = 0; i <= retryCount; i++) {
            Serial.print(".");
        }
        Serial.println();
        retryCount++;
        
        // 如果尝试超过一定次数，重新启动WiFi
        if (retryCount >= 10) {
            Serial.println("Failed to connect. Restarting WiFi setup...");
            retryCount = 0;
            WiFi.disconnect();
            delay(2000);
            WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        }
    }
    
    // WiFi连接成功
    Serial.println("Connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP()); // 打印分配的IP地址
}