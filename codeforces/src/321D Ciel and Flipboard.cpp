//
// Created by Psy.C on 2026/1/8.
//
/**
* b[N][N]：工作矩阵（二进制矩阵） 存储0或1的值
a[N][N]：输入的数值矩阵
 *
* calc函数：计算2×2子矩阵的贡献
d：左上角位置的值
通过异或运算填充2×2子矩阵的其他位置：
b[x+m][y] = b[x][y]^b[m][y]：利用已知的行约束
b[x][y+m] = b[x][y]^b[x][m]：利用已知的列约束
b[x+m][y+m] = b[x+m][y]^b[x+m][m]：利用已知的行约束
 *get_mx函数：计算2×2子矩阵的最大贡献（尝试左上角为0和1两种情况）
 *
*modify函数：修改第k列第m行的值为d，并计算整列的贡献
设置b[m][k] = d和b[m][k+m] = d^b[m][m]
计算第m行的贡献
遍历其他行，累加每行2×2子矩阵的最大贡献
 *maxx函数：对第k列，尝试第m行第k列为0或1，返回最大贡献
 *
*solve函数：基于当前第一列的设置，计算整体最优解
通过异或关系填充右下角区域
计算第m列的贡献
计算其他列的最大贡献
 *
 *b[i+1][j+1] = b[i][j] ^ b[i][j+1] ^ b[i+1][j]
*b[i+m][m] 是我们要计算的位置（右下角）
b[i][m] 是已知值（左下角）
b[m][m] 是已知值（右上角）
*b[x+m][y]：已知的右下角位置的列值
b[x+m][m]：已知的第m列的行值
b[x+m][y+m]：要计算的右下角位置
 *
 *
*calc函数：计算2×2子矩阵的贡献，参数为起始位置(x,y)和左上角值d
int ans = 0; b[x][y] = d;：初始化结果为0，设置左上角位置为d
ans += get(x, y); b[x+m][y] = b[x][y]^b[m][y];：
计算左上角的贡献
根据约束条件设置右下角位置的值
ans += get(x+m, y); b[x][y+m] = b[x][y]^b[x][m];：
计算左下角的贡献
设置右上角位置的值
ans += get(x, y+m); b[x+m][y+m] = b[x+m][y]^b[x+m][m];：
计算右上角的贡献
设置右下角位置的值
ans += get(x+m, y+m);：计算右下角的贡献
return ans;：返回2×2子矩阵的总贡献
 *
*modify函数：修改第k列第m行为d，计算该列的总贡献
b[m][k] = d; b[m][k+m] = d^b[m][m];：设置第m行第k列和第k+m列的值
ans += get(m, k) + get(m, k + m);：计算第m行第k列和第k+m列的贡献
for (int i = 1; i < m; ++i) ans += get_mx(i, k);：遍历1到m-1行，累加每行的最大贡献
return ans;：返回该列的总贡献
 *
*solve函数：基于当前第一列设置，计算整体最优解
for (int i = 1; i < m; ++i) b[i+m][m] = b[i][m]^b[m][m];：根据约束条件填充右下角区域
for (int i = 1; i <= n; ++i) ans += get(i, m);：计算第m列的总贡献
for (int i = 1; i < m; ++i) ans += maxx(i);：计算前m-1列的最大贡献
return ans;：返回总贡献
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 50
#define inf (0x7fffffff>>1)//2^30-1   2^31-1右移一位
using namespace std;

int sgn(const int a) { return !a ? 1 : -1; }//a为0，返回1；否则返回-1

int n, m, b[N][N], a[N][N];
int get(const int x, const int y) { return sgn(b[x][y]) * a[x][y]; }//根据b矩阵的值调整a矩阵的符号

int calc(const int x, const int y, const int d) {
    int ans = 0; b[x][y] = d;
    ans += get(x, y); b[x][y+m] = b[x][y]^b[x][m];
    ans += get(x, y+m); b[x+m][y] = b[x][y]^b[m][y];
    ans += get(x+m, y); b[x+m][y+m] = b[x+m][y]^b[x+m][m];
    ans += get(x+m, y+m);
    return ans;
}
int get_mx(const int x, const int y) { return max(calc(x, y, 0), calc(x, y, 1)); }

int modify(const int k, const int d) {
    b[m][k] = d; b[m][k+m] = d^b[m][m];
    int ans = 0;
    ans += get(m, k) + get(m, k + m);
    for (int i = 1; i < m; ++i) ans += get_mx(i, k);
    return ans;
}
int maxx(const int k) { return max(modify(k, 0), modify(k, 1)); }

int solve() {
    for (int i = 1; i < m; ++i) b[i+m][m] = b[i][m]^b[m][m];
    int ans = 0;
    for (int i = 1; i <= n; ++i) ans += get(i, m);
    for (int i = 1; i < m; ++i) ans += maxx(i);
    return ans;
}

int main() {
    fast;
    cin >> n; m = (n + 1)>>1;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) cin >> a[i][j];
    int ans = -inf;
    for (int s = 0; s < (1<<m); ++s) {//枚举所有可能的第一列状态（2^m种）
        for (int i = 1; i <= m; ++i) b[i][m] = (s>>(i-1))&1;//提取s的第(i-1)位
        ans = max(ans, solve());//对每种状态计算最优解，更新全局最大值
    }
    cout << ans << '\n';
    return 0;
}