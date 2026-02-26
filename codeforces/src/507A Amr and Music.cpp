//
// Created by Psy.C on 2026/2/26.
//
/**
t：元素值
c = {t, i}：将值和原始索引组成pair
d.push_back(c)：添加到vector中
累加元素值到sum
如果超过k则停止
否则增加计数器cnt 输出能选的元素个数
输出选中的元素的原始索引
 */
#include <ranges>
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

int n, k;
ii c;
vector<ii> d;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1, t; i <= n; ++i) {
        cin >> t;
        c = {t, i};
        d.push_back(c);
    }
    ranges::sort(d);
    int cnt = 0, sum = 0;
    for (const auto key: d | views::keys) {
        sum += key;
        if (sum > k) break;
        cnt++;
    }
    cout << cnt << '\n';
    for (int i = 0; i < cnt; ++i)
        cout << d[i].second << ' ';
    return 0;
}