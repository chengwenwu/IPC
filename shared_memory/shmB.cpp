// Copyright (C) 2021-2021 wuchengwen. All Rights Reserved.
// Description: 进程间通信--共享内存示例
// Author : wuchengwen <wuchw@foxmail.com>
// Date :2021-08-02

#include "shm.hpp"
#include <unistd.h>
#include <memory.h>
#include <iostream>

using namespace std;

// 思路：查看共享内存是否可用
// 从共享内存中读取数据，如果读取到A,则向共享内存写B.退出
int main()
{
    // 轮询等待进程A完成共享内存内存的申请，绑定共享内存
    int shmId = shmget(SHM_KEY, SHM_SIZE, 0666);

    while (shmId == -1) {
        shmId = shmget(SHM_KEY, SHM_SIZE, 0666);
        cout << "B is waitting get memory\n";
        sleep(1);
    }

    char *shmMemory = (char *)shmat(shmId, NULL, 0);

    // 轮询读取，等待进程A写数据进来
    while (memcmp(shmMemory, "A", strlen("A")) != 0) {
        cout << "B is watting for A write\n";
        sleep(1);
    }

    // 写B到共享内存
    sprintf(shmMemory, "B");
    cout << "B End\n";

    // 解除绑定
    shmdt(shmMemory);
    return 0;
}