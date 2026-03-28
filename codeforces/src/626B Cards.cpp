//
// Created by Psy.C on 2026/3/27.
//
/**
z和y都为0
y和z都不为0
y>1且x不为0 z>1且x不为0

如果y和z都为0，返回true（只剩x）
如果y和z都不为0，返回true（y和z可以相互作用）
如果y>1且x存在，返回true（多余的y可以与x反应）
如果z>1且x存在，返回true（多余的z可以与x反应）

遍历字符串，统计每种颜色出现的次数
对每种颜色进行判断，看是否能满足条件，如果满足就输出该颜色
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1103;
bool ok(int x, int y, int z) {
    if ((!z&&!y)||(y&&z)||(y>1&&x)||(z>1&&x))
        return true;
    return false;
}

int n, r, g, b;
char s[N];
int main() {
    fast;
    cin >> n >> s;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'R') r++;
        if (s[i] == 'G') g++;
        if (s[i] == 'B') b++;
    }
    if (ok(b, g, r)) cout << 'B';
    if (ok(g, r, b)) cout << 'G';
    if (ok(r, g, b)) cout << 'R';
    return 0;
}