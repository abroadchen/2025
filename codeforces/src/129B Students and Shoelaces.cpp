//
// Created by Psy.C on 2025/11/18.
//
/*
*n: 节点数
m: 边数
a, b: 临时变量，用于读取边的两个端点
f(1): 标志变量，初始化为1
d(0): 计数器，记录删除轮数，初始化为0
mp: 映射容器，记录每个节点的度数
v: 向量，存储所有的边
 *
*循环m次读取每条边：
读取边的两个端点a和b
在映射mp中增加节点a和b的度数计数
将边{a,b}添加到向量v中
*创建向量res存储所有度数为1的节点（叶子节点）
遍历1到n的所有节点，如果度数为1则加入res
 *如果没有度数为1的节点，设置标志f为0并跳出循环
 *删除轮数计数器d加1
 *
*遍历所有度数为1的节点：
将该节点度数设为0（标记为已删除）
遍历所有边，如果边的一个端点是当前删除的节点：
则将另一个端点的度数减1
 */
#include <vector>
#include <iostream>
#include <map>
using namespace std;

typedef long long ll;
ll n, m, a, b, f(1), d(0);
map<ll, ll> mp;
vector<pair<ll, ll>> v;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> a >> b;
        mp[a]++; mp[b]++;
        v.push_back({a, b});
    }
    while (f != 0) {
        vector<ll> res;
        for (int i = 1; i <= n; ++i) if (mp[i] == 1) res.push_back(i);
        if (res.empty()) { f = 0; break; }
        d++;
        for (int i = 0; i < res.size(); ++i) {
            mp[res[i]] = 0;
            for (int j = 0; j < v.size(); ++j) {
                if (v[j].first == res[i]) mp[v[j].second]--;
                else if (v[j].second == res[i]) mp[v[j].first]--;
            }
        }
    }
    cout << d;
    return 0;
}