//
// Created by Psy.C on 2026/3/20.
//
/**
str[N]：原字符串
s[N]：临时字符串，用于存储旋转后的结果
q：查询次数
l, r：区间左右端点
k：旋转步数
k %= len：将旋转步数规范化到[0, len-1]

从右到左遍历区间[l-1, r-1]（转换为0-indexed）
int p = (i - l + 1 + k) % len + l - 1;：计算字符的新位置
i - l + 1：在区间内的相对位置（1-indexed）
+ k：加上旋转步数
% len：循环处理
+ l - 1：转换回原字符串的位置
s[p] = str[i];：将字符放到新位置
这里的逻辑是反向的，实际上是将区间内的字符向右旋转k位
将旋转后的结果从临时数组s复制回原字符串str
时间复杂度：O(q * n)，其中q是查询次数，n是字符串长度。 空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
char str[N], s[N];
int q, l, r, k;
int main() {
    fast;
    cin >> str >> q;
    while (q--) {
        cin >> l >> r >> k;
        int len = r - l + 1; k %= len;
        for (int i = r - 1; i >= l - 1; --i) {
            int p = (i - l + 1 + k) % len + l - 1;
            s[p] = str[i];
        }
        for (int i = l - 1; i <= r - 1; ++i)
            str[i] = s[i];
    }
    cout << str << '\n';
    return 0;
}