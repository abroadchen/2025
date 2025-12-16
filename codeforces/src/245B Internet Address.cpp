//
// Created by Psy.C on 2025/12/16.
//
/*
*查找"http"和"ftp"在字符串中的位置
h存储"http"的位置，f存储"ftp"的位置
声明变量cnt用于存储协议长度
 *如果没找到"http"或"ftp"，将其位置设为一个很大的值（确保不会被选中）
*判断哪个协议出现得更早
如果ftp更早且存在，设置cnt=3（"ftp"长度）
否则设置cnt=4（"http"长度）
 *查找第一个"ru"的位置
*如果"ru"紧接在协议后面（可能是域名的一部分），则查找下一个"ru"
这是为了找到真正的域名结尾".ru"
*根据哪个协议更靠前决定输出哪个协议头
输出从协议结束后到".ru"之前的部分作为域名
 *输出".ru"顶级域名
 *如果".ru"后面还有内容，则输出"/"和剩余部分作为路径
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    string s; cin >> s;
    int h = static_cast<int>(s.find("http")),
    f = static_cast<int>(s.find("ftp")), cnt;
    if (h == string::npos) h = static_cast<int>(s.length()) + 7;
    if (f == string::npos) f = static_cast<int>(s.length()) + 7;
    if (f < h && f != string::npos) cnt = 3; else cnt = 4;
    int r = static_cast<int>(s.find("ru"));
    if (r == h + cnt || r == f + cnt)
        r = static_cast<int>(s.find("ru", r + 1));
    if (h > f && f != string::npos) {
        cout << "ftp://";
        for (int i = f + cnt; i < r; ++i) cout << s[i];
    } else {
        cout << "http://";
        for (int i = h + cnt; i < r; ++i) cout << s[i];
    }
    cout << ".ru";
    if (r + 2 != s.length()) {
        cout << '/';
        for (int i = r + 2; i < s.length(); ++i) cout << s[i];
    }
    return 0;
}