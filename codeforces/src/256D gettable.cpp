//
// Created by Psy.C on 2025/9/18.
//

#include <iostream>
using namespace std;

constexpr int N = (1<<8) + 7, mod = 777777777;

template<class T, class V>
void add(T& a, V b) { a += b; if (a >= mod) a -= mod; }

int table[9][(1 << 8) + 1];
int C[N][N];
int dp[N][N][N];

void getTable() {
    for(int i = 0; i < N; i++) {
        for(int j = C[i][0] = 1; j <= i; j++) {//初始化C[i][0]=1，然后计算C[i][j] (j从1到i)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    for(int l = 0; l < 9; l++) {//l从0到8进行循环，对应不同的问题规模
        const int n = 1 << l;//当前问题的规模
        memset(dp, 0, sizeof(dp));
        dp[0][0][0] = 1;
        for(int i = 0; i < n; i++) {//当前考虑的位置
            for(int j = 0; j <= n; j++) {//已经使用的元素数量
                for(int k = 0; k <= j; k++) {//某种计数状态
                    if(!dp[i][j][k]) continue;//如果当前状态值为0
                    for(int z = 0; z + j <= n; z++) {//下一步要添加的元素个数z
                        if(z == i + 1) add(dp[i + 1][j + z][k],
                            1LL * dp[i][j][k] * C[n - j][z] % mod);
                        else add(dp[i + 1][j + z][k + z],
                            1LL * dp[i][j][k] * C[n - j][z] % mod);
                    }
                }
            }
        }

        for(int k = 0; k <= n; k++) {
            table[l][k] = dp[n][n][k];//将最终的dp状态复制到结果表中
        }
    }
    printf("int table[9][(1 << 8) + 1] = {\n");
    for(int l = 0; l < 9; l++) {
        printf("{");
        printf("%d", table[l][0]);//输出第一个元素
        for(int i = 1; i <= (1 << 8); i++) {
            printf(", %d", table[l][i]);//输出剩余的元素
        }
        printf("}");
        if(l != 8) putchar(',');//除了最后一行，其他行末尾加逗号
        puts("");
    }
    printf("};\n");
}

int main() {
    getTable();
    return 0;
}