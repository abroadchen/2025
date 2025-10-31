//
// Created by Psy.C on 2025/10/31.
//
/*
// N: 字符串最大长度
// M: 字母表大小（26个英文字母）
// ti: 插入操作的代价
// td: 删除操作的代价
// tr: 替换操作的代价
// te: 交换相邻两个字符的操作代价
dp[i][j] 表示将字符串a的前i个字符转换为字符串b的前j个字符的最小代价
空字符串转换为空字符串代价为0
初始化第一列：将a的前i个字符删除为空字符串的代价
初始化第一行：将空字符串插入b的前i个字符的代价

初始化da数组为0，用于记录字符最近出现的位置
初始化db为0，用于记录当前字符在b中匹配的位置

如果当前字符相同，替换代价为0，否则为tr
获取字符b[j-1]在之前计算中最近一次出现在a中的位置
获取字符a[i-1]在b中最近一次匹配的位置
如果当前字符匹配，更新db为当前位置j，否则保持原值

// 1. 在a末尾插入b[j]字符
// 2. 删除a末尾字符
// 3. 替换a末尾字符为b[j]字符
特殊情况：如果找到了可以进行交换操作的位置
更新字符a[i-1]最新出现的位置为i
输出将字符串a完全转换为字符串b的最小代价
 */
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define rep(i, n) for (i = 1; i <= (n); ++i)
using namespace std;

const int N = 5000, M = 26;
int ti, td, tr, te,
i, j, n, m, dp[N][N], da[M], db,
ii, jj, d;
string a, b;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> ti >> td >> tr >> te >> a >> b;
    n = a.length(), m = b.length();
    dp[0][0] = 0;
    rep(i,n) dp[i][0] = dp[i-1][0] + td;
    rep(i,m) dp[0][i] = dp[0][i-1] + ti;
    memset(da, 0, sizeof(da));
    rep(i,n) {// 遍历字符串a的每个字符
        db = 0;
        rep(j,m) {// 遍历字符串b的每个字符
            d = (a[i - 1] == b[j - 1]) ? 0 : tr;
            ii = da[b[j-1]-'a']; jj = db;
            db = (a[i - 1] == b[j - 1]) ? j : db;
            dp[i][j] = min({dp[i][j-1]+ti,
                dp[i-1][j]+td, dp[i-1][j-1]+d});
            if (ii > 0 && jj > 0) dp[i][j] = min(dp[i][j],
                dp[ii-1][jj-1] + (i-ii-1)*td + (j-jj-1)*ti + te);
        }
        da[a[i-1]-'a'] = i;
    }
    cout << dp[n][m];
    return 0;
}