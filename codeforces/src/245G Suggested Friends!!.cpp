//
// Created by Psy.C on 2025/12/16.
//
/*
 *m（边数）和n（节点数，初始化为0）
*声明字符数组ch用于读取字符串
声明映射mp用于将字符串名称映射到整数ID
声明字符串数组name用于存储节点名称
声明位集数组b用于表示邻接矩阵
声明向量数组g用于表示邻接表
 *
*循环m次读取每条边
读取两个节点名称u和v
*如果节点u不在映射中，将其加入映射并分配ID（n++）
如果节点v不在映射中，将其加入映射并分配ID（n++）
*获取u和v的ID
在name数组中存储对应的名称
*在位集中标记s和t相连（无向图）
在邻接表中添加相互连接关系
 *
 */
#include <iostream>
#include <map>
#include <vector>
#include <bitset>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 5555<<1
using namespace std;


int main() {
    fast;
    int m, n = 0; cin >> m;
    char ch[50];
    map<string, int> mp;
    string name[N];
    bitset<N> b[N];
    vector<int> g[N];
    for (int i = 0; i < m; ++i) {
        string u, v;  cin >> ch; u = ch;
        cin >> ch; v = ch;
        if (mp.find(u) == mp.end()) mp[u] = n++;
        if (mp.find(v) == mp.end()) mp[v] = n++;
        int s = mp[u], t = mp[v];
        name[s] = u; name[t] = v;
        b[s][t] = b[t][s] = true;
        g[t].push_back(s); g[s].push_back(t);
    }
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        cout << name[i].c_str() << ' ';
        int c = 0, mx = 0;
        for (int j = 0; j < n; ++j) {//遍历所有节点j
            if (b[i][j] || i == j) continue;//如果j与i相连或j等于i，则跳过
            int t = 0;
            for (const int k : g[j]) if (b[i][k]) t++;//j的邻居中同时也是i的邻居的数量
            if (t > mx) { mx = t; c = 1; }//找到更大的共同邻居数，更新最大值并重置计数器
            else if (t == mx) c++;//等于最大值，增加计数器
        }
        cout << c << '\n';
    }
    return 0;
}