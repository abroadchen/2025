//
// Created by Psy.C on 2025/12/2.
//
/*
*n: 数组大小/节点数
l, r: 左右边界参数
s: 起始位置
*a[N]: 输入数组
d[N]: 差分数组
pre[N]: 前缀和数组
suf[N]: 后缀和数组
res: 结果变量
tag: 标记/调整变量
g[N]: 标记数组
 *优先队列（大根堆）使用负值是因为priority_queue默认是大根堆，而我们需要小根堆的效果
 *存储最优解：{最小代价, 对应位置}
 *
*从位置s+1到n搜索：
计算基础代价：res = (pre[s-1] + suf[t]) * 2
维护优先队列，存储负的差分值
根据条件调整tag值 从优先队列中取出最大值(实际上是负数中的最小值)，从tag中减去它的两倍，并弹出该元素
更新最优解
 *重置变量和清空优先队列
*从位置s-1到1搜索：
类似的计算和优化过程
更新最优解
 *输出最小代价
 *获取最优位置t
 *t > s（向右移动）
 *
 *
*预处理：O(n)
搜索：O(n log n)
方案构造：O(n)
总体：O(n log n)
 */
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int N = 3e5+10;
int n, l, s, r;
int a[N], d[N], pre[N], suf[N], res, tag, g[N];
priority_queue<int> q;
pair<int,int> ans = {1e18,-1};
stack<int> stk;

signed main() {
    fast;
    cin >> n >> l >> s; r = n - 1 - l;
    rep(i,n) cin >> a[i];
    if (s != n && l > n - 2) { cout << "-1\n"; return 0; }
    if (s != 1 && r > n - 2) { cout << "-1\n"; return 0; }
    rep(i,n-1) d[i] = a[i+1] - a[i];
    rep(i,n-1) pre[i] = pre[i-1] + d[i];
    for (int i = n - 1; i; --i) suf[i] = suf[i+1] + d[i];
    for (int t = s + 1; t <= n; ++t) {
        res = (pre[s-1] + suf[t]) << 1;
        if (t != s + 1) q.push(-d[t-1]);
        tag += d[t-1];
        if (l - s + 1 - n + t > 0) tag -= 2 * q.top(), q.pop();
        ans = min(ans, {res+tag, t});
    }
    tag = res = 0; while (!q.empty()) q.pop();
    for (int t = s - 1; t; --t) {
        res = (pre[t-1] + suf[s]) << 1;
        if (t != s - 1) q.push(-d[t]);
        tag += d[t];
        if (r - t + 1 - n + s > 0) tag -= 2 * q.top(), q.pop();
        ans = min(ans, {res+tag, t});
    }
    cout << ans.first << '\n';
    const int t = ans.second; int use; vector<pair<int,int>> p;
    if (t > s) {//如果最优位置在起始位置右侧
        use = l - s + 1 - n + t; int cur = s;
        while (l > 1 && cur > 1) cout << --cur << ' ', --l;
        --l;
        rep(i,cur-1) cout << i << ' ';//输出从1到cur-1的位置
        for (int i = s + 1; i < t; ++i) p.emplace_back(d[i], i);
        sort(p.begin(), p.end());
        for (int i = 0; i < use; ++i) g[p[i].second] = 1;//标记前use个元素（差分值最小的）
        for (int i = s + 1; i < t; ++i) {
            stk.push(i);//如果位置i未被标记，输出栈中所有元素
            if (!g[i]) while (!stk.empty()) cout << stk.top() << ' ', stk.pop();
            l -= g[i];
        }
        const int x = t + 1 + l;
        for (int i = x; i <= n; ++i) cout << i << ' ';
        for (int i = x - 1; i >= t; --i) cout << i << ' ';
        cout << '\n';
    } else {
        use = r - t + 1 - n + s; int cur = s;
        while (r > 1 && cur < n) cout << ++cur << ' ', --r;
        --r;
        for (int i = n; i > cur; --i) cout << i << ' ';
        for (int i = t; i < s - 1; ++i) p.emplace_back(d[i], i);
        sort(p.begin(), p.end());
        for (int i = 0; i < use; ++i) g[p[i].second] = 1;
        for (int i = s - 1; i > t; --i) {
            stk.push(i);
            if (!g[i-1]) while (!stk.empty()) cout << stk.top() << ' ', stk.pop();
            r -= g[i-1];
        }
        const int x = t - 1 - r;
        for (int i = x; i >= 1; --i) cout << i << ' ';
        for (int i = x + 1; i <= t; ++i) cout << i << ' ';
        cout << '\n';
    }
    return 0;
}