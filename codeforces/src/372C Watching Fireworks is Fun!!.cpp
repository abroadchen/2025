//
// Created by Psy.C on 2026/1/22.
//
/**
* n: 网格大小（位置范围1到n）
m: 事件数量（按时间顺序处理）
d: 移动速度（单位时间内最大移动距离）
每个事件i有三个属性：a[i](位置), b[i](收益), t[i](时间)
 *dp[2][N]: 滚动数组，dp[0]和dp[1]交替使用
 *
 *第1个事件在每个位置的收益 = 基础收益 - 与事件位置的距离
 *第1个事件的状态(dp[1]) → 通过第2个事件更新 → 第2个事件的状态(dp[0])
 *
*朴素DP: O(m × n²)
单调队列优化: O(m × n)
空间优化: 使用滚动数组，O(n)

j: 当前目标位置
q[l]: 单调队列中存储的可转移位置
q[l] < j - len 的含义
判断队首位置是否超出了从位置j可达的范围
位置 q[l] 太靠左，无法从位置 j 在时间 len 内到达
需要移除: 从队列前端移除无效的转移源

左侧：dp[1-c][q[r]]
q[r]: 队列末尾存储的位置索引
dp[1-c][q[r]]: 该位置在前一阶段的最优值
含义: 队列末尾位置的dp值
右侧：dp[1-c][j]
j: 当前正在考虑的新位置
dp[1-c][j]: 位置j在前一阶段的最优值
含义: 当前位置的dp值
当前位置j的dp值比队列末尾位置更好

q[l] 太靠右了：位置q[l]在目标位置j的右侧太远
无法到达：从q[l]无法在距离len内到达位置j
超出可达范围：违反了距离约束
操作
移除队首：l++，丢弃这个无效的转移源


1. dp[1-c][q[l]] - 前一阶段最优值
1-c: 滚动数组索引，指向前一阶段
q[l]: 单调队列头部，是可达范围内dp值最大的位置
含义: 从最优的前一位置转移过来的累计收益
2. b[i] - 当前事件收益
第i个事件的基础收益值
含义: 到达第i个事件时获得的收益
3. abs(a[i] - j) - 距离代价
a[i]: 第i个事件的发生位置
j: 当前目标位置
abs(a[i] - j): 从位置j到事件位置a[i]的距离
含义: 在目标位置j执行事件i所需付出的代价
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 150005
#define M 305
#define inf 0x3f3f3f3f
#define INF 1e18
using namespace std;


int main() {
    fast;
    int n, m, d; cin >> n >> m >> d;
    ll a[M], b[M], t[M], dp[2][N];
    for (int i = 1; i <= m; ++i) cin >> a[i] >> b[i] >> t[i];
    memset(dp, -inf, sizeof(dp));
    for (int i = 1; i <= n; ++i) dp[1][i] = b[1] - abs(a[1] - i);//i=1 是基础情况，单独处理
    int c = 0, q[N]={};
    //i≥2 是递推步骤，用循环处理
    for (int i = 2; i <= m; ++i) {//从左到右扫描: 处理左侧可达的转移
        const ll len = (t[i] - t[i-1]) * d;//时间间隔内能移动的最大距离
        int l = 1, r = 0;
        for (int j = 1; j <= n; ++j) {
            while (l <= r && q[l] < j - len) l++;//维护窗口大小 左边太远的位置 左侧不可达
            while (l <= r && dp[1-c][q[r]] < dp[1-c][j]) r--;//维护单调性
            q[++r] = j;//将当前元素加入队列
            dp[c][j] = dp[1-c][q[l]] + b[i] - abs(a[i] - j);
        }
        l = 1, r = 0;
        for (int j = n; j >= 1; --j) {//从右到左扫描: 处理右侧可达的转移
            while (l <= r && q[l] > j + len) l++; //右边太远的位置
            while (l <= r && dp[1-c][q[r]] < dp[1-c][j]) r--;
            q[++r] = j;
            dp[c][j] = max(dp[c][j], dp[1-c][q[l]] + b[i] - abs(a[i] - j));
        }
        c = 1 - c;//滚动数组切换
    }
    ll ans = -INF;
    for (int i = 1; i <= n; ++i) ans = max(ans, dp[1-c][i]);
    cout << ans << '\n';
    return 0;
}