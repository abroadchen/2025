//
// Created by Psy.C on 2026/2/27.
//
/**
n：元素数量
l[N]：值数组（可能是长度或用于计算GCD的数字）
c[N]：与每个元素相关的成本数组
mp：映射，以GCD值为键，以最小成本为值

起始状态，GCD为0，成本为0
对于从1到n的每个元素i：
遍历映射中的所有现有GCD状态
对于具有GCD值it->first的每个现有状态，计算新GCD：gcd(it->first, l[i])
更新此新GCD值的成本：
如果GCD已存在于映射中：取当前成本和it->second + c[i]的最小值
如果GCD不存在：将成本设置为it->second + c[i]
如果映射中存在GCD值1，输出其最小成本
否则输出-1（无法达到GCD为1）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 301;
inline int gcd(const int a, const int b) {
    return !b ? a : gcd(b, a % b);
}

int n, l[N], c[N];
map<int, int> mp;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> l[i];
    for (int i = 1; i <= n; ++i) cin >> c[i];
    mp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            int x = gcd(it->first, l[i]);
            mp.contains(x) ? mp[x] = min(mp[x], it->second+c[i]) :
                mp[x] = it->second+c[i];
        }
    }
    cout << (mp[1] ? mp[1] : -1) << '\n';
    return 0;
}