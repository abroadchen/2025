//
// Created by Psy.C on 2026/1/8.
//

#include <iostream>
#include <sstream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

bool vis[501][501];
int n, m, cnt;//网格的行数 列数 操作计数器
stringstream os;//缓存输出内容
void dfs(const int y, const int x, const bool rt) {
    if (vis[y][x]) return; vis[y][x] = true;
    cnt++;
    os << "B " << y + 1 << ' ' << x + 1 << '\n';//在字符串流中记录"B"操作（坐标从1开始计数）
    if (y > 0) dfs(y-1, x, false);//向四个方向（上、下、左、右）进行DFS递归
    if (y < n - 1) dfs(y+1, x, false);
    if (x > 0) dfs(y, x-1, false);
    if (x < m - 1) dfs(y, x+1, false);
    if (!rt) {//不是根节点（即不是第一次调用）
        cnt += 2;
        os << "D " << y + 1 << ' ' << x + 1 << '\n';//记录"D"操作
        os << "R " << y + 1 << ' ' << x + 1 << '\n';
    }
}



int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {//循环处理每一行
        string s; cin >> s;//读入一行字符串
        for (int j = 0; j < m; ++j) {//循环处理每一列
            if (s[j] == '.') vis[i][j] = false; else vis[i][j] = true;
        }
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) if (!vis[i][j]) {
        dfs(i, j, true);//从该位置开始执行DFS，标记为根节点
    }
    cout << cnt << '\n' << os.str();//输出字符串流中的全部内容
    return 0;
}