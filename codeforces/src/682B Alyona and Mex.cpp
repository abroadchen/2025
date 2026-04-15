//
// Created by Psy.C on 2026/4/15.
//
/**
vector<int> a(n)
m表示当前期望找到的最小正整数，初始值为1
遍历已排序的数组，如果当前元素大于等于m，则说明m这个数字存在或已被覆盖，将m递增
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    int m = 1;
    for (int i = 0; i < n; ++i)
        if (a[i] >= m) m++;
    cout << m;
    return 0;
}