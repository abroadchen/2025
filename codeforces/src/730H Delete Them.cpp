//
// Created by Psy.C on 2026/4/26.
//
/**
n: 总共的字符串数量
m: 必须包含的字符串数量
len: 目标字符串的长度
w[N][N]: 存储n个输入字符串的二维数组
o[N]: 存储最终结果字符串的字符数组

遍历所有必须包含的字符串(d[i]为true)
对于每个必须包含的字符串：
遍历其每个字符位置j
如果o[j]已有值且不等于当前字符，则设为'?'(表示不确定)
否则设置o[j]为当前字符
记录第一个字符串的长度作为标准长度
检查后续字符串长度是否一致，不一致则答案为false

遍历所有不需要必须包含的字符串(d[i]为false)
检查这些字符串是否与构建的目标串冲突：
如果有确定位置(不是'?')且字符不匹配，则标记为不同(dif=true)
如果该字符串完全匹配目标串结构且长度相等，则答案设为false(因为不应该完全匹配)

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 107;
int n, m, len;
char w[N][N], o[N];
bool d[N];///标记第i个字符串是否必须包含在计算中
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1, t; i <= m; ++i)
        cin >> t, d[t] = true;//对应位置的布尔数组设为true
    bool ans = true;
    for (int i = 1, j; i <= n; ++i)
        if (d[i]) {
            for (j = 0; w[i][j]; ++j) {
                if (o[j] && o[j] != w[i][j]) o[j] = '?';
                else o[j] = w[i][j];
            }
            if (len == 0) len = j;
            if (j != len) ans = false;
        }
    for (int i = 1, j; i <= n && ans; ++i)
        if (!d[i]) {
            bool dif = false;
            for (j = 0; w[i][j]; ++j)
                if (o[j] != '?' && w[i][j] != o[j])
                    dif = true;
            if (!dif && j == len) ans = false;
        }
    if (ans) cout << "Yes\n" << o; else cout << "No\n";
    return 0;
}