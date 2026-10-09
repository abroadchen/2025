//
// Created by Psy.C on 2026/10/9.
//
/**
读入
n
n 个角度
只分成一份一定有一个人拿了全部，另一个人什么都没有
前两重循环枚举一个人所能分到的披萨度数的所有方案
tot则是用于累加上面求出的每一种方案所能得到的度数
累加并比较和最优解的距离
因为只求了一个人的,所以最后的结果要*2 
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 4e2;
int f[N], tot, t = N;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> f[i];
    if (n == 1) { cout << "360\n"; return 0; }
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j) {
            tot = 0;
            for (int k = i; k <= j; ++k)//枚举每种方案
                tot += f[k], t = min(t, abs(tot-180));
        }
    cout << t*2 << '\n';
    return 0;
}