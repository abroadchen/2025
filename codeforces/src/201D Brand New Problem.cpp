//
// Created by Psy.C on 2025/12/4.
//

#include <iostream>
#include <algorithm>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 20, inf = 0x3f3f3f3f, M = 1e6+5;
int n, c[N], dp[150][(1<<15)-1], Len, seq[M], pre[20], nxt[M][20];
ll p[N], e[20];
char s[N];

int main() {
    fast;
    cin >> n; p[0] = 1;
    for (int i = 1; i <= 12; ++i) p[i] = p[i-1] * 27;
    for (int i = 0; i < n; ++i) {
        scanf("%s", s);
        for (int j = 0, len = static_cast<int>(strlen(s)); j < len; ++j)
            e[i] += (s[j] - 'a' + 1) * p[j];
        c[i] = i;
    }
    sort(c, c + n, [](const int& a, const int& b) {
        return e[a] < e[b];
    });
    int m, siz, ans = inf, loc = 0;
    cin >> m;
    for (int t = 1; t <= m; ++t) {
        memset(dp, 0x3f, sizeof(dp)); dp[0][0] = 0; Len = 0;
        cin >> siz;
        for (int j = 1; j <= siz; ++j) {
            scanf("%s", s);
            ll num = 0;
            for (int k = 0, len = static_cast<int>(strlen(s)); k < len; ++k)
                num += (s[k] - 'a' + 1) * p[k];
            int l = 0, r = n - 1;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (e[c[mid]] <= num) l = mid; else r = mid - 1;
            }
            if (e[c[l]] == num) seq[++Len] = c[l];
        }
        memset(pre, -1, sizeof(pre));
        for (int i = Len; i >= 0; --i) {
            for (int j = 0; j < n; ++j) nxt[i][j] = pre[j];
            pre[seq[i]] = i;
        }
        for (int i = 0, st; i <= n * (n - 1) / 2; ++i) {
            for (st = 0; st < 1<<n; ++st) if (dp[i][st] < inf) {
                for (int k = n - 1, cnt = 0; k >= 0; --k) {
                    if (!(st & (1<<k))) {
                        if (nxt[dp[i][st]][k] != -1)
                            dp[i+cnt][st|(1<<k)] =
                                min(dp[i+cnt][st|(1<<k)],
                                    nxt[dp[i][st]][k]);
                    } else cnt++;
                }
            }
        }
        for (int i = 0; i <= n * (n - 1) / 2; ++i) {
            if (dp[i][(1<<n)-1] < inf) {
                if (i < ans) { ans = i; loc = t; }
                break;
            }
        }
    }
    if (ans == inf) cout << "Brand new problem!";
    else {
        cout << loc << '\n'; printf("[:");
        for (int i = 1; i <= n * (n - 1) / 2; ++i) putchar('|');
        printf(":]");
    }
    return 0;
}