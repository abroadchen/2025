//
// Created by Psy.C on 2026/3/12.
//
/**
N为105（数组大小），M为20（字符串长度）
k: 查询数量
q[N][5]: 存储查询条件的二维数组，每行存储5个元素

验证在区间[l,r]内能否安全配对(a,b)
遍历所有限制条件
如果查询限制的是a和b之间的关系且关系为"<"或">"，返回false
如果查询中的第一个数是a或b，且第二个数在区间[l,r]内
如果关系是">=" "=" "<="中的任一种，返回false
如果查询中的第二个数是a或b，且第一个数在区间[l,r]内
如果关系是"<=" "=" "<"中的任一种，返回false
如果没有违反任何限制条件，返回true

n: 问题规模参数
s: 临时字符数组，用于读取符号
dp: 动态规划数组，dp[i][j]表示区间[i,j]内合法方案数
读取n（问题规模）和k（约束数量）
读取k个约束条件
将符号转换为数字编码：
< → 0
<= → 1
= → 2
>= → 3
> → 4

外层循环：枚举区间长度l（必须是偶数，因为要配对）
内层循环：枚举区间起始位置i
计算区间结束位置j，初始化dp[i][j]=0
当区间长度为2时（基础情况）
检查配对(i,j)是否满足所有约束条件
如果满足，方案数设为1
当区间长度大于2时，考虑三种配对方案：
配对(i,i+1)，剩余区间[i+2,j]
配对(j-1,j)，剩余区间[i,j-2]
配对(i,j)，剩余区间[i+1,j-1]
每种方案都要通过check验证是否符合约束条件
输出整个区间[1,2n]内的合法方案总数

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 105, M = 20;

int k, q[N][5];
bool check(int a, int b, int l, int r) {
    for (int i = 0; i < k; ++i) {
        if ((q[i][0] == a && q[i][1] == b) ||
            (q[i][0] == b && q[i][1] == a)) {
            if (q[i][2] == 0 || q[i][2] == 4)
                return false;
        } else if (q[i][0] == a || q[i][0] == b) {
            if (q[i][1] >= l && q[i][1] <= r)
                if (q[i][2] >= 2)
                    return false;
        } else if (q[i][1] == a || q[i][1] == b) {
            if (q[i][0] >= l && q[i][0] <= r)
                if (q[i][2] <= 2)
                    return false;
        }
    }
    return true;
}

int n;
char s[M];
ll dp[N][N];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 0; i < k; ++i) {
        cin >> q[i][0] >> s >> q[i][1];
        if (s[0] == '<' && strlen(s) == 1) q[i][2] = 0;
        else if (s[0] == '<') q[i][2] = 1;
        else if (s[0] == '=') q[i][2] = 2;
        else if (s[0] == '>' && strlen(s) == 2) q[i][2] = 3;
        else q[i][2] = 4;
    }
    for (int l = 2; l <= 2*n; l += 2)
        for (int i = 1; i <= 2*n-l+1; ++i) {
            int j = i + l - 1; dp[i][j] = 0;
            if (l == 2) {
                if (check(i, j, i+1, j-1))
                    dp[i][j] = 1;
            } else {
                if (check(i, i+1, i+2, j))
                    dp[i][j] += dp[i+2][j];
                if (check(j-1, j, i, j-2))
                    dp[i][j] += dp[i][j-2];
                if (check(i, j, i+1, j-1))
                    dp[i][j] += dp[i+1][j-1];
            }
        }
    cout << dp[1][2*n] << '\n';
    return 0;
}