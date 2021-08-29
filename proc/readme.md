# 一、编译

直接执行 `make` 会生成可执行文件 `procfs`

# 二、运行

**注意：** 该程序需要在root权限下运行，并且会修改系统配置，即将系统能够打开的最大文件数量会减一。

`./procfs` 可以看到如下打印：

> Linux version 5.11.0-31-generic (buildd@lcy01-amd64-009) (gcc (Ubuntu 10.3.0-1ubuntu1) 10.3.0, GNU ld (GNU Binutils for Ubuntu) 2.36.1)#33-Ubuntu SMP Wed Aug 11 13:19:04 UTC 2021

> file-max: 9223372036854775807

# 三、原理解释

- 该程序主要演示了，通过 `进程文件系统` (即 `procfs`)，在用户态查看和修改内核相关参数。
- 首先我们读取了文件 ``/proc/version`` 来查看系统版本信息。
- 接着我们读取了文件 `/proc/sys/fs/file-max` 来查看系统所能够打开的最大文件数量，并将该数量减一后再次写入文件中。
- 通过命令 `cat /proc/sys/fs/file-max` 我们可以看到修改文件成功了。
- 如果想要将上述修改复原，使用命令 `echo file-max > /proc/sys/fs/file-max`， 重写文件内容即可。这里 `file-max`是 `二` 中打印出来的 `file-max:`后面的那串数字。

# 四、参考资料

- [官方文档介绍]([https://man7.org/linux/man-pages/man5/proc.5.html]())
- [cnblogs教程](https://www.cnblogs.com/bakari/p/10966303.html)
