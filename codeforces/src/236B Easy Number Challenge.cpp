//
// Created by Psy.C on 2025/12/12.
//
/*
*sum[]数组存储每个数的约数个数
第一个循环初始化：
sum[1] = 1（1只有1个约数）
其他数初始为2（每个数至少有1和自身两个约数）
第二个双重循环计算每个数的确切约数个数：
对于每一对(i,j)，其中i≤j且i*j<N
如果i≠j，则i*j有两个不同的约数i和j，所以加2
如果i=j，则i*j有一个平方约数i，所以加1
实际上这个函数是在计算每个正整数的约数个数函数d(n)
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000001
#define mod 1073741824
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

int sum[N];
void get() {
    for (int i = 1; i < N; ++i) {
        if (i == 1) sum[i] = 1; else sum[i] = 2;
    }
    for (int i = 2; i * i < N; ++i) {
        for (int j = i; j * i < N; ++j) {
            if (i != j) sum[i * j] += 2;
            else sum[i * j] += 1;
        }
    }
}

void add(ll& x, const ll y) { x += y; x %= mod; }

int main() {
    fast;
    get();
    int a, b, c; cin>>a>>b>>c;
    ll ans = 0;
    rep(i,a) rep(j,b) rep(k,c) {
        add(ans, sum[i * j * k]);
    }
    cout << ans << '\n';
    return 0;
}