//
// Created by Psy.C on 2026/1/29.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;

int a, b, c;
inline void read() {//|||+|||=|||||
    char ch; cin.get(ch);
    while (ch == '|') a++, cin.get(ch);//第一个加号前的 | 数量（存储到 a）
    cin.get(ch);
    while (ch == '|') b++, cin.get(ch);//加号和等号之间的 | 数量（存储到 b）
    cin.get(ch);
    while (ch == '|') c++, cin.get(ch);//等号后的 | 数量（存储到 c）
}

//x个| + + + y个| + = + z个|
inline void out(const int x, const int y, const int z) {
    rep(i,x) cout << '|'; cout << '+';
    rep(i,y) cout << '|'; cout << '=';
    rep(i,z) cout << '|'; cout << '\n';
}

int main() {
    fast;
    read();
    if (a + b == c) out(a, b, c);
    else if (a + b == c + 2) {//移动一根竖线：将加号或等号后的一个 | 移到另一边
        if (a != 1) out(a - 1, b, c + 1);
        else out(a, b - 1, c + 1);
    } else if (a + b == c - 2) out(a + 1, b, c - 1);
    else cout << "Impossible\n";
    return 0;
}