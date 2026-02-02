//
// Created by Psy.C on 2026/2/2.
//
/**
 *c[i]是否完全在区间c[j]的右侧
 *i的左端点 > j的右端点
 *i的右端点 > j的左端点
 *
*ok(1, 3) && ok(1, 4)：区间1在区间3和4的右侧
ok(2, 3) && ok(2, 4)：区间2在区间3和4的右侧
任一条件满足则Team 1获胜
 *
*ok(3, 1) || ok(4, 1)：区间3或4在区间1的右侧
ok(3, 2) || ok(4, 2)：区间3或4在区间2的右侧
两个条件都满足则Team 2获胜
 *
*时间复杂度：O(1)
空间复杂度：O(1)
 *
* c[1]: [a[1], b[2]]
c[2]: [a[2], b[1]]
c[3]: [a[3], b[4]]
c[4]: [a[4], b[3]]
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

struct { int a, b; } c[10];

bool ok(const int i, const int j) {//判断不重叠
    if (c[i].a > c[j].b && c[i].b > c[j].a) return true;
    return false;
}

int main() {
    fast;
    int a[9], b[9];
    for (int i = 1; i <= 4; ++i) cin >> a[i] >> b[i];
    c[1].a = a[1]; c[1].b = b[2];
    c[2].a = a[2]; c[2].b = b[1];
    c[3].a = a[3]; c[3].b = b[4];
    c[4].a = a[4]; c[4].b = b[3];
    int g = 0;
    if ((ok(1, 3) && ok(1, 4)) || (ok(2, 3) && ok(2, 4))) g = 1;
    else if ((ok(3, 1) || ok(4, 1)) && (ok(3, 2) || ok(4, 2))) g = 2;
    if (!g) cout << "Draw\n"; else cout << "Team " << g << '\n';
    return 0;
}