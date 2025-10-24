//
// Created by Psy.C on 2025/10/23.
//
/*
 *使用 getline 读取一整行输入，并将其存储到字符串 s 中
*初始化两个整型变量 a=0 和 b=0，分别作为指针或索引。
同时定义字符串变量 ans 并初始化为 "NO"，用于最终输出结果
 *
 *开始循环遍历字符串 s，只要 b 小于字符串长度就继续
*检查当前字符 s[b] 是否等于目标字符串 greeting[a] 中的字符。
如果相等，则将 a 加一，指向下一个要匹配的字符。
不管是否匹配，都将 b 自增，移动到下一个字符位置
 *如果已经成功匹配了整个 "hello" 字符串（即 a 达到了 greeting.size()），则设置答案为 "YES"，并跳出循环
 */
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

const string greeting = "hello";//希望在输入中查找的目标子序列

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    string s; getline(cin, s);
    int a(0), b(0); string ans = "NO";
    while (b < s.size()) {
        if (s[b++] == greeting[a]) a++;
        if (a >= greeting.size()) { ans = "YES"; break; }
    }
    cout << ans << endl;
    return 0;
}