//
// Created by Psy.C on 2026/2/11.
//
/**
a：倒数第一位数字（个位），通过s[len-1]-'0'将字符转为数字
b：倒数第二位数字（十位），通过s[len-2]-'0'将字符转为数字
c = a + b * 10：组合最后两位数字形成两位数（十位*10 + 个位）
c % 4 == 0：判断这个两位数是否能被4整除
时间复杂度：O(n)，其中n是字符串长度（strlen需要遍历整个字符串）
空间复杂度：O(n)，存储输入字符串
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000000
using namespace std;

char s[N];

int main() {
    fast;
    cin >> s;
    const int len = static_cast<int>(strlen(s)), a = s[len-1]-'0', b = s[len-2]-'0';
    if (const int c = a + b * 10; c % 4 == 0) cout << "4\n";
    else cout << "0\n";
    return 0;
}