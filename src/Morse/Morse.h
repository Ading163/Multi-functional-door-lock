#ifndef MORSE_H
#define MORSE_H

// Morse code header file
// 莫尔斯电码头文件
class Morse {
public:
    static void init(int morseButtonPin) ;  // Initialize Morse code input // 初始化摩尔斯电码输入
    static void checkCode();   // Check if the input Morse code is correct // 检查输入的摩尔斯电码是否正确
private:
    static int morseButton;  // Morse code button pin // 摩斯密码按钮引脚
};

#endif // MORSE_H
// 结束MORSE_H
