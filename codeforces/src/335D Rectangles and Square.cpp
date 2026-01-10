//
// Created by Psy.C on 2026/1/10.
//

#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 100005, M = 400005, K = 3005, L = 10;
struct pt {
    int x, y, u, d, l, r;
    bool operator<(const pt &o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
    bool operator==(const pt &o) const {
        return x == o.x && y == o.y;
    }
    bool operator<=(const pt &o) const {
        return x < o.x || (x == o.x && y <= o.y);
    }
} p[M], *ed, st[K];

int sub(const pt &x) { return x.x - x.y; }
bool eq(const pt &u, const pt &v) { return sub(u) == sub(v); }
int minn(const pt &x) { return min(x.u, x.r); }

int main() {
    fast;
    int n, i, j = 0, k, x1[N], x2[N], y1[N], y2[N], s[K][K], t[K][K]; cin >> n;
    for (i = n; i--;) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
        p[i<<2] = {x1[i], y1[i]};
        p[i<<2|1] = {x1[i], y2[i]};
        p[i<<2|2] = {x2[i], y1[i]};
        p[i<<2|3] = {x2[i], y2[i]};
        for (j = x2[i]; j > x1[i]; --j) for (k = y2[i]; k > y1[i]; --k) {
            s[j][k] = 1;
        }
    }
    for (i = 1; i < 3001; ++i) for (j = 1; j < 3001; ++j) {
        s[i][j] += s[i][j-1] + s[i-1][j] - s[i-1][j-1];
    }
    sort(p, p + (n<<2), [](const pt &a, const pt &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    });
    ed = unique(p, p + (n<<2));
    for (i = static_cast<int>(ed - p); i--;) t[p[i].x][p[i].y] = i;
    int a[M][L], num[M];
    for (i = n; i--;) {
        a[t[x1[i]][y1[i]]][num[t[x1[i]][y1[i]]]++] = t[x1[i]][y2[i]];
        a[t[x1[i]][y1[i]]][num[t[x1[i]][y1[i]]]++] = t[x2[i]][y1[i]];
        a[t[x1[i]][y2[i]]][num[t[x1[i]][y2[i]]]++] = t[x1[i]][y1[i]];
        a[t[x1[i]][y2[i]]][num[t[x1[i]][y2[i]]]++] = t[x2[i]][y2[i]];
        a[t[x2[i]][y1[i]]][num[t[x2[i]][y1[i]]]++] = t[x1[i]][y1[i]];
        a[t[x2[i]][y1[i]]][num[t[x2[i]][y1[i]]]++] = t[x2[i]][y2[i]];
        a[t[x2[i]][y2[i]]][num[t[x2[i]][y2[i]]]++] = t[x1[i]][y2[i]];
        a[t[x2[i]][y2[i]]][num[t[x2[i]][y2[i]]]++] = t[x2[i]][y1[i]];
    }
    for (i = static_cast<int>(ed - p); i--;) for (j = num[i]; j--;) {
        if (p[a[i][j]].x == p[i].x) p[i].u = max(p[i].u, p[a[i][j]].u+p[a[i][j]].y-p[i].y);
        else p[i].r = max(p[i].r, p[a[i][j]].r+p[a[i][j]].x-p[i].x);
    }
    for (i = 0; i < ed - p; ++i) for (j = num[i]; j--;) {
        if (p[a[i][j]].x == p[i].x) p[i].d = max(p[i].d, p[a[i][j]].d-p[a[i][j]].y+p[i].y);
        else p[i].l = max(p[i].l, p[a[i][j]].l-p[a[i][j]].x+p[i].x);
    }
    sort(p, ed, [](const pt &u, const pt &v) {
        return sub(u) != sub(v) ? sub(u) < sub(v) : u<=v;
    });
    for (i = 0; i < ed - p; i = j) {
        int top = 1;
        st[0] = p[i];
        for (j = i + 1; j < ed - p && eq(p[i], p[j]); ++j) {
            while (top && minn(st[top-1])+st[top-1].x < p[j].x) --top;
            if (min(minn(st[top-1]), min(p[j].d, p[j].l)) >= p[j].x-st[top-1].x &&
                s[p[j].x][p[j].y]-s[st[top-1].x][p[j].y]-s[p[j].x][st[top-1].y]+s[st[top-1].x][st[top-1].y]==
                (p[j].x-st[top-1].x)*(p[j].y-st[top-1].y)) {
                int ans = 0;
                for (k = n; k--;) {
                    if (x1[k] < p[j].x && y1[k] < p[j].y && x2[k] > st[top-1].x && y2[k] > st[top-1].y) ++ans;
                }
                cout << "YES " << ans << "\n";
                bool flag = true;
                for (k = n; k--;) {
                    if (x1[k] < p[j].x && y1[k] < p[j].y && x2[k] > st[top-1].x && y2[k] > st[top-1].y) {
                        if (flag) flag = false; else cout << ' ';
                        cout << n - k;
                    }
                }
                cout << '\n';
                return 0;
            }
            while (top && minn(st[top-1])+st[top-1].x <= p[j].x+minn(p[j])) --top;
            st[top++] = p[j];
        }
    }
    cout << "NO\n";
    return 0;
}