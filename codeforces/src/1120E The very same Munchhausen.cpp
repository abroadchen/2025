//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
若 a==1，答案就是 1（1 = 1×1），直接输出。
tmp 模拟 1/a, 10/a, 100/a ... 的长除余数，num 记录商（即 1/a 的小数展开），sum 是商的数位和累积。
关键守恒关系：整个候选解分为两部分——前面由 num（循环节拼接）构成的主体，加一个尾部修正（"1"串）来精确匹配「等于 a × 数位和」的倍率方程。
变量对应分数化简：把需构造的数写成 单分数 × 循环节 + 单分数 × 尾部 的组合，用 A = sum+1 - a*(S(a-tmp)+1) 求补，B = S(a)*a - 1 是分母参数，g=gcd(A,B) 约分。
长度约束：(A/g)*6 + (B/g)*(5+num.size()) <= N 保证构造出的答案串长度不超过 N(5e5)，否则继续迭代找更短的表示
tmp==0 表示 1/a 是有限小数（a 只含 2、5 因子）。
a > sum：无解，输出 -1。
a == sum：num 本身就是一个解，直接输出。
否则仍需修正如 A
z 在开头是 rep(i,5) z += '0'，即 "00000"，用于隔位补零，保证每个拼接块长度一致（避免数位混淆），从而使整体数位和可用数论公式精确控制。
最终串 = (num+00000) 重复 B/g 次 拼接 ("1"+00000) 重复 A/g 次，长度与数位和被预先算好，使整串恰好满足 N = a·S(N)

条件 != '9' 表示"末位还有加 1 的空间"（如果已经是 9，加 1 会产生进位到前一位，破坏用分数方程精确控制的逻辑，故不允许）。
也就是说：只有末位不是 9 时，才能安全执行"末位 +1"这个修正操作
S(a - tmp)：a-tmp 的数位和（tmp 是当前长除余数）。
S(a-tmp)+1：加上末位那次 +1 后对应部分的"要约数位和增量"。
左边 a*(S(a-tmp)+1)：表示如果接受这个 +1 修正，两边方程中"数位和侧"乘以 a 后应达到的量。
右边 sum + 1：sum 是目前累计的数位和，+1 计数当前末位加 1 的操作
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i = 1; i <= n; i++)
#define ll long long
using namespace std;
constexpr int N = 5e5;

inline ll gcd(ll u, ll v) {
    while (v) { u %= v; swap(u, v); }
    return u;
}
inline ll S(ll u) {//对 u 逐位取模累加，返回各数位之和
    ll res = 0;
    for (; u; u /= 10) res += u%10;
    return res;
}

ll i, a, A, B, tmp, sum, g, t;
string z, num, ans;
int main() {
    fast;
    rep(i,5) z += '0';
    cin >> a;
    if (a == 1) { cout << "1\n"; return 0; }
    B = S(a)*a - 1;
    for (i = 0, tmp = 1; tmp; i++) {
        if (num[num.size()-1] != '9' && a*(S(a-tmp)+1) < sum + 1) {
            A = sum + 1 - a*(S(a-tmp)+1);
            g = gcd(A,B);
            if ((A/g)*6 + (B/g)*(5+num.size()) <= N) { num[num.size()-1]++; break; }
        }
        tmp = tmp*10; t = tmp/a; sum += t;
        if (!num.empty() || t) num += t + '0';
        tmp %= a;
    }
    if (!tmp) {
        if (a > sum) { cout << "-1\n"; return 0; }
        if (a == sum) { cout << num; return 0; }
        A = sum - a; g = gcd(A,B);
    }
    rep(i,B/g) ans += num + z;
    rep(i,A/g) ans += "1" + z;
    cout << ans;
    return 0;
}