#pragma once

#include <linux/netlink.h>

#define NETLINK_TEST 30
#define MSG_LEN 125
#define MAX_PLOAD 125
#define USER_PORT 100

typedef struct {
    struct nlmsghdr hdr;
    char msg[MSG_LEN];
} UserMsgInfo;