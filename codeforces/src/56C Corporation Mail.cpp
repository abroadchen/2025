//
// Created by Psy.C on 2025/10/20.
//
/*
*auto rec: 自动推导rec的类型
=: 表示捕获外部作用域的所有变量（p, cnt, val, s）
[&]: 捕获引用，可以直接修改外部变量
auto& self: 参数为自动推导类型的引用，用于实现递归调用
 *
 *声明局部字符串变量res，用于存储当前解析到的元素名称
*循环解析元素名称：

当前字符是大写字母A-Z时继续循环
将字符添加到res字符串末尾
位置指针p向前移动一位
 *将当前元素之前出现的次数加到总计数器cnt中
 *将当前元素的出现次数加1
*处理子元素：

当前字符不是'.'时继续循环
位置指针p向前移动一位
递归调用自身处理子元素
 *跳过'.'字符，位置指针向前移动一位
 *递归返回时，将当前元素的计数减1（回溯）
 *
 *调用递归函数开始处理，将自身作为参数传入实现递归
 *
 *实现了一个树状结构的遍历算法，通过字符串表示的层次结构计算特定的计数逻辑
 */
#include <ios>
#include <iostream>
#include <map>
using namespace std;

int p = 0, cnt = 0;
string s;
map<string, int> val;

void rec() {
    string res;
    while (s[p] >= 'A' && s[p] <= 'Z') {
        res += s[p];
        p++;
    }
    cnt += val[res];
    val[res]++;
    while (s[p] != '.') {
        p++;
        rec();
    }
    p++;
    val[res]--;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    getline(cin, s);

    rec();
    cout << cnt;
    return 0;
}