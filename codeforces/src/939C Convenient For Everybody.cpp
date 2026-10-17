//
// Created by Psy.C on 2026/10/17.
//
/**
n：元素个数；a[N]：原数组；z[N]：前缀和数组；s、f：窗口起止相关参数；ans：临时窗口和；v：当前最大和；id：最优起点编号
读入 n。

for... cin >> a[i]; z[i] = z[i-1] + a[i];：读入 a[i] 并同时维护前缀和 z[i]（z[i] = 前 i 项之和，z[0]=0）。

cin >> s >> f;：读入窗口的起点参数 s 和终点参数 f。注意题目语义通常是「每个长度为 f-s 的窗口」，s < f，窗口宽度 = f - s。

外层 for (i=1..n)：枚举窗口的起始位置 i（环形），分三种情况计算以 i 为起点的窗口和 ans：

情况一 i <= s：窗口完全在直线范围内不跨过末尾。
ans = z[f-i] - z[s-i]：窗口覆盖下标 [s-i, f-i)，用前缀和相减得这段的和（因为 i 是起始，窗口起点相对位移）。窗口长度 = (f-i)-(s-i) = f-s，与 i 无关，恒定。
情况二 s < i < f：窗口跨越数组末尾（环形回绕）的情况。
ans = z[f-i] + z[n] - z[s-i+n]：拆成两段——末尾段 z[n]-z[s-i+n] 加上开头段 z[f-i]，合成跨越环的窗口和。
情况三 i >= f：窗口整体平移到后半段（仍在直线内，但起点靠后）。
ans = z[f-i+n] - z[s-i+n]：用 +n 做下标平移，避免负数，前缀和相减。
每次算完后 if (ans > v) 用严格大于更新最大值 v 和对应起点 id = i。
输出 id：最优窗口起始位置的编号
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;

int n, a[N], z[N], s, f, ans, v, id;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        z[i] = z[i-1] + a[i];
    }
    cin >> s >> f;
    for (int i = 1; i <= n; ++i) {
        if (i <= s) ans = z[f-i] - z[s-i];
        if (s < i && i < f) ans = z[f-i] + z[n] - z[s-i+n];
        if (i >= f) ans = z[f-i+n] - z[s-i+n];
        if (ans > v) { v = ans; id = i; }
    }
    cout << id;
    return 0;
}