//
// Created by Psy.C on 2026/10/27.
//

/**
真正学会的起点..
v[r] 存放所有"当前余数为 r"的下标。
目标是让 v[r].size() == t 对每个 r 成立，其中 t = n/m。
while (v[i].size() > t)：只要余数类 i 的数量还多于目标 t，就需要往外"吐出"多余的数。

r = max(1ll*i, r)：从不低于 i 的位置开始找"空缺"的目标余数类。

while (v[r%m].size() >= t) r++：向后循环扫描（r 会模 m 回绕，形成环形），找到第一个还没满（size < t）‍的余数类 r%m。

tmp = min(v[i].size()-t, t-v[r%m].size())：从 i 里能转出的数量 v[i].size()-t，与目标类还能接收的数量 t - v[r%m].size()，取较小者作为本次实际转移个数 tmp。

内层 for (j=1..tmp)：

x = (r%m - i + m) % m：从余数 i 移到余数 r%m 需要加的数值（环形距离，非负）。
sum += x：累加总代价。
a[v[i].back()] += x：把 i 类的最后一个元素（下标 v[i].back()）加上 x，使它余数变为 r%m。
v[i].pop_back()：从 i 类移除该元素。
v[r%m].push_back(a[v[i].size()])：把调整后的下标放入目标类。（注意这里 push 的是 a[v[i].size()]，即被弹出的那个下标 after pop 后 v[i].size() 正好等于被弹出元素的下标。）
一个小细节：v[r%m].push_back(a[...]) 参数其实是那个被转移元素的下标，写法稍显绕，但作用是把下标放入目标桶
第一行输出最小总代价 sum。
第二行输出调整后的数组 a[1..n]（每个元素已按转移累加过 gap）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2*1e5;

int n, m, t;
ll a[N+5], sum;
vector<int> v[N+5];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i]; v[a[i]%m].push_back(i);
    }
    ll r = 0; t = n/m;
    for (int i = 0; i < m; i++) {
        while (v[i].size() > t) {
            r = max(1ll*i, r);
            while (v[r%m].size() >= t) r++;
            ll tmp = min(v[i].size()-t, t-v[r%m].size());
            for (int j = 1; j <= tmp; j++) {
                ll x = (r%m - i + m) % m; sum += x;
                a[v[i].back()] += x; v[i].pop_back();
                v[r%m].push_back(a[v[i].size()]);
            }
        }
    }
    cout << sum << '\n';
    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    return 0;
}