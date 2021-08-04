// Copyright (C) 2021-2021 wuchengwen. All Rights Reserved.
// Description: 消息队列头文件
// Author : wuchengwen <wuchw@foxmail.com>
// Date :2021-08-04

#pragma once

#include <string.h>

const char *FILE_NAME = "./msgq_file";
const char PROJ_ID = 'A';
const size_t BUFF_SIZE = 2;

struct Msgbuf {
    long mtype;
    char mtext[2];
};