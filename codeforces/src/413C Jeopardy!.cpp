//
// Created by Psy.C on 2026/2/2.
//
/**
 * n（数组长度），m（操作次数）
 *v 存储被选中的元素
*读入索引 k（转换为0基索引）
将 p[k] 添加到向量 v
将 p[k] 设置为0（相当于移除）
 *
 *计算数组 p 中所有剩余元素的总和
 *
*如果当前元素小于 cnt
翻倍操作：cnt *= 2
加法操作：否则 cnt += i
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];
    vector<int> v;
    for (int i = 0, k; i < m; ++i) {
        cin >> k; k--;
        v.push_back(p[k]);
        p[k] = 0;
    }
    ll cnt = 0;
    for (int i = 0; i < n; ++i) cnt += p[i];
    ranges::sort(v, greater<>());
    for (const int i : v) {
        if (i < cnt) cnt *= 2;
        else cnt += i;
    }
    cout << cnt << '\n';
    return 0;
}