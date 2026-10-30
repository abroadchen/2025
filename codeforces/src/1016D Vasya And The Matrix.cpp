//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
t：多组数据组数。
n、m：矩阵行数、列数。
ans：临时异或累加变量。
f[1..n]：每行要满足的异或值。
g[1..m]：每列要满足的异或值。
a[n][m]：待构造的矩阵
注意 for (t=1; t; t--)：第一轮 t=1 时循环条件 t 为真执行，随后 t-- 变 0，循环结束。所以这里实际上只执行一次（一组数据）。若要真正跑多组应改成先 cin>>t 再 while(t--)，这里写法是个简化/限制版本。
ans ^= f[i]：把整行异或值全部异或进 ans。
ans ^= g[i]：再整列异或进 ans。
于是 ans = f[1]^f[2]^...^f[n] ^ g[1]^...^g[m]
矩阵要同时满足所有行异或与所有列异或，整体所有元素异或只能算一次，所以所有行的异或 = 所有列的异或必然相等，这是必要且充分条件。

若 ans != 0：说明 xor(f) != xor(g)，无解，输出 NO，结束。
把第一行的第 2..m 列直接填成 g[i]（第 i 列的值）。
同时 ans ^= a[1][i]：把这几个已填的 g 值从 ans 里再异或掉一次（相当于消去），这样到第一行第一列时能正确算出剩余值。
（这里 ans 前面已经把所有 f、g 都异或过一遍。异或两次相同的数会抵消。）
把第一列的第 2..n 行直接填成 f[i]（第 i 行要满足的值）
第一行第一列的值 = f[1] ^ ans（此时 ans 已经过第③步消去了第一行后面几个 g 值，再异或 f[1] 恰好使第一行、第一列的异或都能满足）
按行输出整个 n×m 矩阵，每行最后一个数后换行（" \n"[j==m] 在 j==m 时取换行，否则空格）。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
#define ll long long
using namespace std;

constexpr int N = 105;

void out(bool flg) { cout << (flg ? "YES" : "NO") << '\n'; }

ll t, n, m, ans, f[N], g[N], a[N][N];
int main() {
    fast;
    for (t = 1; t; t--) {
        cin >> n >> m;
        rep(i,n) cin >> f[i], ans ^= f[i];
        rep(i,m) cin >> g[i], ans ^= g[i];
        if (ans) return out(0), 0;
        out(1);
        for (int i = 2; i <= m; i++) a[1][i] = g[i], ans ^= a[1][i];
        for (int i = 2; i <= n; i++) a[i][1] = f[i];
        a[1][1] = f[1]^ans;
        rep(i,n) rep(j,m) cout << a[i][j] << " \n"[j==m];
    }
    return 0;
}