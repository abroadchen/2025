//
// Created by Psy.C on 2025/12/14.
//时间复杂度为O((x-a+1) × (y-b+1))

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int x, y, a, b, cnt = 0; cin>>x>>y>>a>>b;
    for (int i = a; i <= x; ++i) for (int j = b; j <= y; ++j) {
        if (i > j) cnt++;//满足条件i > j的数对(i, j)的总数
    }
    cout << cnt << '\n';
    for (int i = a; i <= x; ++i) for (int j = b; j <= y; ++j) {
        if (i > j) cout << i << ' ' << j << '\n';
    }
    return 0;
}