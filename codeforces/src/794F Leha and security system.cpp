//
// Created by Psy.C on 2026/9/16.
//
/**
每个节点两个 10 数组：
f[i][j]：映射函数（懒标记）。若 f[i][j] == j 表示无待下推的变化；否则表示"本节点的 j 应变为 f[i][j]"。
dt[i][j]：实际统计的贡献和
叶子节点 l==r：
for (int x=a[l], cnt=1; x; x/=10)：把数 a[l] 的每一位拆出来。
x%10 取个位当前位。
cnt 从 1 开始，每处理一位乘 10（cnt = cnt*10，这里用 (cnt<<1)+(cnt<<3) 等价 cnt*10）→ cnt 表示当前位的位权（1,10,100…）。
dt[i][x%10] += cnt * max(x%10,1)：把该位的贡献 位权 × 位值 累加到对应数字位。注意 max(x%10,1) 又是防 x%10=0 用 1 代替（0 位贡献本来就是 0，乘不乘都行，只是规范）。
特判 a[l]==0：数本身为 0，单独把 dt[i][0]=1 表示这个 0 的贡献是 1（值 0 —— 实际贡献应为 0，此处设 1 是为了后面积分/替换时不丢位，属于该题的特殊约定）。
内部节点：左右孩子 dp 数组逐位相加，f[i][j]=j（初始无映射）。
⚠️ 这里 max(x%10,1) 与之对应，替换时 dt/dt 用 max(x,1) 做分母，都是为了统一"0 的特殊处理"，保证 dt[0] 可以 "还原为 1 个单位" 且不错位
当父节点有懒标记（即 f[i] 不是恒等映射）时，把这个变化下推到左右孩子：
先把左右孩子的 dt 和 f 快照到 d1/d2、lz1/lz2（避免在遍历中改坏）。
对每个被改动的 x（f[i][x] != x）：
y = f[i][x] 目标值。
把父的 dt 按 x→y 转移到孩子：dt[c][y] += dt[c][x]/max(x,1)*max(y,1)，dt[c][x] -= dt[c][x]（清 0）。
更新孩子的 f 映射：若孩子里某个 j 当前映射到 x，则改映射到 y。
这就是标准的双重映射懒标记下推（处理好"孩子已有其他映射要合成"）
完全覆盖 [L,R]：直接在本节点做替换——把 dt[x] 的贡献转移到 dt[y]（dt[y] += dt[x]/x*y，dt[x]=0），并更新映射 f。
否则下推懒标记再递归左右，最后合并（pull up)
完全覆盖：把 dt[j]（j=1..9）全加起来就是区间和。注意从 j=1 开始，j=0 那位的贡献不算入和（因为 0 位没有真正的数值，只是占位）。
否则下推后递归求和
读入 n、m，建树，m 次操作：
opt==1：读 x、y，对 [l,r] 做 digit 替换。
否则（opt==2）：查询 [l,r] 的和。
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 1e5+10, M = N<<2;
//原数组
int a[N], f[M][10];//懒标记：f[节点][数字j] = 当前 j 实际被映射成哪个数字
ll dt[M][10];//dt[节点][数字j] = 该区间数字位 j 的总贡献（位权加权和）
void build(int i, int l, int r) {
    if (l == r || l > r) {
        if (l == r) {
            for (int x = a[l], cnt = 1; x; x /= 10)
                dt[i][x%10] += cnt*max(x%10, 1), cnt = (cnt<<1)+(cnt<<3);
            if (!a[l]) dt[i][0] = 1;
        }
        for (int j = 0; j < 10; j++) f[i][j] = j;
        return;
    }
    if (l > r) return;
    int mid = (l + r) >> 1;
    build(i<<1, l, mid), build(i<<1|1, mid+1, r);
    for (int j = 0; j < 10; j++)
        dt[i][j] = dt[i<<1][j] + dt[i<<1|1][j], f[i][j] = j;
}

ll d1[10], d2[10];
int lz1[10], lz2[10];
inline void pushdown(int i) {
    for (int j = 0; j < 10; j++) {
        d1[j] = dt[i<<1][j], d2[j] = dt[i<<1|1][j];
        lz1[j] = f[i<<1][j], lz2[j] = f[i<<1|1][j];
    }
    for (int x = 0, y; x < 10; x++) if (f[i][x]^x) {
        y = f[i][x], f[i][x] = x;
        dt[i<<1][y] += d1[x]/max(x, 1)*max(y, 1), dt[i<<1][x] -= d1[x];
        dt[i<<1|1][y] += d2[x]/max(x, 1)*max(y, 1), dt[i<<1|1][x] -= d2[x];
        for (int j = 0; j < 10; j++) {
            if (lz1[j] == x) f[i<<1][j] = y;
            if (lz2[j] == x) f[i<<1|1][j] = y;
        }
    }
}
void modify(int i, int l, int r, int L, int R, int x, int y) {
    if (x == y) return;
    if (l >= L && r <= R) {
        dt[i][y] += dt[i][x]/max(x, 1)*max(y, 1), dt[i][x] = 0;
        for (int j = 0; j < 10; j++)
            if (f[i][j] == x) f[i][j] = y;
        return;
    }
    pushdown(i);
    int mid = (l + r) >> 1;
    if (L <= mid) modify(i<<1, l, mid, L, R, x, y);
    if (R > mid) modify(i<<1|1, mid+1, r, L, R, x, y);
    for (int j = 0; j < 10; j++)
        dt[i][j] = dt[i<<1][j] + dt[i<<1|1][j];
}
ll query(int i, int l, int r, int L, int R) {
    if (l >= L && r <= R) {
        ll sum = 0;
        for (int j = 1; j < 10; j++) sum += dt[i][j];
        return sum;
    }
    if (l > R || r < L) return 0;
    pushdown(i);
    int mid = (l + r) >> 1;
    return query(i<<1, l, mid, L, R) + query(i<<1|1, mid+1, r, L, R);
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m;
int main() {
    n = rd(), m = rd();
    int opt, l, r, x, y;
    for (int i = 1; i <= n; i++) a[i] = rd();
    build(1, 1, n);
    while (m--) {
        opt = rd(), l = rd(), r = rd();
        if (opt == 1)
            x = rd(), y = rd(), modify(1, 1, n, l, r, x, y);
        else printf("%lld\n", query(1, 1, n, l, r));
    }
    return 0;
}