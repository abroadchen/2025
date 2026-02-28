//
// Created by Psy.C on 2026/2/28.
//
/**
计算当前状态(i,j)在下一轮的概率贡献
(get(i-1) + get(j-i-1) + get(n-j))：不改变这对位置的区间数
这些区间是：[1,i-1]、[i+1,j-1]、[j+1,n]范围内的所有子区间

处理翻转导致(i,j)位置改变的情况
k是偏移量，翻转区间包含[i,i+k]和[j,j+k]
(1-dp[i+k][j+k])：原来不是逆序对的变成逆序对
min(min(i,i+k),n-max(j,j+k)+1)：符合条件的翻转区间数

处理另一种翻转情况，其中一个元素位置改变
dp[i+k][j]：考虑(i+k,j)这对元素的逆序关系
处理第三种翻转情况，另一个元素位置改变
dp[i][j+k]：考虑(i,j+k)这对元素的逆序关系

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101, M = 900;

inline double get(const int u) {//1到u的和
    return 1.*u*(u+1)/2;
}

int n, m, num[N];
double dp[N][N], tmp[N][N], sum, ans;
int main() {
    fast;
    cin >> n >> m; sum = 1.*n*(n+1)/2;//总的区间数
    for (int i = 1; i <= n; ++i) cin >> num[i];
    m = min(m, M);//将m限制在M以内
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) dp[i][j] = 1;
    for (int t = 1; t <= m; ++t) {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) tmp[i][j] = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j) {
                tmp[i][j] = dp[i][j]*(get(i-1) + get(j-i-1) + get(n-j))/sum;
                for (int k = 1 - i; k + j <= n; ++k)
                    tmp[i][j] += (1-dp[i+k][j+k])*min(min(i,i+k),n-max(j,j+k)+1)/sum;
                for (int k = 1 - i; k < j-i; ++k)
                    tmp[i][j] += dp[i+k][j]*min(min(i,i+k),j-max(i,i+k))/sum;
                for (int k = i-j+1; k+j <= n; ++k)
                    tmp[i][j] += dp[i][j+k]*min(min(j,j+k)-i,n-max(j,j+k)+1)/sum;
            }
        memcpy(dp, tmp, sizeof(tmp));
    }
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            if (num[i] > num[j]) ans += dp[i][j];
            else ans += 1 - dp[i][j];
        }
    printf("%.10f", ans);
    return 0;
}