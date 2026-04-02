//
// Created by Psy.C on 2026/4/1.
//
/**
n: 元素个数
k: 分割段数
t[N]: 输入数组
s[N]: t的前缀和
x[N]: 特殊前缀和，累加 s[i]/t[i]
y[N]: 1/t[i] 的前缀和
f[i][j]: 前i个元素分成j段的最优解
q: 双端队列，用于维护决策单调性

枚举分割段数j从1到k
每轮清空队列，加入初始状态0
移除队列前端的无效决策点
判断条件基于斜率比较：当前最优决策可能已被更好的替代
状态转移方程：当前最优解 = 最优决策点的代价 + 新增部分的代价
这个公式来源于原DP状态转移的数学变形

维护决策点的凸包性质
如果新点会破坏凸性，则移除队尾元素
比较相邻决策点间的斜率关系
将当前点i加入队列尾部 作为后续状态转移的潜在最优决策
总时间复杂度：O(n*k)

Y(q.front(), j-1)-Y(sf, j-1): 计算队首和第二个元素的Y值差
y[i]*(s[q.front()]-s[sf]): 计算相关的斜率项
如果当前队首不是最优决策，则弹出队首
这是斜率优化的关键步骤，维护决策的单调性
从队首的最优决策转移过来
f[q.front()][j-1]: 上一段的最优解
x[i]-x[q.front()]: x的差值部分
s[q.front()]*(y[i]-y[q.front()]): 计算新增区间的贡献
整体构成了完整的状态转移方程
(Y(q.back(), j-1)-Y(sb, j-1))/(s[q.back()]-s[sb]): 队尾两个点的斜率
(Y(i, j-1)-Y(q.back(), j-1))/(s[i]-s[q.back()]): 新点与队尾点的斜率
如果新点的加入会破坏凸包的单调性，则弹出队尾元素

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define Y(p,t) (f[p][t]-x[p]+y[p]*s[p])
#define sf *(q.begin()+1)///队列中第二个元素（队首后一个元素）
#define sb *(q.rbegin()+1)///队列中倒数第二个元素（队尾前一个元素）
using namespace std;
constexpr int N = 2e5+5, M = 55;
int n, k, t[N];
double s[N], x[N], y[N], f[N][M];
deque<int> q;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> t[i]; s[i] = s[i-1]+t[i];
        x[i] = x[i-1]+s[i]/t[i]; y[i] = y[i-1]+1./t[i];
        f[i][0] = 1e18;
    }
    for (int j = 1; j <= k; ++j) {
        q.clear(), q.push_back(0), f[0][j] = 1e18;
        for (int i = 1; i <= n; ++i) {
            while (q.size() > 1 && Y(q.front(), j-1)-Y(sf, j-1) > y[i]*(s[q.front()]-s[sf]))
                q.pop_front();
            f[i][j] = f[q.front()][j-1]+x[i]-x[q.front()]-s[q.front()]*(y[i]-y[q.front()]);
            while (q.size() > 1 && (Y(q.back(), j-1)-Y(sb, j-1))/(s[q.back()]-s[sb]) >
                (Y(i, j-1)-Y(q.back(), j-1))/(s[i]-s[q.back()]))
                q.pop_back();
            q.push_back(i);
        }
    }
    cout << f[n][k] << '\n';
    return 0;
}