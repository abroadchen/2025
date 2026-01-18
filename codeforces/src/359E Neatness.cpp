//
// Created by Psy.C on 2026/1/18.
//

#include <algorithm>
#include <iostream>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 507
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

int on[N][N];//每个位置是否点亮
set<int> r[N], c[N];
bool vis[N][N];
int n;
bool ok(const int x, const int y, const int vx, const int vy) {
    if (x + vx <= 0 || x + vx > n) return false;
    if (y + vy <= 0 || y + vy > n) return false;
    if (vis[x+vx][y+vy]) return false;
    if (!vy) {//vy=0，移动方向为水平（左右）
        if (vx == 1) return ranges::upper_bound(c[y], x) != c[y].end();//向下 比x大的值
        return ranges::lower_bound(c[y], x) != c[y].begin();//向上 比x小的值
    }
    if (vy == 1) return ranges::upper_bound(r[x], y) != r[x].end();//向右
    return ranges::lower_bound(r[x], y) != r[x].begin();//向左
}


string path;
void dfs(const int x, const int y) {
    vis[x][y] = true;
    if (!on[x][y]) {//当前位置未点亮
        path.push_back('1');//添加点亮操作
        on[x][y] = true;//点亮当前位置
        r[x].insert(y);//更新行信息
        c[y].insert(x);
    }
    if (ok(x, y, 0, 1)) {//向右
        path.push_back('R');
        dfs(x, y + 1);
        path.push_back('L');
    }
    if (ok(x, y, 0, -1)) {//向左
        path.push_back('L');
        dfs(x, y - 1);
        path.push_back('R');
    }
    if (ok(x, y, 1, 0)) {//向下
        path.push_back('D');
        dfs(x + 1, y);
        path.push_back('U');
    }
    if (ok(x, y, -1, 0)) {//向上
        path.push_back('U');
        dfs(x - 1, y);
        path.push_back('D');
    }
    if (on[x][y]) {//回溯时熄灭
        on[x][y] = false;
        path.push_back('2');//添加熄灭操作
        r[x].erase(y);
        c[y].erase(x);
    }
}

int main() {
    fast;
    int sx, sy; cin >> n >> sx >> sy;
    rep(i,n) rep(j,n) {
        cin >> on[i][j];
        if (on[i][j]) {//记录点亮的位置
            r[i].insert(j);
            c[j].insert(i);
        }
    }
    dfs(sx, sy);
    rep(i,n) rep(j,n) if (on[i][j]) {//还有点亮的位置
        return cout << "NO\n", 0;
    }
    cout << "YES\n";
    cout << path << '\n';
    return 0;
}