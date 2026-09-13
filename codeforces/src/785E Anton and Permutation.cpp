//
// Created by Psy.C on 2026/9/13.
//
/**
node 是线段树节点：l 左孩子编号、r 右孩子编号、w 该区间权值和。
t[N*100]：开的动态线段树数组（节点总数上限 N×100，够大）。因为权值线段树是动态开点的，不可能预先开满 2n 个，所以要开大很多
权值线段树的单点插入：往位置 pos 加 val。
if (!x) x = ++cnt：动态开点——只用到的节点才分配，空间省。
递归到叶子更新 w，路径上每层 w += val
查询权值区间 [x,y] 的元素个数和（如果每个点存储该值出现次数的话）。
标准线段树区间查询：完全覆盖直接取 w，否则向下递归合并
外层是一维 BIT（按下标），内层每个位置是一棵权值线段树。
bit_insert(pos, val, w)：在"下标维度"为 pos、"值维度"为 val 的点上加权 w，BIT 基础上所有祖先线段树都插入。
bit_query(pos, x, y)：查询前 pos 个下标中，值落在 [x, y] 内的总权重（二维前缀和语义）

n 个数，初始 a[i] = i（一个排列 1..n），初始无逆序对。
把每个 (下标=i, 值=i) 插入二维 BIT，权重 1 表示"存在该 (下标,值) 点"
每次操作：交换位置 x 和 y 处的数值 a[x]、a[y]，然后输出当前数组的总逆序对数 ans。
if (a[x] < a[y]) ans++; else ans--;：交换前若 a[x]<a[y]，则 (x,y) 这对不是逆序（x<y 但值升序），交换后变成逆序 → 逆序数 +1；反之若 a[x]>a[y]，本来 (x,y) 是逆序，交换后消除 → −1
当交换 x、y 处的数时，除了 (x,y) 这一对，还要更新所有跨在 x-y 之间、与 a[x] 或 a[y] 构成的逆序对。
bit_query(y-1, L, R) - bit_query(x, L, R) = 下标在 (x, y) 开区间内（即 x+1..y-1）、值在 [L,R] 的元素个数。
结合交换前后 a[x]、a[y] 分别与中间元素的大小关系，决定该区间里每个中间元素引起的逆序对是 +1 还是 −1，从而整体调整 ans
交换后，二维 BIT 里对应两点也先删后插，保持数据结构与数组一致。
swap(a[x], a[y]) 同步数组
每次操作后输出当前总逆序对数
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 2e5+5;

struct node { int l, r, w; } t[N*100];

int cnt;
void insert(int& x, int l, int r, int pos, int val) {
    if (!x) x = ++cnt;
    t[x].w += val;
    if (l == r) return;
    int mid = (l+r)/2;
    if (pos <= mid) insert(t[x].l, l, mid, pos, val);
    else insert(t[x].r, mid+1, r, pos, val);
}

ll query(int now, int l, int r, int x, int y) {
    if (!now) return 0;
    if (x <= l && y >= r) return t[now].w;
    int mid = (l+r)/2;
    ll ans = 0;
    if (x <= mid) ans += query(t[now].l, l, mid, x, y);
    if (y > mid) ans += query(t[now].r, mid+1, r, x, y);
    return ans;
}

ll n;
int rt[N*100];//树状数组第 i 个节点对应的权值线段树根
void bit_insert(int pos, int val, int w) {
    while (pos <= n) {
        insert(rt[pos], 1, n, val, w);
        pos += pos&-pos;
    }
}
ll bit_query(int pos, int x, int y) {
    ll ans = 0;
    while (pos) {
        ans += query(rt[pos], 1, n, x, y);
        pos -= pos&-pos;
    }
    return ans;
}


template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

ll m;
int a[N];
int main() {
    rd(n), rd(m);
    for (int i = 1; i <= n; ++i)
        a[i] = i, bit_insert(i, i, 1);
    ll ans = 0;
    for (int i = 1, x, y; i <= m; ++i) {
        rd(x), rd(y);
        if (x == y) { printf("%lld\n", ans); continue; }
        if (x > y) swap(x, y);
        if (a[x] < a[y]) ans++; else ans--;
        if (a[x]+1 <= n) ans += bit_query(y-1, a[x]+1, n)-bit_query(x, a[x]+1, n);
        if (a[x]-1 >= 1) ans -= bit_query(y-1, 1, a[x]-1)-bit_query(x, 1, a[x]-1);
        if (a[y]+1 <= n) ans -= bit_query(y-1, a[y]+1, n)-bit_query(x, a[y]+1, n);
        if (a[y]-1 >= 1) ans += bit_query(y-1, 1, a[y]-1)-bit_query(x, 1, a[y]-1);
        bit_insert(x, a[x], -1);
        bit_insert(x, a[y], 1);
        bit_insert(y, a[y], -1);
        bit_insert(y, a[x], 1);
        swap(a[x], a[y]);
        printf("%lld\n", ans);
    }
    return 0;
}