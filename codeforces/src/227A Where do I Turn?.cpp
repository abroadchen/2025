//
// Created by Psy.C on 2025/12/9.
//
/*
 *
*叉积 > 0：点C在向量AB的左侧
叉积 < 0：点C在向量AB的右侧
叉积 = 0：三点共线
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

struct node { ll x, y; } a, b, c;

int main() {
    fast;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    if ((c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x)) cout << "LEFT\n";
    else if ((c.y - a.y) * (b.x - a.x) < (b.y - a.y) * (c.x - a.x)) cout << "RIGHT\n";
    else cout << "TOWARDS\n";
    return 0;
}