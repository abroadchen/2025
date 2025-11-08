//
// Created by Psy.C on 2025/10/13.
//
/*
 *使用getline函数从标准输入读取一整行文本（包括空格）存储到s中
*从字符串末尾开始向前遍历
i初始化为字符串长度，每次递减1，直到0（包含0）
注意：这里会访问s[size()]，即字符串末尾后的空字符
 *
 */
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s; getline(cin, s);

    for (int i = (int)s.size(); i >= 0; --i) {
        char cur = tolower(s[i]);
        if (!(cur >= 'a' && cur <= 'z')) continue;
        if (cur == 'a' || cur == 'e' || cur == 'i' || cur == 'o' || cur == 'u' || cur == 'y')
            puts("YES");
        else
            puts("NO");
        break;//确保只处理最后一个字母
    }
    return 0;
}