//
// Created by Psy.C on 2026/3/1.
//
/**
a[N]：存储各类型物品的初始数量
t[N]：存储任务类型
r[N]：存储重置标记
vis[N]：访问标记数组
ok[N]：有效性标记数组
m表示阶段数，k表示类型数
f统计：统计所有重置标记的总和

条件判断：如果没有重置标记（f == 0）
lf统计：lf记录空任务（t[i]=0）的数量
模拟过程：
如果t[i] != 0：消耗对应类型的物品
如果t[i] == 0：增加可用容量
判断结果：如果某类型剩余数量≤可用容量，输出'Y'，否则'N'

重置vis和ok数组
重置触发条件：r[i] != 0且还有重置机会
标记后续类型：将从当前阶段开始的所有任务类型标记为vis
寻找最小值：
在未被标记且数量≤当前可用容量的类型中找最小值
将这些类型标记为无效(ok[j] = 0)
可用容量减少最小值
执行任务：消耗对应类型物品或增加可用容量

如果剩余数量≤可用容量 或 类型无效，则输出'Y'
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+1, inf = 0x3f3f3f3f;

int a[N], t[N], r[N], vis[N], ok[N];
int main() {
    fast;
    int q, m, k; cin >> q;
    while (q--) {
        cin >> m >> k;
        for (int i = 1; i <= k; ++i) cin >> a[i];
        int f = 0;
        for (int i = 1; i < m; ++i) {
            cin >> t[i] >> r[i];
            f += r[i];
        }
        if (!f) {
            int lf = 0;
            for (int i = 1; i < m; ++i) {
                if (t[i]) a[t[i]]--;
                else lf++;
            }
            for (int i = 1; i <= k; ++i) {
                if (a[i] <= lf) putchar('Y');
                else putchar('N');
            }
        } else {
            for (int i = 1; i <= k; ++i)
                vis[i] = 0, ok[i] = 1;
            int lf = 0;
            for (int i = 1; i < m; ++i) {
                if (r[i] && f) {
                    f = 0;
                    for (int j = i; j < m; ++j) vis[t[j]] = 1;
                    int mn = inf;
                    for (int j = 1; j <= k; ++j) {
                        if (vis[j]) continue;
                        if (a[j] > lf) continue;
                        mn = min(mn, a[j]);
                        ok[j] = 0;
                    }
                    lf -= mn;
                }
                if (t[i]) a[t[i]]--; else lf++;
            }
            for (int i = 1; i <= k; ++i) {
                if (a[i] <= lf || !ok[i]) putchar('Y');
                else putchar('N');
            }
        }
        puts("");
    }
    return 0;
}