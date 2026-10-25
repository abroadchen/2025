//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
N：数组上限。
n：数字个数；k：可合并的最大相邻差值。
a[N]：存原始输入。
cnt：答案（最终段数）。
m：map<ll,ll>，键 = 数值，值 = 该数值出现的次数（去重计数
读入 n 个数到 a[i]，同时 m[a[i]]++ 统计每个数值出现的次数。
cnt = n：初始假设每个数都是一个独立段（最多 n 段）。
map 会自动按键（数值）从小到大排序，所以 m 中的键是排好序的
it 从 map 开头遍历，it->first 是数值，it->second 是次数。
ll a = it->first, c = it->second;：取出当前键 a 和它出现的次数 c。
++it;：it 前进到下一个键。
if (it == m.end()) break;：若已经是最后一个键，跳出（后面没有可连的点）。
ll b = it->first; --it;：取出下个键 b，然后 --it 把迭代器退回到 a 的位置（保证循环末尾 ++it 后正常前进）。
if (b - a <= k) cnt -= c;：若相邻键的差值 ≤ k，则把 a 的所有出现次数 c 从 cnt 中减掉。
关键点解释：

因为 map 键有序，a 和 b 是排序后的相邻两个不同数值。
若相邻差值 b-a <= k，说明从 a 能"接上"b，即 a 的值可以和它后面的连成一段，a 就不是一个独立的段起点，所以把 a 的次数 c 从 cnt 中减掉（这些原本被算作独立段的 c 个点，实际可以并入下一段）。
若差值 > k，则 a 无法与后面连接，a 保留为独立段，不减
输出最终保留的独立段数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+10;

ll n, k, a[N], cnt;
map<ll,ll> m;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 0; i < n; i++) { cin >> a[i]; m[a[i]]++; }
    cnt = n;
    for (auto it = m.begin(); it != m.end(); ++it) {
        ll a = it->first, c = it->second; ++it;
        if (it == m.end()) break;
        ll b = it->first; --it;
        if (b - a <= k) cnt -= c;
    }
    cout << cnt << '\n';
    return 0;
}