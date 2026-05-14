g++ maker.cpp -o maker -std=c++23 -O2 -Wall -static
g++ std.cpp -o std -std=c++23 -O2 -Wall -static
g++ a.cpp -o a -std=c++23 -O2 -Wall -static -DDEBUG
for ((i = 1; i <= 10000; i++)); do
    ./maker > 1.in
    ./std < 1.in > 1.out
    ./a < 1.in > std.out

    if ! diff -Z 1.out std.out; then
        echo "测试失败，错误数据保存在 1.in"
        exit 1
    fi

    echo "测试通过：第 $i 次"
done

echo "所有测试通过"

