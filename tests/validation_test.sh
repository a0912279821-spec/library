#!/bin/bash

# 测试添加/修改图书时的价格、数量和推荐状态校验
# 重要：测试会临时修改 books.txt，结束时自动恢复，不会破坏用户数据
set -e

echo "1. 编译项目"
make >/dev/null

backup_file=$(mktemp)
cp books.txt "$backup_file"
restore() {
    cp "$backup_file" books.txt
    rm -f "$backup_file"
    echo "已恢复原始 books.txt"
}
trap restore EXIT

fail=0
check() {   # 用法: check "说明" "期望出现的文字" "实际输出"
    if echo "$3" | grep -Fq "$2"; then
        echo "  通过: $1"
    else
        echo "  失败: $1 (没有看到: $2)"
        fail=1
    fi
}

echo "2. 添加图书时，应拒绝负数价格、负数总量和非法推荐状态"
out=$(printf '1\n9001\n测试书\n测试作者\n测试出版社\n-1\n23.50\n-3\n2\n2\n1\n0\n' | ./library)
check "添加时拒绝负数价格" "价格不能小于0" "$out"
check "添加时拒绝负数总量" "图书总量不能小于0" "$out"
check "添加时拒绝非法推荐状态" "推荐状态只能输入 0 或 1" "$out"
if grep -Fq "23.50 2 2 1" books.txt; then
    echo "  通过: 添加后保存了合法数据"
else
    echo "  失败: 添加后没有保存预期的合法数据"
    fail=1
fi

echo "3. 修改图书时，应拒绝负数价格、过小总量和非法推荐状态"
cat > books.txt <<'DATA'
1
9100
旧书名
旧作者
旧出版社
10.00 3 1 0
DATA
out=$(printf '5\n9100\n新书名\n新作者\n新出版社\n-5\n15.00\n1\n2\n3\n0\n0\n' | ./library)
check "修改时拒绝负数价格" "价格不能小于0" "$out"
check "修改时拒绝小于已借出数量的总量" "不能小于已借出数量" "$out"
check "修改时拒绝非法推荐状态" "推荐状态只能输入 0 或 1" "$out"
if grep -Fq "15.00 2 0 0" books.txt; then
    echo "  通过: 修改后库存保持已借出数量"
else
    echo "  失败: 修改后没有保存预期的合法数据"
    fail=1
fi

if [ "$fail" -eq 0 ]; then
    echo "validation_test passed."
else
    echo "validation_test FAILED."
    exit 1
fi
