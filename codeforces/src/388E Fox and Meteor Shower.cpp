//
// Created by Psy.C on 2026/1/28.
//

#include <algorithm>
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ld long double
#define N 1010
#define eps 1e-8
using namespace std;

struct node { ld x, y, vx, vy; } xn[N], tmp;
struct node2 { ld x, y; } jd[N];

ld cross(const node2 u, const node2 v) { return u.x * v.y - u.y * v.x; }

int main() {
    fast;
    int n; cin >> n;
    ld a, b, c, d, e, f, t, ti[N]={};
    for (int i = 1; i <= n; ++i) {
        cin >> c >> a >> b >> f >> d >> e; t = f - c;
        xn[i].vx = (d - a) / t; xn[i].vy = (e - b) / t;
        xn[i].x = a - xn[i].vx * c; xn[i].y = b - xn[i].vy * c;
    }
    int ans = 1;
    for (int i = 1, cnt; i <= n; ++i) {
        cnt = 0;
        for (int j = i + 1; j <= n; ++j) {
            if (i == j) continue;
            tmp.x = xn[i].x - xn[j].x; tmp.y = xn[i].y - xn[j].y;
            tmp.vx = xn[i].vx - xn[j].vx; tmp.vy = xn[i].vy - xn[j].vy;
            t = fabs(tmp.vx) > eps ? tmp.x / tmp.vx : fabs(tmp.vy) > eps ? tmp.y / tmp.vy : 0;
            if (fabs(tmp.vx * t - tmp.x) < eps && fabs(tmp.vy * t - tmp.y) < eps) {
                ti[++cnt] = t;
                jd[cnt].x = tmp.vx; jd[cnt].y = tmp.vy;
            }
        }
        if (!cnt) continue;
        sort(ti + 1, ti + cnt + 1);
        int an = 1;
        for (int j = 2; j <= cnt; ++j) {
            if (fabs(ti[j] - ti[j-1]) < eps) an++; else {
                ans = max(ans, an);
                an = 1;
            }
        }
        ans = max(an, ans);
        sort(jd + 1, jd + cnt + 1, [](const node2 u, const node2 v) {
            if (fabs(cross(u, v)) < eps) {
                if (fabs(u.x - v.x) > eps) return u.x < v.x;
                return u.y < v.y;
            }
            return cross(u, v) < 0;
        });
        an = 1;
        for (int j = 2; j <= cnt; ++j) {
            if (fabs(cross(jd[j], jd[j-1])) < eps) {
                if (fabs(jd[j].x - jd[j-1].x) > eps || fabs(jd[j].y - jd[j-1].y) > eps)
                    an++;
            } else {
                ans = max(ans, an);
                an = 1;
            }
        }
        ans = max(ans, an);
    }
    cout << ans + 1;
    return 0;
}