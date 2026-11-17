//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
sum：公式结果。
x：n/d（配对数）。
f[]：存放所有结果，最后排序输出
读入 n。
t = √n，只需枚举到平方根。
if (!(n%i))：i 是 n 的因子
令 x = n/i。
sum = x*(x-1)*i/2 + x，即 x(x-1)/2 * i + x。
存入 f，计数 +1。这对应因子 d = i 的贡献
条件 i*i != n：当 i 不是 n 的平方根（即配对因子 d=n/i 与 i 不同）时，才处理配对因子，避免平方根重复。
x = n/(n/i)：这里注意，由于整除性，n/(n/i) 并不总是等于 i，但它在这里作为配对因子 d = n/i 对应的 x 值——即令 d = n/i，则 x = n/d = n/(n/i)。
用 d = n/i 计算：sum = x(x-1)/2 * d + x。
存入 f，计数 +1。
关键：程序对每一对因子 (i, n/i) 各算一次（去重平方根），把 n 的全部因子都覆盖了
sort 升序排序所有结果。
依次输出，空格分隔
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 1e6+5;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

ll sum, x, f[N];
int main() {
    fast;
    int n = rd(), t = sqrt(n), tot = 0;
    rep(i,t) if (!(n%i)) {
        x = n/i; sum = x*(x-1)*(ll)i; sum >>= 1; sum += x;
        f[++tot] = sum;
        if (i*i != n) {
            x = n/(n/i); sum = x*(x-1)*(ll)(n/i); sum >>= 1; sum += x;
            f[++tot] = sum;
        }
    }
    sort(f+1, f+1+tot);
    rep(i,tot) cout << f[i] << ' ';
    return 0;
}