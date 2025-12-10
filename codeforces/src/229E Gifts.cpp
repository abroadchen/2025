//
// Created by Psy.C on 2025/12/10.
//
/*
*n: 需要选取的人数
m: 组数
i, j: 循环变量
k[N]: 存储每组人数的数组
a[N][N]: 存储每个组员编号的二维数组
val[N]: 存储所有成员编号的一维数组
tot: 记录总人数并初始化为0
 *
 *取排序后的第n大的数值v(即第n个被选中的成员编号)
*cnt[N]: 每个小组中大于v的成员数量
is[N]: 标记哪些小组包含等于v的成员
ry: 记录有多少个小组包含等于v的成员
rm: 记录总共等于v的成员数量
 *
 *
 *
 *从第n位向前统计等于第n大值的成员总数rm
*c[N][N]: 用于计算组合数
f[N][N]: 动态规划状态表
 *
*第一行和对角线都设为1 (C(i,0)=1 和 C(i,i)=1)
利用组合公式 C(i,j) = C(i-1,j) + C(i-1,j-1) 填充其余位置
*计算总的符合条件的选择方案数t=C(ry,rm)
初始化动态规划初始状态f[0][0]=1
*遍历每个小组i和可能的选择数j
如果当前小组包含目标值且j>0，则从前一状态转移(f[i-1][j-1]/C(k[i], cnt[i]+1))//在第i组中选中目标成员的条件概率
无论是否选择当前小组的目标成员，都要考虑不选择的情况(f[i-1][j]/C(k[i], cnt[i]))//不考虑当前第i组时的状态
 *在第i组中不选中目标成员的条件概率
 *
 *
*k[i]: 第i组的总人数
cnt[i]: 第i组中大于目标值的成员数量
cnt[i]+1: 选择这些成员再加上一个等于目标值的成员
 */
#include <iomanip>
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1050
using namespace std;

int main() {
    fast;
    int n, m, i, j, k[N], a[N][N], val[N], tot=0;
    cin>>n>>m;
    for (i = 1; i <= m; ++i) {
        cin >> k[i];
        for (j = 1; j <= k[i]; ++j) {
            cin>>a[i][j];
            val[++tot] = a[i][j];
        }
    }
    sort(val + 1, val + 1 + tot, [](const int x, const int y) {
        return x > y;
    });
    const int v = val[n];
    int cnt[N], is[N], ry = 0, rm = 0;
    for (i = 1; i <= m; ++i) for (j = 1; j <= k[i]; ++j) {
        if (a[i][j] > v) cnt[i]++;
        if (a[i][j] == v) { ry++; is[i] = 1;}
    }
    for (i = n; i >= 1; --i) { if (val[i] == val[n]) rm++; else break; }
    double c[N][N], f[N][N];
    for (i = 0; i <= tot; ++i) c[i][0] = c[i][i] = 1;
    for (i = 1; i <= tot; ++i) for (j = 1; j <= i; ++j) {
        c[i][j] = c[i-1][j] + c[i-1][j-1];
    }
    const double t = c[ry][rm]; f[0][0] = 1;
    for (i = 1; i <= m; ++i) for (j = 0; j <= rm; ++j) {
        if (is[i] && j) f[i][j] = f[i-1][j-1]/c[k[i]][cnt[i]+1];
        f[i][j] += f[i-1][j]/c[k[i]][cnt[i]];
    }
    cout << fixed << setprecision(9) << f[m][rm]/t << '\n';
    return 0;
}