//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
N = 2147483240：一个很大的"无穷大"初值（接近 int 上限 2147483647），用作比较初始的 w。
read/write：模板快读快写。
c[3] = {'B','G','R'}：三色字符数组，之后被 next_permutation 穷举所有排列。
ans：记录最优目标字符串
read(n) 读长度；cin >> s 读字符串
w = N：初始化为无穷大。
do { ... } while(next_permutation(c, c+3))：生成 c 的所有 6 种排列，每种排列执行一次循环体。
第一遍进入时 c = {'B','G','R'}（原始排列），每次迭代生成下一排列，直到用完所有排列
string t: 临时目标串。
cost = 0: 记录改动次数。
for (int i = 0; i <= n-1; i++):
t.push_back(c[i%3]): 按循环模式构造第 i 个目标字符（c[i%3] 取第 i 个位置对应三色排列中的哪个颜色）。
if (s[i] != t[i]) cost++: 若原串该位与目标不同，改动次数 +1。
即对于当前三色排列，目标串是"按 c[0],c[1],c[2], c[0],c[1],c[2],... 循环重复"
if (cost < w) { w = cost; ans = t; }
找到更小的改动次数，就更新 w 并保存对应目标串 ans。
write(w)：输出最小改动次数。
putchar('\n')、cout << ans << '\n'：输出换行与最优目标串。
*/
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2147483240;
template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

char c[3] = {'B','G','R'};
string ans;
int main() {
    int n; read(n);
    string s; cin >> s;
    int w = N;
    do {
        string t;
        int cost = 0;
        for (int i = 0; i <= n-1; i++) {
            t.push_back(c[i%3]);
            if (s[i] != t[i]) cost++;
        }
        if (cost < w) { w = cost; ans = t; }
    } while (next_permutation(c,c+3));
    write(w), putchar('\n');
    cout << ans << '\n';
    return 0;
}