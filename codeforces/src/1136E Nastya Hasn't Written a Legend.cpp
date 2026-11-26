//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
原序列 a[i] 被拆成 b[i] + c[i]（其中 c 是固定前缀和）。
对 a 的修改 = 对 b 区间赋一个"统一值"，而 c 保持不变。
查询 = 查询 b 的区间和 + c 的区间和。
线段树维护 b[]：

tr：区间和（供区间求和）。
tr2：区间最大值（供二分查找"第一个满足 ≥ v 的位置"）。
lz：区间整体赋值的懒标记（inf 表示无懒标记
把左右儿子的和、最大值上推给父亲
区间赋值懒标记：把整个区间元素统一改成 lz[x]。注意这是"赋值"型（非累加型）标记，所以区间和 = 值 × 长度，最大值 = 值本身
递归建树，叶子存 b[l]，内部节点懒标记初始化为 inf（无标记），并 push_up 合并
标准区间赋值：全盖则置标记并更新 tr/tr2，否则下放后分治，最后上推
区间求和。因为查询时可能调用 push_down 改变了子树状态，结束后再 push_up 恢复父节点值
在区间 [L,R] 内找第一个值 ≥ v 的位置，不存在返回 -1。
优先搜左半（保证返回下标最小的满足者）。
利用 tr2（区间最大值）剪枝：若整段最大值 < v，直接放弃。
注意区间裁剪判断用 L <= l && R >= r（但这里的裁剪逻辑稍保守，仍依赖左右递归的 L <= mid / R > mid 来限制范围）
a[i] = b[i] + c[i]，其中 c 由 k 的前缀和决定（近似 c[i] = sum(1..i-1 k) 的叠加）。
这样把"对 a 做区间携带增量修改"变成"对 b 做统一区间赋值"——题目要求的 k 增量被吸收进 c。
c 的值结构：c[1]=0, c[2]=sum(初始为0后的k1)... c[i]=c[i-1]+sum，是一种嵌套前缀
查询：a 的区间和 = b 的区间和 + c 的区间和（因为 a=b+c，而 c 是固定前缀，可差分求和）。

修改（增量型）：把 [l, ...] 提升，使区间内每个元素至少在 b[l]+r 之上——利用 ask 找到第一个已经 ≥ 新值的断开点 p，只对 [l, p-1]（以及找不到时是 [l,n]）赋值，后面的保持不变。这样确保序列某种"不递减/后缀约束"性质
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

ll tr[N<<2], tr2[N<<2];
#define ls x<<1
#define rs (x<<1|1)
#define mid ((l+r)>>1)
void push_up(int x) { tr[x] = tr[ls] + tr[rs]; tr2[x] = max(tr2[ls], tr2[rs]); }

ll lz[N<<2];
void push_down(int x, int l, int r) {
    if (lz[x] != inf) {
        tr[ls] = lz[x]*(mid-l+1); tr[rs] = lz[x]*(r-mid);
        tr2[ls] = tr2[rs] = lz[x]; lz[ls] = lz[rs] = lz[x]; lz[x] = inf;
        return;
    }
}

ll b[N];
void build(int l, int r, int x) {
    lz[x] = inf;
    if (l == r) { tr[x] = tr2[x] = b[l]; return; }
    build(l, mid, ls); build(mid+1,r,rs);
    push_up(x);
}
void upd(int L, int R, ll v, int l, int r, int x) {
    if (L <= l && R >= r) { lz[x] = v; tr2[x] = v; tr[x] = (r-l+1)*v; return; }
    push_down(x,l,r);
    if (L <= mid) upd(L,R,v,l,mid,ls);
    if (R > mid) upd(L,R,v,mid+1,r,rs);
    push_up(x);
}
ll qry(int L, int R, int l, int r, int x) {
    if (L <= l && R >= r) return tr[x];
    push_down(x,l,r);
    ll res = 0;
    if (L <= mid) res += qry(L,R,l,mid,ls);
    if (R > mid) res += qry(L,R,mid+1,r,rs);
    push_up(x);
    return res;
}
int ask(int L, int R, ll v, int l, int r, int x) {
    if (l == r) {
        if (tr[x] >= v) return l;
        return -1;
    }
    push_down(x,l,r);
    if (L <= l && R >= r) if (tr2[x] < v) return -1;
    int res = -1;
    if (L <= mid) res = ask(L,R,v,l,mid,ls);
    if (res == -1 && R > mid) res = ask(L,R,v,mid+1,r,rs);
    push_up(x);
    return res;
}

int a[N], k[N], m, l, r;
ll sum, c[N];
char str[10];
int main() {
    fast;
    int n; cin >> n;
    rep(i,n) cin >> a[i];
    rep(i,n-1) cin >> k[i];//读相邻差 k[1..n-1]
    //b[i] = a[i] - (k[1]+...+k[i-1])  即差分掉前缀累计
    //c[i] = 前缀和的前缀和: sum 累加进 c
    //sum 变为下一个差分偏移
    rep(i,n) { b[i] = a[i] - sum; c[i] = sum; c[i] += c[i-1]; sum += k[i]; }
    build(1,n,1);
    cin >> m;
    rep(i,m) {
        cin >> str >> l >> r;
        if (str[0] == 's') {
            //b 的区间和 + c 的区间和 => a 的区间和
            ll res = qry(l,r,1,n,1); res += c[r]-c[l-1];
            cout << res << '\n';
        } else {//修改操作
            b[l] = qry(l,l,1,n,1);//取当前 b[l] 的真实值
            int p = ask(l,n,b[l]+r,1,n,1);//在原区间找第一个值 >= b[l]+r 的位置
            if (p == -1) upd(l,n,b[l]+r,1,n,1);//找不到: 赋 [l,n]
            else if (p > l) upd(l,p-1,b[l]+r,1,n,1);//找到 p: 赋 [l,p-1]
        }
    }
    return 0;
}