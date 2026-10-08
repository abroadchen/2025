//
// Created by Psy.C on 2026/10/8.
//
/**
读入
n
n 和序列
a
[
1..
n
]
a[1..n]
把初始状态设为"当前值
=
a
1
−
1
=a
1
​
 −1，收益
0
0"。（这里
a
1
−
1
a
1
​
 −1 对应
x
  
m
o
d
  
a
1
xmoda
1
​
  的最大可能值
a
1
−
1
a
1
​
 −1。）
这一轮遍历当前 dp 中所有值
≥
a
i
+
1
≥a
i+1
​
  的状态（用 lower_bound(a[i+1]) 找到起点）。
对每个状态
x
x（当前值）、
y
y（当前收益）：
若
x
≥
a
i
+
1
x≥a
i+1
​
  则
x
  
m
o
d
  
a
i
+
1
xmoda
i+1
​
  可作为新状态，收益增加 i*(x - x%a[i+1])；
同时把
a
i
+
1
−
1
a
i+1
​
 −1（取到最大余数的状态）的收益按 i*((x+1)/a[i+1]*a[i+1]-a[i+1]) 更新。
最后 erase 掉所有
≥
a
i
+
1
≥a
i+1
​
  的旧状态——因为这些状态被"取模"后必然变小，不会再作为
≥
a
i
+
1
≥a
i+1
​
  的状态存在，可以裁剪掉，保证 dp 规模受控
遍历所有剩余状态，用 ans = max(ans, y + x*n) 得到最终答案并输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

template<typename T1, typename T2>
void chkmax(T1& x, T2 y) { if (x < y) x = y; }

constexpr int N = 2e5;
ll a[N+5];
map<ll, ll> dp;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    dp[a[1]-1] = 0;
    for (int i = 1; i < n; ++i) {
        for (auto it = dp.lower_bound(a[i+1]); it != dp.end(); ++it) {
            ll x = it->first, y = it->second;
            dp[x%a[i+1]] = max(dp[x%a[i+1]], y+1ll*i*(x-x%a[i+1]));
            dp[a[i+1]-1] = max(dp[a[i+1]-1], y+1ll*i*((x+1)/a[i+1]*a[i+1]-a[i+1]));
        }
        dp.erase(dp.lower_bound(a[i+1]), dp.end());
    }
    ll ans = 0;
    for (auto &[fst, snd] : dp) {
        ll x = fst, y = snd;
        chkmax(ans, y+x*n);
    }
    cout << ans << '\n';
    return 0;
}