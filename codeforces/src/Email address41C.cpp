//
// Created by Psy.C on 2025/9/25.
//
/*
*ind：当前处理位置的索引，初始化为0
flag：标志位，用于标记是否已经处理过"at"，初始化为false
 *
*条件判断：如果当前位置满足以下条件：
ind > 0：不是字符串开头
ind + 3 < s.size()：后面至少还有3个字符
s[ind] == 'd' && s[ind + 1] == 'o' && s[ind + 2] == 't'：当前及后面两个字符是"dot"
如果满足条件，将'.'添加到结果字符串t中，索引ind前进3位
 *
*否则判断另一个条件：如果满足以下条件：
!flag：还没有处理过"at"
ind > 0：不是字符串开头
ind + 2 < s.size()：后面至少还有2个字符
s[ind] == 'a' && s[ind + 1] == 't'：当前及后面一个字符是"at"
如果满足条件，将'@'添加到结果字符串t中，设置flag为true，索引ind前进2位
 *
*否则（不满足上述任何条件）：
将当前字符直接添加到结果字符串t中
索引ind前进1位
 *
 */
#include <iostream>
#include <string>
using namespace std;

int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    string s; cin >> s;
    string t;

    long ind(0);
    bool flag(false);
    while (ind < s.size()) {//循环处理字符串，直到处理完所有字符
        if (ind > 0 && (ind + 3 < s.size() && s[ind] == 'd' &&
            s[ind + 1] == 'o' && s[ind + 2] == 't')) {
            t += '.';
            ind += 3;
        } else if (!flag && ind > 0 && (ind + 2 < s.size() &&
            s[ind] == 'a' && s[ind + 1] == 't')) {
            t += '@';
            flag = true;
            ind += 2;
        } else {
            t += s[ind];
            ++ind;
        }
    }
    cout << t << endl;
    return 0;
}