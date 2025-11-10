//
// Created by Psy.C on 2025/11/10.
//
/*
*n, m：网格行数和列数
g：存储网格的字符串向量
pos1[28]：存储28种字符（a-z, A-B）在网格中的位置
 *
*读取网格并记录每种字符的位置：
小写字母a-z映射到0-25
大写字母A-B映射到26-27（只有A和B）
每种字符应该恰好出现2次
 *
*pos2[14]：将网格划分为14个2×2区域，存储每个区域的位置
v：标记数组，记录哪些位置已被处理
*将网格划分为2×2的区域：
每个2×2区域包含4个相邻位置
总共14个区域（因为n×m网格总共有56个位置，56/4=14）
 *
*cnt：计数满足条件的方案数
a：当前方案的标记数组
ans：存储最终方案
 *
*u：当前处理第几个区域（总共7个区域被使用）
state：状态压缩，记录哪些2×2区域已被使用
 *
*检查当前方案是否满足条件：
对于每种字符，获取其两个位置对应的区域编号
确保每对区域编号只出现一次
如果某对区域编号重复出现，则方案无效
 *如果方案有效，保存方案并增加计数
 *
*选择两个未使用的2×2区域分配给当前组：
找到第一个未使用的区域t
将区域t和另一个未使用区域j分配给组u
递归处理下一组
 */
#include <iostream>
#include <cctype>
#include <vector>
#define rep(i,n) for(int (i)=0;(i)<(n);++(i))
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin>>n>>m;
    vector<string> g(n);
    vector<pair<int, int>> pos1[28];
    rep(i,n) {
        cin>>g[i];
        rep(j,m) {
            if (g[i][j] == '.') continue;
            int id = -1;
            if (islower(g[i][j])) id = g[i][j] - 'a';
            else id = 26 + g[i][j] - 'A';
            pos1[id].push_back({i, j});
        }
    }
    vector<pair<int, int>> pos2[14];
    vector<vector<bool>> v(n, vector<bool>(m));
    for (int i = 0, k = 0; i < n; ++i) {
        rep(j,m) {
            if (v[i][j] || g[i][j] == '.') continue;
            rep(a,2) rep(b,2) {
                v[i + a][j + b] = true;
                pos2[k].push_back({i+a, j+b});
            }
            k++;
        }
    }
    int cnt(0);
    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<int>> ans;
    auto dfs = [&](auto&& dfs, int u, int state) {
        if (u == 7) {
            bool ok = true;
            vector<vector<bool>> mark(7, vector<bool>(7));
            rep(i,28) {
                int x = a[pos1[i][0].first][pos1[i][0].second],
                y = a[pos1[i][1].first][pos1[i][1].second];
                if (x > y) swap(x, y);
                if (mark[x][y]) { ok = false; break; }
                mark[x][y] = true;
            }
            if (ok) { ans = a; cnt += 1; }
            return;
        }
        int t(0);
        while (state >> t & 1) t++;
        for (auto [x, y] : pos2[t]) a[x][y] = u;
        for (int j = t + 1; j < 14; ++j) {
            if (state >> j & 1) continue;
            for (auto [x, y] : pos2[j]) a[x][y] = u;
            dfs(dfs, u + 1, state | (1 << t) | (1 << j));
        }
    };
    dfs(dfs, 0, 0);
    cout << 1ll * cnt * 5040 << '\n';//方案数乘以7!（每组内部的排列数）
    rep(i,n) {//输出标记后的网格
        rep(j,m) {
            if (g[i][j] == '.') cout << '.';
            else cout << ans[i][j];
        }
        cout << '\n';
    }
    return 0;
}