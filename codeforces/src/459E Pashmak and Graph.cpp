//
// Created by Psy.C on 2026/2/11.
//
/**
n, m：节点数和边数
dp[i]：到达节点i的最长路径长度
f[i]：临时数组，用于计算
mx：最终答案（最长路径长度）

本次循环：处理完权重为 w 的边 [i, j)
设置 i = j-1：让 i 指向最后一个处理过的边
主循环 i++：下一轮循环开始前，i 自增 1
下轮循环：i = j，正好指向第一个未处理的边
// 等价写法1
int i = 0;
while (i < m) {
    // ...
    i = j;  // 直接跳到j位置
}

// 等价写法2
for (int i = 0; i < m; ) {  // 注意没有i++
    // ...
    i = j;  // 直接跳到j位置
}

时间复杂度
排序：O(m log m)
处理边：O(m)
总体：O(m log m)
空间复杂度
O(n + m)：存储图和DP数组
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 300002
using namespace std;

struct node {
    ll u, v, w;//边的起点和终点 边的权重
    bool operator<(const node o) const {
        return w < o.w;
    }
} e[N];

int n, m, dp[N], f[N], mx;

int main() {
    fast;
    cin >> n >> m;
    memset(dp, 0, sizeof(dp));
    memset(f, 0, sizeof(f));
    for (int i = 0; i < m; ++i) cin >> e[i].u >> e[i].v >> e[i].w;
    sort(e, e + m); mx = 0;
    for (int i = 0; i < m; ++i) {
        int j;
        //找到与当前边权重相同的连续边段 [i, j)
        for (j = i; j < m; ++j) if (e[i].w != e[j].w) break;
        for (int k = i; k < j; ++k)
            //从起点u到终点v的路径长度（+1表示经过这条边）
            f[e[k].v] = max(dp[e[k].u]+1, f[e[k].v]);//之前计算的值
        for (int k = i; k < j; ++k)//将f数组的计算结果更新到dp数组
            dp[e[k].v] = max(f[e[k].v], dp[e[k].v]);
        i = j-1;//跳过已处理的边
    }
    for (int i = 1; i <= n; ++i) mx = max(dp[i], mx);
    cout << mx << '\n';
    return 0;
}