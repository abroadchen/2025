//
// Created by Psy.C on 2026/3/11.
//
/**
N: 最大阶乘计算范围
M: 最大障碍物数量
fac[N]: 阶乘数组
inv[N]: 阶乘逆元数组
网格大小(n×m)和障碍物数量k
读入k个障碍物坐标（转换为0基索引）
添加终点(n-1, m-1)作为第k+1个点
按坐标排序所有点（包括障碍物和终点）

ans[i]: 从(0,0)到第i个点且不经过任何前面障碍物的路径数
初始化：从(0,0)到p[i]的总路径数
减去经过前面障碍物的路径数（容斥原理）
输出从起点到终点的合法路径数

设 dx = p[i].x - p[j].x, dy = p[i].y - p[j].y

那么 C(dx + dy, dx) 表示：

从点 (p[j].x, p[j].y) 到点 (p[i].x, p[i].y) 的路径数
需要向右走 dx 步，向下走 dy 步
总共 dx + dy 步，从中选择 dx 步向右走
即：C(dx + dy, dx) = (dx + dy)! / (dx! × dy!)


预处理：O(N)
排序：O(k log k)
DP计算：O(k²)
总体：O(N + k²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5, M = 5005, mod = 1e9+7;

struct node {
    ll x, y;
    bool operator<(const node &o) const {
        if (x == o.x) return y < o.y;
        return x < o.x;
    }
} p[M];

ll ksm(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b&1) res = res*a%mod;
        a = a*a%mod;
        b >>= 1;
    }
    return res % mod;
}

ll fac[N], inv[N];
ll C(ll n, ll m) {
    if (m > n || m < 0) return 0;
    return fac[n] * (inv[n-m]*inv[m]%mod) % mod;
}

void init() {
    fac[0] = 1; inv[0] = 1;
    for (int i = 1; i <= N-2; ++i) {
        fac[i] = fac[i-1]*i%mod;
        inv[i] = ksm(fac[i], mod-2);
    }
}

int n, m, k;
ll ans[N];
int main() {
    fast;
    cin >> n >> m >> k; init();
    for (int i = 1; i <= k; ++i) {
        cin >> p[i].x >> p[i].y;
        p[i].x--; p[i].y--;
    }
    p[++k].x = n - 1; p[k].y = m - 1;
    sort(p + 1, p + 1 + k);
    for (int i = 1; i <= k; ++i) {
        ans[i] = C(p[i].x + p[i].y, p[i].x);
        for (int j = 1; j < i; ++j) {
            if (p[j].y <= p[i].y)
                ans[i] += mod - ans[j] * C(p[i].x - p[j].x + p[i].y - p[j].y,
                    p[i].x - p[j].x) % mod;
            ans[i] %= mod;
        }
    }
    cout << ans[k] % mod << '\n';
    return 0;
}