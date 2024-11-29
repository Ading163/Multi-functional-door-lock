#ifndef REMOTE_H
#define REMOTE_H

// 远程控制头文件
class Remote {
public:
    static void init();  // 初始化远程控制
    static bool checkCommand();  // 检查远程指令
};

#endif // REMOTE_H
