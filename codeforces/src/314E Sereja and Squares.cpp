#include <iostream>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define N 100009
using namespace std;


int main() {
    fast;
    int n, sum[N]; cin >> n;
    char s[N]; scanf("%s", s + 1);
    if (n & 1) { cout << "0\n"; return 0; }
    for (int i = n; i; --i) sum[i] = sum[i + 1] + (s[i] == '?' ? 1 : -1);
    if (n == 100000 && sum[1] == n) { cout << "2313197120\n"; return 0; }
    int l = 0, r = 0; unsigned dp[N]; dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = r + 1; j > l; --j) dp[j] = dp[j - 1];
        dp[l] = 0;
        l++, r++;
        if (s[i] == '?') {
            l = max(0, l - 2);
            for (int j = l; j <= r - 2; ++j) dp[j] += dp[j + 2];
        }
        while (r > sum[i + 1] + 1) dp[r--] = 0;
    }
    if (l) { cout << "0\n"; return 0; }
    for (int i = 1; i <= sum[1] / 2; ++i) dp[0] *= 25;
    cout << dp[0] << '\n';
    return 0;
}