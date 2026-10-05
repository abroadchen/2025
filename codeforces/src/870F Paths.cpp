//
// Created by Psy.C on 2026/10/5.
//
/**
标准线性筛，
s
t
[
x
]
st[x] 存 x 的最小质因子，
p
[
x
]
p[x]＝欧拉函数 φ(x)，
m
u
[
x
]
mu[x]＝莫比乌斯函数 μ(x)
质数：φ=p-1，μ=-1
含平方因子：μ=0
互质组合：φ、μ 按积性函数相乘
选出那些“最小质因子 ≠ 自身，或 ≤ n/2”的数构成候选集，数量记为 pl
对每个候选，按最小质因子聚类计数 cnt[st[i]]++
p
l
​
 =(
2
pl
​
 )（候选数对总数）
s
1
​
 =∑
i=2
n
​
 (i−1−φ(i))
同时构造 sum 前缀和用于后续
对每个候选数 i，累加 sum[n/st[i]]，用前缀和快速求和
莫比乌斯反演式的容斥：
s
2
+
=
μ
(
i
)
⋅
(
⌊
n
/
i
⌋
2
−
[
i 为大素数
]
)
s2+=μ(i)⋅(⌊n/i⌋
2
 −[i 为大素数])
最后 s2 >>= 1 除以 2
这一部分把“按子集并/交集大小”的计数用 μ 展开，属于数论反演计数的典型写法
最终把三类数对按不同权值（1、2、3）‍加权求和
s
1
​
 ：由 φ 定义的差量累计（经典的互素计数）
s
2
​
 ：由 μ 反演得到的计数
p
l
​
 −s
1
​
 −s
2
​
 ：剩余部分，贡献权 3
 
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e7+10;

int p[N], mu[N], n, m, st[N], cnt[N], sum[N];
vector<int> pri;
ll pl, s1, s2, t;
int main() {
    fast;
    p[1] = mu[1] = 1; cin >> n; m = sqrt(n);
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) pri.emplace_back(i), st[i] = i, p[i] = i-1, mu[i] = -1;
        for (int j : pri) {
            if (i*j > n) break;
            st[i*j] = j;
            if (!(i%j)) { p[i*j] = p[i]*j; mu[i*j] = 0; break; }
            p[i*j] = p[i]*(j-1);
            mu[i*j] = mu[j]*mu[i];
        }
    }
    for (int i = 2; i <= n; ++i)
        if (st[i] != i || i <= n/2)
            pl++, cnt[st[i]]++;
    pl = pl*(pl-1)/2;
    for (int i = 2; i <= n; ++i)
        s1 += i - 1 - p[i], sum[i] = sum[i-1] + cnt[i];
    for (int i = 2; i <= n; ++i)
        if (st[i] != i || i <= n/2)
            s2 += sum[n/st[i]];
    for (int i = 2; i <= n; ++i) {
        t = 0;
        t += 1ll*(n/i)*(n/i);
        if (st[i] == i && i > m) t--;
        s2 += mu[i]*t;
    }
    s2 >>= 1ll;
    cout << 1ll*s1+s2*2+(pl-s1-s2)*3;
    return 0;
}