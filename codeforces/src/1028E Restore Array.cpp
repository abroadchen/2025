//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
b[i]：目标条件数组；a[i]：待构造答案。
z：标记"峰值位置"（后面定位起点用）；f：是否出现过非零值
第一遍读入并判断是否全 0。
第二遍找一个 b[i] > b[i-1] 的位置 z，用于后续确定构造起点
若 b 全 0，则让所有 a[i]=1 即满足（1 取模任何东西结果能让条件成立的最简单特例）
当 n=2 时两个数相等则无法构造；不等时直接给出某种构造。
⚠️ 注意：这里比较/输出的 a[0]、a[1] 在此时其实还没被赋过值（默认 0），从代码看这段分支逻辑实际有瑕疵（作者可能本意是写 b[0]/b[1]），但属构造题特判，不影响整体理解
找到一个严格上升的相邻对 z（b[z] > b[z-1]），否则无解。
以 (z+1)%n 为起点，按环的顺序把下标存入 id，即把环"展平"成一个从 z+1 开始的线性序列。
倒数第一个位置 a[id[n-1]] 直接设为 b[id[n-1]]。
从后往前，对每个位置用公式
a
[
i
]
=
l
o
w
+
(
(
b
[
i
]
−
l
o
w
  
m
o
d
  
m
)
  
m
o
d
  
m
+
m
)
  
m
o
d
  
m
a[i]=low+((b[i]−lowmodm)modm+m)modm
贪心确定（其中 low = b[i-1]+1，m = a[i+1]），保证取模后能匹配 b[i] 同时严格大于相邻目标
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e6+10;

int n, z(-1), id[N];
ll a[N], b[N];
bool f;
int main() {
    fast;
    cin >> n;
    rep(i,n) { cin >> b[i]; f |= b[i]; }
    rep(i,n) if (b[(i-1+n)%n] < b[i]) z = i;
    if (!f) {
        cout << "YES\n";
        rep(i,n) cout << "1 ";
        cout << '\n';
    } else if (n == 2) {
        if (a[0] == a[1]) cout << "NO\n";
        else {
            cout << "YES\n";
            if (a[0] > a[1]) cout << a[0] << ' ' << a[0]+a[1] << '\n';
            else cout << a[0]+a[1] << ' ' << a[1] << '\n';
        }
    } else {
        if (z == -1) return cout << "NO\n", 0;
        int now = 0, cur = (z+1)%n;
        for (int i = 1; i <= n; i++) {
            id[now++] = cur;
            cur = (cur+1)%n;
        }
        a[id[n-1]] = b[id[n-1]];
        for (int i = n-2; i >= 0; i--) {
            ll low = b[id[(i-1+n)%n]] + 1, m = a[id[i+1]];
            a[id[i]] = low+((b[id[i]]%m-low%m)%m+m)%m;
        }
        cout << "YES\n";
        rep(i,n) cout << a[i] << ' ';
        cout << '\n';
    }
    return 0;
}