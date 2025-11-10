//
// Created by Psy.C on 2025/11/10.
//
/*
*n：当前构造的数字
fr：已经使用的'4'的个数
sv：已经使用的'7'的个数
 *剪枝条件：如果数字超过10^10，停止递归
 *如果'4'和'7'的个数相等，将数字加入向量v
*递归生成两种可能：
在末尾添加'7'，'7'的计数加1
在末尾添加'4'，'4'的计数加1
 *
 *从'4'和'7'开始两次DFS，生成所有符合条件的数字
 *使用二分查找找到第一个≥n的数字并输出
 *
 */
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
vector<ll> v;

void dfs(ll n, int fr, int sv) {
    if (n > 1e10) return;
    if (fr == sv) v.push_back(n);
    dfs(n*10+7, fr, sv + 1);
    dfs(n*10+4, fr+1, sv);
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    dfs(4, 1, 0); dfs(7, 0, 1);
    ll n; cin >> n;
    sort(v.begin(), v.end());
    cout << v[lower_bound(v.begin(), v.end(), n)-v.begin()];
    return 0;
}