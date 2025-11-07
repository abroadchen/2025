//
// Created by Psy.C on 2025/11/7.
//
/*
*n 存储元素个数
costs 存储成本值的向量
memo 记忆化搜索的缓存，键是状态(i,pre)，值是{最小成本, 选择的元素列表}
nxt 存储状态转移，键是当前状态，值是下一个状态
 *
 *定义递归函数dp，参数i表示当前位置，pre表示之前保留的位置
 *如果i等于n（超出范围），说明只剩一个元素pre，成本就是costs[pre]，将其存储到memo中并返回成本
 *如果i等于n-1，说明剩下两个元素pre和i，成本是两者最大值，将结果存储到memo并返回
 *如果当前状态(i,pre)还未计算过，则进行计算
*l1: 选择i和i+1，保留pre到下一步
l2: 选择pre和i+1，保留i到下一步
l3: 选择pre和i，保留i+1到下一步
 *
 *
 *循环输出每一步的选择：查找当前状态的解，如果有则输出选择的元素（加1是为了符合题目要求的1基索引）
 *查找下一个状态，如果没有则结束循环，否则转移到下一个状态
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef pair<int,int> pii;
int n;
vector<int> costs;
map<pii, pair<int, vector<int>>> memo;
map<pii, pii> nxt;

int dp(int i, int pre) {
    if (i == n) {
        memo[{i, pre}] = {costs[pre], {pre}};
        return memo[{i, pre}].first;
    }
    if (i == n - 1) {
        memo[{i, pre}] = {max(costs[pre], costs[i]), {pre, i}};
        return memo[{i, pre}].first;
    }
    if (memo.find({i, pre}) == memo.end()) {
        int l1 = max(costs[i], costs[i+1]) + dp(i+2, pre),
        l2 = max(costs[pre], costs[i+1]) + dp(i+2, i),
        l3 = max(costs[pre], costs[i]) + dp(i+2, i+1),
        m = min({l1, l2, l3});
        vector<int> cur;
        if (m == l3) {
            cur = {pre, i};
            nxt[{i, pre}] = {i + 2, i + 1};
        } else if (m == l2) {
            cur = {pre, i + 1};
            nxt[{i, pre}] = {i + 2, i};
        } else {
            cur = {i, i + 1};
            nxt[{i, pre}] = {i + 2, pre};
        }
        memo[{i, pre}] = {m, cur};
    }
    return memo[{i, pre}].first;
}



int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n; costs.resize(n);
    for (int i = 0; i < n; ++i) cin >> costs[i];
    cout << dp(1, 0) << endl;
    pii s = {1, 0};
    while (true) {
        auto it = memo.find(s);
        if (it != memo.end()) {
            for (int j = 0; j < it->second.second.size(); ++j) {
                if (j > 0) cout << " ";
                cout << it->second.second[j] + 1;
            }
            cout << endl;
        }
        auto it2 = nxt.find(s);
        if (it2 == nxt.end()) break;
        s = it2->second;
    }
    return 0;
}