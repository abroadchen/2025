//
// Created by Psy.C on 2026/9/25.
//
/**
v (118) = 0
< (60) = 1
^ (94) = 2
> (62) = 3
这 4 个值按"顺时针一圈"的顺序存：v -> < -> ^ -> > -> v
循环读入两个方向字符 c1、c2 和步数 n（多组测试，读到 EOF 结束）。
c1 是起始方向，c2 是目标方向，n 是旋转步数（每步 90°）
遍历 a[]，把 c1 映射到索引 k（起始方向的编号 0..3）。
把 c2 映射到索引 kk（目标方向的编号 0..3）。
例如 c1='v' → k=0，c2='>' → kk=3
(k+n)%4：从 k 顺时针走 n 步（每次 +1，模 4）到达的索引。若等于 kk，说明顺时针 n 步可达目标。
((k-n)%4+4)%4：从 k 逆时针走 n 步（每次 −1，模 4，+4 保证取正）到达的索引。若等于 kk，说明逆时针 n 步可达目标
两个方向都成立（n 步顺时针和 n 步逆时针都能到 kk）→ 说明方向无法唯一确定，输出 undefined。
这发生的情形：例如 n 是 4 的倍数且 k==kk（转一整圈回到原地，两个方向都等价）；或者 k==kk 且恰好半圈也对……实际就是顺时针与逆时针到达同一索引。
数学上两个条件同时成立 ⟺ k+n ≡ kk 且 k-n ≡ kk (mod 4)，即 2n ≡ 0 (mod 4) 且 k ≡ kk……等价地 n 为偶数且方向差为 0，或 n≡2 (mod4) 等情况导致顺时针/逆时针同时可达同一目标（比如相距 180°，n 为奇数时翻转可正可逆，此时 n 若满足 k+n≡kk 且 k-n≡kk，说明 n 恰为半圈）。
只有顺时针成立 → cw。
否则（只有逆时针成立）→ ccw
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a[5], n, k, kk;
char c1, c2;
int main() {
    fast;
    a[0] = 118, a[1] = 60, a[2] = 94, a[3] = 62;
    while (cin >> c1 >> c2) {
        cin >> n;
        for (int i = 0; i < 4; ++i) {
            if (c1 == a[i]) k = i;
            if (c2 == a[i]) kk = i;
        }
        if ((k+n)%4 == kk && ((k-n)%4+4)%4 == kk) cout << "undefined\n";
        else {
            if ((k+n)%4 == kk) cout << "cw\n";
            else cout << "ccw\n";
        }
    }
    return 0;
}