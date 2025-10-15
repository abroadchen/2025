//
// Created by Psy.C on 2025/10/14.
//
/*
 *定义常量N为256，表示ASCII字符集的大小
 *使用getline函数从标准输入读取一整行字符串（包括空格）
 *
*遍历字符串s中的每个字符
对于第i个字符s[i]，将其ASCII值作为索引，在计数数组c中对应位置的计数加1
实现字符频次统计功能
 *
*遍历所有可能的字符（0-255）
将每个字符出现次数的平方累加到t中
计算所有字符频次的平方和
 *
 *
 */
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef long long ll;
const int N = 256;
vector<ll> c(N, 0);//用于统计每个字符出现的次数

int main() {
    string s; getline(cin, s);
    for (long i = 0; i < s.size(); ++i) ++c[s[i]];
    ll t(0);
    for (long i = 0; i < N; ++i) t += c[i] * c[i];
    printf("%lld\n", t);
    return 0;
}