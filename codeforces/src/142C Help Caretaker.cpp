//
// Created by Psy.C on 2025/11/20.
//
/*
*读取网格尺寸x和y
定义四种五格拼图的位掩码模式
t: 状态空间大小
*模式a (L型):     模式b (镜像L型):
. . X            X . .
. X X            X X .
. X .            . X .

模式c (T型):     模式d (其他形状):
. X .            . X .
. X .            . X .
X X X            X X X
 *
*从右下角向左上角计算
i2, j2: 下一个要处理的位置
*mask: 当前状态的位掩码
mask2 = mask / 2: 移除最低位后的状态
!(mask&1): 当前位置未被占据时才能放置拼图
 *
*是否与已有拼图冲突（!(mask2&shape)）
是否在网格范围内
如果可以放置，则状态转移到mask2|shape并增加计数
 *输出从(0,0)位置开始且没有任何预占位置时的最大拼图数量
 *通过回溯DP过程构造具体的放置方案并输出
 *
 *O(x × y × 2^(2y+1))，其中状态数是指数级的，但由于y较小，实际可行
 */
#include <algorithm>
#include <iostream>
#define m(a,b,c,d) ((1<<(a))|(1<<(b))|(1<<(c))|(1<<(d)))
#define rep(i,n) for((i)=0;(i)<(int)(n);++(i))
using namespace std;

const int N = 10;
int dp[N][N][1<<19];
char ans[N][N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int x, y, i, j, mask; cin >> x >> y;
    int a = m(0,1,y,2*y), b = m(y-3,y-2,y-1,2*y-1),
        c = m(y-1,2*y-2,2*y-1,2*y), d = m(y-1,y,y+1,2*y-1),
        t = 1<<(2*y+1);
    for (i = x - 1; i >= 0; --i) for (j = y - 1; j >= 0; --j) {
        int i2 = i, j2 = j + 1;
        if (j2 == y) { i2++; j2 = 0; }
        rep(mask,t) {
            int mask2 = mask / 2;
            dp[i][j][mask] = max(dp[i][j][mask], dp[i2][j2][mask2]);
            if (!(mask&1)) {
                if (!(mask2&a) && i + 2 < x && j + 2 < y)
                    dp[i][j][mask] = max(dp[i][j][mask], dp[i2][j2][mask2|a] + 1);
                if (!(mask2&b) && i + 2 < x && j - 2 >= 0)
                    dp[i][j][mask] = max(dp[i][j][mask], dp[i2][j2][mask2|b] + 1);
                if (!(mask2&c) && i + 2 < x && j - 1 >= 0 && j + 1 < y)
                    dp[i][j][mask] = max(dp[i][j][mask], dp[i2][j2][mask2|c] + 1);
                if (!(mask2&d) && i + 2 < x && j + 2 < y)
                    dp[i][j][mask] = max(dp[i][j][mask], dp[i2][j2][mask2|d] + 1);
            }
        }
    }
    cout << dp[0][0][0] << '\n';
    rep(i,x) rep(j,y) ans[i][j] = '.'; i = 0; j = 0; mask = 0; char ch = 'A';
    while (dp[i][j][mask] > 0) {
        int i2 = i, j2 = j + 1;
        if (j2 == y) { i2++; j2 = 0; }
        int mask2 = mask / 2;
        if (dp[i][j][mask] == dp[i2][j2][mask2]) { i = i2; j = j2; mask = mask2; continue; }
        if (!(mask2&a) && i + 2 < x && j + 2 < y && dp[i][j][mask] == dp[i2][j2][mask2|a] + 1) {
            ans[i][j] = ans[i][j+1] = ans[i][j+2] = ans[i+1][j+1] = ans[i+2][j+1] = ch;
            i = i2; j = j2; mask = mask2|a; ch++; continue;
        }
        if (!(mask2&b) && i + 2 < x && j - 2 >= 0 && dp[i][j][mask] == dp[i2][j2][mask2|b] + 1) {
            ans[i][j] = ans[i+1][j-2] = ans[i+1][j-1] = ans[i+1][j] = ans[i+2][j] = ch;
            i = i2; j = j2; mask = mask2|b; ch++; continue;
        }
        if (!(mask2&c) && i + 2 < x && j - 1 >= 0 && j + 1 < y && dp[i][j][mask] == dp[i2][j2][mask2|c] + 1) {
            ans[i][j] = ans[i+1][j] = ans[i+2][j-1] = ans[i+2][j] = ans[i+2][j+1] = ch;
            i = i2; j = j2; mask = mask2|c; ch++; continue;
        }
        if (!(mask2&d) && i + 2 < x && j + 2 < y && dp[i][j][mask] == dp[i2][j2][mask2|d] + 1) {
            ans[i][j] = ans[i+1][j] = ans[i+1][j+1] = ans[i+1][j+2] = ans[i+2][j] = ch;
            i = i2; j = j2; mask = mask2|d; ch++; continue;
        }
    }
    rep(i,x) {
        rep(j,y) cout << ans[i][j];
        cout << '\n';
    }
    return 0;
}