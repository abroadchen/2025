//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
bs[i] 是第 i 行（方程）。bs[x][y]=1 记录边（对称）。
deg[i] 用异或统计度是否为奇数。
对奇度点，把 bs[i][i]（对角线/自身项）和 bs[i][n+1]（右端常数）都置 1。这就构造出一个"某某条件"的线性方程组（每行为一个约束）
上三角到对角化的标准高斯消元，但因为是在 GF(2) 上，所有运算都是 ^（异或）‍：找第 i 列的主元行并交换；再对其它所有行，若该行第 i 位为 1，就用第 i 行异或掉（bs[j] ^= bs[i]）消元。处理完后 bs[i] 变成简化的行阶梯/行最简形。

⚠️ 这里有个疑似 bug：for (int j = i; j <= n; j++) if (bs[j][i]) 是在找主元，但按高斯消元只应处理 j >= i 的行；同时对 i != j 的所有行做消元（包括上面已消过的行），这其实是把整个矩阵都做对角化。若第 i 列没有主元（全 0），bs[i] 保持原样，后面 bs[j][i] 可能仍为 1 却无法消掉——对自由变量处理不完整。
bs[i][n+1] 是第 i 个未知数的解（方程右边/常数项），+1 把 0/1 映射成 1/2 输出（典型用于"两种颜色/两种取值"）。
ans = max(bs[i][n+1]+1) —— 像在求所有解里某个最大值（可能是要最大化某种"分组数 / 集合大小"）。
最后输出每个点取值，并 reset() 清空 bitset、清零 deg 以便下一组
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2005;

int T, n, m, x, y, deg[N];
bitset<N> bs[N];
int main() {
    fast;
    cin >> T;
    rep(o,T) {
        cin >> n >> m;
        rep(i,m) cin >> x >> y, bs[x][y] = bs[y][x] = 1, deg[x]^=1, deg[y]^=1;
        rep(i,n) if (deg[i]) bs[i][i] = bs[i][n+1] = 1;
        rep(i,n) {
            for (int j = i; j <= n; j++)
                if (bs[j][i]) { swap(bs[j], bs[i]); break; }//找主元行
            rep(j,n) {
                if (i == j) continue;
                if (bs[j][i]) bs[j] ^= bs[i];//用第 i 行消其余行
            }
        }
        int ans = 0;
        rep(i,n) ans = max(ans, bs[i][n+1]+1);
        cout << ans << '\n';
        rep(i,n) cout << bs[i][n+1]+1 << ' ', bs[i].reset(), deg[i] = 0;
        cout << '\n';
    }
    return 0;
}