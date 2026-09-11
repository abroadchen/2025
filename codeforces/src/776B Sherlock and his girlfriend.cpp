//
// Created by Psy.C on 2026/9/11.
//
/**
isPri 用 bitset 存储是否为素数（省内存、快）；pri 存素数列表
先把所有奇数标记为"潜在素数"（只处理奇数，2 单独处理），并显式把 2 标为素数
从 3 开始的奇数 i，若 i 是素数，则把所有 i 的倍数（从 i² 起）标记为合数。只到 i*i <= N 即可
把 2 和所有奇数素数按顺序存入 pri

先筛素数，读入 n。
输出所需颜色种数：若 n==1 或 n==2 输出 1，否则输出 2。这对应题意：当点数 ≤ 2 时一种颜色就够；点数 ≥ 3 时通常需要 2 种
对每个点 i（从 2 到 n+1），若 i 是素数输出颜色 1，否则输出颜色 2。
这样做的依据：两个都为 1 色的点是素数，素数之间"差为素数"的连边恰好避开了；而同色点之间要避免出现差为素数的连边——把素数归为 1 色、合数归为 2 色，就能用 2 种颜色完成染色（因为任意两个合数之间、任意两个素数之间都满足约束）。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+10;
bitset<N> isPri;
vector<int> pri;
void sieve() {
    for (int i = 3; i <= N; i += 2) isPri[i] = true;
    isPri[2] = true;
    for (int i = 3; i*i <= N; i += 2)
        if (isPri[i]) {
            for (int j = i*i; j <= N; j += i)
                isPri[j] = false;
        }
    pri.push_back(2);
    for (int i = 3; i <= N; i += 2)
        if (isPri[i]) pri.push_back(i);
}

int main() {
    fast;
    sieve();
    int n; cin >> n;
    (n==1 || n==2) ? cout << 1 << '\n' : cout << 2 << '\n';
    for (int i = 2; i <= n+1; ++i) {
        if (isPri[i]) cout << 1 << ' ';
        else cout << 2 << ' ';
    }
    cout << '\n';
    return 0;
}