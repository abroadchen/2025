//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
dp[x]：某种以状态 x 结尾的组合方案数（x 取值范围是各数的因子）。dp[0]=1 表示空集
枚举 a[i] 的全部正因子 d。
对每个因子 d 做一次转移：dp[d] = dp[d] + dp[d-1]（含义：以因子 d 结束的组合，可以来自"继续沿用旧的 dp[d]" 或 "把空/前一状态 d-1 接上新元素"）
dp[d] 累加的必须是本次 a[i] 处理前的旧 dp[d-1]，不能是已被同一根 a[i] 更新过的值（否则会重复计数/状态被污染）。

大因子放入队列 q：q 中因子从大到小（因为 a[i]/j 随 j 增大而减小，先入的是最大的）。
小因子放入栈 s：栈顶是 1..√a_i 中最大开始，即也从大到小。
因此两条通道都保证按因子从大到小执行 dp[d]+=dp[d-1]：处理 d 时，d-1 若也在本根 a[i] 的因子中，则比 d 更小、尚未被本根更新（因从大到小），故累加的是旧值——保证了 01 性质（每个数的因子状态只推进一次）
把所有状态 1..n 的 dp 累加得答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e6+5, mod = 1e9+7;

// template<class T>
// void read(T& x) {
//     int f = 0, ch = 0; x = 0;
//     for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
//     for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
//     if (f) x = -x;
// }
//
// int n, a[N], dp[N], ans;
// stack<int> s;
// queue<int> q;

int n, a[N];
vector<int> v[N];
ll dp[N], ans;
int main() {
    fast;
    int i, j;
    // read(n);
    // rep(i,n) read(a[i]); dp[0] = 1;
    // rep(i,n) {
    //     for (int j = 1; j*j <= a[i]; j++) if (a[i]%j == 0) {
    //         s.push(j);
    //         if (j*j != a[i]) q.push(a[i]/j);
    //     }
    //     while (!q.empty()) { dp[q.front()] = (dp[q.front()] + dp[q.front()-1]) % mod; q.pop(); }
    //     while (!s.empty()) { dp[s.top()] = (dp[s.top()] + dp[s.top()-1]) % mod; s.pop(); }
    // }
    // rep(i,n) ans = (ans + dp[i]) % mod;
    // cout << ans;

    cin >> n;
    rep(i,n) {
        cin >> a[i];
        int sq = sqrt(a[i]);
        rep(j,sq) if (a[i]%j == 0) {
            v[i].push_back(j);
            if (j*j != a[i]) v[i].push_back(a[i]/j);
        }
        ranges::sort(v[i]);
    }
    dp[0] = 1;
    rep(i,n) for (int j = v[i].size()-1; j >= 0; j--) {
        int x = v[i][j];
        if (dp[x-1] == 0) continue;
        ans += dp[x-1]; ans %= mod;
        (dp[x] += dp[x-1]) %= mod;
    }
    cout << ans << '\n';
    return 0;
}