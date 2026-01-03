//
// Created by Psy.C on 2026/1/3.
//
/**
 * 动态规划数组dp，原始数组a，前缀和数组s
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100100
#define M 111
#define rep(i,n) for (i=1; i<=n; ++i)
using namespace std;

int i, j;
ll dp[M][N], a[N], s[N];
double get(const int k) {//返回状态转移的值，计算从k到j的转移代价
    return static_cast<double>(dp[i-1][k] + a[j] * (j - k) - s[j] + s[k]);
}
ll Y(const int k) { return dp[i-1][k] + s[k]; }
ll X(const int x) { return x; }
//是否应该从队首移除元素
bool ok(const int l, const int k, const int jj) {//单调队列中的决策判断
    return Y(k) - Y(l) <= (X(k) - X(l)) * a[jj];//检查点(l,Y(l))到点(k,Y(k))的斜率是否小于等于a[jj]
}
bool maintain(const int k, const int ii, const int jj) {//维护下凸包
    return (Y(k) - Y(ii)) * (X(jj) - X(k)) >=
        (Y(jj) - Y(k)) * (X(k) - X(ii));//三个点(l,Y(l)), (ii,Y(ii)), (jj,Y(jj))是否形成下凸包
}

int main() {
    fast;
    int n, m, p, d[N], t; cin >> n >> m >> p;
    if (p >= m) { cout << "0\n"; return 0; }
    for (i = 2; i <= n; ++i) { cin >> d[i]; d[i] += d[i - 1]; }//从起点到第i点的累积距离
    rep(i,m) {
        int x, y; cin >> x >> y;
        a[i] = 1ll * (y - d[x]);//将原始的坐标系统转换为一个相对坐标系统 从第x个点到y点的相对距离
    }
    sort(a + 1, a + 1 + m);
    rep(i,m) s[i] = s[i - 1] + a[i];//a数组前i项的和
    rep(i,m) dp[0][i] = 1ll * 1e18;
    ll q[N];
    rep(i,p) {//每阶段的最优解
        int h = t = 0; q[0] = 0;//队列初始包含元素0
        for (j = 0; j <= m; ++j) {//遍历所有可能的位置
            while (h<t && ok(static_cast<int>(q[h]),
                static_cast<int>(q[h+1]), j)) h++;//移除队首无效决策点
            dp[i][j] = static_cast<ll>(get(static_cast<int>(q[h])));//使用队首最优决策更新当前状态
            while (h<t && maintain(static_cast<int>(q[t]),
                static_cast<int>(q[t-1]), j)) t--;//维护队列单调性，移除不必要的决策点
            q[++t] = j;//将当前决策j加入队列尾部
        }
    }
    cout << dp[p][m] << '\n';//使用p次操作处理完m个元素的最小代价
    return 0;
}