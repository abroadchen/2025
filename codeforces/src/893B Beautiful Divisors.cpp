//
// Created by Psy.C on 2026/10/9.
//
/**
k 从 1 开始枚举。
s 存当前
k
k 对应的候选值
(
2
k
−
1
)
⋅
2
k
−
1
(2
k
 −1)⋅2
k−1
 。
ans 存符合条件的最大约数，初始为 0（若无任何匹配则输出 0）
对每个
k
=
1
,
2
,
3
,
…
k=1,2,3,…，计算：
s
k
=
(
2
k
−
1
)
⋅
2
k
−
1
s
k
​
 =(2
k
 −1)⋅2
k−1


这是第
k
k 个梅森完全数形式的表达式（偶完全数的标准形式）。

循环条件：s_k <= n——只考虑不超过
n
n 的候选值（更大的无意义，不可能是
n
n 的约数）。

若 n % s_k == 0（
s
k
s
k
​
  是
n
n 的约数），则记录 ans = s_k。

k++：继续尝试更大的
k
k。

注意这里的关键点：由于 k 从小到大递增，
s
k
s
k
​
  也随
k
k 单调递增，所以循环结束时 ans 保存的是满足条件的最大
s
k
s
k
​
 （因为越后面的
k
k 越大，若它也整除
n
n 就会覆盖前面的值）。这正是"找最大的完全数形式约数"
输出最大满足条件的约数（即能整除
n
n 的最大的
(
2
k
−
1
)
2
k
−
1
(2
k
 −1)2
k−1
 ）。
代码里用了 pow(a,b)（double 返回浮点），大
k
k 时可能存在浮点误差。对
n
n 到 1e9 这种规模通常没问题（
k
k 到约 30 左右），但如果
n
n 很大建议改用整数快速幂/位运算（如 (1LL<<k)-1）更稳妥。需要的话我可以给你改写成纯整数版本
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int k=1, s, ans;
int main() {
    fast;
    int n; cin >> n;
    while ((pow(2,k)-1)*pow(2,k-1) <= n) {
        s = (pow(2,k)-1)*pow(2,k-1);
        if (n%s == 0)
            ans = (pow(2,k)-1)*pow(2,k-1);
        k++;
    }
    cout << ans;
    return 0;
}