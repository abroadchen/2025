//
// Created by Psy.C on 2026/2/13.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m, a[100][2], cnt;

int main() {
    fast;
    cin >> n; m = n;
    while (m) {//从后往前存储数据对
        cin >> a[m-1][0] >> a[m-1][1];
        m--;
    }
    cnt = 0;
    for (m = 0; m < n; ++m) {//第二个数减去第一个数大于等于2
        if (a[m][1] - a[m][0] >= 2) cnt++;
    }
    cout << cnt;
    return 0;
}