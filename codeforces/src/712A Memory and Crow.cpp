//
// Created by Psy.C on 2026/4/20.
//
/**
时间复杂度：O(n)，只需一次遍历
空间复杂度：O(n)，存储输入数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+7;
int n;
ll num[N];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> num[i];
    for (int i = 0; i < n - 1; ++i)
        cout << num[i] + num[i+1] << ' ';//当前元素与其后一个元素的和
    cout << num[n-1] << '\n';
    return 0;
}