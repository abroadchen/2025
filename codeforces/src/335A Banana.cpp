//
// Created by Psy.C on 2026/1/10.
//
/**
 * 将每个元素的 n 设为0，t 设为1
* p[ch-'a'].n++：统计字符出现次数
p[ch-'a'].c = ch：记录字符本身
 *
 *如果 p[i].n 不为0（即字符存在）
 *将节点加入优先队列
 *将字符加入结果向量
 *
*如果目标长度 x 小于已有字符数
输出 -1 并结束程序
*从已有长度+1到目标长度 x 循环
如果优先队列不为空：
node u = q.top(); q.pop()：取出优先级最高的节点
ans.push_back(u.c)：将字符加入结果
u.t++：增加该字符的出现次数（注意：这里应该是增加数量）
q.push(u)：将更新后的节点放回队列
 *
*获取优先队列顶部节点（负载最大的）
输出其负载值（向上取整）
 *输出结果字符串
 */
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100
#define rep(i,n) for (int i = 0; i < n; ++i)
using namespace std;

struct node {
    int n, t; char c;
    bool operator<(const node &o) const {
        const int l1 = ceil(static_cast<double>(n)/t),
        l2 = ceil(static_cast<double>(o.n)/o.t);
        if (l1 == l2) return n < o.n;//如果负载相等，按数量排序
        return  l1 < l2;//否则按负载排序
    }
} p[N|1];


signed main() {
    fast;
    for (auto& e : p) e.n = 0, e.t = 1;
    string s; int x; cin >> s >> x;
    for (const auto& ch : s) p[ch-'a'].n++, p[ch-'a'].c = ch;
    priority_queue<node> q; vector<char> ans;
    rep(i,31) if (p[i].n) { q.push(p[i]); ans.push_back(static_cast<char>(i+'a')); }
    if (x < static_cast<int>(ans.size())) { cout << -1 << '\n'; return 0; }
    for (int i = static_cast<int>(ans.size()) + 1; i <= x; ++i) if (!q.empty()) {
        node u = q.top(); q.pop();
        ans.push_back(u.c); u.t++; q.push(u);
    }
    const node b = q.top();
    cout << ceil(static_cast<double>(b.n)/b.t) << '\n';
    for (const char an : ans) cout << an;
    return 0;
}