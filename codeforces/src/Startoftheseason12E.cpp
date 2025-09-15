//
// Created by Psy.C on 2025/9/15.
//

#include <ios>
#include <iostream>
using namespace std;

const int maxm = 2e3+5;
int n, a[maxm][maxm];
inline void solve() {
    cin >> n; n--;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            a[i][j] = (i + j) % n + 1;
    }
    for (int i = 0; i < n; ++i) {
        a[i][n] = a[n][i] = a[i][i];
        a[i][i] = 0;
    }
    n++;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << a[i][j] << ' ';
        cout << endl;
    }
}




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    
    return 0;
}