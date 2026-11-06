//
// Created by Psy.C on 2026/11/6.
//

/**
真正学会的起点..
对每个候选周期 k，先重新计算差分 x[j] = a[j] - a[j-1]（即相邻元素差）
对候选周期 k：把差分数组按模 k 分成 k 条子序列（起点 j=1..k），每条中检查相隔 k 的元素是否全相等（x[t] == x[t+k]）。
若所有子序列内部都相等，则 k 是差分周期，加入答案 ans。
即：判断差分数组 x 是否为周期为 k 的序列（每 k 位一循环）。这与原数组 a 是否"每 k 位呈线性递增/某种规律"对应。
输出合法周期 k 的个数 c，再输出所有满足的 k
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

constexpr int N = 1010;

int n, a[N], x[N], ans[N];
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    int c = 0;
    rep(k,n) {
        bool f = 1;
        rep(j,n) x[j] = a[j] - a[j-1];
        rep(j,k) {
            int t = j;
            while (t + k <= n) {
                if (x[t+k] != x[t]) f = 0;
                t += k;
            }
        }
        if (f == 1) ans[++c] = k;
    }
    cout << c << '\n';
    rep(i,c) cout << ans[i] << ' ';
    return 0;
}