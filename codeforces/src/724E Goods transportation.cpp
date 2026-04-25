//
// Created by Psy.C on 2026/4/24.
//
/**
n: 总共的物品/任务数量
now: 当前状态的滚动数组索引
c: 切换操作的单位成本
p[N]: 操作p的成本数组
s[N]: 操作s的成本数组
f[2][N]: DP状态数组，使用滚动数组优化空间
f[now][j] 表示处理完前i个任务，且第i个任务使用操作s后，总共进行了j次切换的最小成本

1. f[now][0] = f[now^1][0] + p[i];
第i个任务使用操作p，且当前没有切换（0次切换）
从前一个状态的0次切换转移而来
成本增加 p[i]
2. f[now][j] = min(f[now^1][j-1]+s[i], f[now^1][j]+p[i]+j*c);
第i个任务使用操作s，总共有j次切换
有两种可能的转移来源：
选项1: f[now^1][j-1]+s[i] - 从j-1次切换状态转移，这次是切换操作（从p转到s）
选项2: f[now^1][j]+p[i]+j*c - 从j次切换状态转移，这次是保持操作（使用p后继续使用p），但要加上当前已有的j次切换产生的持续成本
3. f[now][i] = f[now^1][i-1] + s[i];
第i个任务使用操作s，且前面已经进行了i-1次切换
这通常表示一种特殊情况或边界情况
在所有可能的切换次数中寻找最小成本
返回最优解

时间复杂度: O(n²)
空间复杂度: O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e4+7;

int n, now;
ll c, p[N], s[N], f[2][N];
int main() {
    fast;
    cin >> n >> c;
    for (int i = 1; i <= n; ++i) cin >> p[i];
    for (int i = 1; i <= n; ++i) cin >> s[i];
    for (int i = 1; i <= n; ++i) {
        now = now^1;//切换当前使用的数组行
        f[now][0] = f[now^1][0] + p[i];
        for (int j = 1; j <= i-1; ++j)
            f[now][j] = min(f[now^1][j-1]+s[i], f[now^1][j]+p[i]+j*c);
        f[now][i] = f[now^1][i-1] + s[i];
    }
    ll ans = f[now][0];
    for (int i = 1; i <= n; ++i) ans = min(ans, f[now][i]);
    cout << ans << '\n';
    return 0;
}