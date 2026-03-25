//
// Created by Psy.C on 2026/3/26.
//
///O(log n)
/**
a[i][j] 代表：在第 i 层，成功到达第 j 个状态的概率
具体来说：
a[1][1] = p：在第1层，达到第1个状态的概率是p
a[1][2] = 1-p：在第1层，达到第2个状态的概率是1-p
在递推过程中，a[i][j] 会累积前面所有可能路径到达当前状态的概率
经过归一化后，a[i][j] 表示在第i层处于状态j的条件概率
b[i][j] 代表：在第 i 层，从第 j 个状态转移到第1个状态的概率
与数组a类似，但专门追踪返回状态1的概率
b[i][2] = 1-p：在第i层，从状态2转移到状态1的概率
在递推中，b数组追踪特定类型的转移概率
f[i][j] 代表：在第 i 层处于第 j 个状态下，完成整个过程的期望步数
f[1][1] = 1：在第1层状态1，期望还需要1步
f[1][2] = 2：在第1层状态2，期望还需要2步
f[i][j] = Σ(f[i-1][k] * a[i-1][k]) / Σ(a[i-1][k]) + j
当前期望 = 下一层各状态期望的加权平均 + 当前层数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int M = 51;

struct node {
    double mat[M][M];
    double *operator[](int x) { return mat[x]; }//mat[i]访问第i行
    void init() { memset(mat, 0, sizeof(mat)); }//全零矩阵
    friend node operator*(node x, node y) {
        node z{}; z.init();
        for (int k = 0; k <= M-1; ++k)
            for (int i = 0; i <= M-1; ++i)
                for (int j = 0; j <= M-1; ++j)
                    z[i][j] += x[i][k] * y[k][j];//矩阵乘法
        return z;
    }
} ba, ret;

void ksm(node &res, node bs, int k) {
    while (k) {
        if (k&1) res = res * bs;
        bs = bs * bs;//指数翻倍
        k >>= 1;
    }
}

int n;
double p, a[M][M], b[M][M], f[M][M];///不同的概率和期望值
int main() {
    fast;
    cin >> n >> p; p /= 1000000000.;//将p转换为小数形式
    a[1][1] = p, a[1][2] = b[1][2] = 1 - p;//基础状态
    for (int i = 2; i <= M-1; ++i) {
        a[i][1] = p; a[i][2] = b[i][2] = 1 - p;//从第2层开始设置基础概率
        for (int j = 2; j <= M-1; ++j) {
            a[i][j] += a[i][j-1] * a[i-1][j-1];
            b[i][j] += b[i][j-1] * a[i-1][j-1];
        }
    }
    //归一化处理
    for (int i = M-1; i >= 1; --i)
        for (int j = 1; j <= M-1; ++j) {
            a[i][j] = a[i][j] * (1. - a[i-1][j]);//更新
            b[i][j] = b[i][j] * (1. - a[i-1][j]);
        }
    f[1][1] = 1; f[1][2] = 2;//期望值
    for (int i = 2; i <= M-1; ++i) {
        for (int j = 2; j <= M-1; ++j) {
            double t = 0;
            for (int k = 1; k < j; ++k) {
                f[i][j] += f[i-1][k] * a[i-1][k];//累加转移期望
                t += a[i-1][k];//累加概率
            }
            f[i][j] = f[i][j]/t + j;//当前期望
        }
        double t = 0;
        for (int k = 2; k <= M-1; ++k) {
            f[i][1] += f[i-1][k] * b[i-1][k];
            t += b[i-1][k];
        }
        f[i][1] = f[i][1]/t + 1;
    }
    //处理小规模情况
    if (n <= M-1) {
        double ans = 0;
        for (int i = 1; i <= M-1; ++i)
            ans += f[n][i] * a[n][i];
        printf("%.15lf\n", ans);
        return 0;
    }
    //大规模情况
    ba[0][0] = 1;//单位元 转移矩阵的第一个元素
    for (int i = 2; i <= M-1; ++i) {
        double t = 0;
        for (int j = 1; j <= i-1; ++j) t += a[M-1][j], ba[j][i] += a[M-1][j];
        for (int j = 1; j <= i-1; ++j) ba[j][i] /= t;//归一化
        ba[0][i] = i;//设置状态值
    }
    double t = 0;
    for (int i = 2; i <= M-1; ++i) t += b[M-1][i], ba[i][1] += b[M-1][i];
    for (int i = 2; i <= M-1; ++i) ba[i][1] /= t;
    ba[0][1] = 1; ret[0][0] = 1;//初始状态
    for (int i = 1; i <= M-1; ++i) ret[0][i] = f[M-1][i];//初始向量
    ksm(ret, ba, n-(M-1));
    double ans = 0;
    for (int i = 1; i <= M-1; ++i)
        ans += ret[0][i] * a[M-1][i];
    printf("%.15lf\n", ans);
    return 0;
}