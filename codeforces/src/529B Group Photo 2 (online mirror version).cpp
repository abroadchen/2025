//
// Created by Psy.C on 2026/3/3.
//
/**
ans: 最优解，初始化为无穷大
h[N]: 标记数组，标记某些数值是否出现过
n: 输入的元素总数
k: 目标值，等于n/2

以x作为参数计算代价
priority_queue<int> q: 最大堆，存储差值
如果x未在h数组中标记过：
找到第一个满足e[i].w == x的元素
将其h值乘以x加到结果中
增加计数sum
遍历所有元素：
如果h > x，选择h并加到结果和计数中
否则选择w，并将差值(w-h)加入优先队列
从优先队列中取出前几个元素，减少总成本
更新全局最优解ans

检查对于给定的x，是否所有元素的w或h至少有一个小于等于x
s[N]: 前缀和数组，统计h值的出现次数
v[N]: 标记数组，标记x值是否出现过

更新s数组（统计h值出现次数）
在h数组中标记h值出现过
在v数组中标记w和h值出现过

枚举所有出现过的值i
如果i未出现过，跳过
如果大于i的h值数量超过k，跳过
如果i不可行，跳过
否则调用get函数计算以i为参数的解

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1001, inf = 2147483647;
struct node { int w, h; } e[N];

int ans = inf, h[N], n, k;
void get(const int x) {
    priority_queue<int> q;
    int sum = 0, res = 0, c = 0, mn = inf;
    if (!h[x]) {
        for (int i = 1; i <= n; ++i)
            if (e[i].w == x && e[i].h < inf) {
                c = i;
                mn = e[i].h;
            }
        res += mn*x;
        sum++;
    }
    for (int i = 1; i <= n; ++i) {
        if (i == c) continue;
        if (e[i].h > x) {
            sum++;
            res += e[i].h*x;
            continue;
        }
        res += e[i].w*x;
        if (e[i].w > e[i].h && e[i].w <= x)
            q.push(e[i].w - e[i].h);
    }
    while (!q.empty() && sum < k) {
        sum++;
        const int d = q.top(); q.pop();
        res -= x*d;
    }
    ans = min(ans, res);
}

bool ok(const int x) {
    for (int i = 1; i <= n; ++i)
        if (e[i].h > x && e[i].w > x)
            return false;
    return true;
}

int s[N], v[N];
int main() {
    fast;
    cin >> n; k = n/2;
    for (int i = 1; i <= n; ++i) {
        cin >> e[i].w >> e[i].h;
        s[e[i].h]++; h[e[i].h] = 1;
        v[e[i].w] = 1; v[e[i].h] = 1;
    }
    for (int i = 1; i <= N-1; ++i) s[i] += s[i-1];
    for (int i = 1; i <= N-1; ++i) {
        if (!v[i]) continue;
        if (s[N-1] - s[i] > k) continue;
        if (!ok(i)) continue;
        get(i);
    }
    cout << ans << '\n';
    return 0;
}