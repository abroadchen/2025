//
// Created by Psy.C on 2026/10/11.
//
/**
分治求解部分答案 ans + 树状数组统计部分和；
multiset<S> 在 main 中维护一组值并支持动态更新最小值
标准单点加 / 前缀和查询。
add：把下标 x 加上 y（x += lowbit 向上更新）。
query：求 [1..x] 的累加和（x -= lowbit 向下汇总）
e[i] 以 i 为"左端点"存了若干条（值, 权值）二元组。
b[i] 和 ans[i] 分别存某个基准值与最终答案

区间为空时返回
计算中点 mid = (l+r)/2。
把下标范围 [l, mid] 的所有 e[i] 里的二元组按 n - fst + 1（把 fst 逆序映射成 BIT 下标）插入 BIT，作为对后续查询的贡献
对候选下标 i ∈ [L,R]，计算 b[i] + query(n-i+1)。
query(n-i+1) 表示某种"前缀积分"——结合前面插入的 n-fst+1 映射，这其实是求满足 fst >= i 的那些二元组权值之和（因为 n-fst+1 <= n-i+1 ⟺ fst >= i）。
取最小者 pos 和最小值 res，存入 ans[mid]
先把 [l,mid] 的贡献全部减去（回滚，保证左右子问题相互独立），递归求解左半 [l, mid-1]（候选范围 [L,pos]）。
再把 e[mid]（函数向下递归时，mid 已不属于任何一侧的插入范围外的边界）单独插入，递归右半 [mid+1, r]（候选范围 [pos,R]）。
这一段本质上是分治求解"四边形/决策单调"或"CDQ 分治 + BIT"里常见的最值分配：把一个序列切分，用 BIT 维护右侧对左侧的贡献，找出每个 mid 对应的最优位置，供左右递归使用。pos（最优位置）把候选区间 [L,R] 分成 [L,pos] 与 [pos,R] 两个子区间，这是"决策单调性 (divide and conquer optimization)"的典型写法
读入 n, m, q。
读入 n-1 组 (a[i], b[i+1])：这里 a[i] 是某个基值，b[i] 是分治里用的基准值。
读入 m 条边 (x,y,z)，存入 e[x]。
调用分治 dfs(1, n, 1, n) 求出所有 ans[i]。
把 a[i] + ans[i] 全部插入 multiset S，输出当前最小值 *S.begin()。
进行 q 次更新：每次修改单个 a[x] 的值（y），在 multiset 中删除旧 a[x]+ans[x]、插入新值 y+ans[x]，再输出新最小值 *S.begin()。
multiset 的作用是支持动态修改单个元素的值，并快速查询全局最小值（每次更新 O(log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=j; i<=k; ++i)
#define ll long long
#define ii pair<int,int>
using namespace std;

constexpr int N = 2e5+10;
constexpr ll inf = 1e18;
int n;
ll tr[N];
inline void add(int x, int y) { for (; x <= n; x += x & -x) tr[x] += y; }
inline ll query(int x) {
    ll res = 0;
    for (; x; x -= x & -x) res += tr[x];
    return res;
}

vector<ii> e[N];
int b[N];//每个下标的基础值
ll ans[N];//对每个位置算出的答案
inline void dfs(int l, int r, int L, int R) {
    if (l > r) return;
    int mid = (l+r)>>1;
    rep(i,l,mid) for (auto [fst, snd] : e[i]) add(n-fst+1, snd);
    int pos = L;
    ll res = inf;
    rep(i,L,R) {
        ll now = b[i] + query(n-i+1);
        if (now < res) pos = i, res = now;
    }
    ans[mid] = res;
    rep(i,l,mid) for (auto [fst, snd] : e[i]) add(n-fst+1, -snd);
    dfs(l, mid-1, L, pos);
    for (auto [fst, snd] : e[mid]) add(n-fst+1, snd);
    dfs(mid+1, r, pos, R);
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int m, q, a[N], x, y, z;
multiset<ll> S;
int main() {
    fast;
    n = rd(), m = rd(), q = rd();
    rep(i,1,n-1) a[i] = rd(), b[i+1] = rd();
    rep(i,1,m) {
        x = rd(), y = rd(), z = rd(), e[x].emplace_back(y, z);
    }
    dfs(1, n, 1, n);
    rep(i,1,n) S.insert(a[i]+ans[i]);
    cout << *S.begin() << '\n';
    rep(i,1,q) {
        x = rd(), y = rd();
        S.erase(S.find(a[x]+ans[x]));
        a[x] = y;
        S.insert(y+ans[x]);
        cout << *S.begin() << '\n';
    }
    return 0;
}