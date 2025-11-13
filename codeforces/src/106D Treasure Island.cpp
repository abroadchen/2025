//
// Created by Psy.C on 2025/11/13.
//
/*
*读入网格行数n和列数m
声明字符串向量a存储网格内容
读入n行字符串构成网格
*声明元组向量b，存储字母及其位置和状态
元组包含：字符、行坐标、列坐标、存活状态(1表示存活)
遍历网格，如果是字母字符就加入向量b
*声明两个二维前缀和数组：
v[i][j]：列方向前缀和（垂直方向）
h[i][j]：行方向前缀和（水平方向）
初始化：如果网格位置是'#'则为1，否则为0
计算前缀和：
v[i][j] = 当前行的值 + 上一行的前缀和
h[i][j] = 当前列的值 + 左一列的前缀和
 *
*定义垂直方向查询函数qv：
查询第i列从行l到行r之间障碍物('#')的数量
如果越界返回1（表示有障碍）
使用前缀和快速计算区间和
*定义水平方向查询函数qh：
查询第i行从列l到列r之间障碍物('#')的数量
如果越界返回1（表示有障碍）
使用前缀和快速计算区间和
 *
*读入方向d和步数s
遍历所有字母（元组解构：c字符，x行坐标，y列坐标，t状态）
如果字母已死亡(t=0)则跳过
*北(N)：向上移动s步，检查路径上是否有障碍
南(S)：向下移动s步，检查路径上是否有障碍
西(W)：向左移动s步，检查路径上是否有障碍
东(E)：向右移动s步，检查路径上是否有障碍
如果路径上有障碍，字母死亡(t=0)
否则更新坐标位置
 *
*收集存活字母：
遍历所有字母，如果存活(t=1)则加入结果字符串
对结果字符串排序
通过前缀和实现O(1)时间复杂度的区间障碍物检测
 */
#include <cctype>
#include <vector>
#include <iostream>
#include <algorithm>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m; cin >> n >> m;
    vector<string> a(n);
    for (auto& x : a) cin >> x;
    vector<tuple<char,int,int,bool>> b;
    rep(i,n) rep(j,m) if (isalpha(a[i][j])) {
        b.emplace_back(a[i][j], i, j, 1);
    }
    vector<vector<int>> v(n, vector<int>(m)),
    h(n, vector<int>(m));
    rep(i,n) rep(j,m) {
        v[i][j] = h[i][j] = (a[i][j] == '#');
        if (i > 0) v[i][j] += v[i - 1][j];
        if (j > 0) h[i][j] += h[i][j - 1];
    }

    auto qv = [&](int i, int l, int r) {
        if (l > r) swap(l, r);
        if (l < 0 || r >= n) return 1;
        return v[r][i] - (l ? v[l - 1][i] : 0);
    };
    auto qh = [&](int i, int l, int r) {
        if (l > r) swap(l, r);
        if (l < 0 || r >= m) return 1;
        return h[i][r] - (l ? h[i][l - 1] : 0);
    };
    int k; cin >> k;
    while (k--) {
        char d; int s; cin >> d >> s;
        for (auto& [c, x, y, t] : b) {
            if (!t) continue;
            if (d == 'N') {
                if (qv(y, x - 1, x - s)) t = 0;
                else x -= s;
            }
            if (d == 'S') {
                if (qv(y, x + 1, x + s)) t = 0;
                else x += s;
            }
            if (d == 'W') {
                if (qh(x, y - 1, y - s)) t = 0;
                else y -= s;
            }
            if (d == 'E') {
                if (qh(x, y + 1, y + s)) t = 0;
                else y += s;
            }
        }
    }
    string ans("");
    for (auto [c, x, y, t] : b) if (t) ans += c;
    sort(ans.begin(), ans.end());
    if (ans.empty()) ans = "no solution";
    cout << ans << '\n';
    return 0;
}