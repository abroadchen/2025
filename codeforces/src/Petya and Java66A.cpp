//
// Created by Psy.C on 2025/10/30.
//
/*
 *定义一个二维字符串向量 r，包含 4 行，每行初始为空。
 *这个结构将用于存储不同数据类型的最小值与最大值范围
 *声明一个一维字符串向量 t，用来保存各种整数类型的名字
 *
*定义整型变量 k 并初始化为 1，用于标记当前处理的是正数还是负数：
1 表示正数；
0 表示负数
 *
*len: 输入字符串长度；
cnt: 数据类型的数量（这里是 4）
 *获取第 i 种数据类型的对应极值（根据 k 判断是负数还是正数）的字符串长度
 *
*判断输入的数字是否超出了当前数据类型的表示范围：
若输入字符串比极限值字符串长，则肯定超出范围；
若两者长度相等但字典序更大，也说明超过了该类型的最大值（或小于最小值）
 *如果发现超出某个类型的范围，就记录该类型名作为结果，并跳出循环
 *
 */
#include <vector>
#include <iostream>
using namespace std;

vector<vector<string>> r(4, vector<string>());
vector<string> t;
string s, ans("byte");
int k(1);

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    r[0].push_back("-9223372036854775808");
    r[0].push_back("9223372036854775807");
    r[1].push_back("-2147483648");
    r[1].push_back("2147483647");
    r[2].push_back("-32768");
    r[2].push_back("32767");
    r[3].push_back("-128");
    r[3].push_back("127");
    t.push_back("BigInteger");
    t.push_back("long");
    t.push_back("int");
    t.push_back("short");
    t.push_back("byte");
    cin >> s;
    if (s[0] == '-') k = 0;

    for (int i = 0, len = s.size(), len2, cnt = r.size(); i < cnt; ++i) {
        len2 = r[i][k].size();
        if (len > len2 || (len == len2 && s > r[i][k])) {
            ans = t[i];
            break;
        }
    }
    cout << ans << endl;
    return 0;
}