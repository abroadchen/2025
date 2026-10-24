//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
n：测试组数。
p, q：每次读入的分子、分母。
b：进制基数。
g, g2：临时 gcd 变量
用 __gcd 求分子分母最大公约数，分子分母同除以 g 完成约分。
约分后若 q == 1（分母为 1），分数是整数，在任何进制下都必然是有限小数 → 直接输出 Finite
进入循环，反复消去分母中的、与 b 共享的质因子：
外层 while(true)：每次先求 g2 = gcd(q, b)，取其当前共享的质因子组合。
内层 while(g2 != 1 && q%g2 == 0) q /= g2：只要 q 能被这个 g2 整除，就一直除，把所有共享因子从分母中剥掉。
若 g2 == 1（不再有共享因子）或 q == 1（分母已全部消完）→ 退出。
循环结束后：
若 q == 1：分母中所有质因子都被 b 覆盖 → Finite（有限小数）‍。
否则分母仍残留 b 之外无法除尽的质因子 → Infinite（无限循环小数）‍

判断 p/q 在 b 进制下是否有限：

分数约分后分母 q = ∏ primes。若 b 进制有限，则必须有：q 的每一个质因子都能整除某个 b^k，即 q 的所有质因子都出现在 b 的质因子集合里。
等价地：反复用 gcd(q, b) 消去 q 里与 b 共享的质因子，若能全部消成 1 → 有限；否则 → 无限
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, p, q, b, g, g2;
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        p = rd(), q = rd(), b = rd();
        g = __gcd(p, q); p /= g, q /= g;
        if (q == 1) cout << "Finite\n";
        else {
            while (true) {
                g2 = __gcd(q, b);
                while (g2 != 1 && q%g2 == 0) q /= g2;
                if (g2 == 1 || q == 1) break;
            }
            if (q == 1) cout << "Finite\n";
            else cout << "Infinite\n";
        }
    }
    return 0;
}