//
// Created by Psy.C on 2025/11/16.
//
/*
*n: 字符串长度
k: 需要改变的字符数量
i: 循环变量
inf: 无穷大值(10^9)
s: 输入字符串
t: 临时字符串
a: 最优结果字符串
 *
*定义节点结构体，用于排序：
c: 改变该位置数字的代价(与目标数字的差值绝对值)
v: 原始数字值
p: 位置索引
重载<运算符定义排序规则：
首先按代价升序排列
代价相同时按原始值降序排列
原始值也相同时根据条件按位置排序
 *
 *创建大小为n的节点向量，循环尝试将所有数字改为0-9
*计算每个位置改为数字i的代价：
abs(s[j] - '0' - i): 位置j处字符改为数字i的代价
s[j] - '0': 原始数字值
j: 位置索引
*按照排序后的顺序选择代价最小的k个位置进行改变
累加总代价sum
在临时字符串t中实际进行字符替换
 *如果当前方案更优(代价更小，或代价相同但字典序更小)，则更新最优解
 *输出最小代价和最优字符串
 *
 *O(10 × n × log n) = O(n log n)
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n, k, i, inf=1e9;
string s, t, a;
struct node {
    int c, v, p;
    bool operator<(const node& x) const {
        if (c != x.c) return c < x.c;
        if (v != x.v) return v > x.v;
        return v >= i ? p < x.p : p > x.p;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> s;
    vector<node> q(n);
    for (i = 0; i <= 9; ++i) {
        int sum(0);
        for (int j = 0; j < n; ++j) q[j] = {
            abs(s[j] - '0' - i), s[j] - '0', j
        };
        sort(q.begin(), q.end());
        t = s;
        for (int j = 0; j < k; ++j) sum += q[j].c,
            t[q[j].p] = i + '0';
        if (sum < inf || sum == inf && t < a)
            inf = sum, a = t;
    }
    cout << inf << '\n' << a;
    return 0;
}