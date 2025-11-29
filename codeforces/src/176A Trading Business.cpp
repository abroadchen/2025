//
// Created by Psy.C on 2025/11/29.
//
/*
*n: 商店数量
m: 物品种类数
k: 初始资金
*a[i][j]: 第i个商店第j种物品的买入价
b[i][j]: 第i个商店第j种物品的卖出价
c[i][j]: 第i个商店第j种物品的数量
vis[M]: 访问标记数组，用于标记已处理的物品
 *
 *f(x,y)计算从商店x买入、在商店y卖出能获得的最大利润
*清空访问标记数组
last: 剩余资金
ans: 累计利润
*在所有未处理的物品中寻找利润最大的物品
b[y][i] - a[x][i]: 在商店y卖出价减去在商店x买入价
mx: 当前最大利润
idx: 最大利润物品的索引
 *
*res: 能购买的数量（资金限制和库存限制的较小值）
ans += res * mx: 累加利润
标记该物品已处理
更新剩余资金
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int N = 20, M = 200;
int n, m, k;
int a[N][M], b[N][M], c[N][M], vis[M];

int f(const int x, const int y) {
    for (auto& i : vis) i = 0;
    int last = k, ans = 0;
    while (last) {
        int flag = 0, mx = 0, idx = 0;
        rep(i,m) {
            if (vis[i]) continue;
            if (b[y][i] - a[x][i] > mx) {
                mx = b[y][i] - a[x][i];
                idx = i;
                flag = 1;
            }
        }
        if (!flag) break;
        const int res = min(last, c[x][idx]);
        ans += res * mx;
        vis[idx] = 1;
        last -= res;
    }
    return ans;
}

int main() {
    fast;
    cin >> n >> m >> k;
    rep(i,n) {
        string s; cin >> s;
        rep(j,m) cin >> a[i][j] >> b[i][j] >> c[i][j];
    }
    int ans = 0;
    rep(i,n) rep(j,n) ans = max(ans, f(i, j));
    cout << ans << '\n';
    return 0;
}