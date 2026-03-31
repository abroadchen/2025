//
// Created by Psy.C on 2026/3/31.
//
/**
vis[N]：访问状态数组，三种状态：0=未访问，1=起点，2=正在访问，3=被其他节点连接
v[27]：邻接表，存储图的边关系
ans：存储拓扑排序的结果

拓扑排序
vis[x] = 2：标记当前节点正在访问
遍历当前节点的所有邻居
如果邻居正在被访问（vis[i] == 2），跳过（避免循环）
递归访问邻居节点
将当前字符添加到结果字符串末尾（后序处理）

对于每个字符串：
创建字符间的边关系：s[j] -> s[j+1]
将后一个字符标记为被连接（vis = 3）
如果首字符没有被其他字符连接，则标记为起点（vis = 1）

遍历所有可能的字符，对每个起点（vis[i] == 1）执行DFS
ranges::reverse(ans)：反转结果字符串（因为DFS是后序添加）
输出最终的拓扑排序结果
O(V + E)，其中V是不同字符的数量，E是相邻字符对的数量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;

int vis[N];
vector<int> v[27];
string ans;
void dfs(int x) {
    vis[x] = 2;
    for (int i : v[x]) {
        if (vis[i] == 2) continue;
        dfs(i);
    }
    ans += (char)('a'+x);
}

int n;
string s;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        for (int j = 0; j < s.size()-1; ++j) {
            v[s[j]-'a'].push_back(s[j+1]-'a');
            vis[s[j+1]-'a'] = 3;
        }
        if (vis[s[0]-'a'] != 3)  vis[s[0]-'a'] = 1;
    }
    for (int i = 0; i < 26; ++i)
        if (vis[i] == 1) dfs(i);
    ranges::reverse(ans);
    cout << ans << '\n';
    return 0;
}