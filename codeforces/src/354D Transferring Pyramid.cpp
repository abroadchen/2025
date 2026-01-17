//
// Created by Psy.C on 2026/1/17.
//
/**
* y: 当前行的有效范围
now = i&1: 当前行（0或1，滚动数组）
pre = now^1: 前一行（与now相反）
 *
*处理所有第一维坐标等于i的点
如果第二维坐标超出y范围，计入s[y+1]，否则计入对应位置
//如果纵坐标超出范围y，则使用y+1，否则使用原坐标
//++s[...]: 对相应位置计数器加1
 *计算s数组的后缀和
 *
*f[pre][j-1]：前一阶段的基础代价
j*(j+1)/2：位置相关的累积代价 //前j项自然数的和，即 1 + 2 + 3 + ... + j
2：转移操作的固定代价
s[j+1]*3：后续特殊点的处理代价 //在位置j+1及之后的特殊点数量（通过后缀和计算） 3每个特殊点的代价
 *
* n - r + 1：实际上表示从底行开始的行号
n - r + c：表示沿某条对角线的坐标
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define N 100005
#define inf 0x3f3f3f3f3f3f3f3f
#define ii pair<int, int>
using namespace std;

//更新x为x和y中的较小值
void minn(int& x, const int y) { x = x > y ? y : x; }

signed main() {
    fast;
    int n, k, f[2][N]; cin >> n >> k;
    const int h = min(n, static_cast<int>(sqrt(6*k)));//限制在n以内
    ii p[N];//存储变换后的坐标
    for (int i = 1, r, c; i <= k; ++i) {//k个点的行列坐标(r,c)
        cin >> r >> c;
        p[i] = {n - r + c, n - r + 1};
    }
    sort(p + 1, p + 1 + k);
    memset(f, 0x3f, sizeof f);
    int x = 1, s[N]; f[0][0] = 0;//x: 当前处理的p数组索引
    for (int i = 1; i <= n; ++i) {
        const int y = min(i, h), now = i&1, pre = now^1;
        for (int j = 0; j <= y + 1; ++j) f[now][j] = inf, s[j] = 0;
        for (; x <= k && p[x].first == i; ++x) ++s[p[x].second > y ?
            y+1 : p[x].second];
        for (int j = y; j >= 0; --j) s[j] += s[j + 1];
        f[now][0] = f[pre][0] + s[1] * 3;
        for (int j = 1; j <= y; ++j)//循环更新f[now][0]的最小值
            minn(f[now][0], f[pre][j - 1] +
                ((j * (j+1)>>1) + 2 + s[j + 1] * 3));
        for (int j = 1; j <= y; ++j)
            f[now][j] = f[now][j - 1], minn(f[now][j],
                f[pre][j - 1] + s[j + 1] * 3);
    }
    cout << f[n&1][0] << '\n';//根据n的奇偶性选择滚动数组的对应行
    return 0;
}