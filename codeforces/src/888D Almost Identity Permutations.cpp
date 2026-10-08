//
// Created by Psy.C on 2026/10/8.
//
/**
长度为 1 的基础方案数贡献 1
累加
C
(
n
,
2
)
=
n
(
n
−
1
)
2
C(n,2)=
2
n(n−1)
​
 ，即从
n
n 个位置里选 2 个的组合数
累加
∑
i
=
1
n
−
2
i
(
i
+
1
)
=
∑
(
i
2
+
i
)
∑
i=1
n−2
​
 i(i+1)=∑(i
2
 +i)，这是一类"选 3 个位置"的计数
双重循环，累加
∑
i
∑
j
j
(
j
+
1
)
2
×
9
∑
i
​
 ∑
j
​

2
j(j+1)
​
 ×9
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, k, sum;
int main() {
    fast;
    cin >> n >> k;
    if (k >= 1) sum += 1;
    if (k >= 2) sum += n*(n-1)/2;
    if (k >= 3) {
        for (int i = 1; i <= n-2; ++i)
            sum += (1+i)*i;
    }
    if (k >= 4) {
        for (int i = n-3; i >= 1; --i)
            for (int j = 1; j <= i; ++j)
                sum += (1+j)*j/2*9;
    }
    cout << sum;
    return 0;
}