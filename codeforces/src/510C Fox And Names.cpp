//
// Created by Psy.C on 2026/2/27.
//
/**
vis[N]: 访问标记数组，记录DFS过程中节点是否被访问过
pre[N]: 递归栈标记，记录节点是否在当前DFS路径上
ans = 1: 结果标志，默认为1（可能）
lst[N]: 记录拓扑排序的结果
cnt: 记录已加入结果列表的节点数量
g[M]: 邻接表，存储图的边关系（字母间的大小关系）

检测环并进行拓扑排序
vis[x] = 1: 标记节点x已被访问
pre[x] = 1: 标记节点x在当前递归栈中
遍历节点x的所有邻接节点i
如果节点i未被访问过，递归调用dfs(i)
如果节点i已被访问过且仍在当前递归栈中，说明发现了环，设置ans=0
pre[x] = 0: 从递归栈中移除节点x
lst[cnt++] = x: 将节点x加入结果列表，cnt自增

遍历相邻的字符串对
m1 = s[i-1], m2 = s[i]: 获取相邻两个字符串
找到第一个不同的字符位置j，通过while循环跳过相同的前缀
如果两个字符串在位置j都有字符（即找到了不同字符），建立边关系
m1[j]-'a'指向m2[j]-'a'，表示第一个字符串的字符应该小于第二个
如果第一个字符串比第二个长，且前面字符都相同，则违反字典序规则，设置ans=0

如果ans为1（没有发现环），输出拓扑排序结果
由于DFS后序遍历的特性，结果列表是逆序的，所以从后往前输出
如果ans为0（存在环），输出"Impossible"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101, M = 30;

int vis[N], pre[N], ans = 1, lst[N], cnt;
vector<int> g[M];
void dfs(const int x) {
    vis[x] = 1; pre[x] = 1;
    for (const int i : g[x]) {
        if (!vis[i]) dfs(i);
        else if (pre[i]) ans = 0;
    }
    pre[x] = 0;
    lst[cnt++] = x;
}

int n;
string s[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 1; i < n; ++i) {
        string m1 = s[i-1], m2 = s[i];
        int j;
        for (j = 0; j < m1.size() && j < m2.size() && m1[j] == m2[j]; ++j){}
        if (j < m1.size() && j < m2.size())
            g[m1[j]-'a'].push_back(m2[j]-'a');
        else if (m1.size() > m2.size()) ans = 0;
    }
    for (int i = 0; i < 26; ++i)
        if (!vis[i]) dfs(i);
    if (ans) {
        for (int i = cnt-1; i >= 0; --i)
            printf("%c", lst[i] + 'a');
    } else cout << "Impossible\n";
    return 0;
}