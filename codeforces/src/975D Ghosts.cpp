//
// Created by Psy.C on 2026/10/22.
//
/**
n：数据条数；a, b：从输入读入的两个参数（用于直线族 y = a*x + b，但代码只用到 a）。
x, y：单条数据的坐标。
ans：结果计数。
mp：map< key, map<x, count> >——外层 key 为 a*x - y，内层为横坐标 x 到该 key 下这个横坐标出现次数的映射
读入 n, a, b。
循环 n 次：scanf("%*d%lld%lld", &x, &y) —— %*d 表示读入但丢弃一个整数（题意是每条数据第一项无用处，可能是指明文/编号等），再读入 x、y。
mp[a*x-y][x]++：key 取 a*x - y，内层按横坐标 x 计数 +1
mp | views::values：遍历 mp 的每一组 value（即 map<x, count>）。std::views::values 是 C++20 的 range 适配器。
t = val：拷贝该组内层映射（auto t = val 做了拷贝，不过后续只读）。
第一层内循环：对组内所有横坐标桶的计数 v 求和，得 sum（该 key 组内所有点的总数）。
第二层内循环：对每个桶的计数 v，累加 ans += v*(sum - v)。
v*(sum-v) 的含义：这个横坐标桶里的 v 个点，每个点可以和同 key 组内其他横坐标桶（共 sum-v 个点）任意配对，产生 v*(sum-v) 个"跨横坐标"的配对。对所有桶累加
输出 ans
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll n, a, b, x, y, ans;
map<ll, map<ll, ll>> mp;
int main() {
    scanf("%lld%lld%lld", &n, &a, &b);
    for (int i = 0; i < n; i++) {
        scanf("%*d%lld%lld", &x, &y);
        mp[a*x-y][x]++;
    }
    for (const auto &val: mp | views::values) {
        auto t = val;
        ll sum = 0;
        for (const auto v: t | views::values) sum += v;
        for (const auto v: t | views::values) ans += v*(sum-v);
    }
    printf("%lld\n", ans);
    return 0;
}