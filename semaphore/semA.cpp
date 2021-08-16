#include <iostream>
#include "sem.hpp"

using namespace std;

int main()
{
    // 获取共享内存
    int shmId = shmget(ftok(SHM_FILE, PROJ_ID), SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
    if (shmId == -1) {
        perror("shmget:");
        return 0;
    }

    // 绑定共享内存地址
    char *shmMemory = (char *)shmat(shmId, NULL, 0);

    // 获取信号量，并设置默认值
    int semIdR = CreateSem(A_READ_FILE, 0);
    int semIdW = CreateSem(A_WRITE_FILE, 0);
    if (semIdR == -1 || semIdW == -1) {
        perror("CreateSem:");
        return -1;
    }

    sleep(3);

    // 向共享内存写数据
    sprintf(shmMemory, "A");
    if (SemV(semIdW) == -1) {
        perror("SemV w error:");
        return 0;
    }
    cout << "A write success\n";

    // 等待进程B,写B进来
    if (SemP(semIdR) == -1) {
        perror("SemV R error:");
        return 0;
    }
    if (memcmp(shmMemory, "B", strlen("B")) == 0) {
        cout << "read from mem: " << shmMemory << endl;
    }

    cout << "A End\n";

    // 解绑内存
    shmdt(shmMemory);

    // 释放信号量
    semctl(semIdR, 0, IPC_RMID);
    semctl(semIdW, 0, IPC_RMID);

    // 释放共享内存
    shmctl(shmId, IPC_RMID, NULL);
    return 0;
}