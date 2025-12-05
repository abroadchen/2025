//
// Created by Psy.C on 2025/12/4.
//
/*
*mp[N][N]：存储输入矩阵数据
m1[N]：存储每行的计算结果
m2[N]：存储每列的计算结果
 *
*mp[i][m]：第i行所有元素的和（存储在第m列）
mp[n][j]：第j列所有元素的和（存储在第n行）
 *
*计算每行的权重和：
对于每个行位置i，计算与其他行的距离权重
距离权重公式：(abs(i-j)-0.5) * 4 * (abs(i-j)-0.5) * 4
将权重乘以对应行的总和累加到sum中
结果存储在m1[i]中
*计算每列的权重和：
类似于行的计算，但是针对列
使用mp[n][k++]获取各列的总和
结果存储在m2[i]中
*寻找最优解：
遍历所有可能的行列组合(i,j)
计算总代价m1[i] + m2[j]
记录最小代价及对应的坐标
 *
 *O(n²)
 */
#include <iostream>
#include <cstring>
#include <climits>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1010
#define rep(i,n) for(ll i=0;i<n;++i)
using namespace std;

ll mp[N][N], m1[N], m2[N];

int main() {
    fast;
    ll n, m;
    while (cin >> n >> m) {
        memset(mp, 0, sizeof(mp));
        rep(i,n) rep(j,m) cin >> mp[i][j];
        rep(i,n) rep(j,m) {
            mp[i][m] += mp[i][j];
            mp[n][j] += mp[i][j];
        }
        rep(i,n+1) {
            ll sum = 0, k = 0;
            rep(j,n+1) {
                if (i == j) continue;
                const ll dif = abs(i-j);
                const double diff = static_cast<double>(dif) - 0.5,
                coef = diff * 4. * diff * 4.;
                sum += static_cast<ll>(coef*static_cast<double>(mp[k++][m]));
            }
            m1[i] = sum;
        }
        rep(i,m+1) {
            ll sum = 0, k = 0;
            rep(j,m+1) {
                if (i == j) continue;
                const ll dif = abs(i-j);
                const double diff = static_cast<double>(dif) - 0.5,
                coef = diff * 4. * diff * 4.;
                sum += static_cast<ll>(coef*static_cast<double>(mp[n][k++]));
            }
            m2[i] = sum;
        }
        ll mi = LLONG_MAX, mx = 0, my = 0;
        rep(i,n+1) rep(j,m+1) if (m1[i] + m2[j] < mi) {
            mi = m1[i] + m2[j];
            mx = i, my = j;
        }
        cout << mi << '\n' << mx << ' ' << my << '\n';
    }
    return 0;
}