//
// Created by Psy.C on 2026/1/16.
//
///算法的时间复杂度是O(n²)，空间复杂度是O(n)
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2010
using namespace std;


int main() {
    fast;
    int n, a[N]; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; a[i] = abs(a[i]);
    }
    int ans = 0;
    for (int i = n; i >= 1; --i) {
        int n1 = 0, n2 = 0;
        for (int j = 1; j < i; ++j) n1 += a[j] < a[i];//i位置左边比a[i]小的元素个数
        for (int j = i + 1; j <= n; ++j) n2 += a[j] < a[i];// i位置右边比a[i]小的元素个数
        ans += min(n1, n2);
    }
    cout << ans << '\n';
    return 0;
}