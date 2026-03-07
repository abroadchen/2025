//
// Created by Psy.C on 2026/3/7.
//
/**
从第二个元素开始遍历排序后的数组
如果当前元素等于前一个元素（a[i] == a[i-1]）：将其加1，确保严格递增
如果当前元素小于前一个元素（a[i] < a[i-1]）：将其调整为a[i-1] + 1
a[i] += a[i-1] - a[i] + 1 等价于 a[i] = a[i-1] + 1
将处理后的元素加到s2中
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e3+5;
int n, a[N];
int main() {
    fast;
    cin >> n;
    int s1 = 0, s2 = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; s1 += a[i];
    }
    sort(a, a + n);
    s2 = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] == a[i-1]) a[i]++;
        else if (a[i] < a[i-1])
            a[i] += a[i-1] - a[i] + 1;
        s2 += a[i];
    }
    cout << s2 - s1 << '\n';
    return 0;
}