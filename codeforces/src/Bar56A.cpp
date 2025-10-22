//
// Created by Psy.C on 2025/10/20.
//
/*
*定义函数c，将字符串转换为整数：

res(0): 初始化结果为0
循环遍历字符串中的每个字符
res = res * 10 + s[i] - '0': 逐位构建整数，将字符转换为对应的数字
返回转换后的整数
 *
*定义检查函数check，判断字符串是否为酒精饮料名称：

检查输入字符串是否等于11种酒精饮料名称中的任意一种
如果是则返回true，否则返回false
 *
 *声明并初始化空字符串s，用于存储每次读取的输入
 *声明并初始化长整型变量t为0，用于计数需要被拒绝的人员数量
 *
*判断输入的第一个字符是否为数字字符：

如果是数字，则调用函数c将字符串转换为整数
如果该年龄小于18岁，则计数器t加1
 *
*如果输入不是以数字开头，则检查是否为酒精饮料名称：

调用check函数判断字符串是否为酒精饮料
如果是酒精饮料，则计数器t加1
 *
 *
 */
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int c(string s) {
    int res(0);
    for (int i = 0; i < s.size(); ++i) res = res * 10 + s[i] - '0';
    return res;
}

bool check(string s) {
    return (s == "ABSINTH" || s == "BEER" || s == "BRANDY" ||
        s == "CHAMPAGNE" || s == "GIN" || s == "RUM" ||
        s == "SAKE" || s == "TEQUILA" || s == "VODKA" ||
        s == "WHISKEY" || s == "WINE");
}

int main() {
    int n(0); scanf("%d\n",&n);
    string s("");

    long t(0);
    for (int i = 0; i < n; ++i) {
        getline(cin,s);
        if (s[0] >= '0' && s[0] <= '9') {
            if (c(s) < 18) ++t;
        } else if (check(s)) ++t;
    }
    printf("%ld\n",t);
    return 0;
}