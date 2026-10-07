//
// Created by Psy.C on 2026/10/7.
//
/**
a为该医生从第几天开始看病，b为每隔几天来一次
用j表示天数，sum表示是第几个医生，a[]表示该从第几天开始看病，
b[]表示每个几天该医生来一次，则可知从第a[sum]天开始，每隔b[sum]的倍数天该医生在看病
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+10;

int a[N], b[N];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];
    int j = 0, sum = 1;
    while (sum != n+1) {
        j++;
        if (j-a[sum] >= 0 && (j-a[sum])%b[sum] == 0)
            sum++;
    }
    cout << j;
    return 0;
}