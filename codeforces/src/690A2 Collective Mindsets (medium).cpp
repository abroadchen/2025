//
// Created by Psy.C on 2026/4/15.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, cnt;
int main() {
    fast;
    cin >> n;
    if (n&1) cout << (n-1)/2;
    else {
        while (1<<(cnt+1) <= n) cnt++;//2^(cnt+1) > n的最小cnt值
        cout << (n-(1<<cnt))/2;
    }
    return 0;
}