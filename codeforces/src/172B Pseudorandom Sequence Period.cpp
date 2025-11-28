//
// Created by Psy.C on 2025/11/28.
//
/*
*a, b, m: 线性同余生成器参数
r: 当前随机数/状态值
flag[N]: 标记数组，记录每个值出现的位置
i: 循环计数器
*a: 乘数
b: 增量
m: 模数
r: 初始种子值
 *
*循环生成随机数序列（最多1亿次）：
使用线性同余公式：r = (a * r + b) % m 生成下一个数
检查这个数是否之前出现过（flag[r]非零）
如果出现过，跳出循环
否则记录这个数在第i次出现
 *输出循环周期长度：当前次数减去第一次出现该值的位置
 *线性同余生成器（LCG）公式：X(n+1) = (a * X(n) + b) % m
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+10;
int a, b, m, r, flag[N], i;

int main() {
    fast;
    cin>>a>>b>>m>>r;
    for (i = 1; i <= 1e8; ++i) {
        r = (a * r + b) % m;
        if (flag[r]) break;
        flag[r] = i;
    }
    cout << i - flag[r] << '\n';
    return 0;
}