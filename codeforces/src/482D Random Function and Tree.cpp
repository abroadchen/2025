//
// Created by Psy.C on 2026/2/17.
//
/**
f[N][2]: DP状态数组
g[N][4]: 辅助DP数组

状态转移方程（使用旧值计算新值）：
f[x][0] += f[x][0] * f[z][0] + f[x][1] * f[z][1]
f[x][1] += f[x][0] * f[z][1] + f[x][1] * f[z][0]
f[x][0]: 以x为根的子树中，节点x颜色与其父节点相同的情况下满足条件的方案数
f[x][1]: 以x为根的子树中，节点x颜色与其父节点不同的情况下满足条件的方案数

g[x][0]: 与父节点同色的辅助计算
g[x][1]: 与父节点异色的辅助计算
res: 临时结果，累积计算
g[x][1] += g[x][0] * f[z][1]
g[x][0] += t * f[z][1] (其中t是原来的g[x][1])
res *= (f[z][0] + 1)

时间复杂度：O(n)
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+2, mod = 1e9+7;
inline void add(int& x, const int y) {
    (x += y) >= mod ? x -= mod : x;
}

vector<int> v[N];//存储树的结构
int f[N][2], g[N][4];
inline void dfs(const int x) {
    ranges::sort(v[x]); //对当前节点x的孩子节点排序
    f[x][1] = 1, f[x][0] = 0;
    for (int i = 0, z; i < v[x].size(); ++i) {
        dfs(z = v[x][i]);//递归处理孩子节点z
        const int t0 = f[x][0], t1 = f[x][1];
        add(f[x][0], 1ll*t0*f[z][0]%mod);//每个孩子节点的贡献直接累加到当前节点
        add(f[x][0], 1ll*t1*f[z][1]%mod);
        add(f[x][1], 1ll*t0*f[z][1]%mod);
        add(f[x][1], 1ll*t1*f[z][0]%mod);
    }
    int res = 1;
    ranges::reverse(v[x]);
    add(f[x][0], f[x][0]), add(f[x][1], f[x][1]);//各自加倍
    g[x][0] = 1, g[x][1] = 0;
    for (int i = 0, z; i < v[x].size(); ++i) {
        z = v[x][i];
        const int t = g[x][1];
        add(g[x][1], 1ll*g[x][0]*f[z][1]%mod);//g值的更新依赖于之前的g值
        add(g[x][0], 1ll*t*f[z][1]%mod);
        res = 1ll*res*(f[z][0]+1)%mod;
    }
    add(f[x][0], mod - g[x][1]);//用辅助数组g来修正f值
    add(f[x][1], mod - res);
}

int q, n;
int main() {
    fast;
    q = 1;
    while (q--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) v[i].clear();
        for (int i = 2, x; i <= n; ++i) {
            cin >> x;
            v[x].push_back(i);
        }
        dfs(1);
        cout << (f[1][0] + f[1][1])%mod << '\n';//根节点两种状态的和（总方案数）
    }
    return 0;
}