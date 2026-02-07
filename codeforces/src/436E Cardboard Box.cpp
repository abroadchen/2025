//
// Created by Psy.C on 2026/2/7.
//
/**
o: 存储单次操作的最小堆（优先处理代价最小的）
t: 存储两次操作的最小堆
vis: 标记数组，记录哪些元素已被处理
clear函数：清空队列顶部已被访问的元素

n: 物品数量，m: 操作次数
a[i]: 第i个物品的第一次操作代价
a[i+n]: 第i个物品的第二次操作相对于第一次的增量
因此，第二次操作的总代价为 a[i] + a[i+n]

o队列：存储 {第一次操作代价, 物品编号}
t队列：存储 {两次操作总代价, 物品编号}

每轮决策过程：
清理队列：移除已访问的元素
获取候选：从单次操作队列取最小值
决策判断：比较当前单次操作+下次单次操作 vs 当前双次操作
如果 a[i] + next_single_cost >= double_cost，则选择双次操作
状态更新：更新代价、计数和访问标记

当还有剩余操作次数且双次操作队列非空时
比较：当前单次操作 + 预期下次单次操作 vs 当前双次操作
如果双次操作更优或相当，则选择双次操作


 */
#include <iostream>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 300005
#define li pair<ll, int>
using namespace std;

priority_queue<li, vector<li>, greater<>> o, t;

int vis[N<<1];
void clear(priority_queue<li, vector<li>, greater<>>& q) {
    while (!q.empty() && vis[q.top().second]) q.pop();
}

int main() {
    fast;
    int n, m; cin >> n >> m;
    int a[N<<1]{}, st[N]{};
    for (int i = 1; i <= n; ++i) cin >> a[i] >> a[i+n], a[i+n] -= a[i];
    for (int i = 1; i <= n; ++i) o.emplace(a[i], i), t.emplace(a[i]+a[i+n], i);
    ll ans = 0;
    while (m--) {
        clear(o), clear(t);
        int i = o.top().second; o.pop(); clear(o);
        if (m && !t.empty() && a[i] + o.top().first >= t.top().first)
            o.emplace(a[i], i), i = t.top().second, t.pop();
        if (i <= n) o.emplace(a[i+n], i+n);//如果进行了单次操作，添加二次操作选项
        ans += a[i];
        st[i>n?i-n:i]++;
        vis[i] = true;
    }
    cout << ans << '\n';//总代价
    for (int i = 1; i <= n; ++i) cout << st[i];//每个物品的操作次数
    return 0;
}