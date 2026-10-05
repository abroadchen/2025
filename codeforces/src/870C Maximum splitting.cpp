//
// Created by Psy.C on 2026/10/5.
//
/**
n≡0：n 个面额 4 → 需 n/4 个；但 n<4（即 n=0）时无法凑，输出 -1 注意 n=0 时 n>>2=0，代码用 n<4 挡成 -1）
n≡1：先用一个 9，剩下 n-9 必须是 4 的倍数 → 需 (n-9)/4 + 1 个；n<9 时 -1
n≡2：先用一个 6，剩下 n-6 是 4 的倍数 → (n-6)/4 + 1 个；n<6 时 -1
n≡3：先用一个 15，剩下 n-15 是 4 的倍数 → (n-15)/4 + 1，但这里写成 +2（相当于先把 15 拆成两次），n<15 时 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int main() {
    fast;
    int t = read(), n;
    while (t--) {
        n = read();
        if (!(n&3)) cout << (n < 4 ? -1 : n>>2) << '\n';
        else if ((n&3) == 1) cout << (n < 9 ? -1 : ((n-9)>>2)+1) << '\n';
        else if ((n&3) == 2) cout << (n < 6 ? -1 : ((n-6)>>2)+1) << '\n';
        else cout << (n < 15 ? -1 : ((n-15)>>2)+2) << '\n';
    }
    return 0;
}