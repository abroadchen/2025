//
// Created by Psy.C on 2026/8/28.
//
/**
- n ：题目总数（一共有多少道题可选）。
- k ：已经花掉的分钟数（比赛已经进行了多久）
t 240 - k 剩余可支配时间 ：比赛总时长 240 分钟减去已用的 k 分钟，得到还能用来做题的时间
s 0 已完成题目计数 ：初始为 0，后面每完成一道就 s++
- *i ：第 i 道题需要花费 5×i 分钟（题目设定：第 1 题 5 分钟，第 2 题 10 分钟，第 3 题 15 分钟……越靠后的题越费时间）。
- t >= 5*i ：如果剩余时间还够做第 i 题。
- s++ ：够的话，完成数 s 加 1
不管时间够不够，都从 t 里扣掉 5*i ：
- 够的情况 ：正常扣减， t 减少，继续下一题。
- 不够的情况 ：扣减后 t 变成负数，后面所有题的 5*i 更大， t >= 5*i 永远不成立，相当于自动跳过了剩下的所有题
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    int t = 240 - k, s = 0;
    for (int i = 1; i <= n; ++i) {
        if (t >= 5*i) s++;
        t = t - 5*i;
    }
    cout << s << '\n';
    return 0;
}