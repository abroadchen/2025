//
// Created by Psy.C on 2026/9/26.
//
/**
用二进制拆分法求
x
y
  
m
o
d
  
m
o
d
x
y
 modmod，时间复杂度
O
(
log
⁡
y
)
O(logy)
在这里主要用于：
ksm(n+1, mod-2) 求
n
+
1
n+1 在模意义下的逆元（由费马小定理
a
p
−
1
≡
1
a
p−1
 ≡1，其逆元为
a
p
−
2
a
p−2
 ）
p：表示
(
n
+
1
−
m
)
/
(
n
+
1
)
(n+1−m)/(n+1)，即某个概率——分子 n+1-m 与 n+1 的逆元相乘
cnt：表示
2
m
⋅
(
n
+
1
)
m
  
m
o
d
  
m
o
d
2
m
 ⋅(n+1)
m
 modmod
最终结果：p * cnt % mod
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int mod = 1e9+7;
int ksm(int x, int y) {
    int res = 1;
    while (y) {
        if (y&1) res=(res*x)%mod;
        x=(x*x)%mod;
        y>>=1;
    }
    return res;
}

int n, m;
signed main() {
    fast;
    cin >> n >> m;
    int p = (n+1-m)*ksm(n+1, mod-2)%mod,
    cnt = ksm(2, m)*ksm(n+1, m)%mod;
    cout << p*cnt%mod << '\n';
    return 0;
}