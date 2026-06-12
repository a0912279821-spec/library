#!/bin/bash

set -e

echo "1. 清理旧的编译文件"
make clean

echo "2. 编译项目"
make

echo "3. 测试程序能否正常启动并退出"
printf "0\n" | ./library

echo "Smoke test passed."
