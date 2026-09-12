//
// Created by Psy.C on 2026/9/12.
//
/**
每条障碍：u=行号（从下往上？或从上往下排序），l、r=列区间，s=跳跃能力（维护的"高度阈值"）。
按 u 降序排列（u > o.u），即从上往下的行先处理。u 在这里代表该障碍所在行的高度（行编号 from top）
q[col]：小根堆，存 (高度h, 球数p)，表示列 col 上当前有"高度 h 的节点带 p 个球"等待被"跨过障碍"
叶节点连到情堆 q[l] 初始放入 (h+1, 1)：即每列初始在高度 h+1（底边之下）有 1 个"起点"球。
ans[o] = 该区间内所有列堆顶的最小高度（即最早会被"激活/溢出"的列）
对列 pos 加入 (h, p)：在高度 h 处放置 p 个球
query 找到列区间 [L,R] 中所有"高度 ≤ h+s"的球（即能被当前障碍 [l,r] 挡住并分裂的球），把它们取出并求和返回（所有分裂前被障碍命中的球总数）。
剪枝：若区间最小高度 ans[o] > h+s，说明该区间没有任何球能被此障碍影响，直接返回 0
对每条障碍（从上到下排序）：query 取走该行内所有"能挡住的球"，总和记为 t。
由于这些球被障碍挡住并分裂：若障碍在中间，分裂成左右各 t 个球，在新的列（左右边界外侧）于该行重新落下；若靠边界则单侧。
M 累加每次被"吸收/计数"到的球数（即最终出口总和）。
最终 M = 所有球（初始 + 各次分裂累加）总数 = 答案
 */
#include <bits/stdc++.h>
#define int long long
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+10, mod = 1e9+7, inf = 1e10+7;
struct node {
    int u, l, r, s;
    bool operator<(const node &o) const {
        return u > o.u;
    }
} k[N];

priority_queue<ii, vector<ii>, greater<>> q[N];
int h;
int ans[N<<2];
void build(int o, int l, int r) {
    if (l == r) {
        q[l].emplace(h+1, 1);
        ans[o] = h+1;
        return;
    }
    int mid = (l+r)>>1;
    build(o<<1, l, mid), build(o<<1|1, mid+1, r);
    ans[o] = min(ans[o<<1], ans[o<<1|1]);
}

void update(int o, int l, int r, int pos, int p, int h) {
    if (l == r) {
        q[l].emplace(h, p);
        ans[o] = min(ans[o], h);
        return;
    }
    int mid = (l+r)>>1;
    if (pos <= mid) update(o<<1, l, mid, pos, p, h);
    else update(o<<1|1, mid+1, r, pos, p, h);
    ans[o] = min(ans[o<<1], ans[o<<1|1]);
}

int query(int o, int l, int r, int L, int R, int h, int s) {
    if (ans[o] > h+s) return 0;//区间内所有球都够不着（高度大于 h+s 都无法被本障碍影响）
    if (l == r) {
        int res = 0;
        while (!q[l].empty() && q[l].top().first <= h+s) {//高度≤h+s的球都会被本障碍吸收/计数
            res = (res + q[l].top().second) % mod;
            q[l].pop();
        }
        ans[o] = q[l].empty() ? inf : q[l].top().first;
        return res;
    }
    int mid = (l+r)>>1, res = 0;
    if (L <= mid) res = query(o<<1, l, mid, L, R, h, s);
    if (R > mid) res = (res + query(o<<1|1, mid+1, r, L, R, h, s)) % mod;
    ans[o] = min(ans[o<<1], ans[o<<1|1]);
    return res;
}

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

int w, n, M;
signed main() {
    h = rd(), w = rd(), n = rd();
    for (int i = 1; i <= n; ++i) k[i].u = rd(), k[i].l = rd(), k[i].r = rd(), k[i].s = rd();
    M = w; build(1, 1, w); sort(k+1, k+n+1);
    for (int i = 1; i <= n; ++i) {
        int t = query(1, 1, w, k[i].l, k[i].r, k[i].u, k[i].s);
        M = (M+t)%mod;
        //左边界，分裂出的球都到右侧
        if (k[i].l == 1) update(1, 1, w, k[i].r+1, (t<<1)%mod, k[i].u);
        //右边界，都到左侧
        else if (k[i].r == w) update(1, 1, w, k[i].l-1, (t<<1)%mod, k[i].u);
        else {
            update(1, 1, w, k[i].l-1, t, k[i].u);//分裂到左
            update(1, 1, w, k[i].r+1, t, k[i].u);
        }
    }
    write(M), putchar('\n');
    return 0;
}