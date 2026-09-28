//
// Created by Psy.C on 2026/9/28.
//
/**
读入长度 n 和数组 a[1..n]
c[x] 记录的是值 x 上一次出现的位置（初始 0，即"第 0 位"没有该值、或者说之前的虚拟起始位置 0）。
对当前位置 i：i - c[a[i]] 表示从上一次出现该值的位置到当前位置 i 的间距（若第一次出现，则 i-0 = i）。
然后乘 (n - i + 1)，再乘 2，再减 2。
把 (i - c) * (n - i + 1) 整个理解为一个"区间计数"：长度为 i - c 的段 × 以 i 为右端点能延伸到末尾的段数 (n - i + 1)。这类区间计数常出现在"数对/区间包含"问题的贡献拆分里。

*2 - 2 以及最后的 + n 是统计口径上的系数调整（可能是把"有序数对/有序区间"转化为"无序"或加回边界项）。
更新 c[a[i]] = i：把该值的最新位置更新为 i，供下一次出现计算间距用。
把累加的 ans 除以 n*n，保留 6 位小数输出。
典型的"分母为 n²"的期望形式，说明 ans 统计的是某种"有序对/区间数 × 权重"的总计数，除以 n² 得其期望或平均。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+5;

ll n, a[N];
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
}

ll ans, c[N];
int main() {
    fast;
    in();
    for (int i = 1; i <= n; ++i) {
        ans += (i - c[a[i]])*(n - i + 1) * 2 - 2;
        c[a[i]] = i;
    }
    ans += n;
    printf("%.6lf", (double)ans/(double)(n*n));
    return 0;
}