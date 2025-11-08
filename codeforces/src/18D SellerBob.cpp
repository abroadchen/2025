//
// Created by Psy.C on 2025/9/17.
//
/*
*maxn=5010: 最大数组大小
f[maxn]: 存储2的幂次的高精度数组，f[i]表示2^i
dp[maxn]: 动态规划数组，dp[i]表示处理前i个事件后的最大收益（高精度）
n: 事件总数
k: 临时变量，存储当前事件的容量值
pre[maxn]: 记录每种容量最后一次获得的时间点
str[10]: 临时字符串，存储事件类型("win"或"sell")
 *
 *
*高精度乘法函数：
将高精度数A乘以整数b
t是进位变量
从低位到高位逐位计算，处理进位
结果C按低位到高位存储（个位在前）
 *
*初始化函数：
f[0] = 1 (2^0 = 1)
递推计算f[i] = f[i-1] * 2 = 2^i
预计算2^0到2^2000的所有值
 *
 *
 *
*如果是"sell"事件且之前获得过该容量的存储条：
计算tmp = dp[pre[k]] + f[k]：表示在pre[k]时刻的状态基础上卖出容量k的存储条
比较tmp和当前dp[i]的大小：
如果tmp位数更多，说明tmp更大，更新dp[i]
如果位数相同，从最高位开始比较，找到第一个不同的位，如果tmp该位更大则更新
 *
 *
 *
 *
 *
 *
 *
 */

#include <cstdio>
#include <vector>
using namespace std;
static const int maxn=5010;
vector<int> f[maxn], dp[maxn];
int n, k, pre[maxn];
char str[10];


vector<int> mul(vector<int>& A, int b) {
    vector<int> C;
    for (int i = 0, t = 0; i < A.size() || t; ++i) {
        if (i < A.size()) t += A[i] * b;
        C.push_back(t % 10);
        t /= 10;
    }
    return C;
}


void init() {
    f[0].push_back(1);
    for (int i = 1; i <= 2000; ++i)
        f[i] = mul(f[i - 1], 2);
}

vector<int> add(vector<int>& A, vector<int>& B) {
    vector<int> C;
    for (int i = 0, t = 0; i < A.size() || i < B.size() || t; ++i) {
        if (i < A.size()) t += A[i];
        if (i < B.size()) t += B[i];
        C.push_back(t % 10);
        t /= 10;
    }
    return C;
}



int main() {

    scanf("%d", &n); init();
    dp[0].push_back(0);

    for (int i = 1; i <= n; ++i) {
        scanf("%s%d", str, &k);
        dp[i] = dp[i - 1];
        if (str[0] == 'w') pre[k] = i;
        else if (pre[k]) {
            vector<int> tmp = add(dp[pre[k]], f[k]);
            if (tmp.size() > dp[i].size()) dp[i] = tmp;
            else if (tmp.size() == dp[i].size()) {
                int k = tmp.size() - 1;
                while (k > 0 && tmp[k] == dp[i][k]) k--;
                if (tmp[k] > dp[i][k]) dp[i] = tmp;
            }
        }
    }

    for (int i = dp[n].size() - 1; i >= 0; --i) printf("%d", dp[n][i]);
    printf("\n");
    return 0;
}