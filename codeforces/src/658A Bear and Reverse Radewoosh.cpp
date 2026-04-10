//
// Created by Psy.C on 2026/4/10.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, c, a[55][2], tim, mx1, mx2;
int main() {
    fast;
    cin >> n >> c;
    for (int i = 0; i < n; ++i) cin >> a[i][0];//存储到数组a的第一列(a[i][0])中
    for (int i = 0; i < n; ++i) cin >> a[i][1];
    for (int i = 0; i < n; ++i) {
        tim += a[i][1];
        mx1 += max(0, a[i][0]-c*tim);//初始分数 - c × 当前总时间
    }
    tim = 0;
    for (int i = n-1; i >= 0; --i) {
        tim += a[i][1];
        mx2 += max(0, a[i][0]-c*tim);
    }
    if (mx1 > mx2) cout << "Limak";
    else if (mx1 < mx2) cout << "Radewoosh";
    else cout << "Tie";
    return 0;
}