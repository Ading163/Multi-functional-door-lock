#ifndef LOCK_H
#define LOCK_H

// Lock module header file
class Lock {
public:
    // Initialize lock module
    static void init(int lockLedPin, int buttonPin);  // 初始化锁控模块 Morse code unlock
    static void morseCodeUnlock();  // 摩斯密码开锁  Fingerprint unlock
    static void fingerprintUnlock();  // 指纹开锁  Remote control unlock
    static void remoteControlUnlock();  // 远程开锁  Handle button press event
    static void handleButton();  // 处理按钮按下事件  Get lock state
    static bool isLockActive();  // 获取锁的状态  Toggle lock state
    static void toggleLock();  // 切换锁状态

private:
    // Lock LED pin
    static int lockLed;  // 锁 LED 引脚 Button pin
    static int button;  // 按钮引脚 Lock state
    static bool isLocked;  // 锁状态
};

#endif // LOCK_H
