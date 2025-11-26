//
// Created by Psy.C on 2025/11/26.
//
/*
*n：元素个数
m：目标值（第m小的差值）
x：第一个结果值
y：第二个结果值，初始化为0
*cnt：映射容器，用于统计每个数值的出现次数
it：映射容器的迭代器
 *
*寻找第一个数值x
遍历map中的每个元素：
it->first：当前数值
it->second：该数值的出现次数
n * 1ll * it->second：以当前数值为第一个数的所有差值对的数量
如果m小于等于当前可提供的差值对数量，则找到x
否则从m中减去当前数值贡献的差值对数量
 *
*寻找第二个数值y
遍历map中的每个元素：
it->first：当前数值（作为y）
cnt[x] * 1ll * it->second：固定x的情况下，与当前数值形成的差值对数量
如果m小于等于当前可提供的差值对数量，则找到y
否则从m中减去当前组合贡献的差值对数量
 *
 *时间复杂度：O(n log n)，主要消耗在map操作上
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;

int main() {
    fast;
    ll n, m, x, y = 0; cin >> n >> m;
    map<ll, ll> cnt; map<ll, ll>::iterator it;
    for (int i = 0; i < n; ++i) { cin >> x; cnt[x]++; }
    for (it = cnt.begin(); it != cnt.end(); ++it) {
        x = it->first;
        if (m <= n * 1ll * it->second) break;
        m -= n * 1ll * it->second;
    }
    for (it = cnt.begin(); it != cnt.end(); ++it) {
        y = it->first;
        if (m <= cnt[x] * 1ll * it->second) break;
        m -= cnt[x] * 1ll * it->second;
    }
    cout << x << " " << y << '\n';
    return 0;
}