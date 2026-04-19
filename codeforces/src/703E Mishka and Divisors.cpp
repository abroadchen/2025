//
// Created by Psy.C on 2026/4/18.
//
/**
v: k的所有因子
k: 目标数
m: 因子数量
mp: 因子到索引的映射
找出k的所有因子
排序因子
建立因子到索引的映射
n: 数组长度
a[N]: 输入数组
b[N]: gcd(a[i], k)数组
f[i][j]: 前i个元素中，使GCD达到v[j]所需的最小长度和最小代价

特殊情况：如果k=1，直接找最小元素
初始化第一行，表示不可能的状态
f[i][j] = f[i-1][j]: 不选择第i个元素
int pre = mp[v[j]/gcd(v[j], b[i])]: 计算选择第i个元素后能达到v[j]需要的前置状态
pll t = {f[i-1][pre].first+1, f[i-1][pre].second+a[i]}: 选择第i个元素的新状态
f[i][j] = min(f[i][j], t): 状态转移
如果无解，输出-1
否则输出最小长度和具体的元素位置
重构解的过程：从后往前，如果状态发生变化说明选择了该元素
O(n * d(k)): n是数组长度，d(k)是k的因子个数


第一部分：f[i-1][pre].first+1
f[i-1][pre].first: 前i-1个元素中，达到状态pre所需的最小长度
+1: 选择当前第i个元素，长度增加1
含义：选择第i个元素后，达到目标状态j的总长度
第二部分：f[i-1][pre].second+a[i]
f[i-1][pre].second: 前i-1个元素中，达到状态pre的最小代价
+a[i]: 加上当前元素的值
含义：选择第i个元素后，达到目标状态j的总代价

k：当前需要达到的GCD目标
b[i]：第i个元素对k的贡献
gcd(k, b[i])：k和b[i]的公共因子
k /= gcd(k, b[i])：更新剩余需要达到的GCD目标
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define pll pair<ll, ll>
using namespace std;
constexpr int N = 1e3+5, M = 8e3;

vector<ll> v;
ll k, m;
map<ll, int> mp;
void init() {
    v.clear();
    for (ll i = 1; i*i <= k; ++i) {
        if (k%i == 0) {
            v.push_back(i);
            if (i*i != k) v.push_back(k/i);
        }
    }
    ranges::sort(v);
    m = v.size()-1; mp.clear();
    for (int i = 0; i <= m; ++i) mp[v[i]] = i;
}

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll n, a[N], b[N];
pll f[N][M];
int main() {
    fast;
    cin >> n >> k; init();
    for (int i = 1; i <= n; ++i) cin >> a[i], b[i] = gcd(a[i], k);
    if (k == 1) {
        cout << "1\n";
        cout << min_element(a+1, a+1+n) - a << '\n';
        return 0;
    }
    for (int j = 1; j <= m; ++j) f[0][j] = {n+1, 0};
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j) {
            f[i][j] = f[i-1][j];
            int pre = mp[v[j]/gcd(v[j], b[i])];
            pll t = {f[i-1][pre].first+1, f[i-1][pre].second+a[i]};
            f[i][j] = min(f[i][j], t);
        }
    if (f[n][m].first > n) cout << "-1\n";
    else {
        cout << f[n][m].first << '\n';
        for (int i = n; i >= 1; --i) {
            if (f[i][mp[k]] != f[i-1][mp[k]]) {
                cout << i << ' ';
                k /= gcd(k, b[i]);
            }
        }
    }
    cout << '\n';
    return 0;
}