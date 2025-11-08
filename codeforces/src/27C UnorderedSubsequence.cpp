//
// Created by Psy.C on 2025/9/20.
//
/*
 *
*从索引0开始遍历到n-2（确保i+1不越界）
检查条件：(a[i + 1] - a[i]) * (a[i] - a[0]) < 0
这个条件判断三个元素a[0]、a[i]、a[i+1]是否形成"驼峰"形状
即a[i]是局部极值点：要么a[0] < a[i] > a[i+1]，要么a[0] > a[i] < a[i+1]
当两个因子异号时乘积小于0，说明找到了这样的点
找到符合条件的索引i后赋值给ind并跳出循环
 *
 *
 *
 *
 *
*输出格式：第一行是元素个数3，第二行是三个元素的位置（1-indexed）
位置分别是：1（第一个元素）、ind+1（中间元素）、ind+2（最后一个元素）
 *
 *
 *
 *
 */
#include <cstdio>
#include <vector>
using namespace std;

int main() {

    long n; scanf("%ld", &n);
    if (n <= 2) {
        puts("0");
        return 0;
    }

    vector<long long> a(n);
    for (long i = 0; i < n; ++i) scanf("%lld", &a[i]);

    long ind(-1);//存储找到的中间元素索引
    for (long i = 0; i + 1 < n; ++i) {
        if ((a[i + 1] - a[i]) * (a[i] - a[0]) < 0) {
            ind = i;
            break;
        }
    }

    if (ind < 0) puts("0");
    else printf("3\n1 %ld %ld\n", ind + 1, ind + 2);
    
    return 0;
}