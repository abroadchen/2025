//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
mn[o]：节点 o 覆盖区间内 L 值的最小值。
cov[o]：懒标记（区间整体赋值）。0 表示没有待下传的赋值。
s[o]：节点 o 覆盖区间内所有 L 值的和（用 ll，因为区间和可能很大）
左右儿子编号分别为 o<<1 和 o<<1|1。mn 取两儿子较小者，s 为两儿子求和
当前节点区间长度为 len。赋值后，整段值都是 x，所以 mn 也是 x。
把 x 同时赋给左右儿子的 cov 和 mn。
s[o<<1] = x*左儿子长度，左儿子长度 = (len+1)>>1（上取整，因为左儿子占 [l, mid]）；右儿子长度 = len>>1（下取整）。
最后把当前节点的懒标记清零（x = 0）。
这里 x 是 int&，所以 x = 0 实际修改了 cov[o]
完全覆盖：直接整体赋值，s = 长度 × val。
否则：先 push_down 保证旧懒标记落地，再递归到交叠的儿子，改完后 update 上推
完全覆盖直接返回 s[o]；否则下传后递归合并
它返回的是最靠右的下标 x，满足该位置上的 L < v（因为调用时传的 v 是 l-1，见后面 query）。
优先从右子树搜，是为了拿到最靠右的那个有效位置
a[i]：数组当前值。
st / stk：编码下标用的临时数组（把 (位置<<5)|位号 存进去，见下）。
top / tk：两个临时数组的长度。
pos[i]：第 i 位上为 1 的所有下标（升序 set）。
用 (pos << 5) | bit 把"位置"和"位号"打包成一个整数：低 5 位是位号（0-19），高位移是位置。pos[i] 最多 1e5，<<5 后 ≤ 3.2e6，不会溢出 int
对每一位，取出它在 p 右侧最近的位置放入 st，在 p 左侧最近的位置放入 stk。
这些是修改 a[p] 后"或值边界"可能发生变化的唯一候选位置（其余位置不受影响）
st 升序、stk 降序排列。
st[top+1] 放哨兵 (n+1)<<5（比任何真实位置大）。
stk[tk+1]=0 是左端哨兵；st[0]=(p+1)<<5 保证分段从 p 右边开始处理
对每一段（p 到右侧某边界），确定能装下多少个左侧"关键位"才能使 或值 ≤ X，从而算出该分段的 L。
nw 记录当前右侧已选位集合，zt 记录左侧能容纳的位集合，两者做按位或。
一旦 或值 > X，就把左侧最远的关键位从 zt 里去掉（it--），得到能选到的左侧最近位置，L = 该位置+1。
每个分段整体赋同一个 L——这就是这道题高效的关键（不是逐点更新，而是按段批量覆盖）
重新以 v 为基准，从左侧开始加入关键位，直到或值超限，得到 a[p] 自己的合法 L，单点写回线段树
以每个位置 k 为右端点，合法子段数是「k - L[k] + 1」。把 [l,r] 内的所有 k 各自对应的 (k - L[k] + 1) 累加即可。

用 find(l-1) 找到临界点 ps：

位置 ps 是「L[ps] < l」的最右边位置。也就是 [ps+1, r] 里的位置 L[k] ≥ l（起点被左侧边界 l 限制），而 [l, ps] 里的位置 L[k] ≤ l……需要仔细推敲分段。
配合 sgt::query 求 [ps+1, r] 的 L 总和，再与等差数列公式相加减，最终：

ans = 总子段数 - (被限制的那部分子段数)
总子段数 = (r-l+1)(r-l+2)/2，用它减去「起点不足 l」的部分，剩下的就是所有 L[k] 导致的合法子段计数。整个公式把离散的枚举压缩成了常数次线段树操作
对每个位置 i，从所有 20 位里，取出「该位出现的最近下标」（rbegin），按位置从右到左排。
从最近的位开始往左扫，逐步把对应位加入 nw，直到 nw 的 or 值（即位集合 1<<bit 的并）超过 X 为止，记录下还能到达的最左边界 L，单点写进线段树

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 0; i < n; ++i)
#define For(i,n) for (i = 1; i <= n; ++i)
#define ll long long
using namespace std;

constexpr int N = 1e5+5, M = 20;

namespace sgt {
    int mn[N<<2], cov[N<<2];
    ll s[N<<2];
    void update(int o) {
        mn[o] = min(mn[o<<1], mn[o<<1|1]);
        s[o] = s[o<<1] + s[o<<1|1];
    }
    void push_down(int o, int len) {
        int &x = cov[o];
        cov[o<<1] = cov[o<<1|1] = mn[o<<1] = mn[o<<1|1] = x;
        s[o<<1] = x*(ll)((len+1)>>1), s[o<<1|1] = x*(ll)(len>>1), x = 0;
    }
    void modify(int l, int r, int o, const int &L, const int &R, const int &val) {
        if (L <= l && r <= R) cov[o] = mn[o] = val, s[o] = (r-l+1ll)*val;
        else {
            if (cov[o]) push_down(o, r-l+1);
            const int mid = (l+r)>>1;
            if (L <= mid) modify(l, mid, o<<1, L, R, val);
            if (mid < R) modify(mid+1, r, o<<1|1, L, R, val);
            update(o);
        }
    }
    ll query(int l, int r, int o, const int &L, const int &R) {
        if (L <= l && r <= R) return s[o];
        if (cov[o]) push_down(o, r-l+1);
        const int mid = (l+r)>>1;
        ll res = 0;
        if (L <= mid) res += query(l, mid, o<<1, L, R);
        if (mid < R) res += query(mid+1, r, o<<1|1, L, R);
        return res;
    }
    int find(int l, int r, int o, const int &v) {
        if (mn[o] > v) return 0;
        if (l == r) return l;
        if (cov[o]) push_down(o, r-l+1);
        const int mid = (l+r)>>1;
        int res = find(mid+1, r, o<<1|1, v);
        if (res == 0) res = find(l, mid, o<<1, v);
        return res;
    }
}

int a[N], st[M+2], top, stk[M+2], tk, n, X;
set<int> pos[M];
void modify(int p, int v) {
    int i;
    rep(i,M) if (a[p]>>i&1) pos[i].erase(p);//从旧值的每位集合中删掉 p
    a[p] = v;
    rep(i,M) if (v>>i&1) pos[i].insert(p);//把 p 插回到新值的每位集合
    tk = top = 0;
    rep(i,M) {
        auto it = pos[i].upper_bound(p);
        if (it != pos[i].end()) st[++top] = *it<<5|i;
        if (it != pos[i].begin()) stk[++tk] = *--it<<5|i;
    }
    sort(st+1, st+top+1), sort(stk+1,stk+tk+1, greater());
    st[top+1] = (n+1)<<5, stk[tk+1] = 0, st[0] = (p+1)<<5;
    int t = (stk[1]>>5)+1, nw = 0, zt = 0;
    For(i,tk) zt |= 1<<(stk[i]&31);//左侧所有位组成的"位集合"
    for (int i = 0, it = tk; i <= top; ++i) {
        int l = st[i]>>5, r = (st[i+1]>>5)-1;
        if (i) nw |= 1<<(st[i]&31);//已包含的右侧位
        if (nw > X) break;//右侧位集合已超限，停止
        while (it && (zt|nw) > X) zt ^= 1<<(stk[it--]&31);//左侧逐步收缩，直到位集合≤X
        int L = (stk[it+1]>>5) + 1;//该分段的合法左起点
        if (l <= r) sgt::modify(1, n, 1, l, r, L);//整段赋同一 L
    }
    nw = v;
    For(i,tk) {
        nw |= 1<<(stk[i]&31);
        if (nw > X) break;
        t = (stk[i+1]>>5) + 1;
    }
    sgt::modify(1, n, 1, p, p, t);
}

ll query(int l, int r) {
    int ps = sgt::find(1, n, 1, l-1);
    ps = max(ps, l-1), ps = min(ps, r);
    ll ans = ps+1 <= r ? -sgt::query(1, n, 1, ps+1, r) : 0;
    ans += r - ps;
    ans += (ps-l+2)*(ps-l+1ll)/2;
    ans += (r+ps+1ll)*(r-ps)/2;
    ans = (r-l+1ll)*(r-l+2)/2 - ans;
    return ans;
}

int m, i, w, j, op, l, r;
int main() {
    fast;
    cin >> n >> m >> X; --X;
    For(i,n) {
        cin >> a[i], top = 0;
        rep(w,M) {
            if (a[i]>>w&1) pos[w].insert(i);//维护全局的"第 w 位出现位置"
            if (!pos[w].empty()) st[++top] = *pos[w].rbegin()<<5|w;//取出该位最近一次出现
        }
        sort(st+1, st+top+1, greater());//按位置倒序（最近的在前）
        st[top+1] = 0;
        int nw = 0, L = (st[1]>>5) + 1;//初始 L = 最近关键位位置 + 1
        For(j,top) {
            nw |= 1<<(st[j]&31);//把第 j 近的关键位加入位集合
            if (nw > X) break;//位集合超限，停止
            L = (st[j+1]>>5) + 1;//否则 L 更新为更左的边界
        }
        sgt::modify(1, n, 1, i, i, L);//单点写入线段树
    }
    while (m--) {
        cin >> op >> l >> r;
        if (op == 1) modify(l, r);//单点改值，局部更新受影响区段
        else cout << query(l, r) << '\n';//区间查询合法子段数
    }
    return 0;
}