//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
对 (a,b) 递归计算欧几里得算法需要的深度：dfs(a,b) = dfs(b, a%b) + a/b + 1。
返回的是欧几里得辗转相除的"步数/层数"。
作用：用来估计"把一堆数通过辗转相减消到 gcd"需要多长，用于后面的随机筛选
随机一个 b ∈ [1, p-1]；
a = u·b mod p；
若 dfs(a,b) > 100（欧几里得深度太长）就重新随机，直到得到一对"辗转相减步数较少"的 (a,b)。
这里 a 就是 u·b mod p，而 b 等于 u·b mod p 除以 u 的某种"记数"…… 实际上 b ≡ a·u⁻¹ (mod p)，只是反过来用了。结合外部，这大概是想表达"u 和 v 都能通过 (a+b)、(2a)、(a−b) 变成某个共同值"
这是欧几里得算法的"模拟手工辗转相减"：
若 a < b：交换，记操作 0；
否则 a -= b，记操作 1。
循环到 b == 0 结束，得到一串 0/1 操作序列 c[1..l]。
这里就把 (a,b) 一路减到最后 (a,0) = (gcd, 0)，记录了每一步是"交换"还是"相减"。

返回长度 l
对 u 和 v 各跑一次 get，得到长度 l1, l2 和操作序列 c1, c2。
输出总步数 l1+l2。
第一部分：输出 c1 正序，1 → '2'，0 → '3'。
第二部分：输出 c2 倒序，1 → '1'，0 → '3'
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
constexpr int N = 220;

int dfs(int a, int b) {
    if (b == 0) return 0;
    return dfs(b, a%b) + a/b + 1;
}
int get(int u, int p, bool *c) {
    int a, b, l = 0;
    do {
        b = rng()%(p-1) + 1;
        a = 1ll*u*b%p;
    } while (dfs(a, b) > 100);
    while (b != 0) {
        if (a < b) c[++l] = 0, swap(a, b);
        else a -= b, c[++l] = 1;
    }
    return l;
}

bool c1[N], c2[N];
int u, v, p;
int main() {
    fast;
    cin >> u >> v >> p;
    int l1 = get(u, p, c1), l2 = get(v, p, c2);
    cout << l1+l2 << '\n';
    for (int i = 1; i <= l1; i++) cout << (c1[i]?2:3) << ' ';
    for (int i = l2; i >= 1; i--) cout << (c2[i]?1:3) << ' ';
    cout << '\n';
    return 0;
}