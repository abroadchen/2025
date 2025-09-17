//
// Created by Psy.C on 2025/9/16.
//

#include <ios>
#include <iostream>
using namespace std;

const int maxn=20;
int n;
double a[maxn][maxn];
double dp[1<<maxn];


double solve(int x, int j) {
    int cnt0 = 0;
    double res = 0.00;
    for (int i = 0; i < n; ++i)
        if (!(x & (1<<i))) {
            cnt0++;
            res += a[i][j];
        }
    double tmp = (cnt0*1.00) * (cnt0 - 1.00) / 2.00;
    return res / tmp;
}






int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    int states = (1 << n) - 1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> a[i][j];

    dp[0] = 1.00;

    for (int i = 0; i < states; ++i)
        for (int j = 0; j < n; ++j)
            if (!(i & (1 << j))) {
                int u = i | (1 << j);
                double p = solve(i, j);
                dp[u] += dp[i] * p;
            }

    for (int i = 0; i < n; ++i)
        printf("%.6f ", dp[states ^ (1 << i)]);
    
    return 0;
}