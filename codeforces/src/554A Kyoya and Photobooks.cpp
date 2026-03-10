//
// Created by Psy.C on 2026/3/10.
//
/**
长度为len的字符串有len + 1个前缀位置（包括空前缀）
每个位置可以插入26个不同的字母
总共产生 (len + 1) * 26 个可能的字符串
但是原字符串本身被多计算了len次（每个位置都可能产生原串）
所以要减去len，得到最终结果

时间复杂度：O(len)，主要消耗在strlen函数
空间复杂度：O(1)，除了输入数组外只使用常数空间
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char s[21];
int main() {
    fast;
    cin >> s;
    int len = strlen(s);
    cout << (len + 1)*26 - len << '\n';
    return 0;
}