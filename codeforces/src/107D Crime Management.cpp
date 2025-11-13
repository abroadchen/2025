//
// Created by Psy.C on 2025/11/13.
//
/*
*定义矩阵乘法函数mul：
计算两个n×n矩阵的乘积
结果对mod取模
*定义矩阵快速幂函数matpow：//使用矩阵快速幂优化O(n)的转移计算到O(log n)
计算矩阵a的d次幂
使用分治法：a^d = (a^(d/2))^2，如果d为奇数再乘以a
 *
 *读入n（步数）和c（字符种类数）
*声明映射code：字符→整数集合
读入c个字符的约束条件，每个字符对应一些整数
 *
*计算状态空间大小：
kr：每个字符的周期
mn：每个字符在状态编码中的权重
per：每个字符的累积权重
A：总状态数
 *
 *声明转移矩阵a，大小为A×A
 *定义解码函数：将整数状态转换为字符状态映射
 *定义编码函数：将字符状态映射转换为整数状态
 *
*构建状态转移矩阵：
对每个状态w
对每个字符，将其状态加1（模周期）
计算转移后的状态to
在转移矩阵中记录a[to][w]++
 *
*计算n步后的状态分布：memo = a^n
统计满足条件的最终状态：
对每个最终状态to
检查是否每个字符的状态都能被对应的约束整除
如果都满足，累加概率到ans
 */
#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;


typedef long long ll;
typedef vector<ll> vll;
typedef vector<vector<ll>> vvll;
const ll mod = 12345;

vvll mul(vvll& a, vvll& b) {
    int n = a.size();
    vvll c(n, vll(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k)
                c[i][j] += a[i][k] * b[k][j];
            c[i][j] %= mod;
        }
    }
    return c;
}

vvll matpow(vvll& a, ll d) {
    if (d == 0) {
        vvll ret(a.size(), vll(a.size(), 0));
        for (int i = 0; i < a.size(); ++i) ret[i][i] = 1;
        return ret;
    }
    vvll x = matpow(a, d / 2);
    x = mul(x, x);
    if (d % 2) x = mul(x, a);
    return x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n; int c; cin >> n >> c;
    map<char, set<int>> code;
    for (int i = 0, k; i < c; ++i) {
        string s; cin >> s >> k;
        code[s[0]].insert(k);
    }
    int A = 1;
    map<char, int> kr, mn, per;
    for (auto x : code) {
        int cur = 1;
        for (auto y : x.second) cur *= y;
        kr[x.first] = cur;
        mn[x.first] = A;
        A *= cur;
        per[x.first] = A;
    }
    vvll a(A, vll(A, 0));
    auto decode = [&](int w) {
        map<char, int> res;
        for (auto x : per) {
            res[x.first] = (w % per[x.first]) / mn[x.first];
        }
        return res;
    };
    auto encode = [&](const map<char, int>& res) {
        int ret = 0;
        for (auto x : res) {
            ret += x.second * mn[x.first];
        }
        return ret;
    };
    for (int w = 0; w < A; ++w) {
        auto res = decode(w);
        for (auto x : per) {
            char cur = x.first;
            res[cur] = (res[cur] + 1) % kr[cur];
            int to = encode(res);
            res[cur] = (res[cur] + kr[cur] - 1) % kr[cur];
            a[to][w]++;
        }
    }
    auto memo = matpow(a, n);
    int ans = 0;
    for (int to = 0; to < A; ++to) {
        auto res = decode(to);
        int g = 0;
        for (auto x : res) {
            for (auto l : code[x.first]) if (x.second % l == 0) {
                g++;
                break;
            }
        }
        if (g == res.size()) ans += memo[to][0];
    }
    cout << ans % mod;
    return 0;
}