//
// Created by Psy.C on 2026/3/23.
//
/**
a[N], b[N]：存储输入的两个字符数组
p[N]：前缀和数组，记录字符串b中'0'的累计数量
p2[N]：前缀和数组，记录字符串b中'1'的累计数量

如果b[i]是'1'，则p2[i]（'1'的计数）增加1，p[i]（'0'的计数）保持不变
如果b[i]是'0'，则p[i]（'0'的计数）增加1，p2[i]（'1'的计数）保持不变
遍历字符串a的每个字符
如果a[i]是'1'，累加在对应范围内的'0'的数量（因为'1'与'0'匹配）
如果a[i]是'0'，累加在对应范围内的'1'的数量（因为'0'与'1'匹配）
p[l2-l1+i] - p[i-1]表示在区间[i, l2-l1+i]内'0'的数量
p2[l2-l1+i] - p2[i-1]表示在区间[i, l2-l1+i]内'1'的数量

时间复杂度：
O(n)，其中n是字符串的长度。

空间复杂度：
O(n)，用于存储前缀和数组

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;
char a[N], b[N];
int p[N], p2[N];
int main() {
    fast;
    scanf("%s%s", a + 1, b + 1);
    int l1 = strlen(a+1), l2 = strlen(b+1);
    for (int i = 1; i <= l2; ++i) {
        if (b[i] == '1') {
            p2[i] = p2[i-1] + 1;
            p[i] = p[i-1];
        } else if (b[i] == '0') {
            p[i] = p[i-1] + 1;
            p2[i] = p2[i-1];
        }
    }
    ll ans = 0;
    for (int i = 1; i <= l1; ++i) {
        if (a[i] == '1')
            ans += p[l2-l1+i] - p[i-1];
        else if (a[i] == '0')
            ans += p2[l2-l1+i] - p2[i-1];
    }
    cout << ans << '\n';
    return 0;
}