//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
这是动态开点 + 回收复用：init() 分配一个节点号（优先从回收池 v 里取，空则用 ++tot）。
del(x) 清除节点 x 的三个字段并把它压回回收池 v
在区间 [l,r] 上对位置 pos 加减 d（d = ±1）。
递归更新，最后若该子树 sum 归零则整棵回收并置 0
普通线段树区间求和
外层是 BIT（按下标 1..n），内层是值域线段树 [1,n]。
modify(x, v, d)：把位置 x 处、值为 v 的点增减 d —— BIT 从 x 开始向上更新所有相关桶，每个桶内线段树更新位置 v。
query(l,r,x,y)：区间前缀差 —— 求 BIT 在下标 [l,r] 内、值域 [x,y] 内的点数（利用 prefix(r)-prefix(l-1)
建点：对每个 b[i]，在二维点集 (i, p[b[i]]) 处 +1。
操作 1（查询）‍：query(l2,r2,l1,r1) =
外层下标范围 [l2,r2]（b 的位置段），
内层值范围 [l1,r1]（a 的位置段），
结果 == b[l2..r2] 中元素其 a 位置落在 [l1,r1] 的个数 == 两区间的公共元素数。
操作 2（交换）‍：先把 (x,p[b[x]])、(y,p[b[y]]) 两个旧点 -1，交换 b[x]、b[y] 后，再对两个新点 +1，保持二维点集与 b 一致
*/
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 2e5+5;

vector<int> v;
int tot;
inline int init() {
    if (v.empty()) return ++tot;
    int x = v.back(); v.pop_back();
    return x;
}

int lc[N<<7], rc[N<<7], sum[N<<7];
inline void del(int x) { lc[x] = rc[x] = sum[x] = 0; v.push_back(x); }
void modify(int &o, int l, int r, int pos, int d) {
    if (!o) o = init();
    sum[o] += d;
    if (l < r) {
        if (pos <= mid) modify(lc[o],l,mid,pos,d);
        else modify(rc[o],mid+1,r,pos,d);
    }
    if (!sum[o]) del(o), o = 0;
}
int query(int o, int l, int r, int L, int R) {
    if (!o || L > r || R < l) return 0;
    if (L <= l && r <= R) return sum[o];
    return query(lc[o],l,mid,L,R) + query(rc[o],mid+1,r,L,R);
}

int n, rt[N];
inline void modify(int x, int v, int d) {
    for (; x <= n; x += x&-x) modify(rt[x],1,n,v,d);
}
inline int query(int l, int r, int x, int y) {
    int ans = 0;
    for (; r; r-=r&-r) ans += query(rt[r],1,n,x,y);
    for (--l; l; l-=l&-l) ans -= query(rt[l],1,n,x,y);
    return ans;
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<typename T,typename... Args>
void read(T& t,Args&... args) {
    read(t); read(args...);
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int m, p[N], b[N];
int main() {
    read(n,m);
    for (int i = 1, x; i <= n; ++i) read(x), p[x] = i;
    for (int i = 1; i <= n; ++i) read(b[i]), modify(i,p[b[i]],1);
    while (m--) {
        int q; read(q);
        if (q == 1) {
            int l1,r1,l2,r2; read(l1,r1,l2,r2);
            write(query(l2,r2,l1,r1)), putchar('\n');
        } else {
            int x, y; read(x, y);
            modify(x,p[b[x]],-1); modify(y,p[b[y]],-1);
            swap(b[x],b[y]);
            modify(x,p[b[x]],1); modify(y,p[b[y]],1);
        }
    }
    return 0;
}