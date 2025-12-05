//
// Created by Psy.C on 2025/12/4.
//

#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1009, M = 7;
int n, m, k;
struct node { int num{}; string var[M], name; } a[N], f[N];
map<string, string> mp;


bool ok(const node& x, const node& y) {
    if (x.num != y.num) return false;
    if (x.name != y.name) return false;
    for (int i = 1; i <= x.num; ++i) {
        if (x.var[i] != y.var[i] && x.var[i] != "T")
            return false;
    }
    return true;
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        char b[N]; cin >> b;
        while (true) {
            const char ch = static_cast<char>(getchar());
            if (ch == '(') break;
            if (ch != ' ') a[i].name += ch;
        }
        string s; getline(cin, s);
        const int len = static_cast<int>(s.length());int cur = 0;
        while (true) {
            while ((s[cur] == ')' || s[cur] == ',' ||
                s[cur] == ' ') && cur < len) ++cur;
            if (cur >= len) break;
            string nxt;
            while (true) {
                nxt += s[cur++];
                if (s[cur] == ')' || s[cur] == ',' ||
                    s[cur] == ' ' || cur >= len) break;
            }
            a[i].var[++a[i].num] = nxt;
            if (s[cur] == ')') break;
        }
    }
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        string s1, s2; cin >> s1 >> s2;
        mp[s2] = s1;
    }
    cin >> k; getchar();
    for (int i = 1; i <= k; ++i) {
        while (true) {
            const char ch = static_cast<char>(getchar());
            if (ch == '(') break;
            if (ch != ' ') f[i].name += ch;
        }
        string s; getline(cin, s);
        int len = static_cast<int>(s.length());int cur = 0;
        while (true) {
            while ((s[cur] == ')' || s[cur] == ',' ||
                s[cur] == ' ') && cur < len) ++cur;
            if (cur >= len) break;
            string nxt;
            while (true) {
                nxt += s[cur++];
                if (s[cur] == ')' || s[cur] == ',' ||
                    s[cur] == ' ' || cur >= len) break;
            }
            f[i].var[++f[i].num] = nxt;
            if (s[cur] == ')') break;
        }
        int ans = 0;
        for (int j = 1; j <= n; ++j) if (ok(a[j], f[i])) ++ans;
        cout << ans << '\n';
    }
    return 0;
}