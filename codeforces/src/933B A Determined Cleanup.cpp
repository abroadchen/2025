//
// Created by Psy.C on 2026/10/16.
//
/**
t 是当前最低位。注意这里用 p % k 而不是 p % (-k)——因为我们要让余数尽量落在合法区间，习惯上用正的 k 来取模
把 p 除以 -k 得到下一个更高位的数值
如果当前余数 t 为负（即它在 (-k, 0) 区间），我们把它加一个 k 变成正数 [0, k-1]；同时为了让等式仍然成立（p = 商*(-k) + 余数），商必须自增 1，即 p++
为什么是 +1？ 因为：

p_old = q * (-k) + t        (t 为负)
      = (q+1) * (-k) + (t+k)    ← 余数 t+k 落在 [0,k-1]，商从 q 变为 q+1
所以 p += 1（因为下一轮会再除以 -k，这里手动加 1 等价于商进位）。
只要 p 不为 0 就继续取位。每轮把修正后的当前位 t 存入 a[++n]。当 p 变为 0 时停止，此时得到从低位到高位排列的所有数字
输出位数 n，然后依次输出每一位
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+10;
ll p, k, a[N], n;
int main() {
    fast;
    cin >> p >> k;
    ll t = 0;
    for (; p; a[++n]=t) {
        t = p%k; p = p/(-k);
        if (t < 0) t += k, p++;
    }
    cout << n << '\n';
    for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
    return 0;
}