//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
g[i] 表示第 i 层一个块能容纳的目标数量，逐层呈 (N-4) 的幂次增长。
主题意：假设可查询上限很大（如 1e9），用 5 层嵌套分块把搜索范围压缩到一次交互可判定的尺度
dfs(x,c) 返回的是：当前回答范围起点为 x、还剩 c 层时，经过完整递归跳转后能覆盖到的最终数值（近似解空间大小函数）
把当前范围 [x, ·) 划分成 v 个分块，输出各分块的右端点（范围分界值）。
读回判定 k：k=0 说明目标在最前面那块，否则目标在第 k 块，递归在该块内继续，层数 c-1。
通过逐层分块，把大规模范围逐步压缩，最终在 5 层内唯一确定目标值并结束（-1 退出）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e4+5;

ll g[6];//各层每块的容量
ll dfs(ll x, int c) {
    if (x >= N-5) return x+g[c]-1;//数值足够大 → 直接跳到块尾
    if (c == 1) return x + min(x,1ll*(N-5));//最底层直接算
    ll v = min(x, 1ll*(N-5)) + 1; x--;
    rep(i,v) x = dfs(x+1,c-1);//每块递归向下
    return x;
}

ll d[N];
void solve(ll x, int c) {
    ll v = min(x, 1ll*(N-5)) + 1, s = x; x--;
    if (c == 1) rep(i,v) x++, d[i] = x;//最底层：直接列出值
    else rep(i,v) x = dfs(x+1,c-1), d[i] = x;//高层：用 dfs 得到边界点
    cout << v-1 << ' ';//先输出分块数
    rep(i,v-1) cout << d[i] << ' ';//输出各分块右端点
    cout << endl;
    int k; cin >> k;//读交互判定
    if (k == -1) exit(0);//-1 = 已猜中/结束
    if (k == 0) solve(s,c-1);//落在 0 号块 → 升层
    else solve(d[k]+1,c-1);//落在 k 号块 → 从该块起点继续
}


int main() {
    fast;
    g[1] = N-4;//
    for (int i = 2; i <= 4; i++) g[i] = g[i-1]*(N-4);//逐层呈乘积暴增
    solve(1, 5);
    return 0;
}