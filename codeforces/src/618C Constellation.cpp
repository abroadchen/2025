//
// Created by Psy.C on 2026/3/25.
//
/**
O(n log n) 用于排序
O(n) 用于寻找不共线点
总体：O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;

struct node {
    ll id, x, y;
    bool operator<(const node &o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
} a[N];

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x >> a[i].y; a[i].id = i;
    }
    sort(a + 1, a + n + 1);
    int cnt = 3;
    //检查前三个点是否共线，如果是则继续寻找第一个不共线的点
    while ((a[1].x-a[2].x)*(a[1].y-a[cnt].y)==
        (a[1].y-a[2].y)*(a[1].x-a[cnt].x)) cnt++;
    //三个不共线的点的原始编号
    cout << a[1].id << ' ' << a[2].id << ' ' << a[cnt].id << '\n';
    return 0;
}