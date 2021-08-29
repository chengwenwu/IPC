# 1、项目介绍

该项目主要是linux系统进程通信示例代码，包括进程之间的通信方式，共享内存、消息队列、信号量，以及用户态和内核态之间的通信。各位有兴趣，可以一起参与贡献。

# 2、目录结构

```shell
      .
├── msg_queue //消息队列示例
├── netlink	// 通过netlink进行内核和用户态通信
│   └── unicast
├── proc	// 通过procfs进行内核和用户态通信
├── semaphore	// 信号量示例
└── shared_memory	// 共享内存示例
```

# 3、环境配置

如果您想贡献该项目，请遵从如下规范：

a、代码排版，需要遵从项目中 `.clang-format`，文件中的约束。

b、文件及目录命名使用下划线小写风格，头文件使用 `.hpp`后缀，内核相关代码请遵从内核风格。

c、其他的参考[华为c++语言编程规范](https://gitee.com/openharmony/docs/blob/master/zh-cn/contribute/OpenHarmony-cpp-coding-style-guide.md)

# 4、贡献
