//
// Created by Psy.C on 2026/5/26.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

set<string> s;
char str[105];
int main() {
    fast;
    cin >> str;
    int len = strlen(str);
    //将原字符串复制到数组后半部分，创建一个双倍长度的字符串
    for (int i = 0; i < len; ++i) str[len+i] = str[i];
    for (int i = 0; i < len; ++i)
        s.insert(string(str+i, str+len+i));//构造从位置i开始、长度为len的子字符串\
    //将每个长度为len的子字符串插入到集合s中
    cout << s.size() << '\n';
    return 0;
}