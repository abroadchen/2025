//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
M=1e4：从大到小枚举 j（j=10000 递减到 2），若 |a[i]| 能被 j² 整除，就除掉 j²。
效果：把每个数化简掉所有平方因子，变成"square-free 核"（无平方因子的基数形式）。
注意 0 会被跳过（abs(0)% 恒为 0，但除 0 除到 0/=... 仍为 0；由于 j 从大到小，0 一直除仍是 0，a[i]=0 保持不变，cnt 单独统计 0）。
约束：因为 j 从 M 往下，且除掉能整除的 j²，最终 a[i] 的平方因子都除尽，但需保证 j*j 都能整除才除，大因子优先，避免重复/漏
s 是一个 bitset，用 a[j]+inf（inf=1e8，把负数偏移到非负）作为下标，记录该值是否出现过，从而 t 统计当前子段 [i..j] 里不同数值的个数。
cnt：子段内 0 的个数。
关键判断条件 if (cnt!=0 && cnt!=j-i+1)：若子段包含 0 但不全是 0，则该子段里的 0 与 0 之间无法区分（0 只算 1 个不同的数，但因为 0 有多个，实际"0"这一数值重复），此时不同数个数需按 t-1 处理（把重复的 0 扣除一个）；否则直接用 t。
++ans[t-1] 或 ++ans[t]：ans[k] 统计"不同数个数恰为 k"的子段数。
内层结束后用 s[...]=0 清空整个 bitset，准备下一个起点 i。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 5e3+5, inf = 1e8, M = 1e4;

int n, a[N], i, j, ans[N];
bitset<2*inf+1> s;
int main() {
    fast;
    cin >> n;
    for (i = 1; i <= n; ++i) {
        cin >> a[i];
        for (j = M; j >= 2; --j)
            if (abs(a[i])%(j*j) == 0) a[i]/=j*j;
    }
    for (i = 1; i <= n; ++i) {
        int t = 0, cnt = 0;
        for (j = i; j <= n; ++j) {
            if (a[j] == 0) ++cnt;
            if (!s[a[j]+inf]) ++t; s[a[j]+inf] = 1;
            if (cnt != 0 && cnt != j-i+1) ++ans[t-1]; else ++ans[t];
        }
        for (j = i; j <= n; ++j) s[a[j]+inf] = 0;
    }
    for (i = 1; i <= n; ++i) cout << ans[i] << ' ';
    return 0;
}