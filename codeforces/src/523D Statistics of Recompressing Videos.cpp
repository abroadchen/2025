//
// Created by Psy.C on 2026/3/2.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int n, k;///数据对数量 阈值
priority_queue<int, vector<int>, greater<>> q;///最小堆（优先队列）
signed main() {
    fast;
    cin >> n >> k;
    for (int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y;
        if (!q.empty() && q.size() >= k) {
            x = max(x, q.top()) + y;
            q.pop();
        } else x += y;
        q.push(x);//将处理后的x值加入优先队列
        cout << x << '\n';
    }
    return 0;
}