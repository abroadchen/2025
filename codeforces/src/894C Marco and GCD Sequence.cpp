//
// Created by Psy.C on 2026/10/9.
//
/**
读入
m
m 个数，升序排序 →
s
[
1
]
s[1] 是最小值
sum 从最后一个（最大）开始，向前逐个求 gcd，最终得到所有数的最大公约数 sum = gcd(all)
若全体数的 gcd 不等于最小值
s
[
1
]
s[1]，则输出 -1 无解并结束。
因为
s
[
1
]
s[1] 是这些数中最小的，而全体 gcd ≤ 每个数，若 gcd ≠
s
[
1
]
s[1] 则说明某个更小公因数为正（或构造不成立）
输出构造序列长度
2
m
2m。
依次输出 { s[1], s[i] } 成对重复
m
m 次，构成序列：
s
1
,
s
1
,
s
1
,
s
2
,
s
1
,
s
3
,
…
,
s
1
,
s
m
s
1
​
 ,s
1
​
 ,s
1
​
 ,s
2
​
 ,s
1
​
 ,s
3
​
 ,…,s
1
​
 ,s
m
​
 。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;

int s[N], sum;
int main() {
    fast;
    int m; cin >> m;
    for (int i = 1; i <= m; ++i) cin >> s[i];
    sort(s+1, s+m+1); sum = s[m];
    for (int i = m-1; i; --i) sum = __gcd(sum, s[i]);
    if (sum != s[1]) { cout << "-1\n"; return 0; }
    cout << 2*m << '\n';
    for (int i = 1; i <= m; ++i) cout << s[1] << ' ' << s[i] << ' ';
    cout << '\n';
    return 0;
}