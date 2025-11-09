//
// Created by Psy.C on 2025/10/14.
//
/*
*从字符串中提取四个数字位：
a: s1的第一个字符（千位）
b: s1的第二个字符（百位）
c: s2的第二个字符（十位）
d: s2的第一个字符（个位）
 *
*检查集合中是否已经存在任何一种旋转形式
如果都不存在（即这是一个新的等价类），则插入原始形式x
这确保了每组旋转等价的数字只计数一次
 *
 */
#include <string>
#include <ios>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    long n; cin >> n;
    set<long> p;
    for (long i = 0; i < n; ++i) {
        string s1, s2; cin >> s1 >> s2;
        long a(s1[0] - '0'), b(s1[1] - '0'), c(s2[1] - '0'), d(s2[0] - '0');
        long x = 1000 * a + 100 * b + 10 * c + d;// 原始数字: abcd
        long y = 1000 * b + 100 * c + 10 * d + a;// 右移一位: bcda
        long z = 1000 * c + 100 * d + 10 * a + b;// 右移两位: cdab
        long w = 1000 * d + 100 * a + 10 * b + c;// 右移三位: dabc
        if (!(p.count(x) || p.count(y) || p.count(z) || p.count(w))) p.insert(x);
        if (i < n - 1) cin >> s1;//如果不是最后一组输入，读取下一个分隔符（可能是空格或其他分隔符）
    }
    cout << p.size() << endl;//输出集合大小，即不同旋转等价类的数量
    return 0;
}