//
// Created by Psy.C on 2025/11/19.
//
/*
*遍历网格内部点(不包括边界)：
检查每个点及其上下左右四个邻居是否都为'1'
如果是，则在t[i-1][j-1]位置标记为1
这是在标记形成"十字"形状的中心点
 *
*外层循环遍历矩形的上边界r1
创建向量x记录当前窗口内的特征点分布
sum记录当前窗口内特征点总数
内层循环遍历矩形的下边界r2
*当窗口高度足够时(至少3行)，将新的一行数据加入统计
u = r2 - 2是当前要考虑的行
将该行的特征点信息累加到x和sum中
 *如果当前窗口内特征点总数少于k，则跳过
*创建前缀和数组p，大小为m+1
计算x数组的前缀和
 *
*idx用于记录满足条件的左边界位置
cnt记录当前情况下的方案数
遍历右边界j：
移动idx找到满足p[idx] ≤ p[j] - k的最大位置
将idx累加到cnt中
 *将当前情况的计数cnt加到总答案ans中
 */
#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, k; cin >> n >> m >> k;
    vector<string> g(n);
    for (int i = 0; i < n; ++i) cin >> g[i];//读取n行字符串构成网格
    vector<vector<int>> t(n, vector<int>(m, 0));
    for (int i = 1; i < n - 1; ++i) {
        for (int j = 1; j < m - 1; ++j) {
            if (g[i][j] == '1' && g[i - 1][j] == '1' &&
                g[i + 1][j] == '1' && g[i][j - 1] == '1' &&
                g[i][j + 1] == '1') t[i-1][j-1] = 1;
        }
    }
    ll ans = 0;
    for (int r1 = 0; r1 < n; ++r1) {
        vector<int> x(m, 0);
        int sum = 0;
        for (int r2 = r1; r2 < n; ++r2) {
            if (r2 >= r1 + 2) {
                int u = r2 - 2;
                for (int v = 0; v < m; ++v) {
                    x[v] += t[u][v];
                    sum += t[u][v];
                }
            }
            if (sum < k) continue;
            vector<int> p(m + 1, 0);
            for (int i = 1; i <= m; ++i) p[i] = p[i-1]+x[i-1];
            int idx = 0; ll cnt = 0;
            for (int j = 1; j <= m - 2; ++j) {
                while (idx < j && p[idx] <= p[j] - k) idx++;
                cnt += idx;
            }
            ans += cnt;
        }
    }
    cout << ans << '\n';
    return 0;
}