//
// Created by Psy.C on 2025/9/19.
//
/*
*读取数字字符串的长度n
读取数字字符串number
 *
 *
*情况1：n % 3 == 0（长度能被3整除）
先输出前3个字符
然后每3个字符为一组，前面加连字符
情况2：n % 3 == 1（长度模3余1）
特殊处理：前2个字符 + 连字符 + 接下来2个字符
从第5个字符开始，每3个字符为一组，前面加连字符
情况3：n % 3 == 2（长度模3余2）
前2个字符作为第一组
从第3个字符开始，每3个字符为一组，前面加连字符
 *
 *
 *
 *
 */
#include <ios>
#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    int n; cin >> n;
    string number; cin >> number;
    if (n % 3 == 0) {
        cout << number[0] << number[1] << number[2];
        for (int i = 3; i < n; i = i + 3)
            cout << '-' << number[i] << number[i + 1] << number[i + 2];
        cout << endl;
    } else if (n % 3 == 1) {
        cout << number[0] << number[1] << '-' << number[2] << number[3];
        for (int i = 4; i < n; i = i + 3)
            cout << '-' << number[i] << number[i + 1] << number[i + 2];
        cout << endl;
    } else {
        cout << number[0] << number[1];
        for (int i = 2; i < n; i = i + 3)
            cout << '-' << number[i] << number[i + 1] << number[i + 2];
        cout << endl;
    }
    
    return 0;
}