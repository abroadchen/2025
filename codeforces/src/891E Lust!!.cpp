//
// Created by Psy.C on 2026/10/9.
//
/**
输入
n
,
k
n,k。
e = min(n, k)：后面求和只用到前 e 项（不能超过
n
n 和
k
k）。
t = inv = ksm(n, mod-2)：
n
−
1
  
m
o
d
  
p
n
−1
 modp，后面 t 会不断乘 inv，即
t
=
n
−
i
t=n
−i
 。
c[n] = 1：差分多项式数组 c 初始化
这里按顺序读入
n
n 个数
a
1
.
.
a
n
a
1
​
 ..a
n
​
 ，并用牛顿前向差分 / 多项式重建（确定一个
n
n 次多项式）‍的方式维护数组 c。

具体来说，这是在用
n
n 个点
(
0
,
a
1
)
,
(
1
,
a
2
)
,
…
,
(
n
−
1
,
a
n
)
(0,a
1
​
 ),(1,a
2
​
 ),…,(n−1,a
n
​
 )（或类似的整数点）来恢复一个多项式，c[0..n] 是该多项式在 0 处展开的系数（多项式的 falling factorial 系数 / 牛顿级数系数）‍。

外层循环每读进一个新值 a[i]，内层循环从 j = n-i 一直更新到 n-1：
这是"用新点插入更新差分表"的标准操作——把新数据点插入已有的前向差分表，重新推公式。

最后 c[n] = -c[n]：修正最高位系数（因为前向差分在端点处有符号翻转）。

这条循环本质上是由
n
n 个点插值出
n
n 次多项式（或幂和多项式）的系数，c 数组存的是该多项式按阶乘幂（falling factorial）基底的系数
t = t*inv%mod（每次循环后）‍：t 在循环第
i
i 次迭代时为
n
−
i
n
−i
 （第一轮 t = n^{-1}，第二轮 n^{-2}$，以此类推）。

res = t：得到
n
−
i
n
−i
 。

内层 for j = k-i+1..k: res = res*j：从
k
−
i
+
1
k−i+1 乘到
k
k，得到
k
(
k
−
1
)
⋯
(
k
−
i
+
1
)
=
k
!
(
k
−
i
)
!
k(k−1)⋯(k−i+1)=
(k−i)!
k!
​

这是下降阶乘（falling factorial）‍
(
k
)
i
(k)
i
​
 。

所以每次迭代的 res =
n
−
i
⋅
(
k
)
i
=
(
k
)
i
n
i
n
−i
 ⋅(k)
i
​
 =
n
i

(k)
i
​

​
把
c
[
i
]
⋅
(
k
)
i
n
i
c[i]⋅
n
i

(k)
i
​

​
  以减号累加进 ans（带符号求和）。

这正对应伯努利数的倒递推 / 幂和多项式求和公式：

∑
i
=
0
n
−
1
i
k
    
    
(
或类似幂和
)
≈
∑
i
c
[
i
]
⋅
(
k
)
i
n
i
∑
i=0
n−1
​
 i
k
 (或类似幂和)≈∑
i
​
 c[i]⋅
n
i

(k)
i
​

​


即把多项式用阶乘幂展开后，代入"下降阶乘在
n
n 处的取值"求和。减号的累积方式对应标准公式的交替求和结构
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5e3+5, mod = 1e9+7;

inline ll ksm(ll a, int b) {
    if (!b) return 1;
    if (b == 1) return a;
    ll c = ksm(a, b>>1);
    c = c*c%mod;
    if (b&1) c = c*a%mod;
    return c;
}

int n, k, e;
ll t, inv, c[N], a[N], res, ans;
int main() {
    fast;
    cin >> n >> k; e = min(n, k);
    //t = inv = n^{-1}
    t = inv = ksm(n, mod-2); c[n] = 1;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        for (int j = n-i; j < n; ++j)
            c[j] = (c[j+1]*a[i]-c[j])%mod;
        c[n] = -c[n];
    }
    for (int i = 1; i <= e; ++i, t=t*inv%mod) {
        res = t;
        for (int j = k-i+1; j <= k; ++j)
            res = res*j%mod;
        ans = (ans - c[i]*res)%mod;
    }
    cout << (ans+mod)%mod;
    return 0;
}