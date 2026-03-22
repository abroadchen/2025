//
// Created by Psy.C on 2026/3/22.
//
/**
g[N]: 辅助数组g
p[N][N]: 概率矩阵
f[N]: 主要计算结果数组
h[N]: 辅助数组h
n: 矩阵大小
flag[N]: 标记数组，记录节点是否已处理
读入n×n的概率矩阵，将百分比转换为小数
初始化所有数组元素为1
特殊处理：设置第n个节点为已访问状态，f[n]=0
对所有未访问的节点，以n为源节点执行一次get操作
类似Dijkstra算法的过程
每次选择f值最小的未访问节点
将该节点标记为已访问
用该节点更新所有其他未访问节点
最终得到从节点1到节点n的期望值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5;

double g[N], p[N][N], f[N], h[N];
void get(int j, int i) {
    g[i] += p[i][j] * f[j] * h[i];
    h[i] *= 1 - p[i][j];
    f[i] = g[i]/(1 - h[i]);
}

int n;
bool flag[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1, x; j <= n; ++j) {
            cin >> x; p[i][j] = x/100.;
        }
    for (int i = 1; i <= n; ++i) f[i] = g[i] = h[i] = 1;
    flag[n] = true, f[n] = 0;
    for (int i = 1; i <= n; ++i)
        if (!flag[i]) get(n, i);
    for (int j = 2; j <= n; ++j) {
        int now = 0; double val = 1e18;
        for (int i = 1; i <= n; ++i)
            if (!flag[i] && f[i] < val)
                now = i, val = f[i];
        flag[now] = true;
        for (int i = 1; i <= n; ++i)
            if (!flag[i]) get(now, i);
    }
    printf("%.6lf\n", f[1]);
    return 0;
}