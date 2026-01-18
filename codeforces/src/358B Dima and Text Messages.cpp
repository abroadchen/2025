//
// Created by Psy.C on 2026/1/18.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    string s, a = "<3";
    for (int i = 0; i < n; ++i) {
        cin >> s;
        a += s + "<3";//读取的字符串s添加到a后面，再加上"<3"
    }
    cin >> s; n = 0;//读取待匹配的字符串，将n重置为0作为匹配指针
    //遍历待匹配字符串s中的每个字符
    for (const char i : s) n += i == a[n];//等于目标字符串a中位置n的字符 逐个匹配a中的字符
    cout << (n == a.size() ? "yes" : "no");//n等于a的长度，说明完全匹配
    return 0;
}