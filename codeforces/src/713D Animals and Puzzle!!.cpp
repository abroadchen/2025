//
// Created by Psy.C on 2026/4/21.
//
/**
lg[N];  // 存储以2为底的对数，lg[i]表示log2(i)
n, m;      // 矩阵的行数和列数
f[N][N][M][M];  // 四维数组，用于二维ST表（Sparse Table）存储区间最大值

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+7, M = 10;

int lg[N], n, m, f[N][N][M][M];
void ST() {
    //预计算每个数字的以2为底的对数
    for (int i = 2; i <= N-6; ++i) lg[i] = lg[i >> 1] + 1;
    //对每行进行一维ST表预处理（按列方向）
    for (int i = 1; i <= n; ++i) {
        for (int k = 1; 1<<k <= m; ++k)//k从1开始，直到2^k不超过m
            for (int j = 1; j <= m-(1<<k)+1; ++j)//j不能超过边界
                f[i][j][0][k] = max(f[i][j][0][k-1],//当前区间左半部分的最大值
                    f[i][j+(1<<(k-1))][0][k-1]);//当前区间右半部分的最大值
    }
    //对整个矩阵进行二维ST表预处理（按行方向）
    for (int k1 = 1; 1<<k1 <= n; ++k1)//k1表示行方向的区间长度参数
        for (int i = 1; i <= n-(1<<k1)+1; ++i)//i不能超过边界
            for (int k2 = 0; 1<<k2 <= m; ++k2)//k2表示列方向的区间长度参数
                for (int j = 1; j <= m-(1<<k2)+1; ++j)//j不能超过边界
                    f[i][j][k1][k2] = max(f[i][j][k1-1][k2],//左上角块的最大值
                        f[i+(1<<(k1-1))][j][k1-1][k2]);//左下角块的最大值
}
int get(int x1, int y1, int x2, int y2) {
    int k1 = lg[x2-x1+1], k2 = lg[y2-y1+1];//覆盖区间所需的最小幂次
    x2 = x2 - (1<<k1) + 1, y2 = y2 - (1<<k2) + 1;//调整右下角坐标
    return max(max(f[x1][y1][k1][k2], f[x1][y2][k1][k2]),//左上和右上的最大值
        max(f[x2][y1][k1][k2], f[x2][y2][k1][k2]));//左下和右下的最大值
}

int q;
int main() {
    fast;
    cin >> n >> m;
    //计算以当前位置为右下角的最大全1正方形边长
    for (int i = 1; i <= n; ++i)
        for (int j = 1, x; j <= m; ++j) {
            cin >> x;//当前格子的值
            if (x) f[i][j][0][0] = min(f[i-1][j-1][0][0],//左上角的最大边长
                min(f[i-1][j][0][0], f[i][j-1][0][0])) + 1;//上方和左方的最大边长中的最小值+1
            else f[i][j][0][0] = 0;//无法构成全1正方形
        }
    ST();
    cin >> q;
    while (q--) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        //二分查找最大可容纳的正方形边长
        int l = 0, r = min(x2 - x1, y2 - y1) + 1, ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (get(x1+mid-1, y1+mid-1, x2, y2) >= mid)//是否存在边长为mid的全1正方形
                l = mid + 1, ans = mid;
            else r = mid - 1;
        }
        cout << ans << '\n';
    }
    return 0;
}