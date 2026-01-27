//
// Created by Psy.C on 2026/1/27.
//
/**
* t1 = atan((r - x[i])/y[i]): 计算到达右边界的角度
t2 = atan((x0 - x[i])/y[i]) + a[i]: 计算从x0出发经第i个点反射后的角度（加上偏转角a[i]）
 *
*外层循环：遍历所有可能的访问状态i
内层循环：尝试添加每个未访问的点j
if ((i&(1<<j)) == 0): 检查点j是否未被访问
i^(1<<j): 将点j加入访问集合
get(dp[i], j): 从当前状态dp[i]经过点j后的结果
max(...): 更新最优值
 *
*时间复杂度
O(n × 2^n)，其中n ≤ 20
适合小规模的组合优化问题
空间复杂度
O(2^n)，用于存储状态压缩DP数组
 *
 */
#include <iomanip>
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db double
#define pi acos(-1.)
using namespace std;

db l, r, x[20], y[20], a[20];
db get(const db x0, const int i) {//从位置x0到达第i个点后的新位置
    const db t1 = atan((r - x[i])/y[i]), t2 = atan((x0 - x[i])/y[i]) + a[i];
    return x[i] + tan(min(t1, t2)) * y[i];
}


int main() {
    fast;
    int n; cin >> n >> l >> r; r -= l;//将右边界相对于左边界偏移
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i] >> a[i];//坐标(x[i], y[i])和角度a[i]
        x[i] -= l;
        a[i] = a[i] / 180. * pi;//将角度从度转换为弧度
    }
    const int N = 1<<n;//所有可能的状态（访问子集）
    db dp[(1<<20)-1]={};//访问mask表示的点集后能达到的最远x坐标
    for (int i = 0; i < N; ++i) for (int j = 0; j < n; ++j) if ((i&(1<<j)) == 0) {
        dp[i^(1<<j)] = max(dp[i^(1<<j)], get(dp[i], j));
    }
    cout << fixed << setprecision(10) << dp[N-1] << '\n';//输出访问所有点后的最优结果
    return 0;
}