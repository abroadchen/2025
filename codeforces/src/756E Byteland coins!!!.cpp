//
// Created by Psy.C on 2026/9/2.
//
/**
先反转字符串（低位在前），方便从低到高处理。
每 9 个十进制位压成一个 int（pw[9] = 10^9，保证 t[j] < 10^9，两个相乘不溢出 long long）。
t[0..l] 存储大数，t[0] 是最低 9 位。l 是最高块下标
从最高块 t[l] 开始，把上一位的余数 cur 乘以 10^9（块基）加到当前块，除以 a[i]，商留在 t[j]，余数传给低位。
最终 cur 就是 X mod a[i]（在已经除过 a[1..i-1] 之后），即 c[i]。
DP 中 step3 需要对 j, j+1, ..., j+b[i] 求和，mx[i] 保证下标不越界，同时限定循环范围
l >= 1 表示除完所有 a[i] 后大数仍 ≥ 10^9（占两个以上块），即 X>c[n]⋅Wn
​
  上界太大，无解。否则 X = t[0] < 10^9，c[n] = t[0] 是最高位
滚动数组：f[i&1] 和 f[(i+1)&1] 交替使用，节省空间。


读入一个很大的十进制数（超过 64 位），用字符串 ch 存。
reverse 反转，这样低位在前（索引 0 是最低位）。
pw[i] = 10^i，t[i/9] 每 9 位分成一组存成 int，用 9 位十进制放入一个 int（最大 999,999,999 < 2^31-1，安全）。
l /= 9 变成组数
t[i/9] 表示第几组，pw[i%9] 给该组内第几位加权
对每个 i（1 到 n-1），把当前大数 t 除以 a[i]，商写回 t，余数存在 c[i]。
从最高位组（j=l）往低位（j=0）逐组做长除法。cur 是进位（上一位的余数），pw[9]=10^9 是进制（每组 9 位）。
c[i] = cur 存下除以 a[i] 的最终余数。
如果商变成 0（!t[l]），收缩 l，即高位组为 0 时减少组数。

mx[i] 表示：由位 1..i（低位）在 b 约束下能组成的最大值。它是自低位向高位累积的"容量上限"
阶段 (a)：体现"编码唯一性"——高一位取 j 时，低位配额是 a[i]*j + c[i]（这正是混合基数的进位规则，c[i] 是低位余数带来的）。
阶段 (b)：给第 i 位加入 b[i] 的取值裕度，用前缀和 s[] 做区间加，一次把 [j, j+b[i]] 的方案合并到位置 j，
从而统计所有满足 c[i] ∈ [0, b[i]] 约束的方案——这一步把 O(n²) 优化成了前缀和 O(1) 区间操作
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 5e5+5, mod = 1000000007;

int s[N];
int sum(int l, int r) {
    return l <= 0 ? s[r] : (s[r]-s[l-1]+mod)%mod;
}

int n, a[N], b[N], l, pw[10], t[N], c[N], mx[N], f[2][N];
char ch[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n-1; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    cin >> ch, l = strlen(ch), reverse(ch, ch+l); pw[0] = 1;
    for (int i = 1; i <= 9; ++i) pw[i] = 10*pw[i-1];
    for (int i = 0; i < l; ++i) t[i/9] += (ch[i]-'0')*pw[i%9];
    l /= 9;
    for (int i = 1; i <= n-1; ++i) {
        if (a[i] == 1) continue;//除以1无余数，c[i]=0，跳过
        int cur = 0;
        for (int j = l; j >= 0; --j) {//从高位到低位做带余除法
            ll tmp = t[j] + 1ll*pw[9]*cur;//当前位 + 上一位的余数*10^9
            t[j] = tmp/a[i], cur = tmp%a[i];//商写回，余数进位给下一位
        }
        c[i] = cur;//除以 a[i] 的最终余数 -> c[i]
        while (l >= 0 && !t[l]) l--;//商高位变 0 时收缩组数
    }
    mx[1] = b[1];
    for (int i = 2; i <= n; ++i) mx[i] = mx[i-1]/a[i-1] + b[i];
    //如果做完除法后还剩下多于一组（大数仍然 ≥ 10^9），说明数太大溢出，输出 0。
    if (l >= 1) cout << "0\n", exit(0);
    c[n] = t[0], f[(n+1)&1][0] = 1;//边界：第 n+1 层空态方案数为 1
    for (int i = n; i >= 1; --i) {
        //step1: 清零本层
        for (int j = 0; j <= mx[i]; ++j) f[i&1][j] = 0;
        //step2: 线性映射 v_i = a[i]*v_{i+1} + c[i]
        for (int j = 0; j <= mx[i+1]; ++j)
            if (1ll*a[i]*j+c[i] <= mx[i])
                f[i&1][a[i]*j+c[i]] = f[(i+1)&1][j];
        //step3: 区间求和 —— 允许减去 d_i ∈ [0, b[i]]
        s[0] = f[i&1][0];
        for (int j = 1; j <= mx[i]; ++j)
            s[j] = (s[j-1]+f[i&1][j])%mod;
        for (int j = 0; j <= mx[i]; ++j)
            f[i&1][j] = (s[min(j+b[i], mx[i])] - (j>=1 ? s[j-1] : 0) + mod) % mod;
    }
    cout << f[1][0] << '\n';
    return 0;
}