//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
读入 l、r、x、y。
若 y % x != 0（即 y 不能被 x 整除），则无解 → 输出 0。
原因：由 LCM(a,b)=y 且 GCD(a,b)=x，必有 x | y（x 整除 y），否则不存在这样的 a、b。
设 t = y/x（即 p·q = t）。枚举 i 为 t 的一个约数（i ≤ √t），那么另一个约数 q = t/i。

对每个 i 检查 5 个条件：

y/x % i == 0：i 必须是 t = y/x 的约数（保证整除）。

i*x >= l && i*x <= r：a = x·p = x·i 在 [l, r] 区间。

y/x/i*x >= l && y/x/i*x <= r：b = x·q = x·(t/i) 在 [l, r] 区间。

__gcd(i, y/x/i) == 1：p=i 与 q=t/i 互质（GCD(a,b)=x 成立的前提）。

若全部满足 → 这是一组合法 (p,q)，其中 p=i，q=t/i
若 i == t/i（p==q，即 a==b），该数对只算 1 次。
否则 (p,q) 与 (q,p) 是有序对的不同两个 → 加 2
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int l, r, x, y, sum;
signed main() {
    fast;
    cin >> l >> r >> x >> y;
    if (y%x) { cout << "0"; return 0; }
    for (int i = 1; i*i <= y/x; i++)
        if (y/x%i == 0 && i*x >= l && i*x <= r && y/x/i*x >= l &&
            y/x/i*x <= r && __gcd(i,y/x/i) == 1)
            sum += i == y/x/i ? 1 : 2;
    cout << sum << '\n';
    return 0;
}