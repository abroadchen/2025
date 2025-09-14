//
// Created by Psy.C on 2025/9/13.
//

#include <ios>
#include <iostream>
using namespace std;

typedef long long ll;
ll dp[40][40];



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, h; cin >> n >> h;

    for (int i = 0; i <= n; ++i) dp[0][i] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 0; k < i; ++k)
                dp[i][j] += dp[k][j - 1] * dp[i - k - 1][j - 1];
        }
    }
    cout << dp[n][n] - dp[n][h - 1] << endl;
    return 0;
}