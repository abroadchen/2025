//
// Created by Psy.C on 2026/10/5.
//
/**
a[1..n]：原数组。
cnt：莫队的频次计数数组。
l, r：当前维护的区间 [l, r]。
sum：当前区间 [l,r] 的代价（通过莫队滑动维护）。
dp[i][j]：把前 i 个元素分成 j 段的最小代价
标准莫队：把当前区间 [l,r] 滑动到 [L,R]，并实时维护 sum（区间内"配对对数"或某种代价）。扩展左/右端点时加 cnt[x]++，收缩时减 --cnt[x]。cnt[a[--l]]++ 先加频次再加到 sum——这是维护"区间内相同值两两配对总数"（即
∑
c
(
c
n
t
c
2
)
∑
c
​
 (
2
cnt
c
​

​
 )）的经典写法。
决策单调性分治优化（divide & conquer optimization，通常称 "Mo's DP" 或 D&C DP optimization）‍：

状态 dp[i][dep]：前 i 个元素分成 dep 段的最小代价。
转移：dp[i][dep] = min_{j<=i} ( dp[j-1][dep-1] + cost(j, i) )。
利用决策单调性，用分治在 O(n log n) 内算完一层：处理区间 [L,R] 的决策点范围 [nl,nr]，算 mid 的最优决策 pos，再递归 [L,mid] 用 [nl,pos]、[mid+1,R] 用 [pos,nr]。
这里 get(i, mid) 就是 cost(i, mid)，通过莫队高效维护
dp[i][0] = inf（0 段不合法），dp[0][0] = 0。
读入数组。
对 dep = 1..k 逐层算 dfs(1, n, 1, n)。
输出 dp[n][k]：前 n 个元素分成 k 段的最小代价

cost(l,r) = 区间内
∑
(
c
n
t
2
)
∑(
2
cnt
​
 )（相同值的配对对数），由莫队 get() 维护。
该代价满足四边形不等式，因此 DP 具有决策单调性，可用分治优化（D&C DP）。
外层从 1 段递推到 k 段，每层 O(n log n)，整体 O(k n log n)。
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 2e5+5;
constexpr ll inf = 1e15;

int l, r, cnt[N]{1}, a[N];
ll sum;
inline ll get(int L, int R) {
    while (l > L) sum += cnt[a[--l]]++;
    while (r < R) sum += cnt[a[++r]]++;
    while (l < L) sum -= --cnt[a[l++]];
    while (r > R) sum -= --cnt[a[r--]];
    return sum;
}

ll dp[N][25];
int dep;
void dfs(int L, int R, int nl, int nr) {
    int mid = (L+R)>>1, pos = 0, tl = max(1, nl), tr = min(mid, nr);
    ll mn = inf;
    for (int i = tl; i <= tr; ++i) {
        ll val = dp[i-1][dep-1] + get(i, mid);
        if (val < mn) mn = val, pos = i;
    }
    dp[mid][dep] = mn;
    if (L == R) return;
    dfs(L, mid, nl, pos); dfs(mid+1, R, pos, nr);
}

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int main() {
    int n, k; cin >> n >> k;
    for (int i = 1; i <= n; ++i) dp[i][0] = inf; dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) a[i] = read();
    while (dep <= k) {
        ++dep;
        dfs(1, n, 1, n);
    }
    cout << dp[n][k];
    return 0;
}