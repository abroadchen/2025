//
// Created by Psy.C on 2025/10/10.
//
/*
*创建一个字符到整数的映射表c
初始化三个键值对：'A'->0, 'B'->0, 'C'->0
这个map用于记录每个字母在比较中出现的位置信息
 *
*循环3次，读取3行输入
每行读取一个字符串s，格式应该是类似"A<B"或"B>C"这样的比较表达式
如果第2个字符是'<'，说明是"A<B"格式，B更大，所以B的计数加1
否则说明是"A>B"格式（即"B>A"），A更大，所以A的计数加1
这样通过计数来判断每个字母的大小关系

 *如果每个字母的计数都是1，说明形成了循环（A<B, B<C, C<A），这是矛盾的
 *
 *计数值为0的字母是最小的，首先输出
 *计数值为1的字母是中间大小的，第二个输出
 *计数值为2的字母是最大的，最后输出
 *
 */
#include <cstdio>
#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {

    map<char, int> c;
    c.insert(pair<char, int>('A', 0));
    c.insert(pair<char, int>('B', 0));
    c.insert(pair<char, int>('C', 0));

    for (int i = 0; i < 3; ++i) {
        string s; getline(cin, s);
        if (s[1] == '<') ++c[s[2]];
        else ++c[s[0]];
    }

    if (c['A'] == 1 && c['B'] == 1 && c['C'] == 1) puts("Impossible");
    else {
        if (c['A'] == 0) printf("A");
        else if (c['B'] == 0) printf("B");
        else if (c['C'] == 0) printf("C");

        if (c['A'] == 1) printf("A");
        else if (c['B'] == 1) printf("B");
        else if (c['C'] == 1) printf("C");

        if (c['A'] == 2) printf("A");
        else if (c['B'] == 2) printf("B");
        else if (c['C'] == 2) printf("C");
    }
    puts("");
    return 0;
}
