// Copyright (C) 2021-2021 wuchengwen. All Rights Reserved.
// Description: 进程间通信---消息队列示例
// Author : wuchengwen <wuchw@foxmail.com>
// Date :2021-08-03

#include "msgq.hpp"
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

void ProcessA()
{
    sleep(2);
    // 获取到消息队列ID
    key_t msgqId = msgget(ftok(FILE_NAME, PROJ_ID), IPC_CREAT | IPC_EXCL | 0666);
    if (msgqId == -1) {
        perror("msgget:");
        return;
    }

    Msgbuf buf = {0};

    cout << "A: wait process B send" << endl;
    // 读取消息
    size_t ret = msgrcv(msgqId, &buf, BUFF_SIZE, 0, 0);
    if (ret == -1) {
        perror("msgrcv");
        return;
    }

    cout << "A: read from queue " << buf.mtext << endl;

    sleep(3);

    memset(&buf, 0, sizeof(buf));
    buf.mtext[0] = 'A';
    buf.mtype = 1;
    // 发送A
    ret = msgsnd(msgqId, &buf, BUFF_SIZE, 0);
    if (ret == -1) {
        perror("msgsend:");
        return;
    }
    cout << "A: send success " << buf.mtext << endl;
}

void ProcessB()
{
    key_t msgqId = msgget(ftok(FILE_NAME, PROJ_ID), 0666);
    while (msgqId == -1) {
        sleep(1);
        msgqId = msgget(ftok(FILE_NAME, PROJ_ID), 0666);
        cout << "B: waitting A create msgque" << endl;
    }

    // 向队列发送消息
    Msgbuf buf = {0};
    buf.mtype = 1;
    buf.mtext[0] = 'B';
    size_t ret = msgsnd(msgqId, &buf, BUFF_SIZE, 0);
    if (ret == -1) {
        perror("msgsend:");
        return;
    }
    cout << "B: msg send ok" << endl;

    sleep(3);

    memset(&buf, 0, sizeof(buf));
    // 从队列中读取内容
    ret = msgrcv(msgqId, &buf, BUFF_SIZE, 0, 0);
    if (ret == -1) {
        perror("msgrcv:");
        return;
    }
    cout << "B: read from queue: " << buf.mtext << endl;

    // 销毁消息队列
    ret = msgctl(msgqId, IPC_RMID, NULL);
    if (ret == -1) {
        perror("msgctrl");
    }
}

// 思路：
//      进程A：延时2秒，然后创建消息队列。阻塞式从消息队列中读取内容。
//            如果读取到B，则延时3s后向消息队列中写入A
//      进程B: 获取消息队列，向消息队列写入B,阻塞式从消息队列读取内容
//            如果读取到A,则结束
int main()
{
    pid_t pid = fork();
    if (pid == -1) {
        cout << "fork error";
        return 0;
    }
    if (pid == 0) {
        ProcessB();
    } else {
        ProcessA();
        // 等待子进程结束
        wait(nullptr);
    }
    return 0;
}