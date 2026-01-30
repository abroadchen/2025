//
// Created by Psy.C on 2026/1/30.
//
/**
 *矩阵大小n和障碍物数量m
* r[N]：记录被占用的行
c[N]：记录被占用的列
R = 0, C = 0：未被占用的行数和列数，初始化为0
x, y, z：临时变量
 *
*R += !r[i]：如果第i行未被占用(r[i]=0)，R增加1
C += !c[i]：如果第i列未被占用(c[i]=0)，C增加1
统计总的空行数R和空列数C
 *
*x = i * j：已占用的行列交叉点数量
y = i * (n - j)：已占行×未占列的数量
z = (n - i) * j：未占行×已占列的数量
 */
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2005
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    int r[N], c[N], R = 0, C = 0, x, y, z;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y;
        r[x] = c[y] = 1;//标记为已占用
    }
    for (int i = 1; i <= n; ++i) R += !r[i], C += !c[i];
    double f[N][N]; f[1][1] = 0;
    for (int i = 0; i <= R; ++i) for (int j = 0; j <= C; ++j) {
        if (!(i||j)) continue;//i和j都为0则跳过（跳过f[0][0]的情况）
        x = i * j, y = i * (n - j), z = (n - i) * j;
        f[i+1][j+1] = (x*f[i][j] + y*f[i][j+1] + z*f[i+1][j] +
            n*n) / (x + y + z);
    }
    cout << fixed << setprecision(8) << f[R+1][C+1] << '\n';
    return 0;
}