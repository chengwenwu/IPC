// Copyright (C) 2021-2021 wuchengwen. All Rights Reserved.
// Description: 进程间通信--共享内存示例
// Author : wuchengwen <wuchw@foxmail.com>
// Date :2021-08-02

#include <iostream>
#include <unistd.h>
#include <memory.h>
#include <errno.h>
#include "shm.hpp"

using namespace std;
// 思路：该进程A创建一个共享内存，并向内存中写入A。
// 轮询共享内存，等待进程B,写入B。这边读取到B之后结束
int main()
{
    // 获取共享内存
    int shmId = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
    if (shmId == -1) {
        perror("shmget:");
        return 0;
    }

    // 绑定共享内存地址
    char *shmMemory = (char *)shmat(shmId, NULL, 0);

    // 向共享内存写数据
    sprintf(shmMemory, "A");
    cout << "A write success\n";

    // 轮询读取，等待进程B,写B进来
    while (memcmp(shmMemory, "B", strlen("B")) != 0) {
        cout << "A Is waitting\n";
        sleep(1);
    }

    cout << "A End\n";

    // 解绑内存
    shmdt(shmMemory);

    // 释放共享内存
    shmctl(shmId, IPC_RMID, NULL);
    return 0;
}