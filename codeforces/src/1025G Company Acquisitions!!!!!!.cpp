//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
p[i] 初始都是 1
对每个位置 i 读入 a[i]。
-a[i]：对非 -1 的数，-a[i] != 0 为真，即 a[i] != -1（-(-1) = 0，-非负 = 负数≠0）。所以这里判断的是 a[i] 是否为已知值。
若 a[i] 是已知值 v，则 p[v] *= 2 (mod 1e9+7)。
含义：p[v] 记录了值 v 在输入中被实际使用/赋值的次数（每出现一次翻倍）。比如值 v 出现 k 次，则 p[v] = 2^k
第一个循环：t 从 1 开始，循环 n-1 次每次乘 2，得到 t = 2^(n-1)。
--t：变成 t = 2^(n-1) - 1。
注意 i^n 这里是位异或（不是判断不等）。i ^ n != 0 当且仅当 i != n，所以循环跑 n-1 次，得到 t = 2^(n-1)。再减 1 → t = 2^(n-1) - 1
!-a[i]：-a[i]==0 ⟺ a[i] == -1，即这个位置是未知的。这里的循环条件其实是对每个 i，若 a[i]==-1 就执行减操作（虽然 i 又当作"值"用，有点复用变量）。
对每个"值 i 是 -1 的情况"，执行 t = t - (p[i]-1)。
对每个值为 -1（未知）的索引 i，从 t 中减去 (p[i]-1)
其中每次出现已知值 v 时 p[v] *= 2
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 505, mod = 1e9+7;

int n, a[N], p[N];
int main() {
    fast;
    int i;
    for (cin >> n, i = 1; i <= n; ++i) p[i] = 1;
    for (i = 1; i <= n; ++i) cin >> a[i], ~a[i]&&(p[a[i]]=2ll*p[a[i]]%mod);
    int t = 1;
    for (i = 1; i^n; ++i) t = 2ll*t%mod;
    for (--t, i = 1; i <= n; ++i) !~a[i]&&(t=(t-(p[i]-1)+mod)%mod);
    cout << t << '\n';
    return 0;
}