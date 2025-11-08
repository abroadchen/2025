//
// Created by Psy.C on 2025/10/22.
//
/*
 *创建字符串向量s存储网格内容
*r(m): 每行中'.'的数量（行统计）
c(n): 每列中'.'的数量（列统计）
pr(m, -1): 每行中'X'的列位置，初始化为-1
pc(n, -1): 每列中'X'的行位置，初始化为-1
 *
*遍历整个网格，如果发现'X'，记录其位置：
pr[i] = j: 第i行的'X'在第j列
pc[j] = i: 第j列的'X'在第i行
 *
*计算行之间的贡献：对于任意两行i和j，贡献值为r[i] * r[j] * |j - i|
计算列之间的贡献：对于任意两列i和j，贡献值为c[i] * c[j] * |j - i|
 *
*对于每一行i，如果该行有'X'（pr[i] != -1）：
计算该'X'对答案的贡献：pr[i] * (n - pr[i] - 1) * 4
向下检查连续的行，如果这些行也有'X'且列位置单调递增，则累加贡献
向上检查连续的行，如果这些行也有'X'且列位置单调递增，则累加贡献
 *
*对于每一列i，如果该列有'X'（pc[i] != -1）：
计算该'X'对答案的贡献：pc[i] * (m - pc[i] - 1) * 4
向右检查连续的列，如果这些列也有'X'且行位置单调递增，则累加贡献
向左检查连续的列，如果这些列也有'X'且行位置单调递增，则累加贡献
 *
 *计算所有'.'的总数：accumulate(r.begin(), r.end(), 0ll)将所有行的'.'数量相加
 *将总数平方，得到所有可能的点对数量
输出结果：tot/cnt，即平均曼哈顿距离
 */
#include <iomanip>
#include <vector>
#include <ios>
#include <iostream>
#include <numeric>
#define rep(i,n) for(int i=0;i<(n);++i)
#define repd(i,n) for(int i=(n);i>=0;--i)
using namespace std;

typedef long long ll;
typedef long double ld;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int m, n; cin>>m>>n;
    vector<string> s(m);
    rep(i,m) cin>>s[i];
    vector<ll> r(m), c(n), pr(m, -1), pc(n, -1);
    rep(i,m) rep(j,n) {
        r[i] += s[i][j] == '.';
        c[j] += s[i][j] == '.';
    }
    rep(i,m) rep(j,n) if (s[i][j] == 'X') { pr[i] = j; pc[j] = i; }
    ll tot(0);
    rep(i,m) rep(j,m) tot += r[i] * r[j] * abs(j - i);
    rep(i,n) rep(j,n) tot += c[i] * c[j] * abs(j - i);
    rep(i,m) if (pr[i] != -1) {
        tot += pr[i] * (n - pr[i] - 1) * 4;
        for (int j = i + 1; j < m; ++j) {
            if (pr[j] == -1 || pr[j] < pr[j - 1]) break;
            tot += pr[i] * (n - pr[j] - 1) * 4;
        }
        repd(j,i-1) {
            if (pr[j] == -1 || pr[j] < pr[j + 1]) break;
            tot += pr[i] * (n - pr[j] - 1) * 4;
        }
    }
    rep(i,n) if (pc[i] != -1) {
        tot += pc[i] * (m - pc[i] - 1) * 4;
        for (int j = i + 1; j < n; ++j) {
            if (pc[j] == -1 || pc[j] < pc[j - 1]) break;
            tot += pc[i] * (m - pc[j] - 1) * 4;
        }
        repd(j,i-1) {
            if (pc[j] == -1 || pc[j] < pc[j + 1]) break;
            tot += pc[i] * (m - pc[j] - 1) * 4;
        }
    }
    ll cnt = accumulate(r.begin(), r.end(), 0ll);
    cnt *= cnt;
    cout << fixed << setprecision(12) << (ld)tot / cnt;
    return 0;
}