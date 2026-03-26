//
// Created by Psy.C on 2026/3/26.
//
///时间复杂度：O(n) 空间复杂度：O(n)
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;
int n, a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n>>1; ++i) {
        a[i] = (i<<1) - 1;//第i个奇数
        a[n-i+1] = (i<<1) - 1;//对称位置也放置相同奇数
        a[i+n] = i<<1;//第i个偶数
        a[(n<<1)-i] = i<<1;//对称位置也放置相同偶数
    }
    //如果a[i]非零，输出a[i]；否则输出n
    for (int i = 1; i <= n<<1; ++i) {
        if (a[i]) cout << a[i] << ' ';
        else cout << n << ' ';
    }
    return 0;
}