//
// Created by Psy.C on 2026/10/21.
//
/**
定义 node 封装一个模 mod=1e9+7 的整数，重载 + - * 都在模意义下。
B = 3917 是哈希基数（底数）。
可确证：node 提供模 1e9+7 下的加减乘；+/- 用条件加减处理负数与溢出，* 用 64 位乘法取模
pw[i] = B^i mod mod，预处理幂。
p[i+1] 是字符串 s[0..i] 的前缀哈希：p[i] = Σ s[key]*B^(...) 的滚动形式（p[i+1] = p[i]*B + s[i]）。
可确证：p 为前缀哈希（多项式哈希），pw 为对应底数幂【标准多项式哈希定义】
sec(l, r) 返回子串 s[l..r-1]（左闭右开，长度 r-l）的哈希值。
公式 p[r] - p[l]*B^(r-l) 是标准子串哈希求法。
可确证：sec(l,r) 用前缀哈希差得到 s[l..r-1] 的哈希，标准子串哈希公式
res 存每个中心的答案，索引范围 0 .. (n-1)/2（只处理"前半部分中心"，偶数回文对称位置由右半互补）。
先处理最中间那个中心（索引 (n-1)>>1）：
若 n 为偶数（(-n&1) 即 n 偶）且中间两字符 s[n/2-1] 与 s[n/2] 相等 → 最长偶回文长度为 2（半径 1），res=1；
否则 -1（表示该中心无法形成偶回文，或上一中心的半径需从 -1 起推）。
可确证：对最中间中心 (n 偶数) 最多 1 的偶回文，初始化为 1 或 -1。
这里的"半径"单位是2（因为偶数回文每次扩展一对字符）
per 是 0-based 倒序循环，i 从 (n-1)/2 递减到 0（注意初始 res[(n-1)>>1] 已设，故实际从 (n-1)/2 - 1 开始覆盖——但代码先初始化了最右，然后 per 循环会重新赋值 res[i] = res[i+1]+2，所以最右那个中心也会被重算一遍；不过初始化那步主要是为 per 提供边界基准）。
递推剪枝依据（马拉车/等半径思想）：

在位置 i 与 i+1 之间的镜像对称：位置 i 的对称中心与位置 (n-1)-i 有关。注意这里比较的是
sec(i, i+r) 与 sec(n-i-r, n-i)，即左半 s[i..i+r-1] 与右镜像 s[n-i-r..n-i-1]。
由于回文具有镜像性，左边中心的半径至少是右边对应中心半径（这里用 res[i] = res[i+1]+2 作为起点估计：res[i+1] 是右侧相邻中心的答案，+2 因为左移一个位置对应半径可至少继承并向外扩展一对可能）。这其实是借用"半径单调/镜像传承"的思路减少哈希比较次数。
循环体：

res[i+1]+2 作为乐观初始半径。
只要当前半径 res[i] 下两半边不等，就 res[i] -= 2 缩小 2（一对一对缩），直到相等或到 -1（表示无任何偶回文）。
一旦左右两段哈希相等即 break，得到该中心最大偶回文半径。
可确证：per 循环从右向左，res[i] 从 res[i+1]+2 开始，用哈希比较 s[i..i+r) == s[n-i-r..n-i)，不等则 r-=2，相同则停。这是"镜像继承 + 中心扩展减枝"的偶回文半径求解
输出前 (n+1)/2 个中心的半径。
可确证：依次输出 res[0..(n+1)/2-1]
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define vi vector<int>
#define rep(i,n) for (int i=0; i<(n); ++i)
#define per(i,n) for (int i=(n)-1; i>=0; --i)
using namespace std;

constexpr int B = 3917, mod = 1e9+7;

struct node {
    int x;
    node(int x=0):x(x){}
    friend node operator+(const node &a, const node &b) {
        int x = a.x + b.x;
        return {x >= mod ? x - mod : x};
    }
    friend node operator-(const node &a, const node &b) {
        int x = a.x - b.x;
        return {x < 0 ? x + mod : x};
    }
    friend node operator*(const node &a, const node &b) {
        return node(1ll*a.x*b.x%mod);
    }
};

int n;
string s;
int main() {
    fast;
    cin >> n >> s;
    vi p(n+1), pw(n+1); pw[0] = 1;
    rep(i,n) pw[i+1] = (node(pw[i])*B).x;
    rep(i,n) p[i+1] = (node(p[i])*B+s[i]).x;
    auto sec = [&](int l, int r) {
        int res = (node(p[r])-node(p[l])*pw[r-l]).x;
        return res;
    };
    vi res((n+1)>>1);
    if ((~n&1) && s[(n-1)>>1] == s[n>>1]) res[(n-1)>>1] = 1; else res[(n-1)>>1] = -1;
    per(i,(n-1)>>1) {
        res[i] = res[i+1] + 2;
        for (; res[i] > -1; res[i] -= 2)
            if (sec(i, i+res[i]) == sec(n-i-res[i], n-i)) break;
    }
    rep(i,(n+1)>>1) cout << res[i] << ' ';
    cout << '\n';
    return 0;
}