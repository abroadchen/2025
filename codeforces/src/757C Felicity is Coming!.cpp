//
// Created by Psy.C on 2026/9/3.
//
/**
如果一个元素属于多个集合（vector 长度 > 1），那么这些集合的交集要求该元素把那些集合"串"在一起。
排序后，所属集合列表完全相同的元素会在 a 中连续出现。这样一组"命运相同"的元素可以任意互换位置而不影响可行性，所以每组内部的排列数是该组元素个数的阶乘。
代码用 cnt 记录当前相同组内连续相同元素的数量，ans = ans*cnt%mod 在组内逐步乘上 1, 2, 3, ... 即乘上该组的阶乘
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+10, mod = 1e9+7;

int n, m;
vector<int> a[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, g; i <= n; ++i) {
        cin >> g;//第 i 个集合有 g 个元素
        for (int j = 1, x; j <= g; ++j)
            cin >> x, a[x].push_back(i);//元素 x 属于集合 i
    }
    sort(a + 1, a + m + 1);
    ll cnt = 1, ans = 1;
    for (int i = 2; i <= m; ++i) {
        if (a[i] == a[i-1]) cnt++, ans = ans*cnt%mod;
        else cnt = 1;
    }
    cout << ans << '\n';
    return 0;
}