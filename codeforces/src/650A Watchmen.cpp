//
// Created by Psy.C on 2026/4/2.
//
/**
mp: 记录点出现次数的map
a[N]: 存储原始点
b[N]: 存储坐标交换后的点
首先比较first，相等时比较second

按x坐标排序点
对每个点i，找出x坐标相同的所有点
lower_bound(a + i, a + n, ii{a[i].first+1, -inf}): 找到第一个x坐标>a[i].first的点
pos - i - 1: 与当前点x坐标相同的点的个数（不包括自己）
累加到答案
按y坐标排序点（通过交换坐标实现）
对每个点i，找出y坐标相同的所有点
累加到答案
unique(a, a + n): 去重（数组必须先排序）
对于重复的点，它们在前面的计算中被重复计算了
mp[a[i]]个相同点会产生C(mp[a[i]], 2) = (mp[a[i]]-1)*mp[a[i]]/2对点
从答案中减去这些重复计算的对数

时间复杂度：O(n log n)，主要是排序的复杂度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 2e5+5, inf = 0x3f3f3f3f;
int n;
map<ii, int> mp;
ii a[N], b[N];

bool cmp(const ii& x, const ii& y) {
    return x.first != y.first ? x.first < y.first : x.second < y.second;
}

int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        mp[a[i]]++;
        b[i].first = a[i].second, b[i].second = a[i].first;
    }
    sort(a, a + n, cmp);
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        int pos = lower_bound(a + i, a + n, ii{a[i].first+1, -inf}) - a;
        if (pos > i)
            ans += 1ll*(pos - i - 1);
    }
    sort(b, b + n, cmp);
    for (int i = 0; i < n; ++i) {
        int pos = lower_bound(b + i, b + n, ii{b[i].first+1, -inf}) - b;
        if (pos > i)
            ans += 1ll*(pos - i - 1);
    }
    int top = unique(a, a + n) - a;
    for (int i = 0; i < top; ++i)
        ans -= 1ll*(mp[a[i]] - 1)*mp[a[i]]/2;
    cout << ans << '\n';
    return 0;
}