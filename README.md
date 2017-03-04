# Mini-Search

A mini search engine based on Echo\-Server, a non\-blocking network library in C++ on Linux.

---

## 1 简介

这是一个基于 [Echo-Server][1] 网络库的文本查询服务，用户在客户端输入某个词后，从服务端返回与这个词最相似的候选词集。

## 2 用到的一些关键技术及优化

-   Echo\-Server 网络库。
-   建立词库。
-   计算最小编辑距离
-   对每个字母建立一个索引项，可以减小候选词的范围，从而减少计算编辑距离的次数。
-   根据索引项，将所有用户搜索词每个字母对应的索引项求并集，组成候选词库。
-   通过将用户搜索的词长度与词库中符合要求的词的长度相减后求绝对值，若这个值大于指定的编辑距离值，则舍去。
此法可有效减少编辑距离的次数。
-   将不大于指编辑距离的，候选词集，加入优先队列中。且将那些编辑距离小，词频大的词放在优先队列的前面。
-   采取的是 LRU 机制，以双链表为底层结构。用户搜索的词最先在 cache 中查找，若找到了，立即返回对应的候选词库；若未找到，则从候选词库中获取，并写至 cache 中。
-   cache 初始化是指服务器启动的时候，从文件中所有项目读入cache中。定时回写采取的是将 cache 中的所有项而非某个项写回文件，原因在于考虑到服务器宕机的情况。文件 I/O 效率太低，可以考虑用数据库的方法，而且这里采用的是单 cache，可以考虑用多 cache 提高效率。

## 3 编译

首先安装好 Echo\-Server。

然后执行如下命令将项目下载到本地：

`git clone https://github.com/cuckootan/Mini-Search`

该项目提供了 **makefile** 文件，因此可以直接进行编译安装。切换至 **Mini-Search** 目录，执行如下命令即可：

`make`

除此之外，还提供了通过 **cmake** 生成 makefile 文件的编译方式。切换至 **Mini-Search** 目录，执行如下命令：

`mkdir build && cd build`

`cmake ..`

`make`

生成的可执行文件在 **${PROJECT_DIR}/bin** 中。

## 4 测试

-   首先设定好服务端的端口号，然后启动服务端。
-   然后在客户端上运行 **telnet** 命令进行测试：

    `telnet SERVER_IP SERVER_PORT`
-   输入一个英文单词，随即会返回与这个词最相似的多个候选词。



  [1]: https://github.com/cuckootan/Echo-Server
