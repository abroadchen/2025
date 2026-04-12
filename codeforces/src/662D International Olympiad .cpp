//
// Created by Psy.C on 2026/4/11.
//
/**
构造一个数字tmp，它是10的幂的和
例如，如果len是4，那么tmp变成10 + 100 + 1000 = 1110
当tmp + 1989大于q时，继续向q添加ten
ten似乎是原始数字中最大位数之后的下一个10的幂
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
string s;
int main() {
    fast;
    cin >> n;
    for (int i = 0, q; i < n; ++i) {
        q = 0;
        cin >> s; s = s.substr(4);//删除前4个字符
        int len = s.length();
        for (int j = 0; j < len; ++j)
            q = q*10 + s[j] - '0';//将剩余字符串转换为整数q
        int tmp = 0, ten = 10;
        for (int j = 1; j < len; ++j) {
            tmp += ten; ten *= 10;
        }
        while (tmp + 1989 > q) q += ten;
        cout << q << '\n';
    }
    return 0;
}