//
// Created by Psy.C on 2026/4/17.
//
/**
ans[p]: 父节点的期望值
1: 从父节点到当前节点的距离
(num[p] - num[v] - 1)/2.: 除v的子树外其他兄弟子树节点的贡献平均值
时间复杂度：O(n)，空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

vector<int> ve[N];///存储节点i的所有子节点
int num[N];///以节点i为根的子树中节点的数量（不包括节点i本身）
void dfs(int p) {
    int len = ve[p].size();
    num[p] = len;//初始化为直接子节点数
    for (int i = 0; i < len; ++i) {
        int v = ve[p][i];
        dfs(v);
        num[p] += num[v];//累加子树节点数
    }
}

double ans[N];
void dfs2(int p) {
    int len = ve[p].size();
    for (int i = 0; i < len; ++i) {
        int v = ve[p][i];
        ans[v] = ans[p] + 1 + (num[p] - num[v] - 1)/2.;
        dfs2(v);
    }
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 2, val; i <= n; ++i) {
        cin >> val;//读取第i个节点的父节点
        ve[val].push_back(i);//在邻接表中添加父子关系
    }
    dfs(1);//计算子树大小
    ans[1] = 1;//设置根节点期望值为1
    dfs2(1);//计算所有节点期望值
    for (int i = 1; i <= n; ++i) {
        if (i != 1) printf(" ");//除了第一个元素，前面都加空格
        printf("%.8f", ans[i]);
    }
    return 0;
}