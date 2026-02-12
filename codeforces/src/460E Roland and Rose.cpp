//
// Created by Psy.C on 2026/2/12.
//

#include <algorithm>
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 10000
using namespace std;

struct node {
    int x, y;
    node() = default;
    node(const int x, const int y) : x(x), y(y) {}
} p[N], o;//原点(0,0)

//平方距离以避免浮点运算
inline int dist(const node a, const node b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int n, r, tot=0, m;
void init() {
    cin>>n>>r;//要选择的点数 半径
    for (int i = -r; i <= r; ++i)
        for (int j = -r; j <= r; ++j)
            if (dist({i,j}, o) <= r*r)//临时节点对象 点(i,j)是否在圆内
                p[++tot] = {i, j};
    sort(p + 1, p + tot + 1, [](const node a, const node b) {
        return dist(a, o) > dist(b, o);//距离原点远的点排在前面
    });
    m = min(18, max(n, tot));//最多18个，但至少n个或tot个
}

int mx, stk[N], ans[N], top=0;

/**
 *
 * @param x 下一个选择的起始索引
 * @param used 已选择的点数
 * @param sum 当前点对距离之和
 */
void dfs(const int x, const int used, const int sum) {
    if (used == n) {
        if (mx < sum) {
            mx = sum;
            memcpy(ans, stk, sizeof(stk));
        }
        return;
    }
    for (int i = x; i <= m; ++i) {
        stk[++top] = i;
        int t = 0;
        for (int j = 1; j < top; ++j)//新点到所有先前选择点的距离之和
            t += dist(p[stk[j]], p[i]);
        dfs(i, used+1, sum+t);//用更新的参数继续
        top--;//移除点来回溯
    }
}

int main() {
    fast;
    init(); dfs(1, 0, 0);
    cout << mx << '\n';
    for (int i = 1; i <= n; ++i)
        cout << p[ans[i]].x << ' ' << p[ans[i]].y << '\n';
    return 0;
}