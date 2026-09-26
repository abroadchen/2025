//
// Created by Psy.C on 2026/9/26.
//
/**
n：总共的天数/物品数/关卡数。
m：剩余的目标体力/生命/需要消化的总量。
ans：当前累积的量（还没被消化掉的部分）
读入 n（总共多少天）和 m（初始目标量，比如"食堂餐费"/"每周目标")
循环 i 从 1 到 n，代表第 i 天/第 i 个输入。
读入当天的量 x，累加到 ans 上（ans += x）。
此时 ans 表示"到目前累积的但每轮最多只能处理 8 个"的存量
每一轮最多能处理掉 8 个单位（min(ans, 8) 取当前存量 ans 和 8 的较小值）。
从目标 m 里扣除被处理掉的量：m -= 处理量。
同时从 ans 里扣掉处理量：ans -= 处理量（剩下的 ans 留到下一轮继续积累）。
注意：因为 ans 可能不足 8，所以处理量是 min(ans, 8)——即每天都尽量处理最多 8 个，但不够就处理全部
如果处理完之后，目标 m 已经小于等于 0（即总处理量已经 ≥ 初始 m），则输出当前天数 i 并结束。
表示"在第 i 天就完成了目标"
如果循环完 n 天还没有完成目标（m 依然 > 0），输出 -1，表示无法完成。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m, ans;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x; ans += x;
        m -= min(ans, 8);
        ans -= min(ans, 8);
        if (m <= 0) { cout << i << '\n'; return 0; }
    }
    cout << "-1\n";
    return 0;
}