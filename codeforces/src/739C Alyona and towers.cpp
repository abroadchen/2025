//
// Created by Psy.C on 2026/4/28.
//
/**
行数n、列数m和4×4的数据数组
声明多个矩阵实例
max-plus代数（不是普通矩阵乘法）
z.a[i][j] = max over k of (x.a[i][k] + y.a[k][j])
初始化单位矩阵e（对角线为0，其他为-inf）
初始化行向量f（全为0）
初始化矩阵B，A，C（用于不同情况的转移）

a数组：存储原数组和差分数组
n：数组长度
每个节点包含左右边界和区间乘积矩阵
递归构建线段树
叶子节点根据a[l]的值选择对应矩阵(A/B/C)
内部节点存储左右子树的矩阵乘积
单点更新操作
找到对应叶子节点并更新矩阵
向上传递更新信息
读入修改操作：区间[l,r]增加d
差分数组更新：a[l]+=d, a[r+1]-=d
更新线段树对应节点
输出查询结果

初始化，读入n
读入原数组
转换为差分数组（逆向操作）
构建线段树
读入查询次数q
执行q次修改和查询操作
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1200007, M = 3e5+7, inf = 1e9;
struct mtx { int n, m, a[4][4]; } e, f, A, B, C;
mtx operator*(const mtx& x, const mtx& y) {
    mtx z{}; z.n = x.n; z.m = y.m;
    for (int i = 0; i < x.n; ++i)
        for (int j = 0; j < y.m; ++j) {
            z.a[i][j] = -inf;
            for (int k = 0; k < x.m; ++k)
                z.a[i][j] = max(z.a[i][j], x.a[i][k] + y.a[k][j]);
        }
    return z;
}

void init() {
    e.n = e.m = 4;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            e.a[i][j] = i == j ? 0 : -inf;
    f.n = 1; f.m = 4; f.a[0][0] = f.a[0][1] = f.a[0][2] = f.a[0][3] = 0;
    B.n = B.m = 4;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            B.a[i][j] = i == 2 ? (j == 2 ? 0 : 1) : -inf;
    B.a[3][3] = 0; A = C = B;
    A.a[0][0] = A.a[0][3] = 1;
    C.a[0][1] = C.a[1][1] = C.a[0][3] = C.a[1][3] = 1;
}

ll a[M];
int n;
namespace sgt {
    struct node { int l, r; mtx prod; } t[N];
    void Build(int p, int l, int r) {
        t[p].l = l, t[p].r = r;
        if (l == r) {
            if (a[l] > 0) t[p].prod = A;
            else if (a[l] == 0) t[p].prod = B;
            else t[p].prod = C;
            return;
        }
        int mid = (l+r)>>1;
        Build(p<<1, l, mid), Build(p<<1|1, mid+1, r);
        t[p].prod = t[p<<1].prod*t[p<<1|1].prod;
    }
    void build() { Build(1, 1, n); }
    void Update(int p, int x) {
        if (t[p].l > x || t[p].r < x) return;
        if (t[p].l == x && t[p].r == x) {
            if (a[x] > 0) t[p].prod = A;
            else if (a[x] == 0) t[p].prod = B;
            else t[p].prod = C;
            return;
        }
        Update(p<<1, x); Update(p<<1|1, x);
        t[p].prod = t[p<<1].prod*t[p<<1|1].prod;
    }
    void update(int x) { Update(1, x); }
    int query() { return (f*t[1].prod).a[0][3]; }
}


void out() {
    int l, r, d; cin >> l >> r >> d; a[l] += d;
    sgt::update(l);
    if (r != n) {
        a[r+1] -= d;
        sgt::update(r+1);
    }
    cout << sgt::query() << '\n';
}

int q;
int main() {
    fast;
    init(); cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = n; i >= 1; --i) a[i] -= a[i-1];
    sgt::build(); cin >> q;
    while (q--) out();
    return 0;
}