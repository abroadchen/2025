//
// Created by Psy.C on 2026/9/29.
//
/**
对每个数做质因数分解，记录每个质因子的指数。
键 i = 质因子；值是一个 bitmask，其中第 (sum-1) 位为 1 表示"这个质因子的指数至少为 sum"。
s[i] |= 1<<(sum-1)：s[i] 的二进制某一位代表该质因子的某个指数档位存在。
这种 bitmask 的妙处：对于质因子 p，把所有数中 p 的指数看成一个集合，第 b 位为 1 表示"存在一个数的指数 ≥ b+1"。这个 mask 就是该质因子子游戏的完整状态
x 是该质因子子游戏的状态 mask。
递归计算 SG 值，vis 记录所有可达后继状态的 SG 值，然后取 mex（最小未出现的非负整数）。
状态转移：y = (x>>i) | (x & ((1<<(i-1))-1))。
这一步表示"进行一个操作"：选 k = i，把所有指数 ≥ i 的数除以 p^i。
除以 p^i 相当于：原本指数 b 的数变成指数 b-k（那些 < k 的指数变成 0，即从集合移除）。
对 bitmask 来说：把所有 ≥ i 的位右移 i 位（x>>i），把 < i 的位保留低 i-1 位原样（x & ((1<<(i-1))-1)），两者取或。
记忆化存储在后继 map sg 里避免重复计算
遍历所有质因子的 SG 值，做异或（Nim 和）‍。
若异或结果 ans != 0 → 先手 Mojtaba 必胜；否则后手 Arpa 必胜。
（使用 views::values 是 C++ ranges 库，遍历 map s 的所有 value，即各质因子子游戏的 mask。）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

map<int, int> s, sg;
static void init(int x) {
    int t = x;
    for (int i = 2; i*i <= t; ++i) {
        if (x%i == 0) {
            int sum = 0;
            while (x%i == 0) sum++, x/=i;
            s[i] |= 1<<(sum-1);
        }
    }
    if (x > 1) s[x] |= 1;
}

static int dfs(int x) {
    if (x == 0) return 0;
    if (sg.contains(x)) return sg[x];
    map<int, int> vis;
    int t = x, m = 0;
    while (t) m++, t>>=1;
    for (int i = 1; i <= m; ++i) {
        int y = x>>i|(x&(1<<(i-1))-1);
        vis[dfs(y)] = 1;
    }
    for (int i = 0; ; ++i)
        if (!vis.contains(i))
            return sg[x] = i;
}

int ans;
signed main() {
    fast;
    int n; cin >> n;
    for (int i = 1, x; i <= n && cin >> x; ++i) init(x);
    for (auto &val: s | views::values) ans ^= dfs(val);
    cout << (ans ? "Mojtaba" : "Arpa") << '\n';
    return 0;
}