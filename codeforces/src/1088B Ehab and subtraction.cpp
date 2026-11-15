//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
n 输入个数，m 需要输出的数量，a[N] 存输入的 n 个数。
unique 把相邻重复元素移到末尾，返回去重后末尾的迭代器
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); ++i)
using namespace std;

constexpr int N = 1e5+5;

int n, m, a[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    sort(a+1, a+n+1);
    int tot = unique(a+1,a+n+1)-a-1;//去重后剩余不同元素个数 = 下标尾 - 首
    rep(i,min(tot,m)) cout << a[i]-a[i-1] << '\n';//去重后 相邻两数的差
    for (int i = min(tot,m)+1; i <= m; i++) cout << 0 << '\n';//如果还应输出到 m 个
    return 0;
}