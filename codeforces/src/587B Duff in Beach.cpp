//
// Created by Psy.C on 2026/3/18.
//
/**
a[]: 原始输入数组
b[]: 用于排序的副本数组
p[]: 位置映射数组
mp: 映射表，将值映射到索引
v[][]: 二维向量，用于动态规划存储

创建映射，将排序后的值映射到它们的排名
这样可以压缩数值范围，便于后续处理
将第一层DP表初始化为全1
记录每个元素在排序后数组中的位置（排名）
计算有效限制m，取l/n和k的最小值
从第2层到第m+1层构建DP表
对于每一层i，根据前一层计算前缀和
s维护前一层的运行总和
x跟踪压缩坐标系中的当前位置
使用模运算防止溢出
遍历1到m层的所有元素
将贡献加到总答案中
乘以可用位置数：(l/n - i + 1)
应用模运算
处理l不能被n整除的剩余部分
对原数组a的前l%n个元素：
使用映射找到它们的排名
将所有可能层级的贡献加到答案中

时间复杂度约为O(m·n)，其中m=min(l/n, k)。

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+5, mod = 1e9+7;
ll n, l, k, ans;
int a[N], b[N], p[N];
map<int, int> mp;
vector<ll> v[N];
int main() {
    fast;
    cin >> n >> l >> k;
    for (int i = 0; i < n; ++i) cin >> a[i], b[i] = a[i];
    sort(b, b + n);
    for (int i = 0; i < n; ++i) mp[b[i]] = i;
    for (int i = 0; i < n; ++i) {
        v[1].push_back(1);
        p[i] = mp[b[i]];
    }
    ll m = min(l/n, k);
    for (int i = 2; i <= m+1; ++i) {
        ll s = 0; int x = 0;
        for (int j = 0; j < n; ++j) {
            while (x <= p[j]) s = (s + v[i-1][x++]) % mod;
            v[i].push_back(s);
        }
    }
    for (int i = 1; i <= m; ++i)
        for (int j = 0; j < n; ++j)
            ans = (ans + v[i][j]*((l/n-i+1)%mod)) % mod;
    int res = l % n;
    for (int i = 0; i < res; ++i) {
        int x = mp[a[i]];
        for (int j = 1; j <= min(k, l/n+1); ++j)
            ans = (ans + v[j][x]) % mod;
    }
    cout << ans << '\n';
    return 0;
}