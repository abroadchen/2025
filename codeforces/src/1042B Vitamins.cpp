//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
用二进制 3 位表示维生素覆盖状态：
A = 1 (001)
B = 2 (010)
C = 4 (100)
全选齐 = 7 (111)
dp[mask] = 达到维生素状态 mask（mask ∈ [0,7]）的最小总花费。

初始化：dp[0]=0（什么都不买，花费 0）；其余 INF。

转移：对每种果汁 i，遍历所有状态 j：
即"用当前果汁把状态 j 扩展到 j|vi"。

答案：dp[7]（A+B+C 全齐的最小花费），若仍为 INF 输出 -1。

复杂度：O(n × 8)，即 O(n)，非常快（n 万级没问题）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;
constexpr int inf = 0x3f3f3f3f;
int n;
int main() {
    fast;
    cin >> n;
    vector<int> p(n+5, 0), v(n+5, 0), dp(8, inf);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        string s; cin >> s;
        for (char c : s) {
            switch (c) {
                case 'A' : v[i] |= 1; break;
                case 'B' : v[i] |= 2; break;
                case 'C' : v[i] |= 4; break;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= 7; ++j)
            dp[j|v[i]] = min(dp[j|v[i]], dp[j]+p[i]);
    cout << (dp[7] == inf ? -1 : dp[7]) << '\n';
    return 0;
}