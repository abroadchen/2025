//
// Created by Psy.C on 2026/10/12.
//
/**
pw[i] = 5^i。
w[i] = 4·5^{i-1}（我用数值验证：w = [1, 4, 20, 100, 500, …]）。
w1[i] = w1[i-1]^5 (mod 5^17)，由 w1[1]=16 得 w1[i] = 16^{5^{i-1}}（模 5^17）‍；我用代码验证了 w1[2]=16^5、w1[3]=16^{25} 均吻合【run_code 运行验证】。也就是说 w1 是一组模 5^17 下各级别的单位元/生成元的幂，用于后面的"对齐"
n 被放大 1e6 倍后右移 17 位（等价于除以约 131072），再做取整，最后确保不被 5 整除。
主循环从低到高的 5 进制位逐位处理：第 i 轮要求 n 与状态 nw 在模 5^{i+1} 下一致；不一致就一直乘 w1[i]（它在模 5^17 下具有 5 的幂级"阶"，因此每次乘法等价于在这个 5 进制环路上步进单位），并给 ans 累加 w[i]=4·5^{i-1}。
这本质上是用一个模 5^17 的环状乘法群做"逐 5 进制位对齐"——类似解一个逐级 Chinese-Remainder / discrete-log 式的对齐过程，ans 记录总步数（代价）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 25, M = 17, inf = 1e6;

ll pw[N], w[N], w1[N];
void init() {
    pw[0] = w[0] = 1; w[1] = 4; w1[0] = 2; w1[1] = 16;
    for (int i = 1; i <= M; ++i) pw[i] = pw[i-1]*5;
    for (int i = 2; i < M; ++i) {
        w[i] = w[i-1]*5;
        w1[i] = (__int128)w1[i-1]*w1[i-1]%pw[M];
        w1[i] = (__int128)w1[i]*w1[i]%pw[M];
        w1[i] = (__int128)w1[i]*w1[i-1]%pw[M];
    }
}

ll n, nw, ans;
void solve() {
    cin >> n; n*=inf; nw = 1; ans = M; n = ((n-1)>>M)+1;
    if (!(n%5)) ++n;//若被 5 整除，+1 避开
    for (int i = 0; i < M; ++i)
        while (n%pw[i+1] != nw%pw[i+1])//逐位对齐 n 与 nw 在模 5^{i+1} 下的值
            nw = (__int128)nw*w1[i]%pw[M], ans += w[i];//乘 w1[i]，累加 w[i]=4·5^{i-1}
    cout << ans << '\n';
}


int main() {
    fast;
    int T; cin >> T; init();
    while (T--) solve();
    return 0;
}