//
// Created by Psy.C on 2026/2/21.
//
/**
c1[i]: 位置1到i中1的个数
c2[i]: 位置1到i中2的个数
t1: 找到第一个位置，使得该位置前缀和中1的个数 ≥ lst1 + t  找到第一个1的计数达到lst1+t的位置
t2: 找到第一个位置，使得该位置前缀和中2的个数 ≥ lst2 + t  找到第一个2的计数达到lst2+t的位置
当2的计数大于1的计数且最后一个是2，或相反情况时

时间复杂度：O(n²log n)，外层循环×内层循环×二分搜索
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+1;
int n, a[N], c1[N], c2[N];
ii ans[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        c1[i] = c1[i-1]; c2[i] = c2[i-1];
        if (a[i] == 1) c1[i]++;
        else c2[i]++;
    }
    int c = 0;
    for (int t = 1, s1, s2, lst1, lst2; t <= n; ++t) {
        s1 = s2 = lst1 = lst2 = 0;
        while (true) {
            int t1 = lower_bound(c1 + 1, c1 + n + 1, lst1 + t) - c1,
            t2 = lower_bound(c2 + 1, c2 + n + 1, lst2 + t) - c2;
            if (t1 > n && t2 > n) break;
            const int mn = min(t1, t2);
            if (mn == t1) s1++; else s2++;
            if (mn == n) {
                if (s2 > s1 && a[n] == 2 || s1 > s2 && a[n] == 1) {
                    ans[c].first = max(s1, s2);
                    ans[c++].second = t;
                }
                break;
            }
            lst1 = c1[mn]; lst2 = c2[mn];
        }
    }
    cout << c << '\n';
    sort(ans, ans + c);
    for (int i = 0; i < c; ++i) cout << ans[i].first << ' ' << ans[i].second << '\n';
    return 0;
}