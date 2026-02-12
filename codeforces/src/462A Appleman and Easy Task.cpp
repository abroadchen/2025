//
// Created by Psy.C on 2026/2/12.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 105
using namespace std;

char a[N][N];
int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) cin >> a[i][j];
    for (int i = 1; i <= n; ++i)
        for (int j = 1, m = 0; j <= n; ++j) {
            //相邻单元格（上、左、右、下）中包含'o'的数量
            if (a[i-1][j] == 'o') m++;
            if (a[i][j-1] == 'o') m++;
            if (a[i][j+1] == 'o') m++;
            if (a[i+1][j] == 'o') m++;
            if (m&1) { cout << "NO"; return 0; }
            m = 0;
        }
    cout << "YES";
    return 0;
}