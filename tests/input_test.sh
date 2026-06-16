#!/bin/bash

# 测试非法菜单输入和 EOF 场景，确保程序不会崩溃或死循环
set -e

echo "1. 编译项目"
make >/dev/null

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

echo "2. 输入字母 abc，应提示重新输入"
out=$(printf 'abc\n0\n' | ./library)
check "字母输入被拒绝" "输入错误，请重新输入。" "$out"

echo "3. 输入越界菜单号 99，应提示重新输入"
out=$(printf '99\n0\n' | ./library)
check "越界菜单号被拒绝" "输入错误，请重新输入。" "$out"

echo "4. 空行后再输入 0，应提示不能为空并正常退出"
out=$(printf '\n0\n' | ./library)
check "空输入被拒绝" "输入不能为空，请重新输入。" "$out"
check "正常退出" "程序已退出。" "$out"

echo "5. 输入流提前结束(EOF)，不能死循环"
# head -100 限制输出行数，万一以后又变成死循环，脚本也不会卡住
out=$(printf 'abc\n' | ./library | head -100)
check "EOF 时正常退出" "检测到输入结束，程序退出。" "$out"

if [ "$fail" -eq 0 ]; then
    echo "input_test passed."
else
    echo "input_test FAILED."
    exit 1
fi
