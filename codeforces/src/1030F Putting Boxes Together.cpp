//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
关键变换 a[i] -= i（把"数字 + 下标"问题转成纯数字轴上的点）
s1[o]：权值和；s2[o]：a[i]*w[i] 之和（取模 mod）。push_up 合并。
qry1 返回区间权值和。带权中位数 = 使得左侧权值和 ≥ 总权值一半的位置 pos。
find 在树中二分定位这个 pos（利用 s1）
对某段
[
l
,
r
]
[l,r]，
∑
w
i
∣
a
i
−
a
p
o
s
∣
∑w
i
​
 ∣a
i
​
 −a
pos
​
 ∣ 分左右计算：
右侧（
a
i
≥
a
p
o
s
a
i
​
 ≥a
pos
​
 ）：
∑
a
i
w
i
−
a
p
o
s
∑
w
i
∑a
i
​
 w
i
​
 −a
pos
​
 ∑w
i
​
 ；
左侧同理用减法。合并即答案。
单点更新 w 及其加权和

s1、s2 是两棵（线段树的）数组；a[i] 是每点的坐标
父节点 = 左右孩子对应求和
把位置 x 的权值改成 v，同时维护它对应的加权和。
查询区间
[
L
,
R
]
[L,R] 的权值和 Σw[i]
查询
[
L
,
R
]
[L,R] 内 Σ a[i]*w[i]（取模）
带权中位数：目标是找到位置 pos，使区间内左侧累加权值 ≥ 总权值一半。
find 配合 sum（待满足的权值）在树里二分定位这个位置
递归建树，叶子存权值 w[l] 与 a[l]*w[l]
对区间
[
l
,
r
]
[l,r]，计算
∑
w
i
(
a
i
−
a
p
o
s
)
∑w
i
​
 (a
i
​
 −a
pos
​
 )（右侧即 a_i ≥ a_{pos} 的部分，正值）。
用 s2（权值×坐标）减去 s1×a[pos]（权值和 × 基准坐标）得到

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
#define lc o<<1
#define rc (o<<1|1)
#define mid ((l+r)>>1)
#define ls lc, l, mid
#define rs rc, mid+1, r
using namespace std;

constexpr int N = 2e5+10, mod = 1e9+7;

ll s1[N<<2], s2[N<<2];
int a[N];
void push_up(int o) {
    s1[o] = s1[lc] + s1[rc];
    s2[o] = (s2[lc] + s2[rc]) % mod;
}
void update(int o, int l, int r, int x, int v) {
    if (l == r) {
        s1[o] = v; s2[o] = 1ll*v*a[l]%mod;//权值改为 v  权值×坐标 = v * a[l] (取模)
        return;
    }
    //x 在左半, 递归左 x 在右半, 递归右
    if (mid >= x) update(ls, x, v); else update(rs, x, v);
    push_up(o);//回溯合并
}

//区间权值和（s1）
ll qry1(int o, int l, int r, int L, int R) {
    if (L <= l && r <= R) return s1[o];
    ll ans = 0;
    if (mid >= L) ans += qry1(ls, L, R);//左半有交集
    if (mid < R) ans += qry1(rs, L, R);//右半有交集
    return ans;
}

//区间加权和（s2）
int qry2(int o, int l, int r, int L, int R) {
    if (L <= l && r <= R) return s2[o];
    if (mid >= R) return qry2(ls, L, R);//只在左半
    if (mid < L) return qry2(rs, L, R);//只在右半
    return (qry2(ls, L, R) + qry2(rs, L, R)) % mod;//跨中间,两边求和
}

ll sum;//全局"剩余要找的权值"
int pos, w[N];//pos=结果位置, w[] 存权值(建树用)
void find(int o, int l, int r, int L, int R) {
    if (sum <= 0) return;//已经找到, 停止
    if (L <= l && r <= R) {
        if (l == r) { sum -= s1[o]; pos = r; return; }//叶子:记录答案
        if (sum > s1[lc]) sum -= s1[lc], find(rs, L, R);//左半不够,右移
        else find(ls, L, R);//左半就够,向左
        return;
    }
    if (mid >= L) find(ls, L, R);
    if (mid < R) find(rs, L, R);
}

void build(int o, int l, int r) {
    if (l == r) { s1[o] = w[l], s2[o] = 1ll*a[l]*w[l]%mod; return; }
    build(ls), build(rs);
    push_up(o);
}

int n;
int qry(int l, int r) {
    int t = qry2(1,1,n,l,r)-qry1(1,1,n,l,r)%mod*a[pos]%mod;
    if (t < 0) t += mod;
    return t;
}

int q;
int main() {
    fast;
    cin >> n >> q;
    rep(i,n) cin >> a[i], a[i] -= i;//读 a 并减去下标(坐标变换)
    rep(i,n) cin >> w[i];//读权值
    build(1, 1, n);//建树
    rep(i,q) {
        int x, y; cin >> x >> y;
        if (x < 0) update(1,1,n,-x,y);//把位置 -x 的权值改成 y
        else {
            sum = (1+qry1(1,1,n,x,y))/2, pos = 0;//目标=权值和一半(向上取整)
            find(1,1,n,x,y);//找到带权中位数 pos
            int ans = qry(pos,y) - qry(x,pos);//右半距离 - 左半距离
            if (ans < 0) ans += mod;
            cout << ans << '\n';//输出 |a_i - a_pos|*w_i 之和
        }
    }
    return 0;
}