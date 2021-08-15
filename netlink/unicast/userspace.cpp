#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include "netlink_com.h"

int main()
{
    const char *umsg = "hello netlink!!";

    /* 创建NETLINK socket */
    int skfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_TEST);
    if (skfd == -1) {
        perror("create socket error\n");
        return -1;
    }

    struct sockaddr_nl saddr = {0};
    saddr.nl_family = AF_NETLINK; //AF_NETLINK
    saddr.nl_pid = USER_PORT;     //端口号(port ID)
    if (bind(skfd, (struct sockaddr *)&saddr, sizeof(saddr)) != 0) {
        perror("bind() error\n");
        close(skfd);
        return -1;
    }

    struct sockaddr_nl daddr = {0};
    daddr.nl_family = AF_NETLINK;

    UserMsgInfo sendMsg = {0};
    sendMsg.hdr.nlmsg_len = sizeof(UserMsgInfo);
    sendMsg.hdr.nlmsg_pid = saddr.nl_pid; //self port

    memcpy(sendMsg.msg, umsg, strlen(umsg));
    ssize_t ret = sendto(skfd, &sendMsg, sendMsg.hdr.nlmsg_len, 0, (struct sockaddr *)&daddr, sizeof(struct sockaddr_nl));
    if (!ret) {
        perror("sendto error\n");
        close(skfd);
        exit(-1);
    }
    printf("send kernel:%s\n", umsg);

    UserMsgInfo info = {0};
    socklen_t len = sizeof(sockaddr_nl);
    ret = recvfrom(skfd, &info, sizeof(UserMsgInfo), 0, (struct sockaddr *)&daddr, &len);
    if (!ret) {
        perror("recv form kernel error\n");
        close(skfd);
        exit(-1);
    }

    printf("from kernel:%s\n", info.msg);
    close(skfd);
    return 0;
}