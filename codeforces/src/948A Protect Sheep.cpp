//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

constexpr int N = 500;

int r, c;
char a[N][N+1];
int main() {
    fast;
    cin >> r >> c;
    rep(i,r) cin >> a[i];
    int flg = 1;
    for (int i = 0; i < r && flg; i++)
        for (int j = 0; j < c && flg; j++)
            if (a[i][j] == 'W') {
                if (i && a[i-1][j] == 'S') flg = 0;
                else if (i < r-1 && a[i+1][j] == 'S') flg = 0;
                else if (j && a[i][j-1] == 'S') flg = 0;
                else if (j < c-1 && a[i][j+1] == 'S') flg = 0;
            }
    if (flg) {
        cout << "Yes\n";
        rep(i,r) {
            rep(j,c) {
                if (a[i][j] == '.') cout << 'D';
                else cout << a[i][j];
            }
            cout << '\n';
        }
    } else cout << "No\n";
    return 0;
}