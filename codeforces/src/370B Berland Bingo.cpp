//
// Created by Psy.C on 2026/1/21.
//
/**
* n: 集合数量
mp[i][j]: 记录第i个集合中元素j的出现次数
读入n个集合，每个集合包含m个元素
 *
*外层循环: 遍历每个集合i
中层循环: 检查是否存在其他集合j能支配集合i
内层循环: 检查集合j是否在所有元素上都不超过集合i
if (mp[j][k] > mp[i][k]): 如果集合j中元素k的数量大于集合i，则j不能支配i
tag = true: 表示集合j支配集合i（j中每个元素的数量都不超过i）
flag = false: 表示存在至少一个集合j支配集合i
 *
 *时间复杂度: O(n² × 元素范围) = O(n² × 102)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 120
using namespace std;


int main() {
    fast;
    int n, mp[N][N]; cin >> n;
    for (int i = 0, m; i < n; ++i) {
        cin >> m;
        while (m--) {
            int j; cin >> j;
            mp[i][j]++;
        }
    }
    int vis[N];
    memset(vis, 63, sizeof vis);
    for (int i = 0; i < n; ++i) {
        bool flag = true;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            bool tag = true;
            for (int k = 0; k <= 101; ++k) {
                if (mp[j][k] > mp[i][k]) { tag = false; break; }
            }
            if (tag) { flag = false; break; }
        }
        if (!flag) vis[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        if (vis[i]) cout << "YES\n"; else cout << "NO\n";
    }
    return 0;
}