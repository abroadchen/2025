//
// Created by Psy.C on 2025/10/8.
//
/*
*p：存储每个节点的父节点
r：存储每个集合的秩（大小）
构造函数：初始化n个独立集合，每个元素的父节点是自己
find：查找根节点，并进行路径压缩优化
unite：合并两个集合，按秩合并优化
 *
*读取输入：n(房间数)、m(门数)、k(钥匙数)
读取每扇门连接的两个房间u[i]和v[i]，并转换为0索引
 *
*p[2][k]：存储每把钥匙在两种状态下的位置（房间号）
l[2][m]：存储每扇门在两种状态下对应的钥匙所在的房间
ni：钥匙名称到索引的映射
 *
*读取第一种状态的信息：
每把钥匙的名称、所在房间、能开的门数
记录钥匙名称到索引的映射
记录钥匙在状态0下的房间位置
记录每扇门对应的钥匙所在房间
 *读取第二种状态的信息，使用已有的钥匙索引映射
 *
*c[2][n][n]：存储两种状态下房间间的连通性
定义lambda函数b，用于计算给定状态下房间的连通性：
创建并查集
迭代地合并可达的房间（如果钥匙所在的房间与门的一端在同一连通分量，则门两端房间连通）
记录最终的连通性矩阵
 *
*计算两种状态下的连通性
检查两种状态的连通性是否一致，不一致则输出"NO"
 *
 *检查每扇门在两种状态下的钥匙位置是否连通
 *
 *检查每把钥匙在两种状态下的位置是否连通
 *
 *
 *
 */
#include <ios>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
using namespace std;

struct UnionFind {
    vector<int> p, r;
    //使用iota将p初始化为 [0, 1, 2, ..., n-1]
    UnionFind(int n) : p(n), r(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (r[x] < r[y]) {
            p[x] = y;
            r[y] += r[x];
        } else {
            p[y] = x;
            r[x] += r[y];
        }
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n, m, k; cin >> n >> m >> k;
    vector<int> u(m), v(m);
    for (int i = 0; i < m; ++i) {
        cin >> u[i] >> v[i];
        --u[i]; --v[i];
    }
    vector<vector<int>> p(2, vector<int>(k));
    vector<vector<int>> l(2, vector<int>(m));

    unordered_map<string, int> ni;//哈希表
    ni.reserve(k);

    for (int i = 0; i < k; ++i) {
        string name;
        int room, keyCount; cin >> name >> room >> keyCount; --room;
        ni[name] = i;
        p[0][i] = room;
        for (int j = 0; j < keyCount; ++j) {
            int doorId; cin >> doorId; --doorId;
            l[0][doorId] = room;
        }
    }
    for (int i = 0; i < k; ++i) {
        string name;
        int room, keyCount; cin >> name >> room >> keyCount; --room;
        int idx = ni[name];
        p[1][idx] = room;
        for (int j = 0; j < keyCount; ++j) {
            int doorId; cin >> doorId; --doorId;
            l[1][doorId] = room;
        }
    }
    vector<vector<vector<bool>>> c(2, vector<vector<bool>>(n, vector<bool>(n, false)));

    auto b = [&](int id) {
        UnionFind uf(n);
        bool f(true);
        while (f) {
            f = false;
            for (int i = 0; i < m; ++i) {
                int roomWithKey = l[id][i];
                int x = u[i], y = v[i];
                if (uf.find(roomWithKey) == uf.find(x) ||
                    uf.find(roomWithKey) == uf.find(y)) {
                    if (uf.unite(x, y)) f = true;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                c[id][i][j] = uf.find(i) == uf.find(j);
        }
    };
    b(0); b(1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (c[0][i][j] != c[1][i][j]) {
                cout << "NO\n";
                return 0;
            }

    for (int i = 0; i < m; ++i) {
        int s = l[0][i], e = l[1][i];
        if (!c[0][s][e]) {
            cout << "NO\n";
            return 0;
        }
    }

    for (int i = 0; i < k; ++i) {
        int s = p[0][i], e = p[1][i];
        if (!c[0][s][e]) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    return 0;
}