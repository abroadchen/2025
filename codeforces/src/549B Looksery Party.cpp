//
// Created by Psy.C on 2026/3/9.
//
/**
n：矩阵大小
a[N]：存储每个节点的度数或计数
i：循环变量
s[N][N]：存储邻接矩阵（字符形式）
ans：存储结果序列

读入n行字符串到s[i][1]开始的位置（使用1基索引）
这形成了一个邻接矩阵，'1'表示有边，'0'表示无边

寻找第一个a[i] == 0的节点
如果找到返回节点编号，否则返回0

循环直到找不到a[i] == 0的节点
pos = f()：找到当前度数为0的节点
ans.push_back(pos)：将该节点加入结果序列
遍历所有节点i：
如果s[pos][i] == '1'（pos到i有边）：
--a[i]：减少节点i的度数（或计数）


 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 101;
int n, a[N], i;
char s[N][N];
vector<int> ans;
int main() {
    for (scanf("%d", &n), i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
    auto f = [&]() {
        for (i = 1; i <= n; ++i)
            if (a[i] == 0)
                return i;
        return 0;
    };
    int pos;
    while ((pos = f())) {
        for (ans.push_back(pos), i = 1; i <= n; ++i)
            if (s[pos][i] == '1')
                --a[i];
    }
    printf("%d\n", ans.size());
    for (auto x : ans) printf("%d ", x);
    return 0;
}