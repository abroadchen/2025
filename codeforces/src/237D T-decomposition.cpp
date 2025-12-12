//
// Created by Psy.C on 2025/12/13.
//
/*
*a[N], b[N]数组存储树的边，第i条边连接节点a[i]和b[i]
e[N]是向量数组，e[i]存储与节点i关联的所有边的索引
循环读入n-1条边（因为树有n个节点和n-1条边）
对于每条边i连接节点a[i]和b[i]，将边的索引i添加到两个端点的邻接表中
 *
 *n-1行，每行格式为"2 a b"，表示选择边(a,b)
*外层循环：遍历每个节点i (1到n)
内层循环：遍历节点i关联的边对
输出相邻边对的索引
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200007
using namespace std;


int main() {
    fast;
    int n; cin>>n;
    int a[N], b[N]; vector<int> e[N];
    for (int i = 1; i < n; ++i) {
        cin>>a[i]>>b[i];
        e[a[i]].push_back(i); e[b[i]].push_back(i);
    }
    cout << n - 1 << '\n';
    for (int i = 1; i < n; ++i) cout << "2 " << a[i] << ' ' << b[i] << '\n';
    for (int i = 1; i <= n; ++i) for (int j = 0; j < e[i].size()-1; ++j) {
        cout << e[i][j] << ' ' << e[i][j+1] << '\n';
    }
    return 0;
}