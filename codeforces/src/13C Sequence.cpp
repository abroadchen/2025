//
// Created by Psy.C on 2025/9/15.
//

#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef long long LL;
const int maxn=5e3+5;
const LL INF=1e18;
LL a[maxn], N, b[maxn], dp[5][maxn];


int main() {
    scanf("%lld",&N);
    for (int i=1;i<=N;++i) {
        scanf("%lld",&a[i]);
        b[i] = a[i];
    }
    sort(b,b + N + 1);
    for (int i = 0; i <= 1; ++i)
        for (int j = 0; j <= N; ++j)
            dp[i][j] = INF;
    for (int i = 1; i <= N; ++i) dp[0][i] = 0;
    for (int i = 1; i <= N; ++i) {
        int v = i % 2, w = (i - 1) % 2;
        for (int j = 0; j <= N; ++j) dp[v][j] = INF;
        for (int j = 1; j <= N; ++j)
            dp[v][j] = min(dp[v][j - 1], dp[w][j] + abs(a[i] - b[j]));
    }
    LL ans = INF;
    int v = N % 2;
    for (int i = 1; i <= N; ++i)
        ans = min(ans, dp[v][i]);
    printf("%lld\n",ans);
    return 0;
}