//
// Created by Psy.C on 2026/3/12.
//
/**
N: 字典树节点数量上限
M: 字符串数量上限
tr[N][27]: 字典树转移数组（26个小写字母+1个标记）
cnt: 节点计数器
vis[N]: 记录到达每个节点的字符串编号
将字符串s插入字典树
val: 字符串的编号
在路径终点记录字符串编号
在字典树中查找字符串s的最长匹配前缀
将查询编号val标记在匹配的节点上

st[M]: 栈，存储可用的匹配对象
top: 栈顶指针
ans[M]: 最终匹配结果
h: 总深度（可能表示某种代价）
将当前节点的所有字符串编号压入栈
递归遍历所有子节点
深度增加1
传递当前栈顶位置

top - tp > 0: 栈中有可用匹配对象
ans[v] = st[top--]: 为查询v分配栈顶元素
h += dep: 累加深度（可能表示匹配代价）
如果无可用对象，将查询传递给父节点

前n个是查询字符串，后n个是候选字符串
将后n个字符串（候选）插入字典树
为前n个字符串（查询）在字典树中标记
从根节点开始DFS
输出总代价h
输出每个查询的匹配结果

构建字典树：O(∑|s_i|)，其中s_i是候选字符串
查找标记：O(∑|s_i|)，其中s_i是查询字符串
DFS处理：O(节点数)
总体：O(总字符串长度)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 8e5+5, M = 2e5+5;

int tr[N][27], cnt;
vector<int> vis[N];
void insert(const string& s, const int val) {
    int i = 0;
    for (const auto v : s) {
        const int k = v - 'a';
        if (!tr[i][k]) tr[i][k] = ++cnt;
        i = tr[i][k];
    }
    vis[i].push_back(val);
}

vector<int> tag[N];
void find(const string& s, const int val) {
    int i = 0;
    for (const auto v : s) {
        const int k = v - 'a';
        if (!tr[i][k]) break;
        i = tr[i][k];
    }
    tag[i].push_back(val);
}

int st[M], top, ans[M], h;
void dfs(const int i, const int fa, const int dep, const int tp) {
    for (const auto v : vis[i]) st[++top] = v;
    for (int j = 0; j < 26; ++j) {
        if (!tr[i][j]) continue;
        dfs(tr[i][j], i, dep + 1, top);
    }
    for (int j = tag[i].size()-1; j >= 0; --j) {
        int v = tag[i][j];
        if (top - tp > 0) {
            ans[v] = st[top--];
            h += dep;
        } else tag[fa].push_back(v);
        tag[i].pop_back();
    }
}

string s[M];
int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= 2*n; ++i) cin >> s[i];
    for (int i = n+1; i <= 2*n; ++i) insert(s[i], i - n);
    for (int i = 1; i <= n; ++i) find(s[i], i);
    dfs(0, 0, 0, 0);
    cout << h << '\n';
    for (int i = 1; i <= n; ++i)
        cout << i << ' ' << ans[i] << '\n';
    return 0;
}