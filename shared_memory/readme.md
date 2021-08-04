# 一、编译

**环境**：ubuntu 20.10 x86_64, gcc10.3.0

1、在当前目录下执行`make`。

2、将会生成`shmA`和`shmB`两个可执行文件。

# 二、运行


1、先启动`shmA`，可以看到如下打印。

> A write success
> A Is waitting
> A Is waitting

2、接着启动`shmB`，可以看到如下打印。

>  B End

- 同时`shmA`的窗口，也打印`A End`

3、也可以先启动`shmB`，在启动`shmA`。这里就不贴结果了。

4、如果出现`shmget:: File exists`报错，可查看共享内存使用情况，并释放已有的共享内存后再次运行：

- 查看共享内存`ipcs -m`
- 释放共享内存 `ipcrm -m [shmid]`

# 三、原理解释

1、先启动`shmA`进程之后，`shmA`进程会申请共享内存。并向共享内存写入字母“A”。

2、`shmA`轮询读取共享内存。如果读到B，则结束。

3、`shmB`启动之后，拿到`shmA`申请的共享内存。

4、`shmB`轮询读取共享内存，如果读到字母“A”，则向共享内存写字母“B“，退出

# 四、参考资料

https://man.gnu.org.ua/manpage/?2+shmget