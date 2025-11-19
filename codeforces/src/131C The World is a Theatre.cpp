//
// Created by Psy.C on 2025/11/19.
//
/*
*初始化组合数表（杨辉三角/帕斯卡三角形）：
c[0][0] = 1（0选0的方式数为1）
对于每一行i（1到30）：
c[i][0] = 1（i选0的方式数为1）
对于每一列j（1到i）：c[i][j] = c[i-1][j] + c[i-1][j-1]
这是组合数的递推公式：C(i,j) = C(i-1,j) + C(i-1,j-1)
 *
 *~scanf() 等价于 scanf() != EOF，用于检查是否成功读取
*遍历i从4到n（至少选择4个n类物品）
计算j = t - i（需要从m类物品中选择的数量）
如果j超出范围（j > m 或 j < 1）则跳过
否则将 c[n][i] * c[m][j] 加到答案中
c[n][i]：从n个物品中选择i个的方式数
c[m][j]：从m个物品中选择j个的方式数
两者相乘：同时选择i个n类物品和j个m类物品的方式数
 */
#include <cstdio>
using namespace std;

typedef long long ll;
const int N = 31;
int n, m, t, i, j;
ll c[N][N];//存储组合数

int main() {
    c[0][0] = 1;
    for (i = 1; i <= 30; ++i) {
        c[i][0] = 1;
        for (j = 1; j <= i; ++j)
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    }
    while (~scanf("%d %d %d", &n, &m, &t)) {
        ll ans = 0;
        for (i = 4; i <= n; ++i) {
            j = t - i;
            if (j > m || j < 1) continue;
            ans += c[n][i] * c[m][j];
        }
        printf("%lld\n", ans);
    }
    return 0;
}