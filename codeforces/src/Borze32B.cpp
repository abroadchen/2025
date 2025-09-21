//
// Created by Psy.C on 2025/9/21.
//时间复杂度：O(n)，其中n是输入字符串长度 空间复杂度：O(1)，只使用常数额外空间
#include <ios>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; getline(cin, s);// 读取整行输入字符串（包括空格）

    size_t index = 0;
    while (index < s.size()) {// 遍历整个字符串
        if (s[index] == '.') printf("0");
        else if (s[index] == '-' && s[index + 1] == '.') {
            printf("1");
            ++index;// 跳过下一个字符，因为已经处理了两个字符
        }
        else if (s[index] == '-' && s[index + 1] == '-') {
            printf("2");
            ++index;
        }
        ++index;// 移动到下一个字符
    }

    return 0;
}