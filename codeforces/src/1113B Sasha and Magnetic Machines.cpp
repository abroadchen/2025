//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
sum 存总和。
sort 后 a[1] 是最小值
选某个较大的数 a[i]，把它变成 a[i]/j（除以因子 j）。
同时把最小值 a[1] 变成 a[1]*j（乘上同一因子 j）——这是一次“搬运”
符号相反，作为“减少量”最大化 push 进 ans
制约条件是 a[i]/j > a[1]：保证了除完后结果还比当前最小值大，避免把 a[1] 搬到一个“乘出来的值太夸张”的失衡场景（朴素推导下的合理剪枝）
sum - ans = 原总和 − 最大可减少量 = 操作一次后能达到的最小总和
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 2e5+5;
int a[N], sum, ans;
signed main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
    sort(a+1, a+n+1);
    for (int i = 2; i <= n; i++)
        for (int j = 2; j*j <= a[i]; j++) if (a[i]%j == 0)
            if (a[i]/j > a[1]) ans = max(ans, -(j-1)*(a[1]-a[i]/j));
    cout << sum - ans;
    return 0;
}