//
// Created by Psy.C on 2026/9/26.
//
/**
用"快速乘 + 每次取 min(…, lim)"实现带饱和的乘法：任何结果超过 lim 就压成 lim，防止 long long 溢出，同时也让"是否超过阈值"的判断正确。
这是下方矩阵乘法中乘法运算的安全实现
一个自定义矩阵类，* 重载为矩阵乘法（内部用 mul 保证不溢出、封顶 lim）。
ksm(t)：标准矩阵快速幂，支持幂 t=0（单位矩阵）、1、2，以及奇偶拆分。
乘法把累加后的每个元素也 min(…, lim) 截断
核心观察：一次前缀和操作 arr[i] += arr[i-1]（等价于把下三角全 1 的矩阵乘到列向量上）。因为下标小的贡献会沿前缀传递到大的。
这里把"做 p 轮"转化为"把下三角全 1 的转移矩阵自乘 p 次，再乘初始列向量"→ 用快速幂 O(lim²·log p) 判断 p 轮是否有人 ≥ lim。
返回 true 表示 p 轮内能达标（用于二分）
把数组前导 0 去掉（保留从第一个非零开始的部分；前导零对前缀和没有贡献）。返回新长度。
这样能缩小问题规模（因为前导 0 不影响第一个非零之后的前缀增长）
向上整除：⌈a/b⌉

n == 2 特判（最简单情形）‍
只有两个数时，第 i 轮后 arr[2] 大概按 arr[1]*i + arr[2] 增长（前缀和线性），直接算出需要的轮数 ⌈(lim-arr[2])/arr[1]⌉，负数取 0
已有数 ≥ lim → 直接 0 轮
若一开始就有元素达标，答案是 0。
n ≥ 10：直接线性模拟（因为矩阵是 n×n 下三角，n 大了矩阵乘法太慢）
n 较大时放弃矩阵快速幂，直接按"X轮"迭代前缀和，直到某个数 ≥ lim 就输出轮数。可行性前提是 lim 不太大。
否则（n 较小，如 ≤9）：用矩阵快速幂 + 二分答案
二分最小轮数 p，check(p) 用矩阵快速幂判断 p 轮能否达标。二分下界 0、上界 inf（一个很大的数）。
输出最小满足条件的轮数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2e5+1, inf = 64356879284;

int lim;
int mul(int a, int b) {
    if (b == 0) return 0;
    int r = mul(a, b>>1);
    r = min(r+r, lim);//翻倍并截断到 lim
    if (b&1) return min(r+a, lim);
    return r;
}

struct Matrix: vector<vector<int>> {
    Matrix _construct(int l = 0, int w = 0, int v = 0) {
        assign(l, vector<int>(w, v));
        return *this;
    }
    Matrix(int l = 0, int w = 0, int v = 0) { assign(l, vector<int>(w, v)); }
    unsigned szL() const { return size(); }
    unsigned szW() const { return empty() ? 0 : (*this)[0].size(); }

    Matrix operator*(const Matrix& o) const {
        if (szW() != o.szL()) return {0, 0, 0};
        int l = szL(), w = o.szW(), p = szW();
        Matrix ret(l, w, 0);
        for (int i = 0; i < l; ++i)
            for (int j = 0; j < w; ++j)
                for (int k = 0; k < p; ++k) {
                    ret[i][j] += mul((*this)[i][k], o[k][j]);
                    ret[i][j] = min(ret[i][j], lim);
                }
        return ret;
    }

    Matrix operator+=(const Matrix& o) {
        *this = (*this)*o;
        return *this;
    }

    Matrix ksm(int t) {
        if (t == 0) {
            Matrix ret(szL(), szL(), 0);
            for (int i = 0; i < szL(); ++i) ret[i][i] = 1;
            return ret;
        }
        if (t == 1) return *this;
        if (t == 2) return (*this)*(*this);
        Matrix tmp = ksm(t/2);
        if (t%2 == 0) return tmp*tmp;
        return (*this)*tmp*tmp;
    }
};

int n, arr[N];
bool check(int p) {
    Matrix mt(n, n, 0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= i; ++j) mt[i][j] = 1;
    Matrix ar(n, 1, 0);
    for (int i = 0; i < n; ++i) ar[i][0] = arr[i+1];
    ar = mt.ksm(p)*ar;
    for (int i = 0; i < n; ++i)
        if (ar[i][0] >= lim) return true;
    return false;
}

int n0(int *arr, int len) {
    int ptr = 0;
    for (int i = 1; i <= len; ++i)
        if (arr[i] != 0 || ptr) arr[++ptr] = arr[i];
    return ptr;
}

int get(int a, int b) { return a/b + bool(a%b); }


signed main() {
    fast;
    cin >> n >> lim;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    n = n0(arr, n);
    if (n == 2) {
        cout << max(0ll, get((lim-arr[2]), arr[1])) << '\n';
        return 0;
    }
    for (int i = 1; i <= n; ++i)
        if (arr[i] >= lim) { cout << "0\n"; return 0; }
    if (n >= 10) {
        int cnt = 0;
        while (true) {
            cnt++;
            for (int i = 1; i <= n; ++i) {
                arr[i] += arr[i-1];
                if (arr[i] >= lim) {
                    cout << cnt << '\n';
                    return 0;
                }
            }
        }
    }
    int l = 0, r = inf;
    while (l < r) {
        int mid = (l+r)/2;
        if (check(mid)) r = mid;
        else l = mid+1;
    }
    cout << l << '\n';
    return 0;
}