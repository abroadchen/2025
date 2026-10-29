//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
d[i]：i 的正因子个数（除数函数 τ(i)）。
vs[i]：线性筛的标记数组（vs[i]=1 表示 i 是合数）。
pr[1..tot]：线性筛得到的质数表。
c[i]：i 的最小质因子的指数幂次 c（用于递推首因子幂次，见下文）。
p：存放"可行的三元排列 (x,y,z)"，x,y,z∈[1,7]。这是为了把容斥的 8 类合并成更少模式的枚举
线性筛 + τ 函数递推：

vs[i]==0 时 i 是质数：d[i]=2（1 和自身），c[i]=1（最小质因子指数 1）。
内层 rep(j,1,lim) 用 pr[j] 去筛：
若 i*pr[j] > lim 跳出（线性筛边界）。
vs[i*pr[j]]=1 标记合数。
情况一 i%pr[j]==0：pr[j] 是 i 已经包含的最小质因子，则：
c[i*pr[j]] = c[i]+1：因为 pr[j] 恰好是 i 的最小质因子（pr 递增，且 i%pr[j]==0 时 pr[j] 是当前最小能整除 i 的），新数的最小质因子指数 = c[i]+1。
d[i*pr[j]] = d[i]/(c[i]+1)*(c[i]+2)：除数函数由 τ = (c+2) 替换 (c+1) 更新。因为 τ(i)=∏(指数+1)，把最小质因子指数从 c 变 c+1，就把因子 (c+1) 换成 (c+2)。
break（线性筛重要：遇到整除就停，保证每个合数只被其最小质因子筛一次，保证 O(n)）。
情况二 i%pr[j]!=0：pr[j] 是新的不同质因子，追加一个指数为 1 的质因子，d 乘 2，c[i*pr[j]]=1。
对于质数自身情形，前面 if(!vs[i]) 已直接设好 d[i]=2,c[i]=1。
这样 O(lim) 时间把所有 i≤lim 的除数个数 d[i] 算好（lim=1e5）。
对每个 (x,y,z)∈[1,7]^3，判断这个三元模式是否"自洽"。
rep(s,1,7)：枚举 s 从 1..7，即所有非空子集（s 的二进制位对应取 x/y/z 中哪几个）。
对每个子集 s：
L = 该子集中元素个数（取了几项）。
R = 该子集中元素的按位或（R |= t[i]）。因为 x,y,z∈[1,7]，它们本身可视为"二进制 mask"（1,2,4 之类），R 记录这些数合并后覆盖了哪些位。
判断 popcount(R) < L：若按位或能覆盖的"不同位"少于元素个数，说明这些数之间有重叠的质因子（不互质），这个三元模式作为"容斥态"不合理，fl=0 排除。
只有当所有非空子集都满足 popcount(R) ≥ L 时，(x,y,z) 才被保留进 p
这 8 项是三元容斥（三者互质统计）的各个"交集"分拆。用 d[某个数] = 该数的约数个数 作为"取值个数"。

f[0]=0：空集。
f[1]：只被 a 整除（x 侧独有除数），即 d[a] - d[ab] - d[ca] + d[abc]（含容斥去掉与 b、c 的交）。
f[2]：只被 b 整除。
f[3]：同时被 a、b 整除（但不含三者公共的），d[ab]-d[abc]。
f[4]：只被 c 整除。
f[5]：同时被 a、c 整除，d[ca]-d[abc]。
f[6]：同时被 b、c 整除，d[bc]-d[abc]。
f[7]：同时被 a、b、c 整除，d[abc]。
这些 f[i] 把"x 的取值集合 Y"（Y 是所有同时整除 a 且属于该 mask 的约数集合）‍按属于哪个交集（mask）分类，且因为这里的 x 代表一个数，d[] 就是该集合大小。

实际问题是：统计满足 gcd(x,y,z)=1 的三元 (x|a, y|b, z|c)。容斥把"gcd=1"拆成"x,y,z 无公共质因子"。而 f 数组按 mask 对 x,y,z 的"取值空间"分块，再叠加。
不过这里 f[i] 直接用 d[数] 相减，本质是把每个变量的可行取值集合按 mask 划分成互不相交的块，保证用 mask (x,y,z) 组合时互不重叠可相加。
对每个保留的合法三元排列 (x,y,z)，累加 f[x]*f[y]*f[z]——即三块取一相乘的项。
但当 x==y 等出现重复 mask 时，需要补加重数（因为枚举的是"排列"，而实际三元统计要考虑每类取值的重数）。这里的 += f[x]*f[z] 等是按排列化公式补出的项。
最后 res/6：因为三元排列 (x,y,z) 的6 种置换都被 p 枚举了（若 x,y,z 互不相同），所以总和除以 6 得三元组无序计数；若其中有相等，则对应重数通过上面的补项调整后，res 整体也能被 6 整除
读 T 组询问，init(N-5) 预处理 d[] 数组和 p 模式表（只做一次）。
循环 T 次调用 get()，输出每组答案

init：线性筛 O(N)，枚举三元 7^3=343×子集 7×3，极小。所以 init 约 O(1e5)。
每组 get：O(343)（p 大小 ≤ 343），常数极小。
总复杂度 O(N + T·343)，其中 N≈1e5
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

struct node {
    int x{}, y{}, z{};
    node() = default;
    node(int a, int b, int c) : x(a), y(b), z(c) {}
};

int d[N], vs[N], pr[N], tot, c[N];
vector<node> p;
void init(int lim) {
    d[1] = 1;
    rep(i,2,lim) {
        if (!vs[i]) pr[++tot] = i, d[i] = 2, c[i] = 1;
        rep(j,1,lim) {
            if (i*pr[j] > lim) break;
            vs[i*pr[j]] = 1;
            if (i%pr[j] == 0) {
                c[i*pr[j]] = c[i] + 1;
                d[i*pr[j]] = d[i]/(c[i]+1)*(c[i]+2);
                break;
            }
            c[i*pr[j]] = 1;
            d[i*pr[j]] = d[i]*2;
        }
    }
    rep(x,1,7) rep(y,1,7) rep(z,1,7) {
        int fl = 1, t[3] = {x, y, z};
        rep(s,1,7) {
            int L = 0, R = 0;
            rep(i,0,2) if (s>>i&1) { L++; R |= t[i]; }
            if (__builtin_popcount(R) < L) { fl = 0; break; }
        }
        if (fl) p.emplace_back(x, y, z);
    }
}

void get() {
    int a, b, c; cin >> a >> b >> c;
    int ab = __gcd(a, b), bc = __gcd(b, c), ca = __gcd(c, a), abc = __gcd(ab, bc);
    ll f[8] = {
        0,
        d[a] - d[ab] - d[ca] + d[abc],
        d[b] - d[bc] - d[ab] + d[abc],
        d[ab] - d[abc],
        d[c] - d[ca] - d[bc] + d[abc],
        d[ca] - d[abc],
        d[bc] - d[abc],
        d[abc]
    }, res = 0;
    for (auto i : p) {
        int x = i.x, y = i.y, z = i.z;
        res += f[x]*f[y]*f[z];
        if (x == y) res += f[x]*f[z];
        if (y == z) res += f[x]*f[y];
        if (z == x) res += f[x]*f[y];
        if (x == y && y == z) res += 2*f[x];
    }
    cout << res/6 << '\n';
}


int main() {
    fast;
    int T; cin >> T, init(N-5);
    while (T--) get();
    return 0;
}