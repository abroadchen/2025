/**
 * n, m是网格的行数和列数，x, y是起始坐标，dx, dy是移动方向
 *cnt记录访问的边界点数量，tim用于计时防止无限循环
 *vis映射记录访问过的坐标点
 *如果起始点在边界上，增加计数并标记为已访问
 *ans记录移动步数
 *
 *直到访问了所有边界点（n+m-2个）
 *计算到达边界的距离（tx为x方向距离，ty为y方向距离）
 *取两个方向中先到达边界的方向的步数
 *按照计算的步数移动，并累加到总步数
 *当到达边界时翻转移动方向
 *如果该边界点未访问过，增加计数
 *
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int n, m, x, y, dx, dy; cin >> n >> m >> x >> y;
    string str; cin >> str;
    str[0] == 'U' ? dx = -1 : dx = 1;
    str[1] == 'L' ? dy = -1 : dy = 1;
    int cnt = 0, tim = 0;
    map<pair<int, int>, int> vis;
    if (x == 1 || x == n || y == 1 || y == m) { cnt++, vis[{x, y}] = 1; }
    ll ans = 0;
    while (cnt != n + m - 2) {
        if (++tim >= 500000) { cout << "-1\n"; return 0; }
        int tx, ty;
        if (dx == 1) tx = abs(n - x); else tx = abs(1 - x);
        if (dy == 1) ty = abs(m - y); else ty = abs(1 - y);
        const int t = min(tx, ty);
        x += dx * t; y += dy * t; ans += t;
        if (x == 1) dx = 1; if (x == n) dx = -1;
        if (y == 1) dy = 1; if (y == m) dy = -1;
        if (!vis[{x, y}]) cnt++, vis[{x, y}] = 1;
    }
    cout << ans + 1 << '\n';
    return 0;
}