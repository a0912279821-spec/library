#!/bin/bash

# 一次运行全部测试脚本
set -e

cd "$(dirname "$0")/.."

echo "===== smoke_test ====="
./tests/smoke_test.sh

echo ""
echo "===== input_test ====="
./tests/input_test.sh

echo ""
echo "===== validation_test ====="
./tests/validation_test.sh

echo ""
echo "===== file_test ====="
./tests/file_test.sh

echo ""
echo "All tests passed."
