//
// Created by Psy.C on 2026/8/26.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


string revstr(string s) {
    string ans;
    for (int i = 0; i < s.length(); ++i)
        ans.insert(ans.begin(), s[i]);
    return ans;
}

int n;
bool isrev(string s) {
    for (int i = 0; i < n/2; ++i)
        if (s[i] != s[n-i-1])
            return false;
    return true;
}

map<string, priority_queue<int>> s;
int main() {
    fast;
    int k, ans = 0; cin >> k >> n;
    for (int i = 0; i < k; ++i) {
        string t; int b;
        cin >> t >> b;
        s[t].push(b);
    }
    int cnt = 0, mn, mx;
    for (auto it = s.begin(); it != s.end(); ++it) {
        string now = it->first, rev = revstr(now);
        while (!s[now].empty()) {
            if (!isrev(now)) {
                if (s.contains(rev) && !s[rev].empty()) {
                    int a = s[now].top(); s[now].pop();
                    int b = s[rev].top(); s[rev].pop();
                    if (a + b > 0) ans += a + b;
                } else s[now].pop();
            } else if (isrev(now)) {
                int a = s[now].top(); s[now].pop();
                if (!s[rev].empty()) {
                    int b = s[rev].top(); s[rev].pop();
                    if (a > 0 && b >= 0) {
                        ans += a + b;
                        cnt += 2;
                    } else if (a + b > 0 && b < 0) {
                        ans += a + b;
                        mn = min(mn, b);
                    } else if (a + b <= 0 && a > 0) {
                        mx = max(mx, a);
                    } else break;
                } else {
                    if (a > 0) mx = max(mx, a);
                    else break;
                }
            }
        }
    }
    if (mx > -mn) ans += mx; else ans -= mn;
    cout << ans << '\n';
    return 0;
}