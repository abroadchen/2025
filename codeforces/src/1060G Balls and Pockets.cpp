//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
find(k)：在 BIT 上做 线段树式二分，返回"前缀和 ≥ k"的最小下标 —— 找第 k 个存活的点。这是经典 BIT 上二分，O(log n)。
add 用于向某个位置加/减存量（插入/删除点）
dv 用于把某个距离除以 j（当前剩余点数）得到"还要走多少轮"，是 批量推进 的核心
L 是一个随时间单调下降的阈值（每次整体下降 k = d*j，其中 d 是还需的轮数、j 当前剩余点数）。
a 已隐含看作有序（因为 a[j]>=L 时从左删）。j 是当前"还活着的点数上界"。
每次循环：先计算还需的批量轮数 d，把共 k 的量一起降；在被跳过的查询（落在 [L-k, L] 区间）里，若还没结算（ans==-1），就改写 op 的 k、x——把查询改写为"换算到第某轮、映射到新的存活编号"，也就是把查询转换为第二阶段可处理的中间形式（op[i].k 改成轮次、op[i].x 改成对应 BIT 中的存活排名）。
T.find(a[j]-L+1)：找到第 a[j]-L+1 个存活点，把它删掉（因为这点 ≥ L，会被"接下来的下降"吞掉）。
L -= k; step += d 推进。
本质：这是一个"每次删掉所有 ≥L 的点，L 逐步下降，分左界批量下降"的过程，配合 BIT 做"存活点第 k 大"。它把每个尚未结算的查询重新编码成第二阶段需要的 (存活排名 x, 轮次 k)。
这里按 k（轮次）升序，随着 L 下降、step 增长，处理"在第 k 轮到期"的查询。
到期的查询用 ans = L - 1 + T.ask(op[i].x) - (op[i].k-step)*j 直接结算：公式含义约等于"当前到达的位置 + BIT 前缀排名 - 已走过的格子数"，给出了最终答案的下标/值。
删点、推进逻辑与第一遍相同。
这一遍把所有 ans!=-1 的查询真正算出了最终数值答案
*/
#include <bits/stdc++.h>
#define rep(i,n) for (int i=1; i<=(n); ++i)
#define ll long long
using namespace std;

constexpr int N = 5e5+5;
constexpr ll inf = 1e18;

int n;
struct BIT {
    int a[N];
    void clear() { for (int i = 1; i <= n; ++i) a[i] = 0; }
    void add(int x, int y) { for (int i = x; i <= n; i += i&-i) a[i] += y; }
    int ask(int x) {
        int s = 0;
        for (int i = x; i; i -= i&-i) s += a[i];
        return s;
    }
    int find(int k) {
        int s = 0, p = 0;
        for (int i = 1<<__lg(n); i; i >>= 1) {
            if (p+i > n) continue;
            if (s+a[p+i] < k) { p += i; s += a[p]; }
        }
        return p+1;
    }
} T;

struct node { int idx; ll x, k; } op[N];
bool cmp(node x, node y) { return x.x > y.x; }
bool cmp2(node x, node y) { return x.k < y.k; }

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

inline ll dv(ll x, ll y) { return (x+y-1)/y; }

int q, a[N];
ll ans[N], L(inf), step;
int main() {
    n = rd(), q = rd();
    rep(i,n) { a[i] = rd(); T.add(i, 1); }
    rep(i,q) {
        op[i].idx = i; op[i].x = rd(), op[i].k = rd();
        ans[i] = op[i].x < a[1] ? op[i].x : -1;
    }
    sort(op+1, op+q+1, cmp);
    for (int i = 1, j = n; i <= q && j;) {
        ll d = dv(L-a[j], j), k = d*j;
        while (i <= q && op[i].x >= L-k) {
            if (ans[op[i].idx] == -1) {
                op[i].k = step + dv(L-op[i].x,j) - op[i].k;
                op[i].x = T.find(op[i].x-(L-j*dv(L-op[i].x,j))+1);
            }
            ++i;
        }
        while (j && a[j] >= L) {
            int tmp = T.find(a[j]-L+1);
            T.add(tmp, -1);
            --j;
        }
        L -= k; step += d;
    }
    sort(op+1, op+q+1, cmp2);
    L = inf; step = 0; T.clear();
    rep(i,n) T.add(i, 1);
    for (int i = 1, j = n; i <= q && j;) {
        ll d = dv(L-a[j],j), k = d*j;
        while (i <= q && op[i].k <= step+d) {
            if (ans[op[i].idx] == -1) ans[op[i].idx] = L-1+T.ask(op[i].x)-(op[i].k-step)*j;
            ++i;
        }
        while (j && a[j] >= L) {
            int tmp = T.find(a[j]-L+1);
            T.add(tmp, -1);
            --j;
        }
        L -= k; step += d;
    }
    rep(i,q) write(ans[i]), putchar('\n');
    return 0;
}