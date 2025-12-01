//
// Created by Psy.C on 2025/11/30.
//

#include <iostream>
#include <algorithm>
#include <string>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int inf = 0x3f3f3f3f;
struct node {
    int son[26], siz, f, dp[2023];
    bool lst;
    char v;
} z[10000];

int cnt = -1;
int create(const char v) {
    cnt++;
    for (int& i : z[cnt].son) i = -1;
    z[cnt].siz = 0;
    z[cnt].v = v;
    return cnt;
}
void add(const int n, const string& s) {
    z[n].siz++;
    if (z[n].son[s[0] - 'a'] == -1) z[n].son[s[0] - 'a'] = create(s[0]);
    if (s.size() == 1) z[z[n].son[s[0] - 'a']].lst = true, z[z[n].son[s[0] - 'a']].siz++;
    else add(z[n].son[s[0] - 'a'], s.substr(1, s.size() - 1));
}

void calc(const int n) {
    if (n == -1) return;
    for (const int i : z[n].son) calc(i);
    z[n].f = 0;
    for (const int t : z[n].son) {
        if (t == -1) continue;
        z[n].f += z[t].f;
    }
    if (n) z[n].f += z[n].siz * (z[n].siz - 1) / 2;
}

void dp(const int n) {
    if (n == -1) return;
    for (const int i : z[n].son) dp(i);
    for (int& i : z[n].dp) i = -inf;
    z[n].dp[0] = 0;
    for (const int t : z[n].son) {
        if (t == -1) continue;
        for (int j = z[n].siz; j > 0; --j) {
            for (int i = j; i > 0; --i) {
                if (z[n].dp[j] < z[n].dp[j-i] + z[t].dp[i])
                    z[n].dp[j] = max(z[n].dp[j],
                        z[n].dp[j-i] + z[t].dp[i]);
            }
        }
    }
    for (int i = 0; i < 2023; ++i) z[n].dp[i] += i * (i - 1) / 2;
    z[n].dp[z[n].siz] = max(z[n].dp[z[n].siz], z[n].f);
}

int main() {
    fast;
    int n, k; cin >> n >> k; create(32);
    string a, b; bool flag = true;
    cin >> a, add(0, a);
    for (int i = 1; i < n; ++i) {
        b = a, cin >> a, add(0, a);
        if (b != a) flag = false;
    }
    if (flag) return cout << k * (k - 1) / 2 * a.size(), 0;
    calc(0); dp(0);
    cout << z[0].dp[k] - k * (k - 1) / 2;
    return 0;
}