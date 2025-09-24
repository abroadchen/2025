//
// Created by Psy.C on 2025/9/24.
//
/*
*g[N][N]：存储网格字符的二维数组
col[N][N]：标记每个位置属于哪个连通块
sf[M], pf[M]：后缀/前缀数组用于优化计算
obj[M]：存储连通块的边界信息{上,下,左,右}
itvs[M]：存储区间信息{左边界,右边界,类型}
 *
*cmp：比较函数，按左边界和右边界排序连通块
intersect：判断两个区间是否相交
 *
 *
 *
*双重循环遍历所有可能的行区间[p,q]
对于每个行区间，筛选出与之相关的连通块：
完全包含在[p,q]区间内的连通块，标记类型为1
与[p,q]区间相交的连通块，标记类型为0
 *
*计算前缀最大值数组pf和后缀最小值数组sf
用于快速查询区间内的最大右边界和最小左边界
 *
*cl：左侧可扩展的宽度
cr：右侧可扩展的宽度
cl * cr：以当前连通块为核心能形成的矩形数量
 *
 *
 */
#include <iosfwd>
#include <iostream>
#include <array>
#include <algorithm>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
using namespace std;
const int N = 1024, M = 96;
char g[N][N];
int col[N][N], sf[M], pf[M];
array<int, 4> obj[M];
array<int, 3> itvs[M];

bool cmp(const array<int, 4>& a, const array<int, 4>& b) {
    return make_pair(a[2], a[3]) < make_pair(b[2], b[3]);
}
bool intersect(int l1, int r1, int l2, int r2) {
    return max(l1, l2) <= min(r1, r2);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, k, cur(0); cin >> n >> m >> k;
    rep (i, 1, n) rep (j, 1, m) cin >> g[i][j];
    rep (i, 1, n) rep (j, 1, m) if (g[i][j] == '*' && !col[i][j]) {
        ++cur;
        obj[cur] = {i, 0, j, 0};
        for (int k = i; k <= n && g[k][j] == '*'; ++k)
            for (int l = j; l <= m && g[k][l] == '*'; ++l) {
                col[k][l] = cur;
                obj[cur][1] = k;
                obj[cur][3] = l;
            }
    }
    sort(obj + 1, obj + k + 1, cmp);

    long long ans = 0;
    int cl, cr, reach;

    rep (p, 1, n) rep (q, p, n) {
        cur = 0;
        rep (i, 1, k) {
            if (p <= obj[i][0] && obj[i][1] <= q)
                itvs[++cur] = {obj[i][2], obj[i][3], 1};
            else if (intersect(p, q, obj[i][0], obj[i][1]))
                itvs[++cur] = {obj[i][2], obj[i][3], 0};
        }
        int tmp(0); sf[cur + 1] = m + 1;
        rep (i, 1, cur) pf[i] = max(pf[i - 1], itvs[i][1]);
        for (int i = cur; i; --i) sf[i] = min(sf[i + 1], itvs[i][0]);
        rep (i, 1, cur) if (itvs[i][2]) {
            reach = itvs[i][1];
            for (int j = i; j > i - 3 && itvs[j][2]; --j) {
                cl = max(0, itvs[j][0] - pf[j - 1]);
                reach = max(reach, itvs[j][1]);
                cr = max(0, sf[i + 1] - reach);
                ans += cl * cr;
                tmp += cl * cr;
            }
        }
    }
    cout << ans;
    return 0;
}