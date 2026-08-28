//
// Created by Psy.C on 2026/8/28.
//
/**
- N = 5 ： 状态数量 ，整个系统有 5 种状态（编号 0~4），用 N×N 矩阵表示状态间的转移。
- M = 200005 ： 序列长度上限 （最多 20 万个位置）
封装一个 5×5 的整数矩阵
把矩阵的每个元素都初始化为 0x3f3f3f3f （十进制约 10 亿），这是 无穷大哨兵值 ——在 min 运算中，它代表"不可达"。
为什么用 0x3f ？因为 0x3f3f3f3f 的两倍 ≈ 21 亿 不超过 int 上限，做加法不会溢出
- x.mat[i][k] ：从状态 i 经过变换 x 到状态 k 的最小代价。
- y.mat[k][j] ：从状态 k 经过变换 y 到状态 j 的最小代价。
- x * y 的 mat[i][j] ：从状态 i 先经过变换 x 再经过变换 y ，到达状态 j 的 最小代价 （枚举中间状态 k 取最小）。
这正好满足 结合律 ： (A*B)*C = A*(B*C) ，所以可以用线段树维护
只计算 第 0 行 的结果。等价于把 x 看作一个行向量 [1×5] （只关心状态 0 的起始行），然后乘以矩阵 y
- 为什么叫 operator^ （异或）？因为普通乘法已经被 * 占用了，用 ^ 做区分（不表示真正的异或运算）。
- 作用：线段树查询时，初始状态向量（只有一行）乘以区间合并矩阵，得到最终状态
smt[M<<2] mtx[4M] 线段树 ，每个节点存一个 5×5 变换矩阵。 M<<2 = 4*M = 80万
ans mtx 查询时的 临时结果矩阵 （只用到第 0 行）
prim mtx 初始状态矩阵 ， prim.mat[0][0] = 0 表示从状态 0 出发、0 代价，其他都是无穷大
g[M] mtx[M] 每个位置 i 对应的 单点变换矩阵 （下标 1~n）

- p ：当前节点编号。
- l , r ：当前节点维护的区间 [l, r] 。
- l == r ：叶子节点，直接存单点变换矩阵 g[l] 。
- smt[p] = smt[左子树] * smt[右子树] ： 先执行左边所有变换，再执行右边所有变换 （注意顺序！矩阵乘法不交换）
- ans 初始为单位矩阵 prim （只含状态 0 出发的信息）。
- 每遇到一个完全在查询区间内的线段树节点，就做 ans = ans ^ smt[p] ，把这段变换 叠加 到当前结果上。
- 因为 ^ 只算第 0 行，最终 ans.mat[0][4] 就是初始状态 0 经过整个区间变换后到达状态 4 的最小代价

- n ：序列长度（字符个数）。
- p ：查询次数。
- prim.mat[0][0] = 0 ：设置初始状态矩阵——从状态 0 出发、0 代价可达状态 0。其他状态的代价仍为无穷大（构造函数初始化的）
- static char s ：静态局部变量，复用内存。
- 读入第 i 个字符 存入 s （是 '2' / '0' / '1' / '7' / '6' 之一）。
- 初始化单位变换 ： g[i].mat[j][j] = 0 表示每个状态 j 可以"原地不动"（代价 0）。这是 单位矩阵 的 min-plus 版本
在状态 0 时遇到字符 2 ：
- g[i].mat[0][0] = 1 ：继续停留在状态 0，代价 +1 。
- g[i].mat[0][1] = 0 ：或者 跃迁到状态 1 ，代价 0 。
- 其他状态到状态 0/1 的路径仍是无穷大（不可达）
在状态 1 时遇到字符 0 ：
- 停留在状态 1：代价 +1。
- 跃迁到状态 2：代价 0
在状态 2 时遇到字符 1 ：
- 停留在状态 2：代价 +1。
- 跃迁到状态 3：代价 0
在状态 3 时遇到字符 7 ：
- 停留在状态 3：代价 +1。
- 跃迁到状态 4（ 最终目标状态 ）：代价 0
字符 6 比较特殊：
- g[i].mat[3][3] = 1 ：状态 3 停留代价 +1。
- g[i].mat[4][4] = 1 ： 已经在状态 4 的话 ，停留代价也是 +1（状态 4 自身有循环）。
- 注意： g[i].mat[4][4] 原来已经被初始化为 0，这里改成 1 表示状态 4 不能免费停留了
调用线段树建树函数，把 g[1] ~ g[n] 的单点变换矩阵按 min-plus 乘法合并到 smt 线段树中
1 static int l, r; cin >> l >> r 读查询区间 [l, r]
2 ans = prim 重置结果为 初始状态矩阵 （只有状态 0 出发，代价 0）
3 query(1, 1, n, l, r) 在线段树中查询区间 [l, r] ，把所有变换叠加到 ans
4 ans.mat[0][4] 从状态 0 出发，经过整个区间的变换后到达状态 4 的 最小代价
5 <= n ? ans.mat[0][4] : -1 代价不超过 n （合理范围）就输出，否则输出 -1 （不可达）

建树 O(n × N³) = O(n × 125) ≈ 千万级
每次查询 O(log n × N³)
总时间 O((n+p) × 125 × log n)
空间 线段树 4M × 25 ≈ 80 万 × 5 × 5 × 4 字节 ≈ 80MB
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 5, M = 2e5+5;

struct mtx {
    int mat[N][N];
    mtx() { memset(mat, 0x3f, sizeof(mat)); }
    mtx friend operator*(mtx x, mtx y) {
        mtx res;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                for (int k = 0; k < N; ++k)
                    res.mat[i][j] = min(res.mat[i][j], x.mat[i][k] + y.mat[k][j]);
        return res;
    }
    mtx friend operator^(mtx x, mtx y) {
        mtx res;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                res.mat[0][i] = min(res.mat[0][i], x.mat[0][j] + y.mat[j][i]);
        return res;
    }
} smt[M<<2], ans, prim, g[M];


void build(int p, int l, int r) {
    if (l == r) { smt[p] = g[l]; return; }
    int mid = (l + r) >> 1;
    build(p<<1, l, mid); build(p<<1|1, mid+1, r);
    smt[p] = smt[p<<1] * smt[p<<1|1];
}

void query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) { ans = ans ^ smt[p]; return; }
    int mid = (l + r) >> 1;
    if (ql <= mid) query(p<<1, l, mid, ql, qr);
    if (mid < qr) query(p<<1|1, mid+1, r, ql, qr);
}

int n, p;
int main() {
    fast;
    cin >> n >> p; prim.mat[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        static char s; cin >> s;
        for (int j = 0; j < N; ++j) g[i].mat[j][j] = 0;
        if (s == '2') { g[i].mat[0][0] = 1; g[i].mat[0][1] = 0; }
        if (s == '0') { g[i].mat[1][1] = 1; g[i].mat[1][2] = 0; }
        if (s == '1') { g[i].mat[2][2] = 1; g[i].mat[2][3] = 0; }
        if (s == '7') { g[i].mat[3][3] = 1; g[i].mat[3][4] = 0; }
        if (s == '6') { g[i].mat[3][3] = 1; g[i].mat[4][4] = 1; }
    }
    build(1, 1, n);
    for (int i = 1; i <= p; ++i) {
        static int l, r; cin >> l >> r;
        ans = prim;
        query(1, 1, n, l, r);
        cout << (ans.mat[0][4] <= n ? ans.mat[0][4] : -1) << '\n';
    }
    return 0;
}