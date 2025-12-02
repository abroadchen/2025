//
// Created by Psy.C on 2025/12/2.
//
/*
*len: 字符串长度
a: 字符串首字母相对于'a'的索引（0-25）
b: 字符串末字母相对于'a'的索引（0-25）
 *
 *遍历所有可能的起始字符（a-z）
 *如果存在从字符j到字符a的路径（dp[j][a]不为0），
 *则更新从字符j到字符b的最大长度为原长度和新路径长度（dp[j][a] + len）的最大值
 *更新从字符a到字符b的直接路径最大长度
 *遍历所有字符，找到从每个字符到自身的最大路径长度，更新ans
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200
using namespace std;

int n, dp[N][N];

int main() {
    fast;
    cin>>n;
    for (int i = 1; i <= n; ++i) {
        string s; cin>>s;
        const int len = static_cast<int>(s.length()),
        a = s[0] - 'a', b = s[len - 1] - 'a';
        for (int j = 0; j < 26; ++j) {
            if (dp[j][a]) dp[j][b] = max(dp[j][a] + len, dp[j][b]);
        }
        dp[a][b] = max(dp[a][b], len);
    }
    int ans = 0;
    for (int i = 0; i < 26; ++i) ans = max(ans, dp[i][i]);
    cout<<ans<<"\n";
    return 0;
}