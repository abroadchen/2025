//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
从两端（左 l、右 r）‍交替取出字符，每次把取到的字符插入到结果最前面（s[...] + ans），直到取完
每次循环 l 或 r 向中间移动一步，ans 是"新字符 + 旧 ans"。
因为新取的字符总是被放在最前面，所以取出的顺序与最终 ans 的顺序是反的——即：最先取出（在最初轮取的字符）最终排在最后
若 len 为偶数，len&1==0，!0 = true → f=true，第一次从**右端 r**取。
若 len 为奇数，len&1==1，!1=false → f=false，第一次从**左端 l**取

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;
char s[N];
string ans;
int main() {
    fast;
    cin >> s;
    int len = int(strlen(s)), l = 0, r = len-1;
    bool f = !bool(len&1);
    while (l <= r) {
        if (f) ans = s[r--] + ans;
        else ans = s[l++] + ans;
        f = !f;
    }
    cout << ans << '\n';
    return 0;
}