// Copyright (C) 2021-2021 wuchengwen. All Rights Reserved.
// Description: 共享内存共用头文件
// Author : wuchengwen <wuchw@foxmail.com>
// Date :2021-08-02

#pragma once

#include <sys/shm.h>

const key_t SHM_KEY = 1;
const size_t SHM_SIZE = 2;