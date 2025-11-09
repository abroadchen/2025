//
// Created by Psy.C on 2025/10/20.
//
/*
*x: 建筑物左端点坐标
h: 建筑物高度
ind: 建筑物原始索引
 *
*双端队列q存储<坐标, 能够压倒的建筑数>
从最右边的建筑开始处理（因为它不会被任何建筑影响）
初始化最后一栋建筑只能压倒自己（数量为1）
 *
*从右向左处理每栋建筑：

cur: 当前处理的建筑
k: 表示当前建筑的信息<坐标, 压倒数量>
*当队列不为空且当前建筑的倒塌范围(cur.x + cur.h - 1)能覆盖队首建筑时
累加被压倒建筑的数量
移除被压倒的建筑（因为它们已被当前建筑"吸收"）
 *将当前建筑信息加入队列前端，并记录答案
 *输出每栋建筑能压倒的建筑数量
 *
 */
#include <vector>
#include <ios>
#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

struct Point {
    int x, h, ind;
    Point() : x(-1), h(-1), ind(-1) {}
    Point(int x, int h, int ind) : x(x), h(h), ind(ind) {}
};

void solve() {
    int n; cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        int x, h; cin >> x >> h;
        a[i] = { x, h, i };
    }
    sort(a.begin(), a.end(), [](auto& a, auto& b) {
        if (a.x <= b.x) return 1;
        return 0;
    });
    deque<pair<int, int>> q = { { a[n - 1].x, 1 } };
    vector<int> ans(n); ans[a[n - 1].ind] = 1;
    for (int i = n - 2; i >= 0; --i) {
        Point cur = a[i];
        pair<int, int> k = { cur.x, 1 };
        while (q.size() >= 1 && cur.x + cur.h - 1 >= q.front().first) {
            k.second = k.second + q.front().second;
            q.pop_front();
        }
        q.push_front(k);
        ans[cur.ind] = k.second;
    }
    for (auto i : ans) cout << i << " ";
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    solve();
    return 0;
}