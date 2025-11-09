//
// Created by Psy.C on 2025/9/24.
//
/*
 *定义常量：MOD = 32768（模数），N = 109（最大语句数）
*ans：目标答案值
num：语句数量
v：当前测试的变量值
f[MOD+9]：函数表，存储每个输入值对应的输出
l：当前解析位置
s[N]：存储解析出的语句
tmp：临时字符串
ch：字符缓存
 *
*getnum()函数解析数字或变量：
如果是'n'，返回当前变量值v
如果是'f'，递归调用exp()获取索引，返回f数组中对应值
如果是数字，解析完整的数字
 *
*sl()函数处理乘法和除法运算（优先级较高）
使用1ll确保大数运算不会溢出
 *
*exp()函数处理加法和减法运算（优先级较低）
减法通过(ret + MOD - t1) % MOD处理负数情况
 *
*iexp()函数处理条件表达式（if语句的条件部分）
解析两个表达式和它们之间的比较操作符
返回比较结果
 *
*getans()函数执行解析出的语句：
遍历所有语句
如果是if语句（以'i'开头），解析条件，如果为真则执行返回表达式
如果是return语句，直接执行返回表达式
 *
 *遇到';'表示语句结束，增加语句计数
 *其他字符添加到当前语句字符串中

*设置当前测试值v = i
执行程序获取输出f[i]
如果输出等于目标答案，记录该输入值
 */
#include <ios>
#include <iostream>
#include <string>
#define IO ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;

const int MOD = 32768, N = 109;

int ans, num, v, f[MOD+9], l;
string s[N], tmp;
char ch;
int exp();
int getnum() {

    int ret(0);
    if (tmp[l] == 'n') return l++, v;
    if (tmp[l] == 'f') return l += 2, ret = f[exp()], l++, ret;
    while (tmp[l] >= '0' && tmp[l] <= '9')
        ret = ret * 10 + (tmp[l] - '0'), l++;
    return ret;
}


int sl() {
    int ret = getnum();
    while (tmp[l] == '*' || tmp[l] == '/') {
        char tp = tmp[l]; l++;
        int t1 = getnum();
        if (tp == '*') {
            ret = (int)((1ll * ret * t1) % MOD);
        } else {
            ret = (ret / t1) % MOD;
        }
    }
    return ret;
}


int exp() {
    int ret = sl();
    while (tmp[l] == '+' || tmp[l] == '-') {
        char tp = tmp[l]; l++;
        int t1 = sl();
        if (tp == '+') ret = (ret + t1) % MOD;
        else ret = (ret + MOD - t1) % MOD;
    }
    return ret;
}



bool iexp() {
    int p1, p2, tp;
    p1 = exp();
    if (tmp[l] == '=') tp = 0, l += 2;
    else if (tmp[l] == '<') tp = -1, l++;
    else tp = 1, l++;
    p2 = exp();
    if (tp == 0) return p1 == p2;
    if (tp == -1) return p1 < p2;
    if (tp == 1) return p1 > p2;
    return 0;
}

int getans() {
    for (int i = 0; i < num; ++i) {
        tmp = s[i];
        if (tmp[0] == 'i') {
            l = 3;
            if (iexp()) return l += 7, exp();
        } else return l = 6, exp();
    }
    return -1;
}

int main() {
    IO;
    cin >>  ans >> ch;
    while (ch != '{') cin >> ch;
    num = 0;

    while (true) {
        cin >> ch;
        if (ch == '}') break;
        if (ch == ';') num++;
        else s[num] += ch;
    }
    int anst(-1);
    for (int i = 0; i < MOD; ++i) {
        v = i;
        f[i] = getans();
        if (f[i] == ans) anst = i;
    }
    cout << anst;
    return 0;
}