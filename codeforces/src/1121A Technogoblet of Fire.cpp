//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
n：学生总数。
m：组别数量（组别编号 1..m）。
k：被检查（点名/录取）的人数。
a[i]：学生 i 的成绩。
s[i]：学生 i 所属的组别编号。
mx[i]：第 i 组的最高成绩（初值 0xcf = 一个很小的负数，等价于 -inf，再对每个学生取 max 更新）。
第二段：读入组别 s[i] 的同时，更新对应组 mx[ s[i] ] = max(..., a[i])。
第三段：读入 k 个学生下标
若 a[x] != mx[s[x]]，说明他不是自己组的最高分，ans++
输出统计结果：k 个学生中，非本组最高分的人数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
#define int long long
using namespace std;

constexpr int N = 2e4+5;
int n, m, k, mx[N], a[N], s[N], ans;
signed main() {
    fast;
    cin >> n >> m >> k;
    memset(mx, 0xcf, sizeof mx);
    rep(i,n) cin >> a[i];
    rep(i,n) { cin >> s[i]; mx[s[i]] = max(mx[s[i]], a[i]); }
    rep(i,k) {
        int x; cin >> x;
        if (a[x] != mx[s[x]]) ans++;
    }
    cout << ans;
    return 0;
}