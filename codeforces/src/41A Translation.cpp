//
// Created by Psy.C on 2025/9/25.
//
/*
 */
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int main() {

    string s1(""), s2("");
    getline(cin, s1); getline(cin, s2);//getline()会读取整行，包括空格
    string so = "YES";
    //const size_t表示这是一个常量的无符号整数类型
    const size_t len = s1.size();
    if (len == s2.size()) {
        for (int i = 0; i < len; ++i) {
            if (s1[i] != s2[len - 1 - i]) {//(len-1-i)表示从字符串s2的末尾开始向前数第i个位置
                so = "NO";
                break;
            }
        }
    } else so = "NO";
    cout << so << endl;
    return 0;
}