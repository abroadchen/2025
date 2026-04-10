//
// Created by Psy.C on 2026/4/10.
//
/**
n: 参赛者数量
m: 组数
i: 循环计数器
r: 组号（1索引）
p: 分数/积分
nam: 参赛者姓名

a = 最高分参赛者（冠军）
b = 第二高分参赛者
c = 第三高分参赛者
如果第二名和第三名分数相等AND还有更多参赛者剩余，则输出"?"（表示第二名位置存在歧义）
否则，输出第一名和第二名的姓名
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ls pair<ll, string>
using namespace std;

bool operator<(const ls& a, const ls& b) {
    return a.first > b.first;//具有较小first值的元素将有更高优先级
}

ll n, m, i, r, p;
string nam;
int main() {
    fast;
    cin >> n >> m;
    priority_queue<ls> q[m];
    for (i = 0; i < n; ++i) {
        cin >> nam >> r >> p;
        q[r-1].emplace(p, nam);
    }
    ls a, b, c;
    for (i = 0; i < m; ++i) {
        a = q[i].top(); q[i].pop();
        b = q[i].top(); q[i].pop();
        c = q[i].top();
        if (b.first == c.first && q[i].empty() == false)
            cout << "?\n";
        else
            cout << a.second << ' ' << b.second << '\n';
    }
    return 0;
}