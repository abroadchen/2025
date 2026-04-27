//
// Created by Psy.C on 2026/4/27.
//
/**
1. 水平方向检查（右方）
寻找与目标同Y轴且在X右侧的最近棋子
如果是车(Rook)或皇后(Queen)，则可以攻击
2. 水平方向检查（左方）
寻找与目标同Y轴且在X左侧的最近棋子
3. 垂直方向检查（上方）
寻找与目标同X轴且在Y上方的最近棋子
4. 垂直方向检查（下方）
寻找与目标同X轴且在Y下方的最近棋子
5. 对角线检查（右上方向）
检查主对角线方向（斜率为1）的右上方向
如果是象(Bishop)或皇后(Queen)，则可以攻击
6. 对角线检查（左下方向）
检查主对角线方向的左下方向
7. 反对角线检查（左上方向）
检查反对角线方向（斜率为-1）的左上方向
8. 反对角线检查（右下方向）
检查反对角线方向的右下方向
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5+7, inf = 2e9;

///op存储棋子类型，x,y存储坐标
struct node { char op[10]; int x, y; } a[N];

int n, X, Y;
int main() {
    fast;
    cin >> n >> X >> Y;
    for (int i = 1; i <= n; ++i) cin >> a[i].op >> a[i].x >> a[i].y;
    int mn = inf, pos = 0;
    for (int i = 1; i <= n; ++i)
        if (a[i].y == Y && a[i].x > X)
            if (mn > a[i].x) {
                mn = a[i].x; pos = i;
            }
    if (a[pos].op[0] == 'R' || a[pos].op[0] == 'Q') {
        cout << "YES\n";
        return 0;
    }
    mn = -inf, pos = 0;
    for (int i = 1; i <= n; ++i)
        if (a[i].y == Y && a[i].x < X)
            if (mn < a[i].x) {
                mn = a[i].x; pos = i;
            }
    if (a[pos].op[0] == 'R' || a[pos].op[0] == 'Q') {
        cout << "YES\n";
        return 0;
    }
    mn = inf, pos = 0;
    for (int i = 1; i <= n; ++i)
        if (a[i].x == X && a[i].y > Y)
            if (mn > a[i].y) {
                mn = a[i].y; pos = i;
            }
    if (a[pos].op[0] == 'R' || a[pos].op[0] == 'Q') {
        cout << "YES\n";
        return 0;
    }
    mn = -inf, pos = 0;
    for (int i = 1; i <= n; ++i)
        if (a[i].x == X && a[i].y < Y)
            if (mn < a[i].y) {
                mn = a[i].y; pos = i;
            }
    if (a[pos].op[0] == 'R' || a[pos].op[0] == 'Q') {
        cout << "YES\n";
        return 0;
    }
    mn = inf, pos = 0;
    for (int i = 1; i <= n; ++i)
        if (a[i].x - X == a[i].y - Y && a[i].x > X)
            if (mn > a[i].x) {
                mn = a[i].x; pos = i;
            }
    if (a[pos].op[0] == 'B' || a[pos].op[0] == 'Q') {
        cout << "YES\n";
        return 0;
    }
    mn = -inf, pos = 0;
    for (int i = 1; i <= n; ++i)
        if (a[i].x - X == a[i].y - Y && a[i].x < X)
            if (mn < a[i].x) {
                mn = a[i].x; pos = i;
            }
    if (a[pos].op[0] == 'B' || a[pos].op[0] == 'Q') {
        cout << "YES\n";
        return 0;
    }
    mn = -inf, pos = 0;
    for (int i = 1; i <= n; ++i)
        if (a[i].x - X == Y - a[i].y && a[i].x < X)
            if (mn < a[i].x) {
                mn = a[i].x; pos = i;
            }
    if (a[pos].op[0] == 'B' || a[pos].op[0] == 'Q') {
        cout << "YES\n";
        return 0;
    }
    mn = inf, pos = 0;
    for (int i = 1; i <= n; ++i)
        if (a[i].x - X == Y - a[i].y && a[i].x > X)
            if (mn > a[i].x) {
                mn = a[i].x; pos = i;
            }
    if (a[pos].op[0] == 'B' || a[pos].op[0] == 'Q') {
        cout << "YES\n";
        return 0;
    }
    cout << "NO\n";
    return 0;
}