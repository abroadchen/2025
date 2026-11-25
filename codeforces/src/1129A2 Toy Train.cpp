//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
n 个环形位置，m 封信。
memset(mn, 0x3f, …)：0x3f 在 int 下是较大的初值（约 1e9+），作为"无穷大"用于取 min，等价 mn 初始很大。
cnt[a]++：起点 a 上的信加一。
mn[a] = min(mn[a], (b+n-a)%n):
(b+n-a)%n 正是"从 a 顺时针走到 b 的弧长"（模运算版本，等价上一题的 dis(a,b)）。
取最小值 = "以 a 为起点的信中，离 a 最近的目标准点弧长"
对每个出发位置 i：
遍历所有起点 j：
若 cnt[j]==0（j 上没有信），跳过。
计算该起点的耗时：
(j+n-i)%n：从 i 顺时针到 j 的弧长（等价上一题 dis(i,j)）。
(cnt[j]-1)*n：第 1 封信在抵达时顺带送，其余 cnt[j]-1 封信每封需绕一整环取回。
+ mn[j]：最后把最后一封送到 j 的最近目标所需弧长。
res = max(res, …)：因为各起点并行，总时间取决于最慢的那个起点。
每 i 输出 res。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 5010;
int n, m, mn[N], cnt[N];
int main() {
    fast;
    cin >> n >> m; memset(mn,0x3f,sizeof mn);
    rep(i,m) {
        int a, b; cin >> a >> b; cnt[a]++;
        mn[a] = min(mn[a], (b+n-a)%n);
    }
    rep(i,n) {
        int res = 0;
        rep(j,n) {
            if (!cnt[j]) continue;
            res = max(res, (cnt[j]-1)*n+mn[j]+(j+n-i)%n);
        }
        cout << res << ' ';
    }
    return 0;
}