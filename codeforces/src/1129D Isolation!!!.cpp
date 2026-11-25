//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
N：数组上限（2e5+5），M=320 是分块数量上限，mod=998244353 取模。
T：分块大小（在 main 里设为 sqrt(n)）
返回下标 x 所在的块编号（1-based）
dec：a = (a - b) mod mod；inc：a = (a + b) mod mod。均用单次加减避免负值/溢出。
cnt[u]：每个元素 u 的"基础贡献层"计数值（不含块懒标记）。
tag[x]：第 x 块的懒标记（整块统一偏移量）。
val[x][...]：第 x 块内的分桶计数（按 cnt[u]+n 索引），用于快速求"满足 cnt ≤ k - tag 的元素个数之和"
把 u 插到块 x，先剥离懒标记得到真实 cnt[u]；
答案直接加上 v；并在 val[x][cnt[u]+n] 的分桶处累加 v。
（注释：cnt[u]+n 加 n 是偏移，保证下标非负，配合 k-tag+n 使用。）
先检查"当前有效计数 ≤ k"，若成立则把 f[u-1] 的贡献从 ans 中移除；
从分桶删除旧的 f[u-1]；
cnt[u] += v（v=±1）改变计数；
再次判断是否 ≤ k，是则加回 f[u-1]，并更新分桶。
即：get 实现"u 的出现次数变化 ±1 后，重新维护它是否为"合法可计入"的状态"
对 [L,R] 区间内每个元素 u 的 cnt[u] 统一加 v（v=1 或 -1），并同步更新 ans 贡献。
小区间（跨 ≤2 块）：直接逐个 get。
大区间：两端散块逐个 get；中间整块用懒标记 tag 一次处理：
val[i][k-tag[i]+n]：块内所有 cnt[u]（剥离 tag 后）满足 cnt[u]+tag[i] ≤ k 的，即 cnt[u] ≤ k-tag[i] 的那一桶的总贡献 v。
v=1（增）：把这些原合法元素从 ans 中减去（dec）；
v=-1（减）：k-tag[i]+1+n 一桶是"减 1 后会新变为合法"的元素，加回 ans（inc）。
最后 tag[i] += v 更新整块偏移。
这就是"懒标记分块在 O(1) 内处理整块"的关键：不用逐个元素改，只需调整分桶指针
pr[i] = 元素 a[i] 上一次出现下标，lst 维护最近位置。
f[0]=1，ins(1,1) 从空开始。
每次迭代：
solve(pr[i]+1, i, 1)：把从"上一次出现之后"到 i 这个区间每个位置的出现次数 +1（即当前元素 a[i] 在 [pr[i]+1, i] 内第一次/n次出现，使该范围内"计数≤k"的状态变化）。
solve(pr[pr[i]]+1, pr[i], -1)：回退"上上次出现区间"，把之前多算的计数 -1。
ins(i+1, f[i]=ans)：把当前累计答案 ans 作为 f[i] 存下，并把 i+1 位置插入带值 ans。
最终输出 f[n]。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5, M = 320, mod = 998244353;
int T;
inline int id(int x) { return (x-1)/T+1; }
inline void dec(int &a, int b) { a -= b; if (a < 0) a += mod; }
inline void inc(int &a, int b) { a += b; if (a >= mod) a -= mod; }

int cnt[N], tag[M], ans, n, val[M][N];
inline void ins(int u, int v) {
    int x = id(u); cnt[u] -= tag[x];
    inc(ans, v);
    inc(val[x][cnt[u]+n], v);
}

int k, f[N];
inline void get(int u, int v) {
    int x = id(u);
    if (cnt[u]+tag[x] <= k) dec(ans, f[u-1]);
    dec(val[x][cnt[u]+n], f[u-1]);
    cnt[u] += v;
    if (cnt[u]+tag[x] <= k) inc(ans, f[u-1]);
    inc(val[x][cnt[u]+n], f[u-1]);
}
inline void solve(int L, int R, int v) {
    if (L > R) return;
    int l = id(L), r = id(R);
    if (l+1 >= r) for (int i = L; i <= R; ++i) get(i,v);
    else {
        for (int i = L; i <= l*T; ++i) get(i,v);
        for (int i = (r-1)*T+1; i <= R; ++i) get(i,v);
        for (int i = l+1; i < r; ++i) {
            if (~v) dec(ans, val[i][k-tag[i]+n]);
            else inc(ans, val[i][k-tag[i]+1+n]);
            tag[i] += v;
        }
    }
}
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int pr[N], lst[N];
int main() {
    fast;
    n = rd(), k = rd();
    for (int i = 1, a; i <= n; ++i) a = rd(), pr[i] = lst[a], lst[a] = i;
    T = sqrt(n); n = n; f[0] = 1; ins(1,1);
    for (int i = 1; i <= n; ++i) {
        solve(pr[i]+1,i,1);
        solve(pr[pr[i]]+1,pr[i],-1);
        ins(i+1,f[i]=ans);
    }
    cout << f[n] << '\n';
    return 0;
}