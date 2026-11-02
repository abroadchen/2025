//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
d[x] 存 x 的所有不同质因子（不含指数）
h[j] = 质数 j 在整体中出现的最大指数（决定 LCM 里 j 的指数）。
hv[j] = 出现该最大指数的元素个数（是否"独一无二"）。
if (h[a[i]]) a[i]--：当这个值本身已作为整体贡献过时，整体退化（试探"去重后能不能少贡献"）
ans = Π 质数^最大指数，即全体数的 LCM（取模 mod）‍。
对每个元素，检查它是否"独占"了某个质因子的最大指数（c==h[j] && hv[j]==1）。
若存在这样完全不独占任何关键质因子的元素，去掉它 LCM 不变 → f=1
若存在"可删且 LCM 不变"的元素，答案 = LCM + 1（f=1），否则答案 = LCM
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 2e6+5, mod = 1e9+7;

bool cmp(int x, int y) { return x > y; }

vector<int> d[N];
int a[N], h[N], hv[N];
signed main() {
    fast;
    for (int i = 2; i < N; i++)
        if (d[i].empty()) for (int j = i; j < N; j += i)
            d[j].push_back(i);//把质数 i 加到所有倍数 j 的因子表
    int n, ans(1), f(1); cin >> n;
    rep(i,n) cin >> a[i];
    sort(a+1, a+1+n, cmp);
    rep(i,n) {
        if (h[a[i]]) a[i]--;//如果这个数已在"贡献表"里, 减1再处理(处理重复/退化)
        for (int j : d[a[i]]) {
            int x = a[i], c = 0;
            while (x%j == 0) x/=j, c++;//统计质因子 j 的指数 c
            if (c > h[j]) h[j] = c, hv[j] = 1;//更新最大指数, 并标记出现1次
            else if (c == h[j]) hv[j]++;//相同指数, 出现次数+1
        }
    }
    rep(i,N-1) rep(j,h[i]) ans = ans*i%mod;
    rep(i,n) {
        f = 1;
        for (int j : d[a[i]]) {
            int x = a[i], c = 0;
            while (x%j == 0) x/=j, c++;
            if (c == h[j] && hv[j] == 1) f = 0;
        }
        if (f) break;
    }
    cout << (ans+f)%mod;
    return 0;
}