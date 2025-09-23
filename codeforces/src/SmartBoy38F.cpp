//
// Created by Psy.C on 2025/9/23.
//
/*
*cnt: 计数器，用于分配唯一ID
val[N]: 存储每个字符串的价值
flag[N]: 标记数组，用于记忆化搜索
 *
*获取字符串s的唯一ID：
如果字符串不存在于映射中，则创建新ID
计算字符串价值：所有字符值之和乘以最大字符值
字符值为'a'-'z'对应1-26
将字符串存入vs向量
返回字符串的ID
 *
*DFS函数返回三元组{当前值, 最优对手值, 胜负状态}：
如果节点没有后继，返回{当前价值, 0, 0}
如果已计算过该节点，直接返回缓存结果
标记该节点已访问
 *
*计算胜负状态ret3：
遍历所有后继节点
如果存在一个后继节点使对手必败(o==0)，则当前节点必胜(ret3=1)
 *
*计算最优得分：
忽略与当前胜负状态相同的后继节点
选择使自己得分最大化的移动
返回{当前总分, 对手最优分, 胜负状态}
 *
 *
 *
 *
 */
#include <cstdio>
#include <iosfwd>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <tuple>
#include <algorithm>
using namespace std;

const int N = 2e5 + 10;

map<string, int> mp;//字符串到整数的映射，用于字符串ID映射
int cnt(0), val[N], flag[N];
vector<string> vs;//存储所有字符串的向量
set<int> v[N];//每个节点的后继节点集合，构建有向图
tuple<int, int, int> dp[N];

int getid(const string& s) {
    if (!mp.count(s)) {
        mp[s] = cnt;
        int sum(0), maxv(0);
        for (auto& c : s) {
            int x = c - 'a' + 1;
            sum += x;
            maxv = max(maxv, x);
        }
        val[cnt] += sum * maxv;
        vs.push_back(s);
        cnt++;
    }
    return mp[s];
}

tuple<int, int, int> dfs(int x) {
    if (v[x].empty()) return {val[x], 0, 0 };
    if (flag[x]) return dp[x];
    flag[x] = 1;
    int ret1(0), ret2(0), ret3(0);
    for (auto& y : v[x]) {
        auto [sum1, sum2, o] = dfs(y);
        if (o == 0) {
            ret3 = 1;
            break;
        }
    }
    for (auto& y : v[x]) {
        auto [sum1, sum2, o] = dfs(y);
        if (o == ret3) continue;
        if (ret1 < sum1) ret1 = sum1, ret2 = sum2;
        if (ret1 == sum1) ret2 = min(ret2, sum2);
    }
    return dp[x] = { ret2 + val[x], ret1, ret3 };
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n; getid("");

    while (n--) {
        vector<int> key;
        string str; cin >> str;

        for (int i = 0; i < str.length(); ++i) {
            for (int j = 1; i + j <= str.length(); ++j)
                key.push_back(getid(str.substr(i, j)));//生成所有子串并记录ID到key向量
            //将所有单字符子串添加到初始节点(0)的后继集合
            v[0].insert(getid(str.substr(i, 1)));
        }
        //对于长度>=2的子串，建立从前缀和后缀到该子串的转移边
        for (int i = 0; i < str.length(); ++i) {
            for (int j = 2; i + j <= str.length(); ++j) {
                int z = getid(str.substr(i, j));
                int x = getid(str.substr(i, j - 1));
                int y = getid(str.substr(i + 1, j - 1));
                v[x].insert(z);
                v[y].insert(z);
            }
        }
        sort(key.begin(), key.end());
        key.resize(unique(key.begin(), key.end()) - key.begin());
        for (auto& x : key) val[x]++;//去重并增加所有出现过的子串的价值计数
    }
    auto [sum1, sum2, o] = dfs(0);
    if (o == 1) puts("First");
    else puts("Second");
    printf("%d %d\n", sum2, sum1);
    return 0;
}