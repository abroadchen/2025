//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
从 i = 2 开始枚举，条件是 i*i < n（注意是严格小于，不含等于）。
找 i 是 n 的因子，且 i 与 n/i 互质（__gcd == 1）。
若满足，令 x = i, y = n/i，即把 n 拆成两个互质因子之积。
关键是 gcd(x, y) = 1（互质），这是后面 CRT / 构造成立的前提
令 a 从 1 遍历到 x-1（a < x）。
检查 (n-1 - a·y) 是否被 x 整除。
如果整除，令 b = (n-1 - a·y) / x。
核心方程是：

(n - 1 - a·y) ≡ 0 (mod x)，即 a·y ≡ n-1 (mod x)。
因为 gcd(x, y) = 1，所以 y 在模 x 下有逆元，这个同余方程对 a 一定有解、且解在 [1, x-1] 区间内循环——这正是枚举 a < x 一定能找到解（若存在）的原因。找到后反推出 b
找到合法 (a, b) 后：
输出 YES
输出 2（表示构造分两组 / 两个因子）
输出第一组 a x
输出第二组 b y
然后立即结束程序
如果所有互质分解、所有 a 都试过仍找不到满足条件的解，输出 NO。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;


int main() {
    fast;
    int n; cin >> n;
    for (int i = 2; i*i < n; ++i) if (n%i == 0 && __gcd(i,n/i) == 1) {
        int x = i, y = n/i;
        for (int a = 1; a < x; ++a) if ((n-1-a*y)%x == 0) {
            int b = (n-1-a*y)/x;
            cout << "YES\n";
            cout << "2\n";
            cout << a << ' ' << x << '\n';
            cout << b << ' ' << y << '\n';
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}