//
// Created by Psy.C on 2026/10/9.
//
/**
tr：区间和。
at：加法懒标记（待下传的区间加值）。
mt：乘法懒标记（待下传的区间乘因子），初值 1
seta：给整段区间每个元素加 v → 区间和加 v*len，懒标记 at += v。
setm：整段区间每个元素乘 v → 区间和乘 v；乘法标记 mt*=v，同时已挂着的加法标记 at 也要乘 v（保证"先乘后加"语义正确）
先下传乘法，再下传加法（保证子节点 val = val·mul + add 的顺序）
build：建树，乘法标记初始 1，叶子赋 a[l]。
modify：区间加或乘（通过函数指针 f 决定用 seta 还是 setm）。
query：查询区间和，分段递归累加。
set(int p) 用函数指针 f 选择操作：p==1 用加法 seta，p==2 用乘法 setm。modify 内部调用 f(rt,l,r,v)
区间1：原 c 个元素，总和 t1。
区间2：原 d 个元素，总和 t2。

区间1最终每个元素值（先乘后加再乘，由于操作间顺序恰好是：乘(c-1)，加(t2/d)，乘(1/c)）：

设区间1第 i 个元素值
x
i
x
i
​
 ，原
T
1
=
∑
x
i
=
t
1
T
1
​
 =∑x
i
​
 =t
1
​
 。

步骤1（乘 c-1）：
x
i
→
x
i
(
c
−
1
)
x
i
​
 →x
i
​
 (c−1)
步骤2（加 t2/d）：
x
i
→
x
i
(
c
−
1
)
+
t
2
/
d
x
i
​
 →x
i
​
 (c−1)+t
2
​
 /d
步骤3（乘 1/c）：
x
i
→
[
x
i
(
c
−
1
)
+
t
2
/
d
]
⋅
(
1
/
c
)
=
x
i
c
−
1
c
+
t
2
d
c
x
i
​
 →[x
i
​
 (c−1)+t
2
​
 /d]⋅(1/c)=x
i
​

c
c−1
​
 +
dc
t
2
​

​

区间1最终总和 =
∑
i
(
x
i
c
−
1
c
+
t
2
d
c
)
=
c
−
1
c
T
1
+
t
2
d
∑
i
​
 (x
i
​

c
c−1
​
 +
dc
t
2
​

​
 )=
c
c−1
​
 T
1
​
 +
d
t
2
​

​
 .

区间2最终每个元素值：

步骤1（乘 d-1）：
y
j
→
y
j
(
d
−
1
)
y
j
​
 →y
j
​
 (d−1)
步骤2（加 t1/c）：
y
j
→
y
j
(
d
−
1
)
+
t
1
/
c
y
j
​
 →y
j
​
 (d−1)+t
1
​
 /c
步骤3（乘 1/d）：
y
j
→
y
j
d
−
1
d
+
t
1
d
c
y
j
​
 →y
j
​

d
d−1
​
 +
dc
t
1
​

​

区间2最终总和 =
d
−
1
d
T
2
+
t
1
c
d
d−1
​
 T
2
​
 +
c
t
1
​

​
 .

现在算总和不变量：最终总和中区间1+区间2
=
c
−
1
c
T
1
+
t
2
d
+
d
−
1
d
T
2
+
t
1
c
=
c
c−1
​
 T
1
​
 +
d
t
2
​

​
 +
d
d−1
​
 T
2
​
 +
c
t
1
​

​

=
T
1
−
T
1
c
+
T
2
d
+
T
2
−
T
2
d
+
T
1
c
=T
1
​
 −
c
T
1
​

​
 +
d
T
2
​

​
 +T
2
​
 −
d
T
2
​

​
 +
c
T
1
​

​

=
T
1
+
T
2
=T
1
​
 +T
2
​
 .
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+7;

int a[N];
namespace sgt {
    double tr[N<<3], at[N<<3], mt[N<<3];
#define lc(x) ((x)<<1)
#define rc(x) (((x)<<1)|1)
#define ls rt<<1, l, mid
#define rs (rt<<1)|1, mid+1, r
    void seta(int rt, int l, int r, double v) {
        tr[rt] += v*(r-l+1.0); at[rt] += v;
    }
    void setm(int rt, int l, int r, double v) {
        tr[rt] *= v;
        mt[rt] *= v; at[rt] *= v;
    }
    void (*f)(int, int, int, double);
    void set(int p) {
        if (p == 1) f = seta;
        if (p == 2) f = setm;
    }
    void push_down(int rt, int l, int r) {
        int mid = (l+r)>>1;
        if (mt[rt] != 1.0) {
            setm(ls, mt[rt]), setm(rs, mt[rt]);
            mt[rt] = 1;
        }
        if (at[rt] != 0.0) {
            seta(ls, at[rt]), seta(rs, at[rt]);
            at[rt] = 0;
        }
    }
    void push_up(int rt) { tr[rt] = tr[lc(rt)] + tr[rc(rt)]; }
    void build(int rt, int l, int r) {
        at[rt] = 0, mt[rt] = 1;
        if (l == r) { tr[rt] = a[l]; return; }
        int mid = (l+r)>>1;
        build(ls), build(rs); push_up(rt);
    }
    void modify(int rt, int l, int r, int L, int R, double v) {
        if (L > R) return;
        if (L <= l && r <= R) { f(rt, l, r, v); return; }
        int mid = (l+r)>>1; push_down(rt, l, r);
        if (R <= mid) modify(ls, L, R, v);
        else if (L > mid) modify(rs, L, R, v);
        else modify(ls, L, R, v), modify(rs, L, R, v);
        push_up(rt);
    }
    double query(int rt, int l, int r, int L, int R) {
        if (L <= l && r <= R) return tr[rt];
        int mid = (l+r)>>1; push_down(rt, l, r);
        if (R <= mid) return query(ls, L, R);
        if (L > mid) return query(rs, L, R);
        return query(ls, L, R) + query(rs, L, R);
    }
#undef lc
#undef rc
#undef ls
#undef rs
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, q;
void init() {
    n = rd(), q = rd();
    for (int i = 1; i <= n; ++i) a[i] = rd();
    sgt::build(1, 1, n);
}

void solve() {
    for (int i = 1; i <= q; ++i) {
        int op = rd();
        if (op == 1) {
            int l1 = rd(), r1 = rd(), l2 = rd(), r2 = rd();
            double c = r1-l1+1.0, d = r2-l2+1.0,
            t1 = sgt::query(1, 1, n, l1, r1),
            t2 = sgt::query(1, 1, n, l2, r2);
            sgt::set(2), sgt::modify(1, 1, n, l1, r1, c-1.0);
            sgt::set(2), sgt::modify(1, 1, n, l2, r2, d-1.0);
            sgt::set(1), sgt::modify(1, 1, n, l1, r1, t2/d);
            sgt::set(1), sgt::modify(1, 1, n, l2, r2, t1/c);
            sgt::set(2), sgt::modify(1, 1, n, l1, r1, 1/c);
            sgt::set(2), sgt::modify(1, 1, n, l2, r2, 1/d);
        }
        if (op == 2) {
            int l = rd(), r = rd();
            printf("%.7lf\n", sgt::query(1, 1, n, l, r));
        }
    }
}

int main() {
    fast;
    init(); solve();
    return 0;
}