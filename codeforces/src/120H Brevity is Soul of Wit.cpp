//
// Created by Psy.C on 2025/11/16.
//
/*
*N = 100000：最大字符串数量
n：字符串数量
l：字符串长度
s：临时字符串变量
d[N]：每个字符串匹配的子序列
v[N]：每个字符串的所有可能子序列（长度≤4）
mp：映射子序列到字符串索引的匹配关系
mark[N]：标记数组，用于DFS中避免重复访问
 *
*匈牙利算法的DFS实现：
x：当前要匹配的字符串索引
mark[x] = true：标记当前节点已访问
遍历字符串x的所有子序列s：
如果子序列s未被匹配（mp[s] == -1）或者
如果匹配s的字符串可以重新匹配且能找到增广路（dfs(mp[s])）
则将子序列s匹配给字符串x
返回是否成功匹配
 *
*对每个字符串：
读取字符串s，获取长度l
枚举所有非空子集掩码mask（1到2^l-1）
__builtin_popcount(mask)：计算mask中1的个数
如果子序列长度≤4：
构造子序列：按位掩码选择字符
将子序列加入字符串i的候选列表
初始化该子序列的匹配为-1（未匹配）
 *
*对每个字符串执行匹配：
清空标记数组
调用DFS尝试为字符串i找到匹配
*检查是否所有字符串都成功匹配
输出每个字符串匹配的子序列
 *
*枚举子序列：O(n × 2^l × l)，其中l是字符串平均长度
匈牙利算法：O(V×E)，V是节点数，E是边数
 */
#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

const int N = 1e5;
int n, l;
string s, d[N];
vector<string> v[N];
map<string, int> mp;
bool mark[N];

bool dfs(int x) {
    mark[x] = true;
    for (string s : v[x]) {
        if (mp[s] == -1 || mark[mp[s]] == false && dfs(mp[s])) {
            mp[s] = x; d[x] = s;
            return true;
        }
    }
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    rep(i,n) {
        cin >> s; l = s.length();
        for (int mask = 1; mask < (1<<l); ++mask) {
            if (__builtin_popcount(mask) <= 4) {
                string t;
                rep(j,l) if (mask & (1<<j)) t.push_back(s[j]);
                v[i].push_back(t);
                mp[t] = -1;
            }
        }
    }
    rep(i,n) memset(mark, false, sizeof(mark)), dfs(i);
    rep(i,n) if (d[i] == "") { cout << -1; return 0; }
    rep(i,n) cout << d[i] << '\n';
    return 0;
}