//
// Created by Psy.C on 2026/3/11.
//
/**
N: 字典树最大节点数 M: 最大字符串长度
v[M]: 输入字符串
ans[M]: 存储结果字符串
dp[M][M]: 回文子串预计算表
k: 目标序号
nxt[N][2]: 字典树转移数组（只支持'a','b'）
mark[N]: 节点标记（存储以此节点结尾的回文子串数量）
L: 当前节点编号
rt: 根节点
build(): 创建新节点并初始化
get(): 初始化字典树
将从位置l开始的所有回文子串插入字典树
逐字符构建路径，如果dp[l][i]为真（表示是回文），则在路径节点标记
在字典树中查找第K小的回文子串
按字典序遍历，当当前节点的标记数大于k时，说明目标在此节点
否则继续向下搜索

预处理长度≤4的回文子串
单个字符必为回文
长度2-4的回文直接比较首尾字符
通过已知的中间回文和两端字符相等判断更大回文
v[j] == v[j+i]: 首尾字符相等
dp[j+2][j+i-2]: 中间部分是回文
初始化字典树
将以每个位置开头的所有回文子串插入字典树
在字典树中查找第K小的回文子串
输出结果

预计算回文: O(n²)
构建字典树: O(n³)（最坏情况）
查找第K小: O(结果长度)
总体: O(n³)

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e7+5, M = 5e3+5;

char v[M], ans[M];
int dp[M][M], k;
struct Trie {
    int nxt[N][2], mark[N], L, rt;
    int build() {
        memset(nxt[L], -1, sizeof nxt[L]);
        mark[L++] = 0;
        return L - 1;
    }
    void get() { L = 0; rt = build(); }
    void init(int l, int r) {
        int p = rt;
        for (int i = l; i <= r; ++i) {
            int t = v[i] - 'a';
            if (nxt[p][t] == -1) nxt[p][t] = build();
            p = nxt[p][t];
            if (dp[l][i]) mark[p]++;
        }
    }
    void dfs(int x, int y) {
        if (k - mark[x] > 0) {
            k -= mark[x];
            for (int i = 0; i < 2; ++i) {
                ans[y] = i + 'a';
                if (nxt[x][i] != -1) dfs(nxt[x][i], y + 1);
                if (k <= 0) return;
            }
        } else {
            k -= mark[x];
            ans[y] = '\0';
        }
    }
} tr;

int main() {
    fast;
    cin >> v;
    cin >> k; int len = strlen(v);
    for (int i = 0; i < len; ++i)
        for (int j = 0; j < len; ++j) dp[i][j] = 0;
    for (int i = 0; i < len; ++i) {
        dp[i][i] = 1;
        if (v[i] == v[i+1]) dp[i][i+1] = 1;
        if (v[i] == v[i+2]) dp[i][i+2] = 1;
        if (v[i] == v[i+3]) dp[i][i+3] = 1;
    }
    for (int i = 4; i < len; ++i)
        for (int j = 0; i + j < len; ++j)
            if (v[j] == v[j+i] && dp[j+2][j+i-2])
                dp[j][j+i] = 1;
    tr.get();
    for (int i = 0; i < len; ++i) tr.init(i, len-1);
    tr.dfs(0, 0);
    cout << ans << '\n';
    return 0;
}