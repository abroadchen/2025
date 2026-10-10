//
// Created by Psy.C on 2026/10/10.
//
/**
n：输入规模。
f[2][N]：滚动数组（两行），存二项式系数模 2（即
(
i
j
)
  
m
o
d
  
2
(
j
i
​
 )mod2）。
x：滚动行指示器（在 0/1 之间翻转
初始化 f[0][0]=1（第 0 行）、f[1][1]=1（第 1 行
(
1
1
)
=
1
(
1
1
​
 )=1）。
从 i=2 到 n，滚动到 x 行，用标准帕斯卡递推
f
[
i
]
[
j
]
=
f
[
i
−
1
]
[
j
]
+
f
[
i
−
1
]
[
j
−
1
]
f[i][j]=f[i−1][j]+f[i−1][j−1] 但全部取模 2。
注意这里不是先清空再填，而是用 +=，但因为只计算一次且模 2，行为上等价于
(
i
j
)
  
m
o
d
  
2
(
j
i
​
 )mod2。到结束时：

f[x][j] =
(
n
j
)
  
m
o
d
  
2
(
j
n
​
 )mod2（第 n 行）
f[1-x][j] =
(
n
−
1
j
)
  
m
o
d
  
2
(
j
n−1
​
 )mod2（第 n-1 行）
第一个多项式：长度 n，系数 = 第 n 行帕斯卡三角 mod 2，即
(
n
i
)
  
m
o
d
  
2
(
i
n
​
 )mod2（从 i=0 到 n）。
第二个多项式：长度 n-1，系数 = 第 n-1 行帕斯卡三角 mod 2，即
(
n
−
1
i
)
  
m
o
d
  
2
(
i
n−1
​
 )mod2（从 i=0 到 n-1）

利用帕斯卡恒等式：
(
1
+
x
)
⋅
(
1
+
x
)
n
−
1
=
(
1
+
x
)
n
(1+x)⋅(1+x)
n−1
 =(1+x)
n


系数即
(
1
+
x
)
n
−
1
(1+x)
n−1
  和
(
1
+
x
)
n
(1+x)
n
 。而代码给出的两个多项式系数是 mod 2 后的二项式系数。在 模 2 / GF(2) 的多项式意义下，这两个多项式满足：

(
1
+
x
)
n
,
(
1
+
x
)
n
−
1
(1+x)
n
 ,(1+x)
n−1


用卢卡斯定理（Lucas）‍，
(
n
k
)
  
m
o
d
  
2
=
1
(
k
n
​
 )mod2=1 当且仅当
k
k 的二进制位是
n
n 的二进制位的子集。这在这个问题上很关键——通常对应一道题：给出一个多项式系数（mod 2），要求构造它能被两个多项式整除，或反过来验证奇偶性
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; ++i)
using namespace std;
constexpr int N = 2e2;
int n, f[N][N], x = 1;
int main() {
    fast;
    cin >> n; f[0][0] = f[1][1] = 1;
    rep(i,2,n) {
        x = 1-x;
        rep(j,1,i) f[x][j] = (f[x][j] + f[1-x][j-1])%2;
    }
    cout << n << '\n';
    rep(i,0,n) cout << f[x][i] << ' '; cout << '\n';
    cout << n-1 << '\n';
    rep(i,0,n-1) cout << f[1-x][i] << ' ';
    return 0;
}