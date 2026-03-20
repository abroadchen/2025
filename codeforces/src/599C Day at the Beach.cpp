//
// Created by Psy.C on 2026/3/20.
//
///时间复杂度：O(n log n)（主要是排序） 空间复杂度：O(n)
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

struct node {
    int val, id;
    friend bool operator<(node a, node b) {
        if (a.val == b.val) return a.id < b.id;
        return a.val < b.val;
    }
} b[N];

int n, a[N], vis[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i], b[i].id = i, b[i].val = a[i];//保留值和原始索引
    sort(b + 1, b + n + 1);
    int mx = 0;//当前处理过的最大索引
    for (int i = 1; i <= n; ++i) {
        if (b[i].id > mx) vis[b[i].id] = -1;//标记为特殊值（表示可以独立成段）
        else vis[b[i].id] = mx;//记录当前的最大索引
        mx = max(mx, b[i].id);//更新最大索引
    }
    int ans = 0;//分割段数计数器
    for (int i = 1; i <= n; ) {
        if (vis[i] == -1) i++;//单独成段，跳过
        else {
            int x = vis[i];//当前段的右边界
            for (int j = i; j <= x; ++j)//在当前段内继续扩展右边界
                x = max(vis[j], x);
            i = x + 1;//移动到下一段的开始
        }
        ans++;
    }
    cout << ans << '\n';
    return 0;
}