//
// Created by Psy.C on 2025/9/24.
//
/*
*cur初始化为1，表示当前期望找到的数字
v是一个long类型的vector，用于存储符合条件的索引
读取输入n，表示数组元素个数
 *
*循环读取n个数字
对于每个数字x，检查是否等于当前期望值cur
如果相等：
将当前索引i添加到向量v中
递增cur，表示下一个期望的数字
 *
 *
*遍历向量v中的每个元素
输出s + v[i]（即2001加上原始索引）
puts("")输出一个换行符
 *
 *
 */
#include <cstdio>
#include <vector>
using namespace std;

const long s = 2001;

int main() {
    long cur(1);
    vector<long> v;
    long n; scanf("%ld", &n);

    for (long i = 0; i < n; ++i) {
        long x; scanf("%ld", &x);
        if (x == cur) {
            v.push_back(i);
            ++cur;
        }
    }
    printf("%ld\n", v.size());

    for (long i = 0; i < v.size(); ++i) {
        printf("%ld ", s + v[i]);
    }
    puts("");

    return 0;
}