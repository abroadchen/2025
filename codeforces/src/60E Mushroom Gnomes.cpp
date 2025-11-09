//
// Created by Psy.C on 2025/10/27.
//
/*
 *定义M为2×2矩阵类型（二维long long数组）
*n: 数组长度
p: 模数
x, y: 操作参数
 *
 *矩阵乘法函数，计算a = a × b
 *标准的2×2矩阵乘法实现，结果存储在临时矩阵c中
 *将结果复制回矩阵a，并对p取模
 *
 *矩阵快速幂函数，计算a^k
 *初始化单位矩阵b
*如果k的最低位为1，则b = b × a
a = a × a
k右移一位
 *将结果复制回矩阵a
 *
 *循环读取输入直到文件结束（~用于检查scanf返回值是否非负）
*mn: 最小值（第一个元素）
mx: 最大值（最后一个元素）
smx: 次大值（倒数第二个元素）
sum: 总和，初始化为0
 *
*每个数对p取模
累加和sum（带模运算）
记录第一个、倒数第二个和最后一个元素
 *如果只有一个元素，直接输出该元素
 *
 *构造变换矩阵A并计算A^(x-1)
 *计算系数a和b
 *根据公式更新sum值
 *重新构造矩阵A并计算A^x
 *更新mx值
 *
 *如果y为0，设置a和b为1
 *否则重新构造矩阵并计算相关系数
 *最后一次更新sum并输出结果
 */
#include <cstdio>
#include <algorithm>
#define rep(i, n) for (int i = 0; i < (n); ++i)
using namespace std;

typedef long long ll;
typedef ll M[2][2];

int n, p;
ll x, y;

void mul(M& a, M b) {
    M c;
    rep(i,2) rep(j,2) {
        c[i][j] = 0;
        rep(k,2) c[i][j] += a[i][k] * b[k][j];
    }
    rep(i,2) rep(j,2) a[i][j] = c[i][j] % p;
}

void pow_mul(M& a, ll k) {
    M b;
    b[0][0] = b[1][1] = 1;
    b[0][1] = b[1][0] = 0;
    while (k) {
        if (k & 1) mul(b, a);
        mul(a, a);
        k >>= 1;
    }
    rep(i,2) rep(j,2) a[i][j] = b[i][j];
}

int main() {

    while (~scanf("%d%lld%lld%d", &n, &x, &y, &p)) {
        int mn, mx, smx, sum(0);
        for (int i = 1; i <= n; ++i) {
            int tmp; scanf("%d", &tmp);
            tmp %= p; sum += tmp;
            if (sum >= p) sum -= p;
            if (i == 1) mn = tmp;
            if (i == n - 1) smx = tmp;
            if (i == n) mx = tmp;
        }
        if (n == 1) printf("%d\n", mn);
        else {
            if (x == 0) swap(x, y);
            M A;
            A[0][0] = A[0][1] = 1, A[1][0] = 0, A[1][1] = 3 % p;
            pow_mul(A, x - 1);
            int a = (A[0][0] + A[0][1] * 3 % p + 1) % p,
            b = A[1][1] * 3 % p;
            sum = ((ll)a * (mn + mx) % p + (ll)((sum - mn - mx) % p + p) % p * b % p) % p;
            A[0][0] = A[0][1] = A[1][0] = 1, A[1][1] = 0;
            pow_mul(A, x);
            a = A[0][0], b = A[1][0];
            mx = ((ll)a * mx % p + (ll)b * smx % p) % p;
            if (y == 0) a = 1, b = 1;
            else {
                A[0][0] = A[0][1] = 1, A[1][0] = 0, A[1][1] = 3 % p;
                pow_mul(A, y - 1);
                a = (A[0][0] + A[0][1] * 3 % p + 1) % p,
                b = A[1][1] * 3 % p;
            }
            sum = ((ll)a * (mn + mx) % p + (ll)((sum - mn - mx) % p + p) % p * b % p) % p;
            printf("%d\n", sum);
        }
    }
    return 0;
}