//
// Created by Psy.C on 2026/3/27.
//
///O(min(n,m))：取决于初始值的大小差异
/**
每次循环都会调整ed1或ed2的值
当ed1较小时增加ed1，当ed2较小时增加ed2
目标是让它们逼近一个共同值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m;
int main() {
    fast;
    cin >> n >> m;
    int ed1 = 2*n, ed2 = 3*m;
    for (int i = 6; i <= min(ed1, ed2); i += 6) {
        if (ed1 <= ed2) ed1 += 2;
        else ed2 += 3;
    }
    cout << max(ed1, ed2);
    return 0;
}