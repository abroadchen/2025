//
// Created by Psy.C on 2026/4/25.
//
/**
n, m: 元素总数和查询次数
a[N]: 存储输入数组
f[i][j]: DP状态，表示从位置i开始，最多保留j个元素时的最小花费
x: 查询值
f[i+1][j]: 不选择位置i的元素，直接跳到下一个位置，保留j个元素
max(0ll, f[i+1][j-1]-a[i]): 选择位置i的元素，花费为 max(0, 前一状态花费 - a[i])

时间复杂度
预处理: O(n²)，DP填表
查询: O(m log n)，每次查询使用二分查找
总体: O(n² + m log n)
空间复杂度
O(n²)，主要是DP数组的空间

总成本变化为 -a[i]：
正数元素：-a[i] < 0（成本减少）
负数元素：-a[i] > 0（成本增加）
f[1][0] ≤ f[1][1] ≤ f[1][2] ≤ ... ≤ f[1][n] （单调递增）
我们要在其中找到最大的 j，使得 f[1][j] ≤ x
使用 upper_bound 找到第一个大于 x 的位置，然后 -1 得到最大的满足条件的位置

处理位置 i 时，位置 i+1 到 n 的所有状态都已经计算完成
*/
// #include <bits/stdc++.h>
// #define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
// #define ll long long
// using namespace std;
// constexpr int N = 777;
// int n, m, a[N];
// ll f[N][N], x;
// int main() {
//     fast;
//     cin >> n >> m;
//     memset(f, 0x3f, sizeof f);
//     for (int i = 1; i < n+1; ++i) cin >> a[i];
//     for (int i = 1; i < n+1; ++i) f[i][0] = 0;//保留0个元素花费为0
//     f[n][1] = max(0, -a[n]);//在最后位置保留1个元素的花费
//     for (int i = n-1; i; --i) {
//         for (int j = 1; j < n-i+2; ++j)
//             f[i][j] = min(f[i+1][j], max(0ll, f[i+1][j-1]-a[i]));
//     }
//     while (m--) {
//         cin >> x;
//         int p = upper_bound(f[1], f[1]+n+1, x) - f[1] - 1;//最大保留数量
//         cout << n-p << '\n';//需要删除的元素个数
//     }
//     return 0;
// }


/**
n, m: 物品数量和查询次数
a[N]: 原数组（修改后存储处理结果）
b[N]: 存储负数（可购买物品）的前缀和
tot: 负数物品数量
q: 最大堆，存储负数（负收益物品）
遇到负数（有利可图）：直接存储到堆中
遇到正数（需要成本）：尝试用堆中最大的负数（最有利的）来抵消
这样可以最大化负数的价值利用
将堆中剩余的负数取出，转换为正数（成本）
按从小到大排序（因为最大堆弹出是递减的）
计算购买前i个最便宜物品的累计成本

时间复杂度
预处理: O(n log n)
查询: O(m log n)
总体: O(n log n + m log n)
空间复杂度
O(n)，主要是数组和优先队列的空间
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e6+7;
int n, m, a[N], b[N], tot;
priority_queue<int> q;
signed main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = n; i >= 1; --i) {
        if (a[i] < 0) q.push(a[i]);//负数直接入队
        else {//正数尝试合并负数
            while (!q.empty() && a[i] >= 0) {
                a[i] += q.top(); q.pop();//用正数"抵消"负数
            }
            if (a[i] < 0) q.push(a[i]);//如果抵消后仍是负数，重新入队
        }
    }
    while (!q.empty()) { b[++tot] = -q.top(); q.pop(); }//取相反数（变为正数成本）
    for (int i = 1; i <= tot; ++i) b[i] += b[i-1];
    for (int i = 1, x; i <= m; ++i) {
        cin >> x;
        if (x >= b[tot]) {//预算充足，可购买所有物品
            cout << "0\n";
            continue;
        }
        int t = upper_bound(b + 1, b + tot, x) - b - 1;//最大可购买数量
        cout << tot - t << '\n';//无法购买的数量
    }
    return 0;
}