//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
读入 n，数组 a[1..n]。
同时记录所有数中的最大值 mx（初值 -1）。
注意：int a[n+1] 是变长数组（VLA）‍，属于 GCC 扩展，在标准 C++ 中非标准，但很多 OJ 环境支持。若严格标准，应改用动态数组或 vector
ans 初值设为很大的 N。
p 记录最优位置（输出用）。
外层 for i 从 1 枚举到 mx（最大值），即枚举所有可能的"目标位置 i
内层遍历所有原始数 a[j]，对每个数计算移动到位置 i 的成本：
若 a[j] - i > 1，即 a[j]>i+1（目标在左边、距离 ≥ 2）→ 成本为 a[j]−i−1。
否则若 i - a[j] > 1，即 i>a[j]+1（目标在右边、距离 ≥ 2）→ 成本为 i−a[j]−1。
两种情况都没命中 → 说明 ∣a[j]−i∣≤1（距离为 0 或 1）→ 成本为 0，不累加。
成本规则归纳：∣a[j]−i∣≤1 时成本 0；超过 1 时，成本 =
∣a[j]−i∣−1。即"前 1 个单位距离免费，超过部分按 1:1 计费"。这通常是因为移动成本里有个"起步价"或者最后 1 步被忽略（比如看作两个数之间的"间隔数"）
若当前位置
i 的总成本 cnt 比当前最优 ans 更小，则：
更新最优位置 p = i；
ans 取最小值。
注意：p 只在 cnt < ans（严格小于）时更新，即保留第一个达到最小的位置（多个最优并列时取最小的那个
i，因为枚举是递增）。
输出最优位置
p 和最小总成本 ans。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); ++i)
using namespace std;

constexpr int N = 2147480000;

int main() {
    fast;
    int n; cin >> n;
    int a[n+1], mx = -1;
    rep(i,n) { cin >> a[i]; mx = max(mx, a[i]); }
    int cnt, ans = N, p = 0;
    rep(i,mx) {
        cnt = 0;
        rep(j,n) {
            if (a[j]-i > 1) cnt += a[j]-i-1;
            else if (i-a[j] > 1) cnt += i-a[j]-1;
        }
        if (cnt < ans) p = i;
        ans = min(ans, cnt);
    }
    cout << p << ' ' << ans << '\n';
    return 0;
}