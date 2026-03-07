//
// Created by Psy.C on 2026/3/7.
//
/**
s[N]：第一个字符串
t[N]：第二个字符串
num[N]：存储两个字符串不同位置的索引
cnt：不同位置的数量

遍历字符串的每一位
如果s[i] ≠ t[i]，将位置i记录到num数组中
cnt++：增加不同位置的计数

只修改前cnt/2个不同位置的字符
将'1'改为'0'，'0'改为'1'
输出修改后的字符串s
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
char s[N], t[N];
int num[N], cnt;
int main() {
    fast;
    cin >> s >> t;
    int len = strlen(s);
    for (int i = 0; i < len; ++i)
        if (s[i] != t[i])
            num[cnt++] = i;
    if (cnt&1) cout << "impossible\n";
    else {
        for (int j = 0; j < cnt/2; ++j) {
            if (s[num[j]] == '1')
                s[num[j]] = '0';
            else if (s[num[j]] == '0')
                s[num[j]] = '1';
        }
        cout << s << '\n';
    }
    return 0;
}