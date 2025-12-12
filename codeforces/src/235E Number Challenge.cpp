//
// Created by Psy.C on 2025/12/12.
//
/*
*m[]存储莫比乌斯函数值μ(n)
p[]存储质数列表
flag[]标记合数
init()函数使用线性筛法计算莫比乌斯函数：
初始化μ(1)=1
对于质数p，μ(p)=-1
对于合数n：
如果n包含某个质因子的平方，则μ(n)=0
否则μ(n)=(-1)^k，k为n的不同质因子个数
 *
*f[d]存储函数值，s[]存储中间结果
使用数论分块优化计算：
对于每个d，计算f(d) = Σ⌊n/l⌋ (l从1到n)
其中n = ⌊c/d⌋
利用⌊n/l⌋值相同的连续区间进行批量计算
 *
*根据莫比乌斯反演公式计算s数组：
对于每个i，如果μ(i)≠0，则w = μ(i) × f(i)
将w累加到所有i的倍数位置上
即：s[j] = Σ(i|j) μ(i) × f(i)
 *
*遍历所有1≤i≤a, 1≤j≤b的数对
如果gcd(i,j)=1，则将(a/i)×(b/j)×s[i×j]加入答案
使用位运算进行模运算
 *
 *将O(n²)的暴力算法优化到接近O(n)的时间复杂度
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 2010
using namespace std;

constexpr int mod = 1<<30, mask = mod - 1;

int m[N*N], p[N*N];
bool flag[N*N];
void init(const int x) {
    int sz = 0; m[1] = 1;
    for (int i = 2; i < x; ++i) {
        if (!flag[i]) p[++sz] = i, m[i] = -1;
        for (int j = 1; j <= sz && static_cast<ll>(i) * p[j] < x; ++j) {
            flag[i * p[j]] = true;
            if (i % p[j] == 0) { m[i * p[j]] = 0; break; }
            m[i * p[j]] = -m[i];
        }
    }
}

int main() {
    fast;
    int a, b, c; cin>>a>>b>>c; init(a * b);
    int f[N], s[N*N];
    for (int d = 1; d <= c; ++d) {
        const int n = c / d;
        for (int l = 1, r; l <= n; l = r + 1) {
            r = n / (n / l);
            f[d] = (f[d] + (n / l) * (r - l + 1)) & mask;
        }
    }
    for (int i = 1; i <= c; ++i) {
        if (!m[i]) continue;
        int w = m[i] * f[i]; w += w < 0 ? mod : 0;
        for (int j = i; j <= a * b; j += i) s[j] = (s[j] + w) & mask;
    }
    int ans = 0;
    for (int i = 1; i <= a; ++i) for (int j = 1; j <= b; ++j) {
        if (__gcd(i, j) == 1) ans = static_cast<int>((ans +
            static_cast<ll>(a / i)*(b/j)*s[i*j]&mask)&mask);
    }
    cout << ans;
    return 0;
}