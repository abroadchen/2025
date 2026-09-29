//
// Created by Psy.C on 2026/9/29.
//
/**
node 是一个长度 110 的数组，索引 0..m-1 存“余数为该值的计数/系数”。
三个全局对象 l、mid、r 分别对应卷积链的左端、中间、右端的多项式/频次分布。
110 是预留足够大的数组空间（m ≤ 100 时够用）
循环卷积（cyclic convolution）在模 m 指数下：把两个“余数分布”做卷积，指数 i+j 对 m 取模后累加。
含义：如果 x[i] 表示“某步骤结果 = i (mod m) 的计数”，则两个步骤的复合计数就是这种循环卷积。% mod 防溢出并取模 1e9+7
对 node（卷积）做快速幂，指数为 k 次卷积（即 x^k，k 次循环卷积）。
t 初始为 x 且 k--，等价于 x^k 的标准二进制快速幂（指数 k=0 时直接返回初值）。
用途：把 mid 自卷积 q-2 次，代表“中间部分重复 q-2 步”的复合
读 n 个数进 l：记录每个 x mod m 的频次。
读 n 个数进 mid（并临时存到 a[]）：记录 x mod m 频次。
读 n 个数进 r：记录 (x + a[i]) mod m 的频次（把第三组输入与 mid 的第二组对应元素相加再取模）。
这说明题目里有某种配对/对应关系：r 的组合依赖于先前读到的 a[i]
最终把 l、mid^(q-2)、r 三段按顺序做卷积，得到完整链的总计数分布 x。
若 q-2 ≤ 0 则中间部分不存在，直接只用 l ⊗ r。
最后答案 = 所有指数为 m 的倍数（即 j%m==0）的 num[j] 之和。因为题目要求“结果为 0 (mod m)”的计数总和
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+10, mod = 1e9+7;
struct node {
    long long num[110]{};
} l, r, mid;

int m;
static node mul(const node &x, const node &y) {
    node res;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j) {
            int k = (i+j)%m;//指数相加取模
            res.num[k] += x.num[i] * y.num[j] % mod;
            res.num[k] %= mod;
        }
    return res;
}

static node ksm(node x, int k) {
    node t = x; k--;
    while (k) {
        if (k&1) t = mul(t, x);
        k >>= 1;
        x = mul(x, x);
    }
    return t;
}

static int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int a[N];
int main() {
    fast;
    int n = rd(), q = rd(); m = rd();
    for (int i = 1; i <= n; ++i) { int x = rd(); l.num[x%m]++; }
    for (int i = 1; i <= n; ++i) { int x = rd(); a[i] = x; mid.num[x%m]++; }
    for (int i = 1; i <= n; ++i) { int x = rd(); r.num[(x+a[i])%m]++; }
    node x;
    if (q - 2 > 0) {
        x = ksm(mid, q-2);
        x = mul(x, l); x = mul(x, r);
    }
    else x = mul(l, r);
    long long ans = 0;
    for (int j = 0; j <= 100; ++j) {
        if (j%m == 0) {
            ans += x.num[j];
            ans %= mod;
        }
    }
    cout << ans << '\n';
    return 0;
}