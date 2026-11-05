//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
n, m：两个数组的长度。
a[N], b[N]：两个数组。
b2[31]：预计算的 2 的幂表（b2[i] = 2^i）。
ans：全局最大值
预计算 b2[0..30] = 1,2,4,...,2^30。
读 n 和数组 a；读 m 和数组 b。
y 读入两次但每次只读后未用（下划线变量），即 "n y"、"m y" 只是把 y 当作占位读掉，实际没用。
对某个 u：

取模分桶：令 p = b2[u+1] = 2^(u+1)。

md：a 中每个数对 p 取模后的频数。
mu：b 中每个数对 p 取模后的频数。
配对计数：

对 a 的每个元素：计算 md[x%p] + mu[(x + b2[u]) % p] 并更新最大。
对 b 的每个元素：计算 mu[x%p] + md[(x + b2[u]) % p] 并更新最大。
关键步骤是 + b2[u] 这个偏移：把一个数组中的元素"加上 2^u 再取模"，去匹配另一数组的桶。这本质上是在枚举一个加性偏移量（2 的幂），统计经过该偏移对齐后，两数组能配对的元素总数。

逻辑核心：若存在某个未知数 X（本题要求的目标值），满足 a[i] 与 b[j] 之间存在某种 a[i] ≡ b[j] + X (mod p) 之类的关系，那么固定 mod 和偏移后，匹配的桶就是 x%p 与 (x+K)%p
对 u = 0..29（共 30 个 2 的幂）依次执行 solve。
输出 max(ans, 2)：答案至少为 2（保低下限）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e5+5;

int n, m, a[N], b2[31], b[N], ans;
void solve(int u) {
    map<int,int> md, mu; int p = b2[u+1];
    rep(i,n) md[a[i]%p]++;
    rep(i,m) mu[b[i]%p]++;
    rep(i,n) ans = max(ans, md[a[i]%p]+mu[(a[i]+b2[u])%p]);
    rep(i,m) ans = max(ans, mu[b[i]%p]+md[(b[i]+b2[u])%p]);
}


int y;
int main() {
    fast;
    for (int i = 0; i <= 30; i++) b2[i] = 1<<i;
    cin >> n >> y;
    rep(i,n) cin >> a[i];
    cin >> m >> y;
    rep(i,m) cin >> b[i];
    for (int i = 0; i <= 29; i++) solve(i);
    cout << max(ans, 2) << '\n';
    return 0;
}