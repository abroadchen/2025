//
// Created by Psy.C on 2026/2/7.
//
/**
t[N]：存储物品类型
h[N]：存储物品所需条件/门槛
m[N]：存储物品的收益/增益

尝试两种起始类型(0或1)
cur：当前拥有的资源值(初始为x)
ty：当前寻找的物品类型(0或1)
res：本次尝试获得的物品数量
持续选择物品直到无法继续
mx：记录找到的最大收益值(初始为-1表示未找到)
id：记录被选中的物品索引

遍历所有物品寻找最优选择：
!used[j]：物品未被使用
t[j] == ty：物品类型匹配当前需求
cur >= h[j]：当前资源满足物品门槛
mx <= m[j]：收益不小于已找到的最大收益
如果条件满足，更新mx和id
如果mx仍为-1，说明没有符合条件的物品，跳出循环
标记选中物品为已使用
增加结果计数
更新当前资源值(加上收益)
切换类型(ty ^= 1实现0和1之间的切换)
结束内层while循环后，更新全局最大值

 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2010
using namespace std;


int main() {
    fast;
    int n, x; cin >> n >> x;
    int t[N], h[N], m[N];
    for (int i = 0; i < n; ++i) cin >> t[i] >> h[i] >> m[i];
    int ans = 0; bool used[N];
    for (int i = 0; i < 2; ++i) {
        memset(used, false, sizeof(used));
        int cur = x, ty = i, res = 0;
        while (true) {
            int mx = -1, id = 0;
            for (int j = 0; j < n; ++j) {
                if (!used[j] && t[j] == ty && cur >= h[j] && mx <= m[j]) {
                    mx = m[j];
                    id = j;
                }
            }
            if (mx == -1) break;
            used[id] = true;
            res++;
            cur += mx;
            ty ^= 1;
        }
        ans = max(ans, res);
    }
    cout << ans << '\n';
    return 0;
}