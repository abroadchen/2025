//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
若 n == 0：输出 0。
否则：
若 (n+1) 为奇数（即 (n+1)%2 != 0，也就是 n 为偶数）：输出 n+1；
若 (n+1) 为偶数（即 n 为奇数）：输出 (n+1)/2
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n;
int main() {
    fast;
    cin >> n;
    cout << (!n ? 0 : ((n+1)%2 ? n+1 : (n+1)/2));
    return 0;
}