//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
N：数组与询问的上限（5×10^5）；M=31：用 31 个位（0-30），因为 int 是 32 位有符号，最高有效位到 30
qu 表示一次询问：[l,r] 区间、id 是原始编号（用于按原顺序输出）。
q[] 存所有询问；t1[]、t2[] 是分治时用来临时归类（左半区 / 右半区）的辅助数组
node 是一个线性基：p[i] 存「最高位是第 i 位」的那个基向量。
clear() 把整个基清零。
b[]：b[i] 存以分治中点 mid 为界、向左右延伸的某个区间的线性基
向线性基 now 中插入数 x（高斯消元式插入）。从高位到低位，若 x 的第 i 位为 1：
若该位还没有基向量，就把 x 存进去并结束；
否则 x ^= now.p[i] 消去这一位，继续看更低的位置。
这就是经典的线性基插入，保证基中每个向量的最高位互不相同
把两个线性基 b 的所有基向量逐步 insert 进 a，完成两个区间的「集合合并」（因为线性基不需要管顺序，只关心向量集合），返回合并后的基 a
贪心求这个线性基能表示出的最大值：从高位到低位，若异或该位基向量会变大就异或上去。这是「区间最大异或和」的标准求法
a[]：原数组；ans[]：每个询问的答案
分治主函数：[l,r] 是当前值域区间，[L,R] 是当前待处理的询问在 q 数组中的下标范围
没有询问要处理，直接返回
值域只剩下一个点 l==r 时，区间内只有 a[l] 这一个数，答案就是 a[l]，直接赋给该范围内的所有询问。
取值域中点 mid；c1、c2 分别统计会进入左、右子问题的询问个数。
中点 b[mid]：初始化为只含 a[mid] 的线性基。
向左推进：b[i] = 从 a[i] 到 a[mid] 这段的线性基（b[i] 继承 b[i+1] 再插入 a[i]）。
向右推进：b[i] = 从 a[mid] 到 a[i] 这段的线性基。
至此，任何「横跨 mid」的询问 [lq, rq]（lq≤mid<rq）的答案，就是 b[lq] 与 b[rq] 合并后的基求最大值——即整段 a[lq..rq] 的基
遍历本层所有询问，若它横跨 mid（q.l ≤ mid 且 q.r ≥ mid+1），就直接合并 b[q.l] + b[q.r] 求出答案，continue 不再下放
否则按位置分流：整段都在左半（r≤mid）的进 t1，整段在右半（l>mid）的进 t2
把 t1、t2 写回 q[L..R]，重构询问数组，左半查询在前、右半查询在后。
对左右两半递归求解。
读入 n、数组 a、m 个询问（记录编号），从 solve(1,n,1,m) 开始分治，最后按原编号输出答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define per(i,n) for (int i=n; i>=0; i--)
using namespace std;

constexpr int N = 5e5+5, M = 31;

struct qu { int l, r, id; } q[N], t1[N], t2[N];
struct node {
    int p[M];
    void clear() { for (int &i : p) i = 0; }
} b[N];

void insert(node &now, int x) {
    per(i,M-1) {
        if (((x>>i)&1) == 0) continue;
        if (now.p[i] == 0) { now.p[i] = x; return; }
        x ^= now.p[i];
    }
}
node merge(node a, node b) {
    for (int i = 0; i <= M-1; i++) if (b.p[i]) insert(a,b.p[i]);
    return a;
}
int get(node x) {
    int res = 0;
    per(i,M-1) if ((res^x.p[i]) > res) res ^= x.p[i];
    return res;
}

int ans[N], a[N];
void solve(int l, int r, int L, int R) {
    if (L > R) return;
    if (l == r) { for (int i = L; i <= R; i++) ans[q[i].id] = a[l]; return; }
    int mid = (l+r)>>1, c1 = 0, c2 = 0;
    b[mid].clear(), insert(b[mid], a[mid]);
    for (int i = mid-1; i >= l; i--) b[i] = b[i+1], insert(b[i], a[i]);
    for (int i = mid+1; i <= r; i++) b[i] = b[i-1], insert(b[i], a[i]);
    for (int i = L; i <= R; i++) {
        if (l <= q[i].l && q[i].l <= mid && mid+1 <= q[i].r && q[i].r <= r) {
            ans[q[i].id] = get(merge(b[q[i].l], b[q[i].r]));
            continue;
        }
        if (q[i].l <= mid && q[i].r <= mid) t1[++c1] = q[i]; else t2[++c2] = q[i];
    }
    rep(i,c1) q[L+i-1] = t1[i];
    rep(i,c2) q[L+c1+i-1] = t2[i];
    solve(l,mid,L,L+c1-1), solve(mid+1,r,L+c1,L+c1+c2-1);
}

int n, m;
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    cin >> m;
    rep(i,m) { cin >> q[i].l >> q[i].r; q[i].id = i; }
    solve(1,n,1,m);
    rep(i,m) cout << ans[i] << '\n';
    return 0;
}