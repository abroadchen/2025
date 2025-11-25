//
// Created by Psy.C on 2025/11/24.
//
/*
*n, m：节点数和边数
hv[N]：预计算的哈希值数组
ha[N]：存储每个节点的邻接哈希值
hb[N]：存储每个节点加上自身哈希值的结果
 *
*hv[i] = mod^(i-1)，用于节点编号的哈希编码
这样可以将节点集合映射为唯一的哈希值
 *
*对于有cnt个相同值的组，可以形成cnt*(cnt-1)/2对
这些对代表具有相同邻居集合的节点对
 *
 *ha[i]就表示节点i的邻居集合的哈希值
 *
*统计的两种模式：
相同邻居模式：ha[u] = ha[v]
表示节点u和v有完全相同的邻居集合
包含关系模式：hb[u] = hb[v] 即 ha[u] + hv[u] = ha[v] + hv[v]
表示ha[u] - ha[v] = hv[v] - hv[u]
这意味着N(u) \ {v} = N(v) \ {u}（除去对方后邻居相同）
 *
 *时间复杂度：O(m + n log n)，空间复杂度：O(n)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0); \
cin.tie(nullptr); cout.tie(nullptr)
using namespace std;

typedef long long ll;
constexpr int N = 1e6+7, mod = 1e9+7;
int n, m;
ll hv[N], ha[N], hb[N];

void init() {
    hv[1] = 1;
    for (int i = 2; i <= n; ++i)
        hv[i] = hv[i-1] * mod;
}

void solve() {
    for (int i = 1; i <= n; ++i) hb[i] = ha[i] + hv[i];
    sort(ha + 1, ha + n + 1);//统计相同值的个数
    sort(hb + 1, hb + n + 1);
    ll cur = ha[1], ans(0), cnt(1);
    for (int i = 2; i <= n; ++i) {
        if (ha[i] == cur) ++cnt;
        else {
            ans += cnt * (cnt - 1) / 2;
            cnt = 1;
            cur = ha[i];
        }
    }
    ans += cnt * (cnt - 1) / 2;
    cur = hb[1]; cnt = 1;
    for (int i = 2; i <= n; ++i) {
        if (hb[i] == cur) ++cnt;
        else {
            ans += cnt * (cnt - 1) / 2;
            cnt = 1;
            cur = hb[i];
        }
    }
    ans += cnt * (cnt - 1) / 2;
    cout << ans << '\n';
}

int main() {
    fast;
    cin >> n >> m; init();
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        ha[u] += hv[v]; ha[v] += hv[u];
    }
    solve();
    return 0;
}