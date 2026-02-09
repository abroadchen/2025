//
// Created by Psy.C on 2026/2/9.
//
/**
因数分解：O(√x)
建图：O(d²)，d是因数个数
DFS：O(答案个数)
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000005
using namespace std;

int cnt = 0;
vector<ll> t;//x的所有因数
vector<int> son[N];//可以整除t[i]的t[j]的索引j
/**
 *
 * @param k 剩余步数
 * @param n 当前因数的索引
 */
void dfs(const ll k, const ll n) {
    if (cnt == 1e5) return;
    if (n == 0) {
        cout << 1 << ' ';//对应因数1
        cnt++;
        return;
    }
    if (k == 0) {
        cout << t[n] << ' ';//当前因数t[n]
        cnt++;
        return;
    }
    for (const int i : son[n]) {//遍历所有可以整除t[n]的因数索引i
        dfs(k - 1, i);
        if (cnt == 1e5) return;
    }
}

int main() {
    fast;
    ll x, k; cin >> x >> k;
    for (ll i = 1; i*i <= x; ++i) if (x % i == 0) {//i是x的因数
        if (i*i == x) t.push_back(i);//完全平方数，只添加一个因数
        else t.push_back(i), t.push_back(x / i);
    }
    ranges::sort(t);
    for (int i = 0; i < t.size(); ++i)//遍历所有因数
        for (int j = 0; j <= i; ++j)//遍历≤t[i]的因数
            if (t[i] % t[j] == 0) son[i].push_back(j);
    dfs(k, t.size()-1);
    return 0;
}