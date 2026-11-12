//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
b：待求约数个数的整数（ll）。
ans：最终答案（约数个数，累加）。
读入一个数 b
取 b 的平方根（向下取整），作为枚举上界（转成 int）。
因为约数是成对出现的（d 与 b/d），其中必有一个 ≤ √b，所以只需枚举到 √b。这是该算法的关键优化
for (i=1; i<=x; ++i)：枚举从 1 到 √b。
if (b%i == 0)：若 i 能整除 b，则 i 是一个约数。
if (i*i == b)：若 i 正好等于 √b（即 b 是完全平方数），此时 i 与 b/i 是同一个约数，只能算 1 个 → ans++。
else ans += 2：一般情况下，i 和 b/i 是两个不同的约数，成对出现 → 一次性加 2
输出 ans（约数个数），换行，结束
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll b, ans;
int main() {
    fast;
    cin >> b;
    int x = sqrt(b);
    for (ll i = 1; i <= x; ++i) if (b%i == 0) {
        if (i*i == b) ans++;
        else ans += 2;
    }
    cout << ans << '\n';
    return 0;
}