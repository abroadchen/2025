//
// Created by Psy.C on 2025/10/28.
//

#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

string a, b, c, x;
int n;

string convert(string s) {
    string res("");
    for (int i = 0; i < s.size(); ++i) {//遍历输入字符串的每个字符
        if ('a' <= s[i] && s[i] <= 'z') res += s[i];
        else if ('A' <= s[i] && s[i] <= 'Z') res += s[i] - 'A' + 'a';//换为小写字母后添加到结果中
    }
    return res;
}

int main() {
    getline(cin, a); a = convert(a);
    getline(cin, b); b = convert(b);
    getline(cin, c); c = convert(c);

    scanf("%d\n", &n);
    while (n--) {
        getline(cin, x); x = convert(x);
        //检查x是否等于a, b, c三个字符串的任意一种排列组合连接的结果
        if (x == a + b + c || x == a + c + b ||
            x == b + a + c || x == b + c + a ||
            x == c + a + b || x == c + b + a)
            puts("ACC");
        else puts("WA");
    }
    return 0;
}