//
// Created by Psy.C on 2025/11/21.
//
/*
 *t表示整数部分的最后一位索引
 *
 *如果没有找到小数点（即输入是整数）
 *整数部分结束于字符串末尾
 *添加默认的两位小数"00"
 *如果有小数点
 *整数部分结束于小数点前一位
 *处理小数部分：添加第一位小数（如果存在）
 *添加第二位小数（如果存在，否则补0）
 *从右到左处理整数部分，每三位添加一个逗号分隔符
 *将当前字符添加到结果前面
 *每处理三位数字就添加一个逗号（除了最左边的部分）
 *
 * 如果第一个字符是负号
 *如果结果开头是逗号，则替换为美元符号
 *
*i: 当前正在处理的数字位置（从右向左遍历）
t - i: 表示从当前位置到整数部分末尾的距离（已经处理了多少位数字）
 *每当处理完3的倍数个数字时，就在当前位置后面添加一个逗号分隔符
 *
 *
 */
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; getline(cin, s);
    string ans(".");

    size_t p = s.find('.'), t;
    if (p == string::npos) { t = s.size() - 1; ans += "00"; }
    else {
        t = p - 1;
        if (s.size() >= p + 2) ans += s[p+1];//小数点后至少有1位数字
        if (s.size() >= p + 3) ans += s[p+2];
        else ans += '0';
    }
    for (int i = t; i >= 1; --i) {
        ans = s[i] + ans;
        if ((t - i) % 3 == 2) ans = ',' + ans;
    }
    if (s[0] == '-') {
        if (ans[0] == ',') { ans[0] = '$'; ans = '(' + ans; }
        else ans = "($" + ans;
        ans += ')';
    } else {
        ans = s[0] + ans;//添加第一位数字
        ans = '$' + ans;
    }
    cout << ans << '\n';
    return 0;
}