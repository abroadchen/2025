//
// Created by Psy.C on 2025/11/16.
//
/*
*读取矩阵维度n(行数)和m(列数)
创建n×m的二维矩阵g
读取矩阵所有元素
*读取目标三个值到向量t
对t进行排序
*r[i]: 第i行的元素和
c[j]: 第j列的元素和
*计算行和的前缀和
计算列和的前缀和
现在r[i]表示前i+1行的累积和，c[j]表示前j+1列的累积和
 *
*将矩阵按行分割成三部分：[0,i], [i+1,j], [j+1,n-1]
ret[0]: 前i+1行的和
ret[1]: 第i+1到j行的和
ret[2]: 第j+1到n-1行的和
排序后返回
 *
 *将矩阵按列分割成三部分：[0,i], [i+1,j], [j+1,m-1]
 *
*枚举行分割方案：
i从0到n-2，j从i+1到n-2
获取分割结果cur，如果与目标t相等则计数加1
 *枚举列分割方案
 *
 *O(n² + m²)
 */
#include <numeric>
#include <iostream>
#include <algorithm>
#include <vector>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(nullptr)->sync_with_stdio(false);
    auto solve = [&](int x=1) {
        int n, m; cin >> n >> m;
        vector<vector<int>> g(n, vector<int>(m));
        rep(i,n) rep(j,m) cin >> g[i][j];
        vector<int> t(3);
        rep(i,3) cin >> t[i];
        sort(t.begin(), t.end());
        vector<int> r(n), c(m);
        rep(i,n) rep(j,m) r[i] += g[i][j], c[j] += g[i][j];
        partial_sum(r.begin(), r.end(), r.begin());
        partial_sum(c.begin(), c.end(), c.begin());

        auto getr = [&](int i, int j) {
            vector<int> ret(3);
            ret[0] += r[i];
            ret[1] += r[j] - r[i];
            ret[2] += r[n - 1] - r[j];
            sort(ret.begin(), ret.end());
            return ret;
        };
        auto getc = [&](int i, int j) {
            vector<int> ret(3);
            ret[0] += c[i];
            ret[1] += c[j] - c[i];
            ret[2] += c[m - 1] - c[j];
            sort(ret.begin(), ret.end());
            return ret;
        };
        int ans(0);
        rep(i,n-1) {
            for (int j = i + 1; j < n - 1; ++j) {
                if (i == j) continue;
                vector<int> cur = getr(i, j);
                ans += cur == t;
            }
        }
        rep(i,m-1) {
            for (int j = i + 1; j < m - 1; ++j) {
                if (i == j) continue;
                vector<int> cur = getc(i, j);
                ans += cur == t;
            }
        }
        cout << ans << '\n';
    };
    int x = 1;
    rep(i,x) solve(i);
    return 0;
}