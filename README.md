
```
# Project IOT Directory Structure

```plaintext
Project IOT
├─ 📁.vscode
│  └─ 📄extensions.json      // VSCode推荐扩展的配置文件
├─ 📁include
│  └─ 📄README               // 包含头文件的说明或示例
├─ 📁lib
│  └─ 📄README               // 外部库目录的说明或示例
├─ 📁src                    // 主程序代码目录
│  ├─ 📁Cloud               // 云端同步模块
│  │  ├─ 📄Cloud.cpp         // 云端同步的功能实现
│  │  └─ 📄Cloud.h           // 云端同步模块的头文件
│  ├─ 📁Config              // 配置模块
│  │  └─ 📄Config.h          // WiFi信息和云端服务配置文件
│  ├─ 📁Display             // OLED显示模块
│  │  ├─ 📄Display.cpp       // OLED显示功能实现
│  │  └─ 📄Display.h         // OLED显示模块的头文件
│  ├─ 📁Feedback            // 反馈模块
│  │  ├─ 📄Feedback.cpp      // 控制LED和蜂鸣器的功能实现
│  │  └─ 📄Feedback.h        // 反馈模块的头文件
│  ├─ 📁Fingerprint         // 指纹识别模块
│  │  ├─ 📄Fingerprint.cpp   // 指纹识别功能实现
│  │  └─ 📄Fingerprint.h     // 指纹识别模块的头文件
│  ├─ 📁Lock                // 电子锁控制模块
│  │  ├─ 📄Lock.cpp          // 电子锁的控制功能实现
│  │  └─ 📄Lock.h            // 电子锁模块的头文件
│  ├─ 📁Morse               // 莫尔斯电码模块
│  │  ├─ 📄Morse.cpp         // 莫尔斯电码解码与输入处理
│  │  └─ 📄Morse.h           // 莫尔斯电码模块的头文件
│  ├─ 📁Remote              // 远程控制模块
│  │  ├─ 📄Remote.cpp        // 远程控制解锁功能实现
│  │  └─ 📄Remote.h          // 远程控制模块的头文件
│  ├─ 📁Wifi                // WiFi模块
│  │  ├─ 📄Wifi.cpp          // WiFi连接和通信功能实现
│  │  └─ 📄Wifi.h            // WiFi模块的头文件
│  └─ 📄main.cpp             // 主程序入口，负责初始化各模块并运行主循环
├─ 📁test                   // 测试相关目录
│  └─ 📄README               // 测试目录的说明或示例
├─ 📄.gitignore              // Git忽略规则文件
└─ 📄platformio.ini          // PlatformIO项目配置文件

```