//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
n：数组长度。
读入 a[i]，并用 vis[值]=1 标记每个数值出现过
对于每一对 (i, j)：

v = a[i] + a[j]：作为"目标和"。
内层遍历 k 属于 1..n：
计算补数 v - a[k]。
若 v-a[k] <= 0 跳过（要求补数为正）。
若 vis[v-a[k]] 为真，说明数组里存在与 a[k] 之和恰为 v 的数，cnt++。
cnt /= 2：因为每个匹配对 (k, k') 会在 k 和 k' 两个位置各被数一次，除以 2 去重。
ans = max(ans, cnt)：取所有 (i,j) 里的最大值
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 2e6+10;
int n, a[N], ans;
bool vis[N];
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i], vis[a[i]] = 1;
    rep(i,n) for (int j = i+1; j <= n; j++) {
        int v = a[i] + a[j], cnt = 0;
        rep(k,n) {
            if (v-a[k] <= 0) continue;
            if (vis[v-a[k]]) cnt++;
        }
        cnt /= 2;
        ans = max(ans, cnt);
    }
    cout << ans;
    return 0;
}