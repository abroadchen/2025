//
// Created by Psy.C on 2026/3/31.
//
/**
初始化答案 ans 为13（一个较大的初始值）
使用双重循环比较每对字符串
内层循环计算两个字符串之间的汉明距离（不同字符的位置数量）
汉明距离：cnt 记录在相同位置上字符不同的数量
更新 ans 为所有距离中的最小值
时间复杂度：O(n² × 6) = O(n²)，空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005;
int n;
char str[N][7];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> str[i];
    int ans = 13;
    for (int i = 0; i < n; i++)
        for (int j = i+1, cnt; j < n; j++) {
            cnt = 0;
            for (int k = 0; k < 6; k++)
                cnt += str[i][k] != str[j][k];
            ans = min(ans, cnt);
        }
    cout << (ans-1)/2 << '\n';
    return 0;
}