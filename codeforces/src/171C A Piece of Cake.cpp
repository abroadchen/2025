//
// Created by Psy.C on 2025/11/28.
//
/*
*n: 数字的个数
s: 临时存储每个输入的数字
 *第1个数乘以1，第2个数乘以2，...，第i个数乘以i
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;

int main() {
    fast;
    int n, s; ll ans = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        ans += s * i;
    }
    cout << ans;
    return 0;
}