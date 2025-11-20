//
// Created by Psy.C on 2025/11/20.
//
/*
*演讲者在高度为h的地方演讲时，会有h-1个观众（因为演讲者自己不算）
演讲者的恐惧值限制了他能面对的最⼤观众数
所以需要：h - 1 ≤ fear_value，即 h ≤ fear_value + 1
 *
*检查冲突：查看之前安排的所有演讲者中，是否有与当前演讲者在同一高度或更高高度的
解决冲突：如果有冲突（h[j] >= h[i]），就把之前的演讲者高度提升（++h[j]）
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin >> n;
    vector<pair<int, string>> a(n);//恐惧值和姓名
    for (int i = 0; i < n; ++i) cin >> a[i].second >> a[i].first;
    sort(a.begin(), a.end());//按恐惧值升序排序

    bool f(true);
    vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        h[i] = i - a[i].first;
        if (h[i] < 0) { f = false; break; }
        ++h[i];//避免高度为0的情况，确保每个演讲者都有一个有效的演讲高度
        for (int j = 0; j < i; ++j) if (h[j] >= h[i]) ++h[j];//调整前面演讲者的高度：如果前面演讲者的高度≥当前高度，则将其加1
    }
    if (f) for (int i = 0; i < n; ++i) cout << a[i].second << " " << h[i] << '\n';
    else puts("-1");
    return 0;
}