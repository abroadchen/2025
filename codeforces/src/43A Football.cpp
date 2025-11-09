//
// Created by Psy.C on 2025/9/26.
//
/*
*s：存储第一个球队名称
s2：存储第二个球队名称
tmp：临时存储输入的字符串
*goals[0]：记录第一个球队的进球数
goals[1]：记录第二个球队的进球数
 *从标准输入读取一整行字符串（包括空格）存储到tmp中
 *如果s是空字符串（第一次读入），将当前行内容赋给s
*否则如果当前行内容不等于s且s2还是空字符串，则将当前行内容赋给s2
这样可以识别出第二个不同的球队名称

如果当前行等于第一个球队名称s，则第一个球队进球数+1，否则第二个球队进球数+1
比较两个球队的进球数，进球多的球队名称赋给tmp
 */
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int main() {

    int n; scanf("%d\n",&n);
    string s(""), s2(""), tmp("");
    int goals[2] = {0};

    while (n--) {
        getline(cin, tmp);
        if ("" == s) s = tmp;
        else if (tmp != s && "" == s2) s2 = tmp;
        (tmp == s) ? ++goals[0] : ++goals[1];
    }

    tmp = (goals[0] > goals[1]) ? s : s2;
    cout << tmp << endl;
    return 0;
}