//
// Created by Psy.C on 2026/10/10.
//
/**
arr[i] 存 s[1..i] 这个数字串对应的数值模 mod（滚动取模）
t[i] 存 10^i mod mod
get(l, r) 用前缀哈希 O(1) 算出子串 s[l..r] 的数值模 mod
这是一种字符串哈希 / 滚动哈希技巧，用来快速比较"数值大小关系"
对 check(a, b)：

先排除 B 的起始字符是 '0'（B 有前导零，除非 B 是单个 0）
排除 C 的起始字符是 '0'
再验证等式：get(1,a) + get(a+1,b) - get(b+1,n) ≡ 0 (mod mod)
注意：这里用取模比较代替直接的大整数加法比较，因为数字可能非常长（长度可达 1e6），无法直接做高精度运算。只要等式在模 mod 下成立即视为成立（因为答案存在时这个模比较通常有效，属于哈希碰撞可接受范围）
i 是 C 在字符串中的结束位置（也是 B 的结束位置，因为 B 是 [a+1..b]，C 是 [b+1..n]），所以 C 的长度为 n - i。
k = n - i 即 C 的长度。

对于每个 C 长度，尝试几种 B 的长度（k、k-1、i-k、i-k+1 等），即枚举 A 与 B 的分界 a。a 位置 = b 位置前面的部分。

需要遍历指数级的拆分，但利用等式长度关系（A+B=C 时，C 的位数要么等于 max(lenA, lenB)，要么等于 max(lenA,lenB)+1）可以大大缩小搜索空间——这就是为什么只尝试少数几种 k 相关的分界。

一旦 check 找到解，flg 设为 false，后续循环因 if (flg) 不再执行，输出第一个合法解后程序结束
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e6+10, mod = 520040527;

int t[N], arr[N], n;
string s;
void init() {
    t[0] = 1;
    for (int i = 1; i <= N-10; i++) t[i] = t[i-1]*10%mod;//10 的幂
    for (int i = 1; i <= n; i++) arr[i] = (arr[i-1]*10+s[i]-'0')%mod;//前缀哈希
}

int get(int l, int r) { return (arr[r]+mod*mod-arr[l-1]*+t[r-l+1])%mod; }

bool flg = true;
void check(int a, int b) {
    if (a+1 != b && s[a+1] == '0') return;
    if (b+1 != n && s[b+1] == '0') return;
    if ((get(1, a)+get(a+1, b)-get(b+1, n)+mod)%mod == 0) {//输出 A+B=C
        for (int i = 1; i <= a; i++) cout << s[i];
        cout << '+';
        for (int i = a+1; i <= b; i++) cout << s[i];
        cout << '=';
        for (int i = b+1; i <= n; i++) cout << s[i];
        flg = false;
    }
}

signed main() {
    fast;
    cin >> s; n = s.size(); s = ' ' + s; init();
    for (int i = n-1; i >= n/2; i--) {
        int k = n-i;
        if (flg) check(k, i);
        if (flg) check(k-1, i);
        if (flg) check(i-k, i);
        if (flg) check(i-k+1, i);
    }
    return 0;
}