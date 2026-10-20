//
// Created by Psy.C on 2026/10/20.
//
/**
读入 n（名称个数）、k（分组次数）、m2（查询次数）。
读入 n 个名称存入 a[0..n-1]
读入每个名称的初始价格 x。
mp[a[i]] = x：map<string,ll> 把名称 → 价格存进 mp。
p[i] = x：把价格也存进数组 p[0..n-1]，下标对应名称顺序（后面分组操作用下标索引）。
注意：mp 和 p 存的是同一份初始价格，只是访问方式不同——mp 用名字查，p 用下标查
每次分组：

先读本次组内元素个数 m。
y = inf：把最小值初始化为无穷大。
内层循环第一遍：
读入组内每个元素的下标 x（注意代码里 x-1 才是数组下标，说明输入是 1-based）。
把 x 存进临时 vector t。
y = min(y, p[x-1])：用 p[] 数组（初始价格，而非当前 mp 价格）‍统计组内最低初始价格。
内层循环第二遍：
遍历组内每个下标 t[j]-1，把对应名称 a[t[j]-1] 在 mp 中的价格统一覆盖为组内初始最低价 y。
关键点：

分组时找的是 p[]（初始价格）里的最小值，而不是 mp 当前值。
然后把这组里所有名称的 mp 价格全部设为该最低价
cnt 累加每次查询名称 s 的当前价格 mp[s]。
输出 cnt（后面输出语句原本可能是 << '\n' 或还有更多输出，此处为空格）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define ll long long
using namespace std;
constexpr ll inf = 1e11;

int main() {
    fast;
    int n, k, m2; cin>>n>>k>>m2;
    string a[n];
    rep(i,n) cin>>a[i];
    ll x, p[n], y;
    map<string,ll> mp;
    rep(i,n) cin >> x, mp[a[i]] = x, p[i] = x;
    int m;
    rep(i,k) {
        cin >> m; y = inf;
        vector<int> t;
        rep(j,m) { cin >> x; t.push_back(x); y = min(y, p[x-1]); }
        rep(j,m) mp[a[t[j]-1]] = y;
    }
    ll cnt = 0;
    string s;
    rep(i,m2) { cin >> s; cnt += mp[s]; }
    cout << cnt << ' ';
    return 0;
}