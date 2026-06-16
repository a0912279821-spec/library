#!/bin/bash

# 测试 books.txt 损坏场景，确保程序不崩溃、不读入脏数据
# 重要：测试会临时修改 books.txt，结束时自动恢复，不会破坏用户数据
set -e

echo "1. 编译项目"
make >/dev/null

# 先备份真实数据，并设置“退出时自动恢复”（即使测试中途失败也会恢复）
cp books.txt books.txt.bak
restore() {
    mv books.txt.bak books.txt
    echo "已恢复原始 books.txt"
}
trap restore EXIT

# 小工具：检查程序输出里是否包含期望的提示文字
fail=0
check() {   # 用法: check "说明" "期望出现的文字" "实际输出"
    if echo "$3" | grep -q "$2"; then
        echo "  通过: $1"
    else
        echo "  失败: $1 (没有看到: $2)"
        fail=1
    fi
}

echo "2. 空文件，应提示格式不正确"
: > books.txt
out=$(printf '0\n' | ./library)
check "空文件被识别" "books.txt 格式不正确" "$out"

echo "3. 首行非法(字母)，应提示格式不正确"
printf 'abc\n' > books.txt
out=$(printf '0\n' | ./library)
check "首行非法被识别" "books.txt 格式不正确" "$out"

echo "4. 数量超大(999999)，应提示且不崩溃"
printf '999999\n' > books.txt
out=$(printf '0\n' | ./library)
check "数量超大被拦截" "books.txt 格式不正确" "$out"

echo "5. 内容不完整(声明3条只给1条)，应提示数据不完整"
printf '3\n1001\nC语言\n谭浩强\n清华\n39.80 10 10 1\n' > books.txt
out=$(printf '0\n' | ./library)
check "内容不完整被识别" "books.txt 数据不完整" "$out"

if [ "$fail" -eq 0 ]; then
    echo "file_test passed."
else
    echo "file_test FAILED."
    exit 1
fi
