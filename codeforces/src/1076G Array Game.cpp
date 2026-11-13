//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
线段树每个节点除了区间范围 [l, r] 和懒标 tag 外，还维护了两个长度为 m+1 的置换数组 f[] 和 g[]。
关键点：f[i] 和 g[i] 是两个函数/置换——它们表示"当某个输入为 i 时，输出是什么"。这里用函数复合表示区间操作
合并左右子节点时，ans.f 是 r.f 后再经过 l.f 的复合：ans.f[i] = l.f[r.f[i]]。
同理 ans.g[i] = l.g[r.g[i]]。
这是"先应用右子区间、再应用左子区间"的函数叠加（右先左后）
叶子节点：f 和 g 是两个独立的置换。它们的取值：

f[0] = 1-a[l]、g[0] = a[l]：输入 0 时，f 输出 1-a（取反），g 输出 a（保持）。
对 1 <= i < m：f[i]=g[i]=i+1（类似循环移位）。
f[m]=g[m]=0：输入 m 时映射回 0。
这其实是把单点的 0/1 状态编码成两个置换，用于后续在区间级别做复合计算
up：交换节点的 f 和 g 两个数组——这就是"区间翻转"的实现。因为翻转操作会把两种置换互换。
push_down：下传懒标记给两个孩子，并让两个孩子的 f/g 也互换（因为区间翻转会翻转整个子区间）
标准区间更新。完全包含时翻转并打标记，否则下传懒标记后递归更新，最后回溯合并。
主函数里只有当 d 为奇数时才调用 upd（偶次翻转等价于不翻）
标准区间查询，返回覆盖区间的复合置换节点。跨越时用 merge 合并左右部分（注意顺序：先左后右）。
查询时同样要先 push_down 保证懒标记生效
输入 n、m、q，读入 n 个数并转成 0/1（模 2）。
op=1：区间 [l,r] 翻转 d 次——因为异或 1 两次等于没翻，所以只在 d 为奇数时执行翻转。
op=2：输出查询结果 1 + (calc(1,l,r).f[0] == 1)，即若查询区间的复合置换把 0 映射到 1，则输出 2 否则输出 1。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define mid ((l+r)>>1)
#define int long long
using namespace std;

constexpr int N = 2e5+10, M = 8e5+10;

struct node { int l, r, tag, f[30], g[30]; } t[M];
int m;
node merge(const node &l, const node &r) {
    node ans{}; ans.l = l.l, ans.r = r.r, ans.tag = 0;
    for (int i = 0; i <= m; i++) {
        ans.f[i] = l.f[r.f[i]]; ans.g[i] = l.g[r.g[i]];
    }
    return ans;
}

int a[N];
void build(int x, int l, int r) {
    if (l == r) {
        t[x].f[0] = 1 - a[l]; t[x].g[0] = a[l];
        for (int i = 1; i < m; i++) t[x].f[i] = t[x].g[i] = i + 1;
        t[x].f[m] = t[x].g[m] = 0; t[x].l = l; t[x].r = r;
        return;
    }
    build(x<<1, l, mid); build(x<<1|1, mid+1, r);
    t[x] = merge(t[x<<1], t[x<<1|1]);
}
void up(int x) { for (int i = 0; i <= m; i++) swap(t[x].f[i], t[x].g[i]); }
void push_down(int x) {
    if (!t[x].tag) return;
    t[x].tag = 0; t[x<<1].tag ^= 1; t[x<<1|1].tag ^= 1;
    up(x<<1), up(x<<1|1);
}
void upd(int x, int l, int r) {
    int L = t[x].l, R = t[x].r;
    if (l <= L && R <= r) return up(x), t[x].tag ^= 1, void();
    if (R < l || r < L) return;
    push_down(x);
    upd(x<<1, l, r), upd(x<<1|1, l, r);
    t[x] = merge(t[x<<1], t[x<<1|1]);
}
node calc(int x, int L, int R) {
    int l =  t[x].l, r = t[x].r;
    if (L <= l && r <= R) return t[x];
    push_down(x);
    if (mid < L) return calc(x<<1|1, L, R);
    if (R <= mid) return calc(x<<1, L, R);
    return merge(calc(x<<1, L, R), calc(x<<1|1, L, R));
}

int n, q;
signed main() {
    fast;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) { cin >> a[i]; a[i] = (a[i]-1)%2; }
    build(1, 1, n);
    while (q--) {
        int op, l, r, d; cin >> op >> l >> r;
        if (op == 1) {
            cin >> d;
            if (d&1) upd(1, l, r);
        }
        else cout << 1+(calc(1,l,r).f[0] == 1) << '\n';
    }
    return 0;
}