//
// Created by Psy.C on 2026/9/9.
//
/**
pw[i] = 2^i mod，用于后面加权
s0：集合元素个数（count）。
s1：元素值的和（sum）。
s2：元素值平方的和（sum of squares）。
单元素构造 node(x)：{1, x, x²}。
operator+ 定义为合并两个集合的统计信息：
合并时元素个数相加：s0 + o.s0。
求和：两组各元素仍然相加，但每组内部元素个数不同，求和需要按"每个集合里元素个数"加权。这里用了 pw[o.s0]（=2^{o.s0}）和 pw[s0]（=2^{s0}），表示把另一组所有子集组合的贡献合并。实际上这是在做一个按幂加权的迪利克雷/Dilar组合，本质是 SOS 卷积下的"合并两组并产生新集合对"的统计。
平方和：s2*pw[o.s0] + 2*s1*o.s1 + pw[s0]*o.s2，利用 (a+b)²=a²+2ab+b² 展开，每组分别乘上对方子集数。
这里的 operator+ 实质是子集（超集）卷积的合并算子——当合并两个不相交集合时，交叉项 2*s1*o.s1 正是 2·(sum_a)·(sum_b)，对应所有 (a 中的元素 + b 中的元素) 的配对，也就是统计"从两个集合各取一个数组合成新数的和'"
读入 n；预处理 2 的幂 pw。
读入 n 个数 x，每个都 f[x] = f[x] + node(x)：把元素 x 并入下标为 x 的集合。这样 f[pos] 记录了"值恰为 pos 的重复元素的个数/和/平方和"（同一值出现多次会合并）
这是 SOS DP 的双方向第一段：对每个十进制位，做超集前缀和（累加所有"某一位比 j 大"的下标的 f）。
具体：cur 依次为 1,10,100,...,100000（六位）。对每个 j，若 j 在当前位的数字不是 9（即 (j/cur)%10 != 9），则 j+cur 有效，把 f[j+cur]（当前位比 j 大 1 的下标的集合）合并进 f[j]。由于顺序从大到小，最终 f[j] 会包含所有"在任意个十进制位上大于等于 j 对应位"的下标的累计（即超集：所有满足逐位 >= j 的坐标的统计）。
这一步得到的是：f[j] = （值域中所有"逐位不小于 j"的数的集合）合并后的 node，记录了这些数的个数、和、平方和
先把每个下标的 s2（平方和）取出来作为初始 ret。
再做逆变换（莫比乌斯/差分）‍：把刚才的超集求和撤销，得到每个下标 j"恰好等于那个超集的补——即只有被禁止位为 j 的那些"的贡献。实际上这是一次容斥恢复：ret[j] -= ret[j+cur] 把 j+cur 带来的超额部分减掉，六轮后 ret[j] 就表示"值为 j 的（按 xor 定义）实际贡献"。
这一步的作用是：把之前的超集和转回"精确等于某值"的贡献，得到一个 ret 数组，其中 ret[j] 是"所有能通过逐位覆盖归于 j 的配对贡献之和"
对每个下标 j，计算 j * ret[j]（下标乘以其精确贡献），再对所有 j 做按位异或（^=）累加。
输出最终答案 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6, mod = 1000000007;

int pw[N+5];
struct node {
    int s0, s1, s2;
    node() { s0 = s1 = s2 = 0; }
    node(int x) { s0 = 1; s1 = x; s2 = 1ll*x*x%mod; }
    node(int _s0, int _s1, int _s2) : s0(_s0), s1(_s1), s2(_s2) {}
    node operator+(const node& o) const {
        return node(
            s0+o.s0, (1ll*s1*pw[o.s0]+1ll*pw[s0]*o.s1)%mod,
            (1ll*s2*pw[o.s0]%mod+2ll*s1*o.s1+1ll*pw[s0]*o.s2)%mod
        );
    }
} f[N+5];

int ret[N+5];
int main() {
    fast;
    int n; cin >> n; pw[0] = 1;
    for (int i = 1; i <= n; ++i) pw[i] = 2ll*pw[i-1]%mod;
    for (int i = 1, x; i <= n; ++i) cin >> x, f[x] = f[x] + node(x);
    int cur = 1;
    for (int i = 0; i <= 5; ++i) {
        for (int j = N-1; ~j; --j)
            if ((j/cur)%10 != 9)
                f[j] = f[j] + f[j+cur];
        cur = cur*10;
    }
    for (int i = 0; i < N; ++i) ret[i] = f[i].s2;
    cur = 1;
    for (int i = 0; i <= 5; ++i) {
        for (int j = 0; j < N; ++j)
            if ((j/cur)%10 != 9)
                ret[j] = (ret[j] - ret[j+cur] + mod) % mod;
        cur = cur*10;
    }
    ll ans = 0;
    for (int j = 0; j < N; ++j) ans ^= 1ll*j*ret[j];
    cout << ans << '\n';
    return 0;
}