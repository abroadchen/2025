//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
inf：Pollard-Rho 的迭代次数上限，值为 131072=2^17
flg[i]：线性筛标记（i 是否为合数）。
pri[]：素数表。
cnt：素数个数。
mn[i]：i 的最小质因子对应的素数编号（它在素数表中的下标）
Miller-Rabin 的测试底数集合。这 8 个底数（含 82、373）对 3.1x10^18以内的数可以保证确定性判定（名字像是借用了"第一组 12 个小素数足以判定"的算法变体）。实际这里用组合确保容错
一个哈希表：质因数 → 指数。fac(Y) 分解完成后，mp 里存的就是
Y
Y 的完整质因数分解
∏
p
e
∏p
e
模乘。因为 x*y 在 long long 下会溢出，用 __int128 先做乘法再取模，保证不溢出，这是大数分解的标准写法
欧拉线性筛：筛出
[
2
,
n
]
[2,n] 内所有素数存入 pri，同时对每个合数记录其最小质因子在素数表中的下标 mn（用来快速判断一个小于上限的数是否素数、以及取它的最小素因子）。break 保证每个合数只被它的最小质因子筛一次，O(n) 复杂度
欧拉线性筛：筛出
[
2
,
n
]
[2,n] 内所有素数存入 pri，同时对每个合数记录其最小质因子在素数表中的下标 mn（用来快速判断一个小于上限的数是否素数、以及取它的最小素因子）。break 保证每个合数只被它的最小质因子筛一次，O(n) 复杂度
把
n
−
1
n−1 写成
s
⋅
2
c
s⋅2
c
 ，其中
s
s 为奇数。这是 Miller-Rabin 的分解步骤
对每个底数 i：若 n 能被小底数整除（且 n≠该底数），直接判合数
计算
u
=
i
s
  
m
o
d
  
n
u=i
s
 modn，然后连续平方
c
c 次：若在过程中出现
u
≠
1
u

=1 且
u
≠
n
−
1
u

=n−1 但平方后变 1（
v
=
=
1
v==1），则违反了"非平凡平方根"条件，判定为合数
若最终
u
≠
1
u

=1（不满足
a
s
≡
±
1
a
s
 ≡±1 的结论），判合数。全部底数通过后返回 1（素数）
随机选起始点 x（在
[
1
,
n
−
1
]
[1,n−1] 内），y=x 是慢指针，t 是累积的乘积（用于 gcd 检测）
k 是"倍增步长"上界，nw 是从某次重置后走的总步数
Floyd 判圈：x 走一步（x = x²+c mod n），并把与 y 的差的绝对值累积进 t
分批检测：每走 128 步或快到步长边界时，用 gcd(t,n) 检查是否已经找到非平凡因子。若是则返回该因子 g；否则重置 t=1 继续。分批是为了减少 gcd 调用次数
当走到步长边界 nw==k 时，慢指针 y 追到 x（即把 y 更新为当前 x），步长 k 翻倍。若到迭代上限还没找到因子返回 0
把质因数 x 的指数累加 y（更新哈希表）
若 n ≤ 筛子上限：直接取它的最小质因子 p，循环除掉 p 统计指数 num，写入 mp，n 被砍成更小的数（继续循环）
否则（n 超筛子范围）：

先做 MR 判定：若 n 本身是素数，则 push(n,1) 并终止。
若不是素数，就调用 Pollard-Rho PR(n,k) 找一个非平凡因子 p（c 从 97 起始，找不到就递减重试，直到找到）。
然后把 n 除以 p，并递归分解 p（因为 p 也可能还能再分）。
这样不断把大数 n 分解成素数存入 mp
快速沃尔什变换 / 子集和（FWHT 的 OR 版本，实际是 SOS DP——Sum Over Subsets）‍。

枚举维度 i（共 n 个质因数，对应 n 位）。
对每个掩码 j，若第 i 位为 0，则把 A[j|(1<<i)] 的值按 op 符号累加到 A[j]。
op=+1：做子集和（求 A[j] = Σ_{sub⊆j} A[sub]）。
op=-1：做逆变换（容斥回去，求原数组）。
这就是高维前缀和的标准实现（当 n 是维度数、用 1<<n 个状态时）

c[i]：读入的 n 个数。
P[]：Y 的互异质因子列表。
f[], g[]：两个计数数组（按掩码索引）。
a[], b[]：X 与 Y 在各个质因子上的指数
先线性筛预处理到
10
6
10
6
读入 n、X、Y，t=X 备份（后面分解 X 用）
读入序列 c[]
关键剪枝：若 Y 不能被 X 整除，那么不可能有
X
∣
lcm
⁡
(
c
i
,
c
j
)
X∣lcm(c
i
​
 ,c
j
​
 ) 且
lcm
⁡
∣
Y
lcm∣Y（因为 lcm 整除 Y 却又要包含 X 的所有因子，矛盾），直接输出 0 结束
对 Y 做大数分解，把质因数分解存入 mp
把 mp 里的每一项（质因子, 指数）读出来：质因子存入 P[]，Y 的指数存入 b[]，总个数记为 num。这就是后续掩码的维度数
对 t=X，逐个统计 X 在每个质因子 P[j] 上的指数，存入 a[j]
对每个数 c[i]，初始化掩码 fa=0, fb=0，并把 p=c[i] 用于除因子
跳过 X 和 Y 在该质因子上指数相等的情况：此时该质因子上指数被 lcm 关系锁定，不参与掩码区分（无论 c 的指数如何都满足
统计 c[i] 在质因子 P[j] 上的指数 t：

若 t ≠ a[j]（不等于 X 在该质因子的指数）→ 第 j-1 位置 1 记入 fa。
若 t ≠ b[j]（不等于 Y 的指数）→ 记入 fb。
这样 fa 编码了"c[i] 在哪些质因子上指数与 X 不同"，fb 编码了"与 Y 不同"。lcm 整除 X 方向的约束集中体现在 fa，整除 Y 方向体现在 fb
若 X ∣ c[i]：则该数一个"能饱含 X"的数，把它按 fa 掩码计入 f[fa]（计数）。
若 c[i] ∣ Y：则它是"能被 Y 包含"的数，按 fb 掩码计入 g[fb]。
语义：f[fa] 统计所有满足
X
∣
c
i
X∣c
i
​
  的数的掩码分布；g[fb] 统计满足
c
i
∣
Y
c
i
​
 ∣Y 的数的掩码分布
对 f、g 分别做子集和（op=+1）‍：f[mask] 变为"所有掩码是 mask 子集的数的总数"，g 同理
对应掩码相乘：f[i]*g[i] = 两个数掩码都"⊆i"的组合对数
做逆变换（op=-1）‍，即用容斥恢复出"每个精确子集掩码对应"的组合对数量
输出 f[0]。

为什么是 f[0]？ 掩码 = 0 表示"该数在每个质因子上的指数恰好等于 X 的指数（fa 中无 1 位）且等于 Y 的指数（fb 无 1 位）"。高维前缀和的逆变换后 f[0] 正好统计出所有满足
X
∣
lcm
⁡
(
c
i
,
c
j
)
X∣lcm(c
i
​
 ,c
j
​
 ) 且
lcm
⁡
(
c
i
,
c
j
)
∣
Y
lcm(c
i
​
 ,c
j
​
 )∣Y 的
(
i
,
j
)
(i,j) 对数，即题目所求答案
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

constexpr int N = 1e6+5, inf = 131072;

namespace Ju {
    int flg[N], pri[N], cnt, mn[N], tmp[8] = {2,3,5,7,11,13,82,373};
    map<ll, int> mp;
    ll mul(ll x, ll y, ll p) { return (__int128)x*y%p; }
    ll ksm(ll x, ll y, ll p) {
        ll ret = 1;
        for (; y; y >>= 1) {
            if (y&1) ret=mul(ret,x,p);
            x=mul(x,x,p);
        }
        return ret;
    }
    void init(int n) {
        for (int i = 2; i <= n; ++i) {
            if (!flg[i]) pri[++cnt] = i, mn[i] = cnt;
            for (int j = 1; j <= cnt && pri[j]*i <= n; ++j) {
                flg[pri[j]*i] = 1, mn[pri[j]*i] = j;
                if (!(i%pri[j])) break;
            }
        }
    }
    int MR(ll n) {
        if (n <= N-5) return n > 1 && pri[mn[n]] == n;
        int c = 0; ll s = n-1, u, v;
        while (!(s&1)) s >>= 1, ++c;
        for (int i : tmp) {
            if (!(n%i)) return 0;
            u = ksm(i, s, n);
            for (int j = 0; j < c; ++j, u = v)
                if (v=mul(u,u,n), u != 1 && u != n-1 && v == 1)
                    return 0;
            if (u != 1) return 0;
        }
        return 1;
    }
    ll PR(ll n, int c) {
        ll x = rand()%(n-1)+1, y = x, t = 1;
        for (int k = 2, nw = 1; k <= inf; ) {
            x = (mul(x,x,n)+c)%n;
            t = mul(t,(y-x+n)%n,n);
            if (nw%128 == 0 || nw+1 == k) {
                ll g = __gcd(t, n);
                if (g != 1 && g != n) return g;
                t = 1;
            }
            if (++nw == k) y = x, k <<= 1;
        }
        return 0;
    }
    void push(ll x, int y) { mp[x] += y; }
    void fac(ll n) {
        while (n > 1) {
            if (n <= N-5) {
                int num = 0, p = pri[mn[n]];
                while (n%p == 0) n/=p, ++num;
                push(p,num);
            } else {
                ll p;
                if (MR(n)) { push(n,1); break; }
                for (int k = 97; !((p=PR(n,k))); --k) {}
                n /= p, fac(p);
            }
        }
    }
}
using namespace Ju;

void fwt(ll *A, int n, int op) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < 1<<n; ++j)
            if (!((j>>i)&1)) A[j] += A[j^(1<<i)]*op;
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

ll c[N], P[20], f[N], g[N];
int a[20], b[20];
int main() {
    init(N-5);
    int n, num = 0; ll X, Y, t;
    read(n), read(X), read(Y), t = X;
    for (int i = 1; i <= n; ++i) read(c[i]);
    if (Y%X) { write(0); return 0; }
    fac(Y);
    for (auto [fst, snd] : mp) ++num, P[num] = fst, b[num] = snd;
    for (int j = 1; j <= num; ++j)
        while (t%P[j] == 0) t /= P[j], ++a[j];
    for (int i = 1; i <= n; ++i) {
        int fa = 0, fb = 0; ll p = c[i];
        for (int j = 1; j <= num; ++j) {
            if (a[j] == b[j]) continue;
            int t = 0;
            while (p%P[j] == 0) p /= P[j], ++t;
            if (t != a[j]) fa |= 1<<(j-1);
            if (t != b[j]) fb |= 1<<(j-1);
        }
        if (!(c[i]%X)) ++f[fa];
        if (!(Y%c[i])) ++g[fb];
    }
    fwt(f, num, 1); fwt(g, num, 1);
    for (int i = 0; i < 1<<num; ++i) f[i] = f[i]*g[i];
    fwt(f, num, -1);
    write(f[0]);
    return 0;
}