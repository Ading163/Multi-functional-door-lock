#ifndef FEEDBACK_H
#define FEEDBACK_H

// 反馈模块头文件
class Feedback {
public:
    static void init();  // 初始化反馈模块
    static void success();  // 成功反馈
    static void failure();  // 失败反馈
};

#endif // FEEDBACK_H
