//
// Created by Psy.C on 2025/12/7.
//
/*
 *
*遍历左操作数l的所有可能值(0-3位)
遍历右操作数r的所有可能值(0-3位)
如果位i在l中被设置，且位j在r中被设置
计算i和j通过操作符op运算后的结果
将结果对应位置1，累加到res中
 *
*'0'返回1(二进制0001，表示值0)
'1'返回8(二进制1000，表示值3)
其他情况(应该是'?')返回6(二进制0110，表示值1和2)
 *
 *检查结果是否包含值1或2(位1和2)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


char get(const char x, const char y, const char ch) {
    if (ch == '&') return static_cast<char>(x & y);
    if (ch == '|') return static_cast<char>(x | y);
    if (ch == '^') return static_cast<char>(x ^ y);
    return 0;
}

char dfs() {
    char ch; cin.get(ch);
    while (ch == ' ' || ch == '\n') cin.get(ch);//跳过空格和换行符等空白字符
    if (ch == '(') {
        char res = 0;
        const char l = dfs();
        char op; cin.get(op);
        while (op == ' ' || op == '\n') cin.get(op);
        const char r = dfs();
        char t;//读取并跳过闭合括号')'及可能的空白字符
        do {
            cin.get(t);
        } while (t == ' ' || t == '\n');
        for (char i = 0; i < 4; ++i) if (l & 1 << i) {
            for (char j = 0; j < 4; ++j) if (r & 1 << j) {
                res = static_cast<char>(res | 1 << get(i, j, op));
            }
        }
        return res;
    }
    if (ch == '0') return 1;
    if (ch == '1') return 8;
    return 6;
}

int main() {
    fast;
    int n; cin >> n; cin.ignore();
    if (dfs() & 6) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}