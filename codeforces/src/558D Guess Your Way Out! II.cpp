//
// Created by Psy.C on 2026/3/11.
//
/**
N = 50: 最大深度
l[N+5], r[N+5]: 预计算的区间边界
l[i] = 2^(i-1), r[i] = 2^i - 1
n: 目标深度
q: 查询数量
mp: 差分数组，用于区间标记

将查询区间扩展到深度n
x <<= 1: x *= 2
y = y<<1|1: y = y * 2 + 1
ok为真：目标在[x,y]区间内（区间加1）
ok为假：目标不在[x,y]区间内（补集区间加1）
遍历所有关键点
sum：当前有效查询数量
当sum == q时，表示该区间被所有查询覆盖
计算满足条件的区间长度和位置
cnt == 0: 无解，数据矛盾
cnt > 1: 多解，信息不足
cnt == 1: 唯一解

预计算: O(N)
查询处理: O(q log q)（map操作）
差分处理: O(关键点数量)
总体: O(q log q)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 50;
ll l[N+5], r[N+5];
int n, q;
map<ll, int> mp;
int main() {
    fast;
    l[1] = r[1] = 1;
    for (int i = 2; i <= N; ++i)
        l[i] = l[i-1]<<1, r[i] = r[i-1]<<1|1;
    cin >> n >> q;
    if (q == 0) {
        if (n == 1) cout << "1\n";
        else cout << "Data not sufficient!\n";
        return 0;
    }
    for (int i = 0, dep, ok; i < q; ++i) {
        ll x, y; cin >> dep >> x >> y >> ok;
        while (dep < n) {
            x <<= 1; y = y<<1|1; dep++;
        }
        if (ok) mp[x]++, mp[y+1]--;
        else {
            mp[l[n]]++; mp[x]--;
            mp[y+1]++; mp[r[n]+1]--;
        }
    }
    int sum = 0;
    ll pre = -1, cnt = 0, ans = 0;
    for (auto [fst, snd] : mp) {
        sum += snd;
        if (pre != -1) {
            cnt += fst - pre;
            ans = pre;
        }
        if (sum == q) pre = fst;
        else pre = -1;
    }
    if (cnt == 0) cout << "Game cheated!\n";
    else if (cnt > 1) cout << "Data not sufficient!\n";
    else cout << ans << '\n';
    return 0;
}