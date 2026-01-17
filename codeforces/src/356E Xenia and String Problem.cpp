//
// Created by Psy.C on 2026/1/17.
//

#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ull unsigned long long
#define N 100010
#define bas 211
using namespace std;

ull mi[N], ha[N];
char s[N];

int n;
bool ok(const int l1, const int l2, const int le) {
    const int r1 = l1 + le - 1, r2 = l2 + le - 1;
    if (r1 > n || r2 > n) return false;
    const ull s1 = ha[r1] - ha[l1-1] * mi[r1 - l1 + 1],
    s2 = ha[r2] - ha[l2-1] * mi[r2 - l2 + 1];
    return s1 == s2;
}


bool gray[N][30];
int len[31], num[N][26], a[N];
void judge(const int l, const int k) {
    if (k == 1) { gray[l][k] = true; return; }
    if (const int mid = l + len[k-1],r = l + len[k] - 1;
        num[r][a[mid]] - num[l-1][a[mid]] == 1 &&
        ok(l, mid + 1, len[k-1]) && gray[l][k-1] &&
        gray[mid+1][k-1]) gray[l][k] = true;
}

int mx;
int lcp(const int l1, const int l2) {
    int le = 0;
    for (int i = mx; i >= 0; --i) if (ok(l1 + le, l2 + le, 1<<i)) {
        le += 1<<i;
    }
    return le;
}

ll val[N][26];
void f(const int l, const int k) {
    const int r = l + len[k] - 1, mid = l + len[k-1];
    if (k == 1) {
        for (int i = 0; i < 26; ++i) if (a[l] != i) val[l][i]++;
        return;
    }
    if (ok(l, mid + 1, len[k-1]) && gray[l][k-1] && gray[mid+1][k-1]) {
        for (int i = 0; i < 26; ++i) if (a[mid] != i && num[r][i] - num[l-1][i] == 0) {
            val[mid][i] += 1ll * len[k] * len[k];
        }
    }
    const int l1 = l, l2 = mid + 1, t = lcp(l1, l2);
    if (t >= len[k-1]) return;
    if (l1 + t + 1 + lcp(l1 + t + 1, l2 + t + 1) < mid) return;
    if (gray[l2][k-1] && num[r][a[mid]] - num[mid][a[mid]] == 0)
        val[l1 + t][a[l2 + t]] += 1ll * len[k] * len[k];
    if (gray[l1][k-1] && num[mid-1][a[mid]] - num[l-1][a[mid]] == 0)
        val[l2 + t][a[l1 + t]] += 1ll * len[k] * len[k];
}

int main() {
    fast; scanf("%s", s + 1);
    n = static_cast<int>(strlen(s + 1)); mi[0] = 1;

    for (int i = 1; i <= n; ++i) {
        a[i] = s[i] - 'a';
        num[i][a[i]]++;
        for (int j = 0; j < 26; ++j) num[i][j] += num[i-1][j];
        mi[i] = mi[i-1] * bas;
        ha[i] = ha[i-1] * bas + s[i];
    }
    for (int i = 1; i <= 30; ++i) {
        len[i] = len[i-1] * 2 + 1;
        if (len[i] > n) { mx = i - 1; break; }
    }
    ll ans = 0, cost[N]={};
    for (int i = 1; i <= mx; ++i) for (int j = 1; j <= n; ++j) {
        if (j + len[i] - 1 > n) break;
        judge(j, i);
        if (gray[j][i]) {
            ans += 1ll * len[i] * len[i];
            cost[j] += 1ll * len[i] * len[i];
            cost[j + len[i]] -= 1ll * len[i] * len[i];
        }
    }
    for (int i = 1; i <= n; ++i) cost[i] += cost[i-1];
    for (int i = 1; i <= mx; ++i) for (int j = 1; j <= n; ++j) {
        if (j + len[i] - 1 > n) break;
        f(j, i);
    }
    ll sum = 0;
    for (int j = 1; j <= n; ++j) for (int k = 0; k < 26; ++k) {
        sum = max(sum, -cost[j] + val[j][k]);
    }
    cout << sum + ans << '\n';
    return 0;
}