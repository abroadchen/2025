//
// Created by Psy.C on 2026/4/10.
//
/**
n: 已存在的元素数量
m: 目标和的约束条件
mp: 映射表，用来统计已存在数字的出现次数
v: 存储不存在于输入中的数字的向量

对于每个在输入中不存在的数字i (mp[i] == 0)
检查从剩余预算m中减去i后是否仍为非负数
如果是，将i添加到结果向量并将m减少i
如果不是，跳出循环（预算不足）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int inf = 1e9;
int n, m;
map<int, int> mp;
vector<int> v;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        mp[x]++;
    }
    for (int i = 1; i <= inf; ++i)
        if (mp[i] == 0) {
            if (m - i >= 0) {
                m -= i;
                v.push_back(i);
            } else break;
        }
    cout << v.size() << '\n';
    auto it = v.begin();
    while (it != v.end()) {
        cout << *it << ' ';
        ++it;
    }
    return 0;
}