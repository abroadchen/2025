//
// Created by Psy.C on 2026/3/30.
//
/**
寻找数组b中与a[0]相等的元素位置
pos就是可能的旋转偏移量
(i+pos)%(n-1) 实现了循环移位
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
int n, a[N], b[N], c1, c2;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (x) a[c1++] = x;//只存储非零元素
    }
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (x) b[c2++] = x;
    }
    int pos = -1;
    for (int i = 0; i < n; ++i)
        if (b[i] == a[0]) {
            pos = i;
            break;
        }
    for (int i = 0; i < n-1; ++i)
        if (a[i] != b[(i+pos)%(n-1)]) {
            cout << "NO\n";
            return 0;
        }
    cout << "YES\n";
    return 0;
}