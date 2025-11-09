//
// Created by Psy.C on 2025/11/8.
//
/*
*读取网格行数n、列数m和阈值e
创建大小为n的字符串向量g存储网格
读取网格的每一行
 *
*创建26个向量的向量p，用于存储每个小写字母的位置
创建向量sp存储所有'S'字符的位置
遍历网格中每个位置：
如果是'S'，将其坐标加入sp
如果是小写字母，将其坐标加入对应字母的向量中
 *
*创建大小为26的向量d，初始化为最大整数，用于存储每个字母到最近'S'的距离平方
如果存在'S'字符：
对每个字母i：
对该字母的每个位置x：
对每个'S'的位置y：
计算曼哈顿坐标差
计算欧几里得距离的平方
更新最小距离平方
 *
*遍历字符串中的每个字符：
如果是小写字母：
检查该字母是否在网格中存在，不存在则输出-1并退出
如果是大写字母：
转换为小写并获取索引
检查对应小写字母是否存在于网格中，不存在则输出-1并退出
检查是否存在'S'字符，不存在则输出-1并退出
如果该字母到最近'S'的距离平方大于e²，则计数器加1
 *
 */
#include <cctype>
#include <iostream>
#include <vector>
#include <algorithm>
#define rep(i,n) for(i=0;i<(n);++i)
#define sqr(x) ((x)*(x))
using namespace std;

typedef pair<int,int> pii;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, e, i, j; cin >> n >> m >> e;
    vector<string> g(n);
    rep(i,n) cin >> g[i];
    vector<vector<pii>> p(26);
    vector<pii> sp;
    rep(i,n) rep(j,m) {
        char c = g[i][j];
        if (c == 'S') sp.push_back({i, j});
        else p[c - 'a'].push_back({i, j});
    }
    vector<int> d(26, INT_MAX);
    if (!sp.empty()) {
        rep(i,26) {
            for (auto& x : p[i]) {
                for (auto& y : sp) {
                    int dx = x.first - y.first,
                    dy = x.second - y.second,
                    d2 = dx * dx + dy * dy;
                    d[i] = min(d[i], d2);
                }
            }
        }
    }
    int q; cin >> q;
    string s; cin >> s; int cnt(0);
    for (char ch : s) {
        if (islower(ch)) {
            if (p[ch - 'a'].empty()) { cout << -1; return 0; }
        } else {
            char lo = tolower(ch);
            int idx = lo - 'a';
            if (p[idx].empty()) { cout << -1; return 0; }
            if (sp.empty()) { cout << -1; return 0; }
            if (d[idx] > e * e) cnt++;
        }
    }
    cout << cnt;
    return 0;
}