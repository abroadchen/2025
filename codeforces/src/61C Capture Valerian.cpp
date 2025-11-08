//
// Created by Psy.C on 2025/10/28.
//
/*
*定义字符转数字函数c2d：
如果字符是数字(0-9)，返回其对应的数值(c - '0')
如果字符是字母(A-Z)，返回其对应的数值(c - 'A' + 10)
 *
*定义进制转十进制函数b2d：
接收一个字符串n和进制数o
使用霍纳法则将n进制数转换为十进制数
逐位处理，每次将结果乘以进制数再加上当前位的值
 *
*定义两个数组用于罗马数字转换：
v数组存储罗马数字对应的十进制值（按从大到小排序）
r数组存储对应的罗马数字符号（包括组合符号如CM, CD等）
 *
*定义十进制转罗马数字函数d2r：
从最大的罗马数字值开始遍历
只要当前数字大于等于罗马数字值，就将对应符号添加到结果中并减去该值
重复直到数字为0
 *
*定义数字转字符函数d2c：
如果数字小于10，返回对应的数字字符('0' + o)
否则返回对应的字母字符('A' + o - 10)
 *
*定义十进制转任意进制函数d2bb：
特殊情况：如果n为0，直接返回"0"
否则通过不断取余和整除来获取各位数字
由于是从低位到高位生成，需要反转字符串
 *
 */
#include <ios>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

typedef long long ll;
string s1, s2, s3;
int a, b;

int c2d(char c) { if (isdigit(c)) return c - '0'; return c - 'A' + 10; }

ll b2d(const string& n, int o) {
    ll res(0);
    for (char c : n) res = res * o + c2d(c);
    return res;
}

int v[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
string r[] = {"M", "CM", "D", "CD", "C", "XC",
    "L", "XL", "X", "IX", "V", "IV", "I"};

string d2r(int n) {
    string res;
    for (int i = 0; i < 13; ++i) {
        while (n >= v[i]) {
            res += r[i];
            n -= v[i];
        }
    }
    return res;
}

char d2c(int o) {
    if (o < 10) return '0' + o;
    return 'A' + o - 10;
}

string d2bb(ll n, int o) {
    if (n == 0) return "0";
    string res;
    while (n > 0) res += d2c(n % o), n /= o;
    reverse(res.begin(), res.end());
    return res;
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cin >> s1 >> s2;

    a = stoi(s1);//将s1转换为整数并赋值给a
    cin >> s3;
    ll d = b2d(s3, a);//将s3从a进制转换为十进制数，存储在d中
    if (s2 == "R") cout << d2r((int)d) << endl;//输出十进制数d对应的罗马数字
    else {
        b = stoi(s2);//目标进制
        cout << d2bb(d, b) << endl;//输出十进制数d转换为b进制的结果
    }
    return 0;
}