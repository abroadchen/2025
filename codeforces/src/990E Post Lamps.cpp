//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
n, k, l：点数 / 障碍数 / 步长种类数。
t[N]：t[i] = 位置 i 往回退时能退到的最远"安全（非障碍）"位置（用于跳跃时跳过障碍）。
v[N]：障碍标记数组（bool）。
a[N]：各步长的代价
读入 k 个障碍位置 x，把 v[x] 置为 1
从 1 到 n-1。
若位置 i 不是障碍（v[i]==0）：t[i] = i（从 i 出发能落在 i 自己）。
若位置 i 是障碍（v[i]==1）：t[i] = t[i-1]（从 i 出发被障碍挡住，只能回退到前一个安全位置 i-1 能到达的位置）。
读入 a[1..l]：步长 1-l 各自的代价
ans 初始 -1（表示"尚未找到可行解"）。
若起点 v[0]==1（位置0是障碍），根本没法开始，直接输出 -1
遍历位置 1..n。
cnt：连续障碍数（遇到障碍 +1，遇到安全格清零）。
mx = max(mx, cnt+1)：更新 max，记录 "最长连续障碍段长度 + 1"。
rep(i, mx, l+1)：枚举所有"能越过最大障碍段"的步长 i（从 mx 到 l）。
对每个步长 i 做一次跳跃模拟：
j：当前位置，从 0 出发。
res：累计代价。
循环条件 j < n（还没到终点 n）。
每次：
j += i：向前跳 i 步（到达 j+i）。
res += a[i]：累加该步长的代价。
j = t[j]：关键——若跳到的位置 j 是障碍，t[j] 会把它"吸附"到障碍前最近的安全位置（避免落在障碍上）。
循环直到 j >= n（越过终点 n，完成）。
若某次 t[j] == j（即跳到的位置本就是安全格，t[j]=j），则循环正常推进；若 j 是障碍，t[j] 回退到安全格。这样保证跳点永远安全，但注意 res 与循环可能因"回退过多无法推进"而……（这里代码实际上没有 dead-loop 保护，依赖 t[] 定义，回退后 j 变小再跳仍可能回到同一障碍——但按题意通常设计为可过）
若该步长能完成（res 有效），更新 ans 为所有可行步长中的最小代价
输出最小代价（若无解则为 -1）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i = (j); i < (k); i++)
#define ll long long
using namespace std;

constexpr int N = 1e6+10;

int n, k, l, x, t[N];
bool v[N];
ll a[N];
int main() {
    fast;
    cin >> n >> k >> l;
    rep(i,0,k) cin >> x, v[x] = 1;
    rep(i,1,n) { if (v[i] == 0) t[i] = i; else t[i] = t[i-1]; }
    rep(i,1,l+1) cin >> a[i];
    ll ans = -1;
    if (v[0] == 1) { cout << "-1"; return 0; }
    int mx = 1, cnt = 0;
    rep(i,1,n+1) {
        if (v[i] == 1) cnt++; else cnt = 0;
        mx = max(mx, cnt+1);
    }
    rep(i,mx,l+1) {
        int j = 0;
        ll res = 0;
        for (; j < n; j += i, res += a[i]) j = t[j];
        if (res != -1) {
            if (ans == -1) ans = res;
            ans = min(ans, res);
        }
    }
    cout << ans;
    return 0;
}