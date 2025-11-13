//
// Created by Psy.C on 2025/11/13.
//
/*
*n：总资源量/容量
m：物品种类数
c0, d0：基础物品的消耗和价值
a,b,c,d：临时变量用于读入
dp[N]：动态规划数组
vp：pair向量，存储物品信息
 *
*读入m种物品信息，每种物品有4个属性：
a：该物品的总数量
b：制作一个该物品需要的数量
c：制作一个该物品的消耗量
d：制作一个该物品的价值
使用二进制拆分优化：优化将O(n)的复杂度降低到O(log n)
将a/b个物品拆分成1,2,4,8,...的组合
这样可以减少物品数量，提高效率
例如：如果有13个物品，拆分为1+2+4+6个物品
 *
*dp[i]表示拥有i资源时能获得的最大价值
初始值为全部用于制作基础物品的价值
 *
*0-1背包问题求解：
遍历所有物品（经过二进制拆分后的）
x：该物品的消耗量
p：该物品的价值
从后往前更新dp数组，避免重复使用同一物品
状态转移方程：dp[j] = max(dp[j], dp[j-x] + p)
 *
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<int, int> ii;
const int N = 1005;
int n, m, c0, d0, a, b, c, d, dp[N];
vector<ii> vp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> c0 >> d0;

    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c >> d;
        int l(1), r(a / b);
        while (r - l >= 0) {
            ii x = {l * c, l * d}; vp.push_back(x);
            r -= l;
            l <<= 1;
        }
        if (r >= 0) {
            ii x = {r * c, r * d}; vp.push_back(x);
        }
    }
    for (int i = 0; i <= n; ++i) dp[i] = (i / c0) * d0;
    for (int i = 0; i < vp.size(); ++i) {
        int x = vp[i].first, p = vp[i].second;
        for (int j = n; j >= x; --j)
            dp[j] = max(dp[j], dp[j - x] + p);
    }
    cout << dp[n] << '\n';
    return 0;
}