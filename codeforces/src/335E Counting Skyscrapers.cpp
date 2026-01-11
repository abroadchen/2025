//
// Created by Psy.C on 2026/1/11.
//
/**
* 1. 生日悖论相关计算
假设有 2^i 个可能的选择，
每次随机选择不冲突的概率是 (1 - 1/2^i)
连续 (j-1) 次都不冲突的概率是 (1 - 1/2^i)^(j-1)
2. 哈希碰撞概率
哈希表大小为 2^i，
插入第j个元素时，
前面(j-1)个元素都没有冲突的概率是 (1 - 1/2^i)^(j-1)
3. 二叉树或平衡树分析
在某种树结构中，
第i层有 2^i 个位置，
前(j-1)个元素在该层都不冲突的概率
 *
*n：总数量
j：当前循环变量
(n-j)：剩余数量（从j+1到n的数量）
 *
*(n-j)：考虑剩余的元素数量
(1./m[2*i])：某层的概率权重（1/2^(2i)）
t：连续不冲突的概率
最后一项：修正系数
 *
 *i：树的层数或哈希表的级别
 */
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

double ksm(double a, int b) {
    double t = 1.;
    while (b) {
        if (b&1) t = t * a;
        a = a * a;
        b >>= 1;
    }
    return t;
}


int main() {
    fast;
    char s[10]; int n, h; cin >> s >> n >> h;
    if (s[0] == 'B') { cout << n << '\n'; return 0; }//字符串s的第一个字符是'B'
    double ans = n, m[200]; m[0] = 1.;
    for (int i = 1; i <= 2*h; ++i) m[i] = m[i-1] * 2.;//m[i] = 2^i
    for (int i = 1; i <= h; ++i) for (int j = 1; j <= n; ++j) {
        const double t = ksm(1. - 1. / m[i], j - 1);
        ans += 1.*(n-j)*(1./m[2*i])*t*(m[i]-m[i-1]*(1+(j-1)/(m[i]-1.)));
    }
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}