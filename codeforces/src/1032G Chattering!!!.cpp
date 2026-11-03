//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
N = 300010：数组容量上界（因为数组被复制 3 份，3n 最大约 3e5）。
M = 19：倍增/ST 表的层数上限（因为 2^19 = 524288 > 3e5，能满足区间 3n 的倍增查询
lg[i]：预计算的"以 2 为底 i 的对数下取整"，供 ST 表和倍增使用
val[i]：存下标 i 对应的实际数值。
type：表示“取最大还是取最小”的标志（下面 get 里用到符号）。
a[i][j]：ST 表，a[i][j] 存的是"从下标 i 开始、长度为 2^j 的区间里最值所在的下标"
get(x, y)：比较下标 x、y 的实际值 val[x] 与 val[y]，返回较大值所在的下标。
注意：这里始终返回"值更大"的下标，但配合 type 的符号：

type=1 时 val 是正数，取的就是真实最大值下标；
type=-1 时 val 是负数，val[x] < val[y] 比较的是负数，数值更小（负数绝对值更大）的会被当作"更大"返回，实际等价于取最小值的下标
build 方法构造 ST 表：

type = t 记录取最大还是最小。
第一轮 j=0：a[i][0] = i（长度为 1 的区间就是 i 自己），val[i] = type * b[i]（对原数组乘上符号）。
后续 j 层：a[i][j] 由两个长度为 2^(j-1) 的区间合并得到：
a[i][j] = get(a[i][j-1], a[i+2^(j-1)][j-1])，即左半区间最值下标与右半区间最值下标比较，取更大者
query(l, r)：查询区间 [l, r] 的最值下标：

k = lg[区间长度],取能覆盖整个区间的最大 2 的幂。
用两个长度为 2^k 的区间（[l, l+2^k-1] 和 [r-2^k+1, r]）覆盖 [l,r]，两者取 get 即可（ST 表经典两段覆盖技巧）
a[N]：存原始数（后被复制成 3 份）。
b[N]、c[N]：每个下标 i 的可扩张区间的左端 b[i] 和右端 c[i]。
l[i][j]、r[i][j]：倍增跳表，第 i 层、以下标 j 为起点经过 2^i 步扩张得到的区间左右端。
读入 n
从 2 到 3n 计算 lg[i] = lg[i/2] + 1，即 i 的 log2 下取整。经典预处理，供 ST 表和倍增查询用
读入 n 个数到 a[1..n]，并复制到后面两份：
a[i+n] = a[i]、a[i+2n] = a[i]，这样数组长度变成 3n，从而把环（循环数组）摊平成一条长度为 3n 的链，方便处理跨越末位的区间
若只有一个数（n=1），直接输出 "0 " 并结束。因为环上就 1 个点，无需任何扩张，答案为 0。
对每个下标 i（在 3n 的展开数组上）：

b[i] = max(1, i - a[i])：向左最多能覆盖到 i - a[i]（但不能小于 1），即从左边界起；
c[i] = min(3n, i + a[i])：向右最多覆盖到 i + a[i]（不能超过 3n），即右边界。
也就是说，从位置 i 出发一趟能覆盖 [i - a[i], i + a[i]]，乘以 a[i] 的幅度
边界处理：所有层里，位置 3n 的右端锁定为 3n，位置 1 的左端锁为 1（避免越界）
第 0 层（也就是"走 1 趟"）：l[0][i] = b[i]，r[0][i] = c[i]，即每个下标扩张 1 次后的区间
L（type=-1）：对左端点数组 l[0] 建"最小值"ST 表，用于查询区间左端的最小值。
R（type=1）：对右端点数组 r[0] 建"最大值"ST 表，用于查询区间右端的最大值。
这里是核心的 倍增扩张：从"走 2^(i-1) 趟"得到的结果继续走 2^(i-1) 趟，从而得到"走 2^i 趟"的结果。

对每个起点 j：

先求出当前区间 [l[i-1][j], r[i-1][j]] 内部的：
pl：左端点数组最小值所在下标；
pr：右端点数组最大值所在下标。
那么从区间内最左端和最右端继续扩张 2^(i-1) 趟，综合两者：
真正的左端 = 这两个扩张结果左端的 min；
真正的右端 = 这两个扩张结果右端的 max。
这样 l[i][j]、r[i][j] 就表示 从 j 出发，扩张 2^i 趟能覆盖到的区间
这里对 j = n+1 到 2n 的每个位置（即展开数组的中间那一份，对应环上的每个真实元素）求答案。思路是"用最大的步数贪婪逼近答案"，类似倍增求 LCA：

u = v = j，表示从 j 出发，当前覆盖区间的左右端都以 j 为起点（当前区间就是 [j,j]）。
ans = 0 统计趟数。
外层从大步到小步（i 从大到小）‍:对每一层 i：

若"扩张 2^i 趟后，覆盖长度 >= n"，说明这一步跨过了环一周，没必要加，直接 continue（跳过，尝试更小的步）。
否则，说明还能安全扩张 2^i 趟：
用 RMQ 查当前区间 [l[i][u], r[i][v]] 的最左端 nu 和最右端 nv；
更新 u = nu, v = nv；
ans += 2^i 累加趟数。
循环结束后 ans++：因为最后差的最后一步（不足整 2 的幂的那一步）要补 1，所以答案 +1。

最后输出 ans，每个 j 输出一个答案，用空格隔开，末尾换行
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 3e5+10, M = 19;

int lg[N];
struct Rmq {
    int val[N], type, a[N][M];
    int get(int x, int y) { return val[x] < val[y] ? y : x; }
    void build(int *b, int n, int t) {
        type = t;
        rep(i,n) a[i][0] = i, val[i] = type*b[i];
        rep(j,lg[n]) rep(i,n-(1<<j)+1) a[i][j] = get(a[i][j-1],a[i+(1<<(j-1))][j-1]);
    }
    int query(int l, int r) {
        int k = lg[r-l+1];
        return get(a[l][k],a[r-(1<<k)+1][k]);
    }
} L, R;


int n, a[N], b[N], c[N], l[M][N], r[M][N];
int main() {
    fast;
    cin >> n;
    for (int i = 2; i <= 3*n; i++) lg[i] = lg[i>>1]+1;
    rep(i,n) {
        cin >> a[i];
        a[i+n] = a[i+n*2] = a[i];
    }
    if (n == 1) return cout << "0 \n", 0;
    rep(i,3*n) {
        b[i] = max(1,i-a[i]);
        c[i] = min(3*n,i+a[i]);
    }
    for (int i = 0; i <= lg[3*n]; i++) r[i][3*n] = 3*n;
    for (int i = 0; i <= lg[3*n]; i++) l[i][1] = 1;
    rep(i,3*n) { l[0][i] = b[i]; r[0][i] = c[i]; }
    L.build(l[0], n*3, -1); R.build(r[0], n*3, 1);
    rep(i,lg[3*n]) rep(j,3*n) {
        int pl = L.query(l[i-1][j],r[i-1][j]), pr = R.query(l[i-1][j],r[i-1][j]);
        l[i][j] = min(l[i-1][pl], l[i-1][pr]);
        r[i][j] = max(r[i-1][pl], r[i-1][pr]);
    }
    for (int j = n+1; j <= n*2; j++) {
        int u = j, v = j, ans = 0;
        for (int i = lg[3*n]; i >= 0; i--) {
            if (max(r[i][v], r[i][u]) - min(l[i][u],l[i][v]) + 1 >= n) continue;
            int nu = L.query(l[i][u],r[i][v]), nv = R.query(l[i][u],r[i][v]);
            u = nu; v = nv;
            ans += 1<<i;
        }
        ans++;
        cout << ans << ' ';
    }
    cout << '\n';
    return 0;
}