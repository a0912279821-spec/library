# 图书管理系统

## 项目简介

这是一个基于 C 语言实现的命令行图书管理系统，适合作为 C 语言课程项目。项目支持图书信息管理、借书还书、文件保存读取等功能。

## 功能列表

- 添加图书
- 显示所有图书
- 查询图书
- 删除图书
- 修改图书信息
- 借书
- 还书
- 文件保存与读取
- 预算购书推荐

## 技术栈

- C 语言
- 结构体
- 文件读写
- 函数模块化
- 基础数据处理

## 运行截图

![图书管理系统运行菜单](assets/menu.png)

## 如何运行

### 1. 下载项目

如果还没有下载项目，可以在 Mac 终端中输入：

```bash
cd Desktop
git clone https://github.com/a0912279821-spec/library.git
cd library
```

如果已经下载过项目，只需要进入项目文件夹：

```bash
cd Desktop/library
```

### 2. 查看项目文件

```bash
ls
```

正常情况下可以看到：

```text
README.md
books.txt
include
src
Makefile
```

### 3. 编译程序

项目已拆分为多个文件，推荐使用 Makefile 一键编译：

```bash
make
```

其中：

- `make` 会读取 `Makefile`，编译 `src/` 目录下所有 `.c` 文件
- `-Iinclude` 让编译器找到 `include/library.h` 头文件
- 最终生成名为 `library` 的可执行程序

### 4. 运行程序

```bash
./library
```

运行后会出现菜单：

```text
==== 图书管理系统 ====
1.添加图书
2.显示全部图书
3.查询图书
4.删除图书
5.修改图书
6.借书
7.还书
8.预算购书推荐
0.退出系统
请输入你的选择:
```

输入对应数字即可使用功能，例如输入 `2` 可以显示全部图书，输入 `0` 可以退出系统。

## 测试

项目提供了一个简单的 smoke test，用来检查项目能否正常清理、编译、启动并退出。

运行命令：

    ./tests/smoke_test.sh

正常情况下会看到：

    Smoke test passed.

## 项目文件

```text
library/
├── include/
│   └── library.h      # 头文件：max 宏、Book 结构体、函数声明
├── src/
│   ├── main.c         # 主程序：main 函数与菜单分发
│   └── library.c      # 业务逻辑实现与全局变量定义
├── README.md          # 项目说明文档
├── books.txt          # 示例图书数据文件
├── .gitignore         # Git 忽略配置
├── Makefile           # 编译运行脚本
└── tests/             # 测试脚本目录
```

## 我学到了什么

通过这个项目，我练习了：

- 如何使用结构体保存图书信息
- 如何用函数拆分不同功能
- 如何处理用户输入
- 如何进行文件保存和读取
- 如何把一个课程作业整理成 GitHub 项目
- 如何使用 Git 分支、commit、push 和 pull request 完成一次项目修改

## 后续改进计划

- [x] 增加示例数据文件
- [x] 修复库存更新逻辑
- [x] 添加 Mac 编译运行教程
- [x] 增加运行截图
- [x] 把单个 C 文件拆分成多个文件
- [x] 增加 Makefile
