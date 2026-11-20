//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
读入 n（人数）、x（主角实力）、y；
统计 cnt = 实力 ≤ x 的人数（这些人主角能直接打败）
情况 1：x > y → 主角实力大于 y，输出 n。

含义：当 x > y 时，主角是最强的（或能一路打败所有人），所以它能"统治"到最后一轮，总共交手/参与 n 相关结果（通常是 n-1，但这里输出 n，对应"能战至最后"或判定为可全胜）。
实际上这类题的语义：若 x>y，主角在一次操作中能同时处理掉两个对手（借 y 的力量团灭），故直接全胜，输出 n。

情况 2：x <= y → 主角无法借用 y，只能一对一，输出 (cnt+1)/2（cnt 向上取整一半）。

此时只有实力 ≤ x 的对手主角能打，而实力 > x 的人主角打不过；
每回合主角只能淘汰一个"可战胜"的对手，经过 cnt 个可胜对手后主角升到最强，之后剩余都不可战胜 → 需要回合数 (cnt)/2……最终等价 (cnt+1)/2
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 101;
int a[N], cnt;
int main() {
    fast;
    int n, x, y; cin >> n >> x >> y;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] <= x) cnt++;
    }
    if (x > y) cout << n << '\n';
    else cout << (cnt+1)/2 << '\n';
    return 0;
}