//
// Created by Psy.C on 2026/3/8.
//
/**
e[N]：标记数组，1表示已访问
mp[N]：莫比乌斯函数值
p[N]：素数数组
cnt：素数计数
mp[1] = 1：μ(1) = 1
mp[i] = -1：当i是素数时
mp[p[j]*i] = 0：当i包含素因子p[j]时
mp[p[j]*i] = -mp[i]：否则

h[x]：因子x的出现次数
f[x]：上次计算的C(h[x],2)值
ans：当前答案
h[x]*(h[x]-1)/2：从h[x]个数中选2个的组合数
使用莫比乌斯函数的容斥原理
对x的所有因子进行更新
v为1表示添加，-1表示删除
遍历所有因子，对每个因子调用add函数

如果位置x已被激活：删除a[x]，更新vis[x]为0
否则：添加a[x]，更新vis[x]为1
∑_{d|gcd(a,b)} μ(d) = [gcd(a,b)=1]
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e6+1, M = 5e5;

int e[N], mp[N], p[N], cnt;
void get() {
    e[1] = 1, mp[1] = 1;
    for (int i = 2; i <= M; ++i) {
        if (!e[i]) p[++cnt] = i, mp[i] = -1;
        for (int j = 1; j <= cnt; ++j) {
            if (p[j]*i > M) break;
            mp[p[j]*i] = i%p[j]==0 ? 0 : -mp[i];
            e[p[j]*i] = 1;
            if (i%p[j]==0) break;
        }
    }
}

int h[N], f[N], ans;
void add(int x, int v) {
    h[x] += v;
    ans += (h[x]*(h[x]-1)/2 - f[x])*mp[x];
    f[x] = h[x]*(h[x]-1)/2;
}

void update(int x, int v) {
    for (int i = 1; i*i <= x; ++i)
        if (x%i==0) {
            add(i, v);
            if (i*i != x) add(x/i, v);
        }
}

int n, q, a[N], vis[N];
signed main() {
    fast;
    get(); cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, x; i <= q; ++i) {
        cin >> x;
        if (vis[x]) update(a[x], -1), vis[x] = 0;
        else {
            update(a[x], 1);
            vis[x] = 1;
        }
        cout << ans << '\n';
    }
    return 0;
}