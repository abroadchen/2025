//
// Created by Psy.C on 2026/4/25.
//
/**
mod, mod1: 两个大质数，用于双哈希避免冲突
a0[i], a1[i]: 存储 seed^i % mod 的幂次
ha0[i], ha1[i]: 存储字符串前缀哈希值
vis[i]: 记录第i个子串对应的字符串编号
dp: 存储给定字符串哈希值到编号的映射
st: 用于检查是否有重复

从位置 (j-1)*k+i 开始的长度为k的子串的哈希值：
ha0[j*k+i]: 前缀哈希到结束位置
ha0[(j-1)*k+i]*a0[k]: 减去起始位置之前的贡献
+mod 防止负数结果

时间复杂度
O(k × n) = O(kn)，其中每次检查需要O(n)时间
总体复杂度取决于k和n的大小
空间复杂度
O(g + n)，主要是存储目标字符串哈希和中间结果
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define pll pair<ll, ll>
using namespace std;
constexpr int N = 2e6+7, mod = 1e9+7, mod1 = 19260817;

int n, k;
ll a0[N], a1[N], seed = 31, ha0[N], ha1[N], vis[N];
char str0[N], str[N];
set<int> st;
map<pll, int> dp;
int main() {
    fast;
    cin >> n >> k; a0[0] = a1[0] = 1;
    for (int i = 1; i <= k; ++i)//初始化幂次数组，用于滚动哈希计算
        a0[i] = a0[i-1]*seed % mod, a1[i] = a1[i-1]*seed % mod1;
    cin >> str0;
    int len = n*k, g;
    for (int i = 0; i < len; ++i) str0[i+len] = str0[i];//将原字符串扩展一倍，方便处理循环情况
    cin >> g;
    for (int i = 0; i < g; ++i) {
        cin >> str;
        pll p;
        for (int j = 0; j < k; ++j) {
            p.first = (p.first*seed + str[j] - 'a') % mod;
            p.second = (p.second*seed + str[j] - 'a') % mod1;
        }
        dp[p] = i + 1;//哈希值到编号的映射
    }
    for (int i = 1; str0[i-1]; ++i) {
        ha0[i] = (ha0[i-1]*seed + str0[i-1] - 'a') % mod;
        ha1[i] = (ha1[i-1]*seed + str0[i-1] - 'a') % mod1;
    }
    for (int i = 0; i < k; ++i) {//尝试所有可能的起始位置
        for (int j = 1; j <= n; ++j) vis[j] = 0; st.clear();
        for (int j = 1; j <= n; ++j) {
            //计算第j个长度为k的子串的哈希值
            pll p = {
                (ha0[j*k+i] - (ha0[(j-1)*k+i]*a0[k]%mod)+mod)%mod,
                (ha1[j*k+i] - (ha1[(j-1)*k+i]*a1[k]%mod1)+mod1)%mod1
            };
            vis[j] = dp[p];//获取对应字符串编号
            if (st.contains(vis[j])) break;//发现重复，跳出
            st.insert(vis[j]);
        }
        int mn = *min_element(vis+1, vis+1+n);
        if (st.size() == n && mn) {//找到n个不同且有效的字符串
            cout << "YES\n";
            for (int j = 1; j <= n; ++j) cout << vis[j] << ' ';
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}