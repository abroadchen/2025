//
// Created by Psy.C on 2026/1/23.
//
/**
* m: 任务数量
n: 工人数量
val[N]: 存储每个任务分配给哪个工人的数组
set<ii> s: 按成本排序维护可用工人
st[N]: 存储工人及其能力和成本信息
b[N]: 存储任务及其要求
 *
 *最多可以为每个工人分配x个任务时的最小成本
*x: 每个工人最大任务数
对于每组x个任务，找到合适的工人
添加能力满足要求的工人到集合中
选择可用的最便宜工人（s.begin()）
将此工人分配给当前批次的所有x个任务
更新总成本和分配数组
 *
 *工人数量(n)、任务数量(m)、预算限制(ss)
*读取任务要求并存储原始索引
读取工人能力和成本
 *将两个数组按降序排序（优先级高的在前）
 *
 *找到成本不超过预算ss的最小x
*如果不存在有效解，输出"NO"
否则，再次运行函数以填充分配
输出每个任务的工人分配
 */
#include <algorithm>
#include <iostream>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
#define N 100050
#define inf 1e18
using namespace std;

int m, n, val[N];
set<ii> s;
pair<int, ii> st[N];
ii b[N];
ll get(const int x) {
    ll sum = 0; s.clear();
    for (int i = 0, c = 0; i < m; i += x) {
        while (c < n && st[c].first >= b[i].first) {
            s.insert(st[c].second);
            c++;
        }
        if (s.empty()) return 1ll * inf;
        auto [fst, snd] = *(s.begin());
        sum += fst;
        s.erase(s.begin());
        for (int j = i; j < m && j < i + x; ++j)
            val[b[j].second] = snd + 1;
    }
    return sum;
}


int main() {
    fast;
    int ss, i; cin >> n >> m >> ss;
    for (i = 0; i < m; ++i) {
        cin >> b[i].first; b[i].second = i;
    }
    for (i = 0; i < n; ++i) cin >> st[i].first;
    for (i = 0; i < n; ++i) {
        cin >> st[i].second.first;
        st[i].second.second = i;
    }
    sort(b, b + m); reverse(b, b + m);
    sort(st, st + n); reverse(st, st + n);
    int l = 1, r = m + 1;
    while (l < r) {
        if (const int mid = (l + r) >> 1; get(mid) <= ss) r = mid;
        else l = mid + 1;
    }
    if (l >= m + 1) { cout << "NO\n"; return 0; }
    cout << "YES\n";
    get(l);
    for (i = 0; i < m - 1; ++i) cout << val[i] << ' ';
    cout << val[m-1] << '\n';
    return 0;
}