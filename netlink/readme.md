netlink是linux内核和用户态程序通信的机制之一，内核可以使用unicast的方式进行单播通信，也可以brocast形式的广播通信，目前只实现了单播通信示例。

# 一、编译

1、在unicast当前目录下执行 `make`，将会得到 `kernel_code.ko`文件

2、使用 `gcc userspace.cpp -o main`  编译用户态代码，得到 `main`。

# 二、运行

1、使用命令 `sudo insmod kernel_code.ko`将内核模块插入到内核。

2、`./main`执行用户态程序，可以看到如下内容的打印。

> send kernel:hello netlink!!
> from kernel:hello users!!!

3、执行 `sudo dmesg -c` 查看并清除内核log。可以看到有如下记录：

> test_netlink_init
> kernel recv from user: hello netlink!!

4、结束后，调用 `sudo rmmod kernel_code` 卸载内核模块。

# 三、原理解释

1、用户态进程通过netlink发送 `hello netlink!!` 给内核。

2、内核调用函数 `netlink_rcv_msg`接收数据，并调用 `send_usrmsg` 发送字符串 `hello users!!!`回应。

# 四、参考资料

[https://man7.org/linux/man-pages/man7/netlink.7.html]()
