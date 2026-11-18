//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
若长度为 1 直接返回 1（单字符视为回文）。
否则比较首尾对称字符，只要有一对不相等就返回 0（非回文）；全部相等返回 1（是回文）
从第 1 个字符开始，只要发现某位与前一位不同就返回 0；全相同返回 1。
即判断整串是不是 "aaaa..." 这种全同字符串
T = rd()：读测试组数。

每组读入字符串 a：

若 chk(a) 为真（整串全同一个字符）：任何重排都和原串相同（或仍是回文），无法构造合法不同串，输出 -1。

否则：循环执行
check(a) 判断当前 a 是否为回文；只要还是回文，就用 random_shuffle 随机打乱 a，直到打乱后不再回文为止。
random_shuffle 会以某种随机顺序重排字符，这里用作穷举手段来找一个非回文排列。
循环结束后输出这个非回文的 a 并换行
*/
#include <bits/stdc++.h>
#define rep(i,j,k) for (int i=j; i<=k; ++i)
using namespace std;

bool check(const string &a) {
    if (a.size() == 1) return 1;
    rep(i,0,a.size()/2-1)
        if (a[i] != a[a.size()-i-1]) return 0;
    return 1;
}
bool chk(const string &a) {
    rep(i,1,a.size()-1) if (a[i] != a[i-1]) return 0;
    return 1;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

int main() {
    int T = rd();
    while (T--) {
        string a; cin >> a;
        if (chk(a)) write(-1), putchar('\n');
        else {
            while (check(a)) random_shuffle(a.begin(), a.end());
            cout << a << '\n';
        }
    }
    return 0;
}