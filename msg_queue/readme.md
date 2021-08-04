# 一、编译

**环境**：ubuntu 20.10 x86_64, gcc10.3.0

1、在当前目录下执行`make`。

2、将会生成可执行文件`msgq`。

# 二、运行

1、启动`msgq`，可以看到如下打印。

> B: waitting A create msgque
> A: wait process B send
> B: waitting A create msgque
> B: msg send ok
> A: read from queue B
> A: send success A
> B: read from queue: A



4、如果出现`msgget:: File exists`报错，可查看消息队列使用情况，并销毁已有的消息队列后再次运行：

- 查看消息队列`ipcs -q`
- 销毁消息队列 `ipcrm -q [msqid]`

# 三、原理解释

1、首先fork创建子进程，执行ProcessB。父进程执行ProcessA。

2、ProcessA：

- 延时2秒，然后创建消息队列。阻塞式从消息队列中读取内容。
- 如果读取到内容，则打印并延时3s后向消息队列中写入字母`A`;

3、ProcessB：

- 获取消息队列，向消息队列写入B，阻塞式从消息队列读取内容

- 如果读取到内容，则打印，销毁消息队列，结束。

# 四、参考资料

https://man7.org/linux/man-pages/man2/wait.2.html

https://man7.org/linux/man-pages/man2/msgctl.2.html